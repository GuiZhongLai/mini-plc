#include "dev_client.h"
#include "modbus_client.h"
#include "snap7_client.h"

#include <chrono>

class DevClientData
{
public:
    std::vector<DevRequest> rdRequest;
    std::vector<DevRequest> wrRequest;
    uint16_t timeout = 2000;
    uint16_t retry = 3;
    DevClient::State state = DevClient::UnconnectedState;
    DevClient::Error error = DevClient::NoError;
    std::string errorString;
    std::chrono::steady_clock::time_point connectTime;
};

DevClient *DevClient::create(eBusType busType, const std::string &devName, uint16_t rSize, uint16_t tSize)
{
    switch (busType)
    {
    case eBusType::MODBUS:
        return new ModbusClient(devName, rSize, tSize);
    case eBusType::SNAP7:
        return new Snap7Client(devName, rSize, tSize);
    default:
        return nullptr;
    }
}

DevClient::DevClient(eBusType busType, const std::string &devName, uint16_t rSize, uint16_t tSize)
    : m_busType(busType), m_name(devName), m_datas(new uint8_t[rSize + tSize]()), m_readBytes(rSize), m_writeBytes(tSize), m_timeout(2000), m_retry(3), d_ptr(new DevClientData)
{
}

DevClient::~DevClient()
{
    delete[] m_datas;
    delete d_ptr;
}

void *DevClient::readBuff(uint16_t byteOffset)
{
    if (m_readBytes <= 0 || byteOffset >= m_readBytes)
        return nullptr;

    return m_datas + byteOffset;
}

void *DevClient::writeBuff(uint16_t byteOffset)
{
    if (m_writeBytes <= 0 || byteOffset >= m_writeBytes)
        return nullptr;

    return m_datas + m_readBytes + byteOffset;
}

std::vector<DevRequest> DevClient::requestList()
{
    std::vector<DevRequest> vReq;
    for (auto it : d_ptr->rdRequest)
        vReq.push_back(it);

    for (auto it : d_ptr->wrRequest)
        vReq.push_back(it);

    return vReq;
}

void DevClient::clearRequest(void)
{
    d_ptr->rdRequest.clear();
    d_ptr->wrRequest.clear();
}

void DevClient::appendReadRequest(DevRequest &req)
{
    d_ptr->rdRequest.push_back(req);
}

void DevClient::appendWriteRequest(DevRequest &req)
{
    d_ptr->wrRequest.push_back(req);
}

void DevClient::abortAllRequest()
{
    for (auto &req : d_ptr->rdRequest)
        abortRequest(req);

    for (auto &req : d_ptr->wrRequest)
        abortRequest(req);
}

void DevClient::setNumberOfRetries(int number)
{
    if (number > 0)
        d_ptr->retry = number;
}

void DevClient::setTimeout(int newTimeout)
{
    if (newTimeout >= 50)
        d_ptr->timeout = newTimeout;
}

int DevClient::numberOfReties() const
{
    return d_ptr->retry;
}

int DevClient::timeout() const
{
    return d_ptr->timeout;
}

DevClient::Error DevClient::error() const
{
    return d_ptr->error;
}

std::string DevClient::errorString() const
{
    return d_ptr->errorString;
}

DevClient::State DevClient::state() const
{
    return d_ptr->state;
}

std::any DevClient::connectionParameter(int) const
{
    return std::any();
}

void DevClient::setConnectionParameter(int, const std::any &)
{
}

void DevClient::readRequest()
{
    if (state() != ConnectedState)
    {
        auto now = std::chrono::steady_clock::now();
        if (state() != ConnectingState && state() != ClosingState)
        {
            connectDevice();
            d_ptr->connectTime = now;
        }
        else if (std::chrono::duration_cast<std::chrono::milliseconds>(now - d_ptr->connectTime).count() > 30000)
        {
            disconnectDevice();
            d_ptr->connectTime = now;
        }
        // abort reply
        for (auto &req : d_ptr->rdRequest)
        {
            abortRequest(req);
        }

        for (auto &req : d_ptr->wrRequest)
        {
            abortRequest(req);
        }
        return;
    }

    for (auto &req : d_ptr->rdRequest)
    {
        readRequest(req);
    }
}

void DevClient::writeRequest()
{
    if (state() != ConnectedState)
    {
        return;
    }

    for (auto &req : d_ptr->wrRequest)
    {
        writeRequest(req);
    }
}

void DevClient::readResponse()
{
    for (auto &req : d_ptr->rdRequest)
    {
        readResponse(req);
    }
}

void DevClient::writeResponse()
{
    for (auto &req : d_ptr->wrRequest)
    {
        writeResponse(req);
    }
}

void DevClient::setError(const std::string &errorText, Error error)
{
    const auto d = d_ptr;

    d->error = error;
    d->errorString = errorText;
}

void DevClient::setState(State newState)
{
    const auto d = d_ptr;
    if (newState == d->state)
        return;

    d_ptr->state = newState;
}
