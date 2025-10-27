#ifndef DEV_CLIENT_H
#define DEV_CLIENT_H

#include <cstdint>
#include <string>
#include <vector>
#include <any>

class DevRequest
{
public:
    uint32_t index = 0;    // 索引号
    void *datas = nullptr; // 设备访问的内存地址(起始地址)
    uint32_t offset;       // 设备访问的内存偏移地址
    uint32_t size = 0;     // 设备访问的内存大小, 单位为byte
    uint32_t group;        // 设备访问的组类别
    uint32_t dbNum = 0;    // 设备访问的db编号(西门子PLC专属)
    bool bReadOnly = true; // 设备访问的读/写标识
    void *reply = nullptr; // 响应
};

class DevClientData;
class DevClient
{
    friend class DevManager;

public:
    enum eBusType
    {
        MODBUS,
        SNAP7,
        INVALID,
    };

    enum Error
    {
        NoError,            // No errors have occurred.
        ReadError,          // An error occurred during a read operation.
        WriteError,         // An error occurred during a write operation.
        ConnectionError,    // An error occurred when attempting to open the backend.
        ConfigurationError, // An error occurred when attempting to set a configuration parameter.
        TimeoutError,       // A timeout occurred during I/O. An I/O operation did not finish within a given time frame.
        ProtocolError,      // A Modbus specific protocol error occurred.
        ReplyAbortedError,  // The reply was aborted due to a disconnection of the device.
        UnknownError        // An unknown error occurred.
    };

    enum State
    {
        UnconnectedState, // The device is disconnected.
        ConnectingState,  // The device is being connected.
        ConnectedState,   // The device is connected to the Modbus network.
        ClosingState,     // The device is being closed.
    };

    enum ConnectionParameter
    {
        SerialPortNameParameter,
        SerialParityParameter,
        SerialBaudRateParameter,
        SerialDataBitsParameter,
        SerialStopBitsParameter,
        NetworkPortParameter,
        NetworkAddressParameter,
        RackParameter,
        SlotParameter,

        UserParameter = 0x100 // Reserved
    };

public:
    static DevClient *create(eBusType busType, const std::string &devName, uint16_t rSize = 0,
                             uint16_t tSize = 0);

public:
    explicit DevClient(eBusType busType, const std::string &devName, uint16_t rSize = 0,
                       uint16_t tSize = 0);
    virtual ~DevClient();

    DevClient(const DevClient &) = delete;
    DevClientData &operator=(const DevClient &) = delete;

protected:
    const eBusType m_busType;
    std::string m_name;
    std::string m_descr;
    uint8_t *const m_datas;
    const uint16_t m_readBytes;
    const uint16_t m_writeBytes;
    uint16_t m_timeout;
    uint16_t m_retry;

public:
    const std::string &name() const
    {
        return m_name;
    }
    eBusType busType() const
    {
        return m_busType;
    }
    void *readBuff(uint16_t byteOffset = 0);
    void *writeBuff(uint16_t byteOffset = 0);
    int readSize() const
    {
        return m_readBytes;
    }
    int writeSize() const
    {
        return m_writeBytes;
    }
    std::vector<DevRequest> requestList();
    void setDescr(std::string descr)
    {
        m_descr = descr;
    }
    const std::string &descr() const
    {
        return m_descr;
    }

public:
    virtual bool connectDevice() = 0;
    virtual void disconnectDevice() {}

    void clearRequest(void);
    void appendReadRequest(DevRequest &);
    void appendWriteRequest(DevRequest &);

    virtual Error readRequest(DevRequest &)
    {
        return NoError;
    }
    virtual Error writeRequest(DevRequest &)
    {
        return NoError;
    }
    virtual Error readResponse(DevRequest &)
    {
        return NoError;
    }
    virtual Error writeResponse(DevRequest &)
    {
        return NoError;
    }
    virtual Error abortRequest(DevRequest &)
    {
        return NoError;
    }
    void abortAllRequest();
    virtual bool isFinishedRequest(DevRequest &) const
    {
        return true;
    }
    virtual void setNumberOfRetries(int number);
    virtual void setTimeout(int newTimeout);
    virtual int numberOfReties() const;
    virtual int timeout() const;

    DevClient::Error error() const;
    std::string errorString() const;
    DevClient::State state() const;

    virtual std::any connectionParameter(int parameter) const;
    virtual void setConnectionParameter(int parameter, const std::any &value);

protected:
    void readRequest();
    void writeRequest();
    void readResponse();
    void writeResponse();

    void setError(const std::string &errorText, Error error);
    void setState(State newState);

protected:
    DevClientData *d_ptr;
};

#endif