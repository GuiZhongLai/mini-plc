#include <gtest/gtest.h>
#include "../../core/io_module/dev_client.h"

#include <thread>
#include <chrono>
#include <random>

// 改进的实际设备连接测试类
class RealDeviceTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // 设备配置
        modbusIp = "192.168.11.14";
        modbusPort = 502;
        snap7Ip = "192.168.11.14";
        snap7Rack = 0;
        snap7Slot = 1;

        // 创建测试数据缓冲区
        testBuffer.resize(256, 0);

        // 预先连接设备，避免每个测试重复连接
        setupConnections();
    }

    void TearDown() override
    {
        if (modbusClient)
        {
            modbusClient->disconnectDevice();
            delete modbusClient;
        }
        if (snap7Client)
        {
            snap7Client->disconnectDevice();
            delete snap7Client;
        }
    }

    void setupConnections()
    {
        // 连接Modbus
        modbusClient = DevClient::create(DevClient::MODBUS, "RealModbus", 200, 100);
        ASSERT_NE(modbusClient, nullptr);
        modbusClient->setConnectionParameter(DevClient::NetworkAddressParameter,
                                             std::any(modbusIp));
        modbusClient->setConnectionParameter(DevClient::NetworkPortParameter,
                                             std::any(modbusPort));
        modbusClient->setTimeout(1000); // 减少超时时间
        modbusClient->setNumberOfRetries(2);

        std::cout << "连接Modbus设备..." << std::endl;
        ASSERT_TRUE(modbusClient->connectDevice());
        waitForConnection(modbusClient, 2000);
        ASSERT_EQ(modbusClient->state(), DevClient::ConnectedState);

        // 连接Snap7
        snap7Client = DevClient::create(DevClient::SNAP7, "RealSnap7", 200, 100);
        ASSERT_NE(snap7Client, nullptr);
        snap7Client->setConnectionParameter(DevClient::NetworkAddressParameter,
                                            std::any(snap7Ip));
        snap7Client->setConnectionParameter(DevClient::RackParameter,
                                            std::any(snap7Rack));
        snap7Client->setConnectionParameter(DevClient::SlotParameter,
                                            std::any(snap7Slot));
        snap7Client->setTimeout(1000);
        snap7Client->setNumberOfRetries(2);

        std::cout << "连接Snap7设备..." << std::endl;
        ASSERT_TRUE(snap7Client->connectDevice());
        waitForConnection(snap7Client, 2000);
        ASSERT_EQ(snap7Client->state(), DevClient::ConnectedState);

        std::cout << "设备连接完成，准备测试..." << std::endl;
    }

    void waitForConnection(DevClient *client, int maxWaitMs = 2000)
    {
        auto start = std::chrono::steady_clock::now();
        while (std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::steady_clock::now() - start)
                   .count() < maxWaitMs)
        {
            if (client->state() == DevClient::ConnectedState)
            {
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void printBufferHex(const std::vector<uint8_t> &buffer, int size, const std::string &title)
    {
        std::cout << title << ": ";
        for (int i = 0; i < size && i < static_cast<int>(buffer.size()); ++i)
        {
            std::cout << std::hex << std::setw(2) << std::setfill('0')
                      << static_cast<int>(buffer[i]) << " ";
        }
        std::cout << std::dec << std::endl;
    }

    std::string modbusIp;
    int modbusPort;
    std::string snap7Ip;
    int snap7Rack;
    int snap7Slot;

    DevClient *modbusClient = nullptr;
    DevClient *snap7Client = nullptr;
    std::vector<uint8_t> testBuffer;
};

// 改进的Snap7 DB块读写测试
TEST_F(RealDeviceTest, Snap7DBDetailedTest)
{
    std::cout << "\n=== Snap7 DB块详细测试 ===" << std::endl;

    // 首先检查所有DB块的初始状态
    std::cout << "\n1. 检查DB块初始状态:" << std::endl;

    // 检查DB1
    {
        std::fill(testBuffer.begin(), testBuffer.end(), 0);
        DevRequest readReq;
        readReq.index = 1;
        readReq.group = 0x84; // DB块
        readReq.dbNum = 1;    // DB1
        readReq.offset = 0;   // 起始偏移
        readReq.size = 32;    // 读取32字节
        readReq.datas = testBuffer.data();
        readReq.bReadOnly = true;

        snap7Client->appendReadRequest(readReq);
        snap7Client->readRequest(readReq);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        snap7Client->readResponse(readReq);

        if (snap7Client->error() == DevClient::NoError)
        {
            printBufferHex(testBuffer, 32, "DB1初始数据");
        }
        else
        {
            std::cout << "DB1读取错误: " << snap7Client->errorString() << std::endl;
        }
        snap7Client->clearRequest();
    }

    // 检查DB2
    {
        std::fill(testBuffer.begin(), testBuffer.end(), 0);
        DevRequest readReq;
        readReq.index = 2;
        readReq.group = 0x84;
        readReq.dbNum = 2; // DB2
        readReq.offset = 0;
        readReq.size = 32;
        readReq.datas = testBuffer.data();
        readReq.bReadOnly = true;

        snap7Client->appendReadRequest(readReq);
        snap7Client->readRequest(readReq);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        snap7Client->readResponse(readReq);

        if (snap7Client->error() == DevClient::NoError)
        {
            printBufferHex(testBuffer, 32, "DB2初始数据");
        }
        else
        {
            std::cout << "DB2读取错误: " << snap7Client->errorString() << std::endl;
        }
        snap7Client->clearRequest();
    }

    // 检查DB3
    {
        std::fill(testBuffer.begin(), testBuffer.end(), 0);
        DevRequest readReq;
        readReq.index = 3;
        readReq.group = 0x84;
        readReq.dbNum = 3; // DB3
        readReq.offset = 0;
        readReq.size = 32;
        readReq.datas = testBuffer.data();
        readReq.bReadOnly = true;

        snap7Client->appendReadRequest(readReq);
        snap7Client->readRequest(readReq);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        snap7Client->readResponse(readReq);

        if (snap7Client->error() == DevClient::NoError)
        {
            printBufferHex(testBuffer, 32, "DB3初始数据");
        }
        else
        {
            std::cout << "DB3读取错误: " << snap7Client->errorString() << std::endl;
        }
        snap7Client->clearRequest();
    }

    std::cout << "\n2. DB块写入测试:" << std::endl;

    // 测试写入DB1
    {
        std::vector<uint8_t> db1Data = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
        DevRequest writeReq;
        writeReq.index = 4;
        writeReq.group = 0x84;
        writeReq.dbNum = 1;
        writeReq.offset = 0; // 从偏移0开始写入
        writeReq.size = static_cast<uint32_t>(db1Data.size());
        writeReq.datas = db1Data.data();
        writeReq.bReadOnly = false;

        snap7Client->appendWriteRequest(writeReq);
        snap7Client->writeRequest(writeReq);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        snap7Client->writeResponse(writeReq);

        if (snap7Client->error() == DevClient::NoError)
        {
            std::cout << "DB1写入成功: ";
            for (auto b : db1Data)
            {
                std::cout << std::hex << static_cast<int>(b) << " ";
            }
            std::cout << std::dec << std::endl;
        }
        else
        {
            std::cout << "DB1写入错误: " << snap7Client->errorString() << std::endl;
        }
        snap7Client->clearRequest();
    }

    // 测试写入DB2
    {
        std::vector<uint8_t> db2Data = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x99, 0x00};
        DevRequest writeReq;
        writeReq.index = 5;
        writeReq.group = 0x84;
        writeReq.dbNum = 2;
        writeReq.offset = 10; // 从偏移10开始写入
        writeReq.size = static_cast<uint32_t>(db2Data.size());
        writeReq.datas = db2Data.data();
        writeReq.bReadOnly = false;

        snap7Client->appendWriteRequest(writeReq);
        snap7Client->writeRequest(writeReq);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        snap7Client->writeResponse(writeReq);

        if (snap7Client->error() == DevClient::NoError)
        {
            std::cout << "DB2写入成功: ";
            for (auto b : db2Data)
            {
                std::cout << std::hex << static_cast<int>(b) << " ";
            }
            std::cout << std::dec << std::endl;
        }
        else
        {
            std::cout << "DB2写入错误: " << snap7Client->errorString() << std::endl;
        }
        snap7Client->clearRequest();
    }

    std::cout << "\n3. 验证写入的数据:" << std::endl;

    // 验证DB1
    {
        std::fill(testBuffer.begin(), testBuffer.end(), 0);
        DevRequest verifyReq;
        verifyReq.index = 6;
        verifyReq.group = 0x84;
        verifyReq.dbNum = 1;
        verifyReq.offset = 0;
        verifyReq.size = 8;
        verifyReq.datas = testBuffer.data();
        verifyReq.bReadOnly = true;

        snap7Client->appendReadRequest(verifyReq);
        snap7Client->readRequest(verifyReq);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        snap7Client->readResponse(verifyReq);

        if (snap7Client->error() == DevClient::NoError)
        {
            printBufferHex(testBuffer, 8, "DB1验证数据");
        }
        else
        {
            std::cout << "DB1验证错误: " << snap7Client->errorString() << std::endl;
        }
        snap7Client->clearRequest();
    }

    // 验证DB2
    {
        std::fill(testBuffer.begin(), testBuffer.end(), 0);
        DevRequest verifyReq;
        verifyReq.index = 7;
        verifyReq.group = 0x84;
        verifyReq.dbNum = 2;
        verifyReq.offset = 10;
        verifyReq.size = 8;
        verifyReq.datas = testBuffer.data();
        verifyReq.bReadOnly = true;

        snap7Client->appendReadRequest(verifyReq);
        snap7Client->readRequest(verifyReq);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        snap7Client->readResponse(verifyReq);

        if (snap7Client->error() == DevClient::NoError)
        {
            printBufferHex(testBuffer, 8, "DB2验证数据");
        }
        else
        {
            std::cout << "DB2验证错误: " << snap7Client->errorString() << std::endl;
        }
        snap7Client->clearRequest();
    }
}

