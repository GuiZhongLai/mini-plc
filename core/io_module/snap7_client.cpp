#include "snap7_client.h"

#include <iostream>
#include <cstring>

Snap7Client::Snap7Client(const std::string &devName, uint16_t rSize, uint16_t tSize)
    : DevClient(MODBUS, devName, rSize, tSize), d(new Snap7ClientBackend(this))
{
}

Snap7Client::~Snap7Client()
{
    disconnectDevice();
    delete d;
}

bool Snap7Client::connectDevice()
{
    if (state() != UnconnectedState)
        return false;

    std::cout << "[DevManager] Snap7 Device connect...\n";

    setState(ConnectingState);
    d->connectDevice();

    return true;
}

void Snap7Client::disconnectDevice()
{
    std::cout << "[DevManager] Snap7 Device disconnect...\n";

    setState(ClosingState);
    d->disconnectDevice();
}

void Snap7Client::setNumberOfRetries(int number)
{
    if (number > 5)
        number = 5;
    DevClient::setNumberOfRetries(number);
}

void Snap7Client::setTimeout(int newTimeout)
{
    if (newTimeout >= 50)
    {
        m_timeout = newTimeout;
        d->setTimeout(newTimeout);
    }
}

DevClient::Error Snap7Client::readRequest(DevRequest &req)
{
    if (req.reply != nullptr)
        return NoError;

    req.reply = new Snap7Reply(req.size);
    d->readRequest(&req);
    return NoError;
}

DevClient::Error Snap7Client::writeRequest(DevRequest &req)
{
    if (req.reply != nullptr)
        return NoError;

    req.reply = new Snap7Reply(0);
    d->writeRequest(&req);
    return NoError;
}

DevClient::Error Snap7Client::readResponse(DevRequest &req)
{
    if (!req.reply)
        return NoError;

    auto reply = static_cast<Snap7Reply *>(req.reply);
    if (reply->isFinished())
    {
        auto error = reply->error();
        if (error == NoError)
        {
            memcpy(req.datas, reply->datas(), reply->dataSize());
        }
        abortRequest(req);
        return error;
    }
    return NoError;
}

DevClient::Error Snap7Client::writeResponse(DevRequest &req)
{
    if (!req.reply)
        return NoError;

    auto reply = static_cast<Snap7Reply *>(req.reply);
    if (reply->isFinished())
    {
        auto error = reply->error();
        abortRequest(req);
        return error;
    }
    return NoError;
}

DevClient::Error Snap7Client::abortRequest(DevRequest &req)
{
    if (req.reply != nullptr)
    {
        static_cast<Snap7Reply *>(req.reply)->abort();
        delete static_cast<Snap7Reply *>(req.reply);
        req.reply = nullptr;
    }
    return NoError;
}

bool Snap7Client::isFinishedRequest(DevRequest &req) const
{
    if (!req.reply)
        return true;
    return static_cast<Snap7Reply *>(req.reply)->isFinished();
}

std::any Snap7Client::connectionParameter(int parameter) const
{
    switch (parameter)
    {
    case RackParameter:
        return std::any(d->m_rack);
    case SlotParameter:
        return std::any(d->m_slot);
    case NetworkAddressParameter:
        return std::any(d->strIpAddr);
    case NetworkPortParameter:
        return std::any(d->m_port);
    default:
        break;
    }
    return std::any();
}

