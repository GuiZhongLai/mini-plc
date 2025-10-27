#ifndef MODBUS_CLIENT_H
#define MODBUS_CLIENT_H

#include "dev_client.h"
#include "modbus.h"
#include "modbus-tcp.h"

#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <variant>

class ModbusClientBackend;
class ModbusClient : public DevClient
{
public:
    ModbusClient(const std::string &, uint16_t rSize = 0, uint16_t tSize = 0);
    ~ModbusClient();

public:
    virtual bool connectDevice() override;
    virtual void disconnectDevice() override;
    virtual void setNumberOfRetries(int number) override;
    virtual void setTimeout(int newTimeout) override;

    virtual DevClient::Error readRequest(DevRequest &) override;
    virtual DevClient::Error writeRequest(DevRequest &) override;
    virtual DevClient::Error readResponse(DevRequest &) override;
    virtual DevClient::Error writeResponse(DevRequest &) override;
    virtual DevClient::Error abortRequest(DevRequest &) override;
    virtual bool isFinishedRequest(DevRequest &) const override;

    virtual std::any connectionParameter(int parameter) const override;
    virtual void setConnectionParameter(int parameter, const std::any &value) override;

protected:
    ModbusClientBackend *d;
    friend class ModbusClientBackend;
};

class ModbusReply
{
public:
    ModbusReply(uint16_t size)
        : m_bytes(size), m_datas(new uint16_t[size])
    {
    }

    ~ModbusReply()
    {
        delete[] m_datas;
    }

    bool isAborted() const
    {
        return m_abort;
    }
    void abort()
    {
        // 前台调用，外部释放
        m_abort = true;
    }

    bool isFinished() const
    {
        return m_finished;
    }
    void setFinished()
    {
        // 后台调用，外部释放
        m_finished = true;
    }

    uint16_t dataSize() const
    {
        return m_bytes;
    }
    uint16_t *datas() const
    {
        return m_datas;
    }

    DevClient::Error error() const
    {
        return m_error;
    }
    void setError(DevClient::Error error)
    {
        m_error = error;
    }

protected:
    const uint16_t m_bytes;
    uint16_t *const m_datas;
    bool m_finished = false;
    bool m_abort = false;
    DevClient::Error m_error = DevClient::NoError;
};

class ModbusClientBackend
{
    friend class ModbusClient;

public:
    ModbusClientBackend(ModbusClient *parent);
    ~ModbusClientBackend();

    void setTimeout(int newTimeout);
    void connectDevice();
    void disconnectDevice();
    void readRequest(DevRequest *req);
    void writeRequest(DevRequest *req);

private:
    void doConnectDevice();
    void doDisConnectDevice();
    void doReadRequest(DevRequest *req);
    void doWriteRequest(DevRequest *req);
    void run(); // 线程主函数

    ModbusClient *pModbusClient;
    std::thread m_thread;
    bool bQuit = false;

    // libmodbus 上下文
    modbus_t *ctx = nullptr;

    // 配置参数
    int nPort = 502;
    std::string strIpAddr;

    // 线程同步
    std::mutex mtx_;
    std::condition_variable cv_;
    bool initialized_ = false;

    enum CommandType
    {
        Connect,
        Disconnect,
        SetTimeout,
        Read,
        Write
    };

    // 命令能携带的数据类型
    using CommandData = std::variant<
        std::monostate, // 空状态（用于 Connect/Disconnect）
        int,            // 用于 SetTimeout
        DevRequest *    // 用于 Read/Write
        >;
    struct Command
    {
        CommandType type;
        CommandData data;

        // 构造函数
        Command(CommandType t) : type(t) {}

        Command(CommandType t, int timeout)
            : type(t), data(timeout) {}

        Command(CommandType t, DevRequest *req)
            : type(t), data(req) {}
    };

    std::queue<Command> command_queue_;

    // 初始化完成通知
    void notifyInitialized()
    {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            initialized_ = true;
        }
        cv_.notify_all();
    }

    bool waitUntilInitialized();
};

#endif