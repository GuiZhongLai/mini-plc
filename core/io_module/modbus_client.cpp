#include "modbus_client.h"

#include <iostream>
#include <cstring>

ModbusClient::ModbusClient(const std::string &devName, uint16_t rSize, uint16_t tSize)
    : DevClient(MODBUS, devName, rSize, tSize), d(new ModbusClientBackend(this))
{
}

ModbusClient::~ModbusClient()
{
    disconnectDevice();
    delete d;
}

bool ModbusClient::connectDevice()
{
    if (state() != UnconnectedState)
        return false;

    std::cout << "[DevManager] Modbus Device connect...\n";

    setState(ConnectingState);
    d->connectDevice();

    return true;
}

void ModbusClient::disconnectDevice()
{
    std::cout << "[DevManager] Modbus Device disconnect...\n";

    setState(ClosingState);
    d->disconnectDevice();
}

void ModbusClient::setNumberOfRetries(int number)
{
    if (number > 5)
        number = 5;
    DevClient::setNumberOfRetries(number);
}

void ModbusClient::setTimeout(int newTimeout)
{
    if (newTimeout >= 50)
    {
        m_timeout = newTimeout;
        d->setTimeout(newTimeout);
    }
}

DevClient::Error ModbusClient::readRequest(DevRequest &req)
{
    if (req.reply != nullptr)
        return NoError;

    req.reply = new ModbusReply(req.size / 2);
    d->readRequest(&req);
    return NoError;
}

DevClient::Error ModbusClient::writeRequest(DevRequest &req)
{
    if (req.reply != nullptr)
        return NoError;

    req.reply = new ModbusReply(0);
    d->writeRequest(&req);
    return NoError;
}

DevClient::Error ModbusClient::readResponse(DevRequest &req)
{
    if (!req.reply)
        return NoError;

    auto reply = static_cast<ModbusReply *>(req.reply);
    if (reply->isFinished())
    {
        auto error = reply->error();
        if (error == NoError)
        {
            for (int i = 0; i < reply->dataSize(); ++i)
            {
                static_cast<uint16_t *>(req.datas)[i] = reply->datas()[i];
            }
        }
        abortRequest(req);
        return error;
    }
    return NoError;
}

DevClient::Error ModbusClient::writeResponse(DevRequest &req)
{
    if (!req.reply)
        return NoError;

    auto reply = static_cast<ModbusReply *>(req.reply);
    if (reply->isFinished())
    {
        auto error = reply->error();
        abortRequest(req);
        return error;
    }
    return NoError;
}

DevClient::Error ModbusClient::abortRequest(DevRequest &req)
{
    if (req.reply != nullptr)
    {
        static_cast<ModbusReply *>(req.reply)->abort();
        delete static_cast<ModbusReply *>(req.reply);
        req.reply = nullptr;
    }
    return NoError;
}

bool ModbusClient::isFinishedRequest(DevRequest &req) const
{
    if (!req.reply)
        return true;
    return static_cast<ModbusReply *>(req.reply)->isFinished();
}

std::any ModbusClient::connectionParameter(int parameter) const
{
    switch (parameter)
    {
    case NetworkPortParameter:
        return std::any(d->nPort);
    case NetworkAddressParameter:
        return std::any(d->strIpAddr);
    default:
        break;
    }
    return std::any();
}

void ModbusClient::setConnectionParameter(int parameter, const std::any &value)
{
    try
    {
        switch (parameter)
        {
        case NetworkPortParameter:
            d->nPort = std::any_cast<int>(value);
            break;
        case NetworkAddressParameter:
            d->strIpAddr = std::any_cast<std::string>(value);
            break;
        default:
            break;
        }
    }
    catch (...)
    {
        // 类型错误
    }
}

ModbusClientBackend::ModbusClientBackend(ModbusClient *parent)
    : pModbusClient(parent)
{
    m_thread = std::thread(&ModbusClientBackend::run, this);
    waitUntilInitialized();
}

ModbusClientBackend::~ModbusClientBackend()
{
    bQuit = true;
    cv_.notify_all();
    if (m_thread.joinable())
    {
        m_thread.join();
    }

    if (ctx)
    {
        modbus_close(ctx);
        modbus_free(ctx);
    }
}

void ModbusClientBackend::setTimeout(int newTimeout)
{
    std::lock_guard<std::mutex> lock(mtx_);
    command_queue_.push({SetTimeout, newTimeout});
    cv_.notify_one();
}

void ModbusClientBackend::connectDevice()
{
    std::lock_guard<std::mutex> lock(mtx_);
    command_queue_.push({Connect});
    cv_.notify_one();
}

void ModbusClientBackend::disconnectDevice()
{
    std::lock_guard<std::mutex> lock(mtx_);
    command_queue_.push({Disconnect});
    cv_.notify_one();
}

void ModbusClientBackend::readRequest(DevRequest *req)
{
    std::lock_guard<std::mutex> lock(mtx_);
    command_queue_.push({Read, req});
    cv_.notify_one();
}

void ModbusClientBackend::writeRequest(DevRequest *req)
{
    std::lock_guard<std::mutex> lock(mtx_);
    command_queue_.push({Write, req});
    cv_.notify_one();
}