// 快速Modbus测试
TEST_F(RealDeviceTest, FastModbusTest)
{
    std::cout << "\n=== 快速Modbus测试 ===" << std::endl;

    // 快速读写测试
    auto start = std::chrono::high_resolution_clock::now();
    int successCount = 0;

    for (int i = 0; i < 5; ++i)
    {
        uint16_t writeValue = 100 + i * 10;
        uint16_t readValue = 0;

        // 写入
        DevRequest writeReq;
        writeReq.index = i * 2;
        writeReq.offset = 40 + i; // 使用40-44地址
        writeReq.size = 2;
        writeReq.datas = &writeValue;
        writeReq.bReadOnly = false;

        modbusClient->appendWriteRequest(writeReq);
        modbusClient->writeRequest(writeReq);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        modbusClient->writeResponse(writeReq);
        modbusClient->clearRequest();

        // 读取验证
        DevRequest readReq;
        readReq.index = i * 2 + 1;
        readReq.offset = 40 + i;
        readReq.size = 2;
        readReq.datas = &readValue;
        readReq.bReadOnly = true;

        modbusClient->appendReadRequest(readReq);
        modbusClient->readRequest(readReq);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        modbusClient->readResponse(readReq);
        modbusClient->clearRequest();

        if (writeValue == readValue)
        {
            successCount++;
            std::cout << "地址[" << (40 + i) << "] 写入: " << writeValue
                      << ", 读取: " << readValue << " ✓" << std::endl;
        }
        else
        {
            std::cout << "地址[" << (40 + i) << "] 写入: " << writeValue
                      << ", 读取: " << readValue << " ✗" << std::endl;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "快速测试完成: " << successCount << "/5 成功, 耗时: "
              << duration.count() << "ms" << std::endl;
    EXPECT_GE(successCount, 3); // 至少3次成功
}

// 连接稳定性测试
TEST_F(RealDeviceTest, ConnectionStability)
{
    std::cout << "\n=== 连接稳定性测试 ===" << std::endl;

    // 测试多次操作后的连接状态
    for (int i = 0; i < 10; ++i)
    {
        // 简单的心跳操作
        uint16_t dummy = 0;
        DevRequest heartbeat;
        heartbeat.index = 100 + i;
        heartbeat.offset = 0;
        heartbeat.size = 2;
        heartbeat.datas = &dummy;
        heartbeat.bReadOnly = true;

        modbusClient->appendReadRequest(heartbeat);
        modbusClient->readRequest(heartbeat);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        modbusClient->readResponse(heartbeat);
        modbusClient->clearRequest();

        // 检查连接状态
        ASSERT_EQ(modbusClient->state(), DevClient::ConnectedState);
    }

    std::cout << "连接稳定性测试完成 - 10次操作后连接正常" << std::endl;
}