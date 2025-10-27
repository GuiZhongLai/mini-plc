#include <gtest/gtest.h>
#include <stdexcept>
#include <cstring>
#include "../../core/comm/snap7_server.h"
#include "../../core/memory/plc_memory.h"

#include <thread>
#include <chrono>

class Snap7ServerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // 创建PLC内存配置
        PlcConfig config;
        config.db_count = 3; // DB1, DB2
        config.db_size = 1024;
        config.input_size = 128;
        config.output_size = 128;
        config.memory_size = 256;

        memory_manager_ = new PlcMemory(config);
        memory_manager_->initialize();
        server_ = new Snap7Server(*memory_manager_);
    }

    void TearDown() override
    {
        delete server_;
        delete memory_manager_;
    }

    PlcMemory *memory_manager_;
    Snap7Server *server_;
};

// 测试服务器启动和停止
TEST_F(Snap7ServerTest, StartStopServer)
{
    // 初始状态检查
    EXPECT_FALSE(server_->isRunning());

    // 启动服务器
    EXPECT_TRUE(server_->start());
    EXPECT_TRUE(server_->isRunning());

    // 检查CPU状态
    EXPECT_EQ(server_->getS7CpuStatus(), 0x08); // 0x08 = RUN

    // 重复启动应该返回true
    EXPECT_TRUE(server_->start());

    // 停止服务器
    server_->stop();
    EXPECT_FALSE(server_->isRunning());
}

// 测试内存区域注册
TEST_F(Snap7ServerTest, MemoryAreaRegistration)
{
    // 启动服务器会触发内存区域注册
    EXPECT_TRUE(server_->start());

    // 验证所有内存区域都已正确注册
    // 这里可以通过检查服务器是否能正常响应客户端请求来间接验证
    // 或者添加一个方法来检查区域注册状态

    server_->stop();
}

// 测试客户端连接计数
TEST_F(Snap7ServerTest, ClientCount)
{
    EXPECT_TRUE(server_->start());

    // 启动后此时状态应该是0x08
    EXPECT_EQ(server_->getS7CpuStatus(), 0x08);

    // 注意：这里无法模拟真实客户端连接
    // 在实际测试中，可以启动一个真实的S7客户端进行连接测试

    server_->stop();
}

// 测试内存访问集成
TEST_F(Snap7ServerTest, MemoryAccessIntegration)
{
    EXPECT_TRUE(server_->start());

    // 获取内存基址并写入测试数据
    unsigned char *input_base = memory_manager_->getAreaBase(INPUT, 0);
    unsigned char *output_base = memory_manager_->getAreaBase(OUTPUT, 0);
    unsigned char *db1_base = memory_manager_->getAreaBase(DATA_BLOCK, 1);

    ASSERT_NE(input_base, nullptr);
    ASSERT_NE(output_base, nullptr);
    ASSERT_NE(db1_base, nullptr);

    // 写入测试数据
    input_base[0] = 0xAA;
    output_base[0] = 0xBB;
    db1_base[0] = 0xCC;

    // 验证数据写入
    EXPECT_EQ(input_base[0], 0xAA);
    EXPECT_EQ(output_base[0], 0xBB);
    EXPECT_EQ(db1_base[0], 0xCC);

    server_->stop();
}

// 性能测试 - 快速启动停止
TEST_F(Snap7ServerTest, PerformanceStartStop)
{
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(server_->start());
        server_->stop();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);

    // 10次启动停止应该在合理时间内完成
    EXPECT_LT(duration.count(), 5000); // 5秒内完成
}

// 测试析构函数
TEST_F(Snap7ServerTest, DestructorTest)
{
    {
        PlcConfig config;
        config.db_count = 2;
        config.db_size = 512;
        config.input_size = 64;
        config.output_size = 64;
        config.memory_size = 128;

        PlcMemory memory(config);
        memory.initialize();
        Snap7Server local_server(memory);

        EXPECT_TRUE(local_server.start());
        // local_server在作用域结束时自动析构
    }
    // 如果没有崩溃，说明析构函数工作正常
}