void Snap7Client::setConnectionParameter(int parameter, const std::any &value)
{
    try
    {
        switch (parameter)
        {
        case RackParameter:
            d->m_rack = std::any_cast<int>(value);
            break;
        case SlotParameter:
            d->m_slot = std::any_cast<int>(value);
            break;
        case NetworkAddressParameter:
            d->strIpAddr = std::any_cast<std::string>(value);
            break;
        case NetworkPortParameter:
            d->m_port = std::any_cast<int>(value);
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

Snap7ClientBackend::Snap7ClientBackend(Snap7Client *parent)
    : pSnap7Client(parent)
{
    m_thread = std::thread(&Snap7ClientBackend::run, this);
    waitUntilInitialized();
}

Snap7ClientBackend::~Snap7ClientBackend()
{
    bQuit = true;
    cv_.notify_all();
    if (m_thread.joinable())
    {
        m_thread.join();
    }

    if (ctx)
    {
        ctx->Disconnect();
        delete ctx;
    }
}

void Snap7ClientBackend::setTimeout(int newTimeout)
{
    std::lock_guard<std::mutex> lock(mtx_);
    command_queue_.push({SetTimeout, newTimeout});
    cv_.notify_one();
}

void Snap7ClientBackend::connectDevice()
{
    std::lock_guard<std::mutex> lock(mtx_);
    command_queue_.push({Connect});
    cv_.notify_one();
}

void Snap7ClientBackend::disconnectDevice()
{
    std::lock_guard<std::mutex> lock(mtx_);
    command_queue_.push({Disconnect});
    cv_.notify_one();
}

void Snap7ClientBackend::readRequest(DevRequest *req)
{
    std::lock_guard<std::mutex> lock(mtx_);
    command_queue_.push({Read, req});
    cv_.notify_one();
}

void Snap7ClientBackend::writeRequest(DevRequest *req)
{
    std::lock_guard<std::mutex> lock(mtx_);
    command_queue_.push({Write, req});
    cv_.notify_one();
}

void Snap7ClientBackend::doConnectDevice()
{
    pSnap7Client->setState(DevClient::ConnectingState);

    auto toAbort = [this]() -> bool
    {
        if (!bQuit && pSnap7Client->state() != DevClient::ClosingState)
            return false;

        return true;
    };

    for (int retry = 5; retry > 0; --retry)
    {
        auto start_time = std::chrono::steady_clock::now();

        do
        {
            if (!ctx)
                ctx = new TS7Client;

            if (0 != ctx->ConnectTo(strIpAddr.c_str(), m_rack, m_slot))
                break;

            if (toAbort())
                break;

            int timeout = pSnap7Client->m_timeout;
            ctx->SetParam(p_i32_SendTimeout, &timeout);
            ctx->SetParam(p_i32_RecvTimeout, &timeout);

            if (toAbort())
                break;

            std::cout << "[DevManager] Snap7 Device connected\n";
            pSnap7Client->setState(DevClient::ConnectedState);
            return;
        } while (false);

        // 连接失败
        if (ctx)
        {
            ctx->Disconnect();
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

    pSnap7Client->setState(DevClient::UnconnectedState);
}

void Snap7ClientBackend::doDisConnectDevice()
{
    if (ctx)
    {
        ctx->Disconnect();
    }
    pSnap7Client->setState(DevClient::UnconnectedState);
}

void Snap7ClientBackend::doReadRequest(DevRequest *req)
{
    auto reply = static_cast<Snap7Reply *>(req->reply);
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

        int err = ctx->ReadArea(static_cast<int>(req->group), static_cast<int>(req->dbNum),
                                static_cast<int>(req->offset),
                                static_cast<int>(req->size),
                                S7WLByte,
                                reply->datas());
        if (err == 0)
        {
            reply->setError(DevClient::NoError);
            break;
        }
        else
        {
            std::cout << "snap7 read requset error : " << CliErrorText(err).c_str();
            if (++retry >= pSnap7Client->m_retry)
            {
                reply->setError(DevClient::TimeoutError);
                doDisConnectDevice(); // 断开重连
                break;
            }

            // 等待超时或被取消
            while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count() < pSnap7Client->m_timeout && !reply->isAborted())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(15));
            }
        }
    }
    reply->setFinished();
}

void Snap7ClientBackend::doWriteRequest(DevRequest *req)
{
    auto reply = static_cast<Snap7Reply *>(req->reply);
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

        std::vector<uint8_t> buffer(req->size);
        std::memcpy(buffer.data(), req->datas, req->size);

        int err = ctx->WriteArea(static_cast<int>(req->group), static_cast<int>(req->dbNum),
                                 static_cast<int>(req->offset),
                                 static_cast<int>(req->size),
                                 S7WLByte,
                                 buffer.data());

        if (err == 0)
        {
            reply->setError(DevClient::NoError);
            break;
        }
        else
        {
            std::cout << "snap7 write requset error : " << CliErrorText(err).c_str();
            if (++retry >= pSnap7Client->m_retry)
            {
                reply->setError(DevClient::TimeoutError);
                break;
            }

            while (std::chrono::duration_cast<std::chrono::milliseconds>(
                       std::chrono::steady_clock::now() - start_time)
                           .count() < pSnap7Client->m_timeout &&
                   !reply->isAborted())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(15));
            }
        }
    }
    reply->setFinished();
}

void Snap7ClientBackend::run()
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
                pSnap7Client->m_timeout = *timeout;
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
            if (auto *pReq = std::get_if<DevRequest *>(&cmd.data))
            {
                doReadRequest(*pReq);
            }
            break;
        }
        case Write:
        {
            if (auto *pReq = std::get_if<DevRequest *>(&cmd.data))
            {
                doWriteRequest(*pReq);
            }
            break;
        }
        default:
            break;
        }
    }
}

bool Snap7ClientBackend::waitUntilInitialized()
{
    std::unique_lock<std::mutex> lock(mtx_);
    return cv_.wait_for(lock, std::chrono::seconds(3), [this]
                        { return initialized_; });
}