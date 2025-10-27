#ifndef SNAP7_SERVER_H
#define SNAP7_SERVER_H

#include "snap7.h"
#include "plc_memory.h"

#include <functional>
#include <thread>
#include <atomic>
#include <memory>
#include <string>

class Snap7Server
{
public:
    /**
     * @brief 构造函数
     * @param memory PlcMemory引用
     */
    explicit Snap7Server(PlcMemory &memory);

    Snap7Server(const Snap7Server &) = delete;
    Snap7Server &operator=(const Snap7Server &) = delete;

    /**
     * @brief 析构函数
     */
    ~Snap7Server();

    /**
     * @brief 启动服务器
     * @return 是否成功启动
     */
    bool start();

    /**
     * @brief 停止服务器
     */
    void stop();

    /**
     * @brief 检查服务器是否运行中
     */
    bool isRunning() const;

    /**
     * @brief 获取客户端连接数
     */
    int getClientCount() const;

    /**
     * @brief 获取S7 CPU状态
     */
    int getS7CpuStatus() const;

private:
    TS7Server *server_;
    PlcMemory &memory_manager_;
    bool running_;

    bool registerArea();
    void unregisterArea();
};

#endif