void ModbusClientBackend::doConnectDevice()
{
    pModbusClient->setState(DevClient::ConnectingState);

    auto toAbort = [this]() -> bool
    {
        if (!bQuit && pModbusClient->state() != DevClient::ClosingState)
            return false;

        return true;
    };

    for (int retry = 5; retry > 0; --retry)
    {
        auto start_time = std::chrono::steady_clock::now();

        do
        {
            if (toAbort())
                break;

            if (!ctx)
                ctx = modbus_new_tcp(strIpAddr.c_str(), nPort);
            modbus_set_slave(ctx, 1);

            if (toAbort())
                break;

            if (modbus_connect(ctx) != 0)
                break;

            if (toAbort())
                break;

            int sec = pModbusClient->m_timeout / 1000;
            modbus_set_response_timeout(ctx, sec, 0);

            if (toAbort())
                break;

            std::cout << "[DevManager] Modbus Device connected\n";
            pModbusClient->setState(DevClient::ConnectedState);
            return;
        } while (false);

        // 连接失败
        if (ctx)
        {
            modbus_close(ctx);
            modbus_free(ctx);
            ctx = nullptr;
        }

        // 等待 1 秒或中断
        while (std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::steady_clock::now() - start_time)
                       .count() < 1000 &&
               !toAbort())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
    }

    pModbusClient->setState(DevClient::UnconnectedState);
}

void ModbusClientBackend::doDisConnectDevice()
{
    if (ctx)
    {
        modbus_close(ctx);
        modbus_free(ctx);
        ctx = nullptr;
    }
    pModbusClient->setState(DevClient::UnconnectedState);
}

void ModbusClientBackend::doReadRequest(DevRequest *req)
{
    auto reply = static_cast<ModbusReply *>(req->reply);
    if (!reply)
        return;

    for (int retry = 0;; ++retry)
    {
        auto start_time = std::chrono::steady_clock::now();

        if (reply->isAborted())
        {
            reply->setError(DevClient::ReplyAbortedError);
            break;
        }

        if (!ctx)
        {
            reply->setError(DevClient::UnknownError);
            break;
        }

        int err = modbus_read_registers(ctx, req->offset, reply->dataSize(), reply->datas());
        if (err != -1)
        {
            reply->setError(DevClient::NoError);
            break;
        }
        else
        {
            if (++retry >= pModbusClient->m_retry)
            {
                reply->setError(DevClient::TimeoutError);
                disconnectDevice(); // 断开重连
                break;
            }

            // 等待超时或被取消
            while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count() < pModbusClient->m_timeout && !reply->isAborted())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(15));
            }
        }
    }
    reply->setFinished();
}

void ModbusClientBackend::doWriteRequest(DevRequest *req)
{
    auto reply = static_cast<ModbusReply *>(req->reply);
    if (!reply)
        return;

    for (int retry = 0;; ++retry)
    {
        auto start_time = std::chrono::steady_clock::now();

        if (reply->isAborted())
        {
            reply->setError(DevClient::ReplyAbortedError);
            break;
        }

        if (!ctx)
        {
            reply->setError(DevClient::UnknownError);
            break;
        }

        const int words = req->size / 2;
        std::vector<uint16_t> buffer(words);
        std::memcpy(buffer.data(), req->datas, req->size);

        int err = modbus_write_registers(ctx, req->offset, words, buffer.data());
        if (err != -1)
        {
            reply->setError(DevClient::NoError);
            break;
        }
        else
        {
            if (++retry >= pModbusClient->m_retry)
            {
                reply->setError(DevClient::TimeoutError);
                break;
            }

            while (std::chrono::duration_cast<std::chrono::milliseconds>(
                       std::chrono::steady_clock::now() - start_time)
                           .count() < pModbusClient->m_timeout &&
                   !reply->isAborted())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(15));
            }
        }
    }
    reply->setFinished();
}

void ModbusClientBackend::run()
{
    {
        std::lock_guard<std::mutex> lock(mtx_);
        initialized_ = true;
    }
    cv_.notify_all();

    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this]
                 { return !command_queue_.empty() || bQuit; });

        if (bQuit && command_queue_.empty())
            break;

        auto cmd = std::move(command_queue_.front());
        command_queue_.pop();
        lock.unlock();

        // 执行命令
        switch (cmd.type)
        {
        case SetTimeout:
        {
            if (auto *timeout = std::get_if<int>(&cmd.data))
            {
                pModbusClient->m_timeout = *timeout;
            }
            break;
        }
        case Connect:
            doConnectDevice();
            break;
        case Disconnect:
            doDisConnectDevice();
            break;
        case Read:
        {
            if (auto *req = std::get_if<DevRequest *>(&cmd.data))
            {
                doReadRequest(*req);
            }
            break;
        }
        case Write:
        {
            if (auto *req = std::get_if<DevRequest *>(&cmd.data))
            {
                doWriteRequest(*req);
            }
            break;
        }
        default:
            break;
        }
    }
}

bool ModbusClientBackend::waitUntilInitialized()
{
    std::unique_lock<std::mutex> lock(mtx_);
    return cv_.wait_for(lock, std::chrono::seconds(3), [this]
                        { return initialized_; });
}