#include "snap7_server.h"

#include <iostream>
#include <chrono>

Snap7Server::Snap7Server(PlcMemory &memory)
    : memory_manager_(memory), running_(false)
{

    server_ = new TS7Server();
}

Snap7Server::~Snap7Server()
{
    stop();
    delete server_;
}

bool Snap7Server::start()
{
    if (running_)
    {
        return true;
    }

    // 注册所有内存区域
    if (!registerArea())
    {
        std::cerr << "Failed to register PLC memory to Snap7 server." << std::endl;
        return false;
    }

    // 设置本地端口
    int32_t nPort = 16767;
    int error = server_->SetParam(p_u16_LocalPort, &nPort);
    if (error == 0)
    {
        std::cout << "Snap7 Server set socket local port 16767. " << std::endl;
    }
    else
    {
        std::cerr << "Failed to set socket local port." << std::endl;
        return false;
    }
    // 启动服务器
    error = server_->Start();
    if (error == 0)
    {
        running_ = true;
        std::cout << "Snap7 Server started." << std::endl;
        return true;
    }
    else
    {
        std::cerr << "Failed to start Snap7 Server: " << SrvErrorText(error) << std::endl;
        return false;
    }
}

void Snap7Server::stop()
{
    if (running_)
    {
        unregisterArea();
        server_->Stop();
        running_ = false;
        std::cout << "Snap7 Server stopped." << std::endl;
    }
}

bool Snap7Server::isRunning() const
{
    return running_;
}

int Snap7Server::getClientCount() const
{
    return server_->ClientsCount();
}

int Snap7Server::getS7CpuStatus() const
{
    return server_->GetCpuStatus();
}

bool Snap7Server::registerArea()
{
    PlcConfig config = memory_manager_.getPlcConfig();

    // 注册db区
    for (int i = 1; i < static_cast<int>(config.db_count); i++)
    {
        unsigned char *base = memory_manager_.getAreaBase(DATA_BLOCK, i);
        if (base)
        {
            int err = server_->RegisterArea(srvAreaDB, i, base, config.db_size);
            if (err != 0)
                return false;
        }
    }

    // 注册输入区 %I
    if (unsigned char *base = memory_manager_.getAreaBase(INPUT, 0))
    {
        server_->RegisterArea(srvAreaPE, 0, base, config.input_size);
    }

    // 注册输出区 %Q
    if (unsigned char *base = memory_manager_.getAreaBase(OUTPUT, 0))
    {
        server_->RegisterArea(srvAreaPA, 0, base, config.output_size);
    }

    // 注册标志区 %M
    if (unsigned char *base = memory_manager_.getAreaBase(MEMORY, 0))
    {
        server_->RegisterArea(srvAreaMK, 0, base, config.memory_size);
    }

    return true;
}

void Snap7Server::unregisterArea()
{
    PlcConfig config = memory_manager_.getPlcConfig();
    for (int i = 1; i < static_cast<int>(config.db_count); i++)
    {
        server_->UnregisterArea(srvAreaDB, i);
    }
    server_->UnregisterArea(srvAreaPE, 0);
    server_->UnregisterArea(srvAreaPA, 0);
    server_->UnregisterArea(srvAreaMK, 0);
}
