#include <gtest/gtest.h>
#include <stdexcept>
#include <cstring>
#include "../../core/memory/plc_memory.h"

class PLCMemoryTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // 使用默认配置
        config.input_size = 64;
        config.output_size = 64;
        config.memory_size = 128;
        config.db_count = 8;
        config.db_size = 256;
        config.enable_persistence = false; // 测试时关闭持久化

        memory = new PlcMemory(config);
        ASSERT_TRUE(memory->initialize());
    }

    void TearDown() override
    {
        memory->cleanup();
        delete memory;
    }

    PlcConfig config;
    PlcMemory *memory;
};

// 测试内存初始化
TEST_F(PLCMemoryTest, Initialization)
{
    EXPECT_NE(memory, nullptr);
    EXPECT_GT(memory->getAreaSize(INPUT), 0);
    EXPECT_GT(memory->getAreaSize(OUTPUT), 0);
    EXPECT_GT(memory->getAreaSize(MEMORY), 0);
    EXPECT_GT(memory->getAreaSize(DATA_BLOCK), 0);
}

// 测试地址解析
TEST_F(PLCMemoryTest, AddressParsing)
{
    PlcAddress addr;

    // 测试位地址解析
    EXPECT_TRUE(memory->parseAddress("%IX0.1", addr));
    EXPECT_EQ(addr.area, INPUT);
    EXPECT_EQ(addr.offset, 0);
    EXPECT_EQ(addr.bit, 1);
    EXPECT_EQ(addr.width, BIT);

    // 测试字节地址解析
    EXPECT_TRUE(memory->parseAddress("%IB4", addr));
    EXPECT_EQ(addr.area, INPUT);
    EXPECT_EQ(addr.offset, 4);
    EXPECT_EQ(addr.bit, -1);
    EXPECT_EQ(addr.width, BYTE);

    // 测试字地址解析
    EXPECT_TRUE(memory->parseAddress("%QW6", addr));
    EXPECT_EQ(addr.area, OUTPUT);
    EXPECT_EQ(addr.offset, 6);
    EXPECT_EQ(addr.width, WORD);

    // 测试双字地址解析
    EXPECT_TRUE(memory->parseAddress("%MD12", addr));
    EXPECT_EQ(addr.area, MEMORY);
    EXPECT_EQ(addr.offset, 12);
    EXPECT_EQ(addr.width, DWORD);

    // 测试DB地址解析
    EXPECT_TRUE(memory->parseAddress("DB1.DBD4", addr));
    EXPECT_EQ(addr.area, DATA_BLOCK);
    EXPECT_EQ(addr.db_number, 1);
    EXPECT_EQ(addr.offset, 4);
    EXPECT_EQ(addr.width, DWORD);

    // 测试DB位地址解析
    EXPECT_TRUE(memory->parseAddress("DB1.DBW2.7", addr));
    EXPECT_EQ(addr.area, DATA_BLOCK);
    EXPECT_EQ(addr.db_number, 1);
    EXPECT_EQ(addr.offset, 2);
    EXPECT_EQ(addr.bit, 7);
    EXPECT_EQ(addr.width, BIT);

    // 测试无效地址
    EXPECT_FALSE(memory->parseAddress("invalid", addr));
}

// 测试位读写操作
TEST_F(PLCMemoryTest, BitReadWrite)
{
    bool value;

    // 测试输入区位操作
    EXPECT_TRUE(memory->writeBit(INPUT, 0, 0, 0, true));
    EXPECT_TRUE(memory->readBit(INPUT, 0, 0, 0, value));
    EXPECT_TRUE(value);

    EXPECT_TRUE(memory->writeBit(INPUT, 0, 0, 0, false));
    EXPECT_TRUE(memory->readBit(INPUT, 0, 0, 0, value));
    EXPECT_FALSE(value);

    // 测试输出区位操作
    EXPECT_TRUE(memory->writeBit(OUTPUT, 0, 1, 3, true));
    EXPECT_TRUE(memory->readBit(OUTPUT, 0, 1, 3, value));
    EXPECT_TRUE(value);
}

// 测试字节读写操作
TEST_F(PLCMemoryTest, ByteReadWrite)
{
    uint8_t value;

    // 测试内存区字节操作
    EXPECT_TRUE(memory->writeByte(MEMORY, 0, 0, 0xAB));
    EXPECT_TRUE(memory->readByte(MEMORY, 0, 0, value));
    EXPECT_EQ(value, 0xAB);

    // 测试DB区字节操作
    EXPECT_TRUE(memory->writeByte(DATA_BLOCK, 1, 10, 0xCD));
    EXPECT_TRUE(memory->readByte(DATA_BLOCK, 1, 10, value));
    EXPECT_EQ(value, 0xCD);
}

// 测试字读写操作
TEST_F(PLCMemoryTest, WordReadWrite)
{
    uint16_t value;

    EXPECT_TRUE(memory->writeWord(OUTPUT, 0, 2, 0x1234));
    EXPECT_TRUE(memory->readWord(OUTPUT, 0, 2, value));
    EXPECT_EQ(value, 0x1234);

    // 测试字节序（小端）
    EXPECT_TRUE(memory->writeWord(MEMORY, 0, 4, 0xABCD));
    uint8_t low_byte, high_byte;
    EXPECT_TRUE(memory->readByte(MEMORY, 0, 4, low_byte));
    EXPECT_TRUE(memory->readByte(MEMORY, 0, 5, high_byte));
    EXPECT_EQ(low_byte, 0xCD);
    EXPECT_EQ(high_byte, 0xAB);
}

// 测试双字读写操作
TEST_F(PLCMemoryTest, DWordReadWrite)
{
    uint32_t value;

    EXPECT_TRUE(memory->writeDWord(MEMORY, 0, 8, 0x12345678));
    EXPECT_TRUE(memory->readDWord(MEMORY, 0, 8, value));
    EXPECT_EQ(value, 0x12345678);
}

// 测试批量字节操作
TEST_F(PLCMemoryTest, BulkByteOperations)
{
    const size_t data_size = 16;
    uint8_t write_data[data_size] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                                     0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
    uint8_t read_data[data_size] = {0};

    // 测试批量写入和读取
    EXPECT_TRUE(memory->writeBytes(MEMORY, 0, 0, data_size, write_data));
    EXPECT_TRUE(memory->readBytes(MEMORY, 0, 0, data_size, read_data));
    EXPECT_EQ(memcmp(write_data, read_data, data_size), 0);
}

// 测试边界条件和错误处理
TEST_F(PLCMemoryTest, BoundaryAndErrorConditions)
{
    bool value;
    uint8_t byte_value;

    // 测试超出边界访问
    EXPECT_FALSE(memory->readBit(INPUT, 0, config.input_size, 0, value));
    EXPECT_FALSE(memory->writeBit(OUTPUT, 0, config.output_size, 0, true));

    // 测试无效位偏移
    EXPECT_FALSE(memory->readBit(MEMORY, 0, 0, 8, value));  // 位偏移超出0-7范围
    EXPECT_FALSE(memory->readBit(MEMORY, 0, 0, -1, value)); // 位偏移为负数

    // 测试无效DB编号
    EXPECT_FALSE(memory->readByte(DATA_BLOCK, config.db_count + 1, 0, byte_value));
    EXPECT_FALSE(memory->writeByte(DATA_BLOCK, 0, 0, 0xFF));

    // 测试批量操作超出边界
    uint8_t buffer[100];
    EXPECT_FALSE(memory->readBytes(MEMORY, 0, config.memory_size - 50, 100, buffer));
}

// 测试区域大小获取
TEST_F(PLCMemoryTest, AreaSize)
{
    EXPECT_EQ(memory->getAreaSize(INPUT), config.input_size);
    EXPECT_EQ(memory->getAreaSize(OUTPUT), config.output_size);
    EXPECT_EQ(memory->getAreaSize(MEMORY), config.memory_size);
    EXPECT_EQ(memory->getAreaSize(DATA_BLOCK), config.db_count * config.db_size);
}

// 测试并发访问（基础测试）
TEST_F(PLCMemoryTest, ConcurrentAccessBasic)
{
    // 多个线程同时读写不同区域应该正常工作
    // 这里只做基础功能测试，压力测试需要更复杂的设置

    bool bit_value;
    uint8_t byte_value;

    // 交叉访问不同区域
    EXPECT_TRUE(memory->writeBit(INPUT, 0, 0, 0, true));
    EXPECT_TRUE(memory->writeByte(OUTPUT, 0, 0, 0xAA));
    EXPECT_TRUE(memory->writeWord(MEMORY, 0, 0, 0x1234));

    EXPECT_TRUE(memory->readBit(INPUT, 0, 0, 0, bit_value));
    EXPECT_TRUE(memory->readByte(OUTPUT, 0, 0, byte_value));

    EXPECT_TRUE(bit_value);
    EXPECT_EQ(byte_value, 0xAA);
}

// 测试复杂场景：多个区域同时操作
TEST_F(PLCMemoryTest, MultiAreaOperations)
{
    PlcAddress addr;
    bool bit_value;
    uint8_t byte_value;
    // 同时操作多个区域
    EXPECT_TRUE(memory->parseAddress("%IB1.4", addr));
    EXPECT_TRUE(memory->writeBit(addr.area, addr.db_number, addr.offset, addr.bit, true));
    EXPECT_TRUE(memory->parseAddress("%QX5.3", addr));
    EXPECT_TRUE(memory->writeBit(addr.area, addr.db_number, addr.offset, addr.bit, false));
    EXPECT_TRUE(memory->parseAddress("%MB10", addr));
    EXPECT_TRUE(memory->writeByte(addr.area, addr.db_number, addr.offset, 0x55));
    // 验证所有写入的值
    EXPECT_TRUE(memory->parseAddress("%IB1.4", addr));
    EXPECT_TRUE(memory->readBit(addr.area, addr.db_number, addr.offset, addr.bit, bit_value));
    EXPECT_TRUE(bit_value);
    EXPECT_TRUE(memory->parseAddress("%QX5.3", addr));
    EXPECT_TRUE(memory->readBit(addr.area, addr.db_number, addr.offset, addr.bit, bit_value));
    EXPECT_FALSE(bit_value);
    EXPECT_TRUE(memory->parseAddress("%MB10", addr));
    EXPECT_TRUE(memory->readByte(addr.area, addr.db_number, addr.offset, byte_value));
    EXPECT_EQ(byte_value, 0x55);
}
// 测试数据一致性：写入后立即读取应该得到相同值
TEST_F(PLCMemoryTest, DataConsistency)
{
    PlcAddress addr;

    // 测试各种数据类型的写入读取一致性
    const uint32_t test_values[] = {0, 1, 0xFF, 0xFFFF, 0xFFFFFFFF, 0x12345678, 0xABCDEF12};

    for (uint32_t test_value : test_values)
    {
        // 双字测试
        EXPECT_TRUE(memory->parseAddress("%MD100", addr));
        EXPECT_TRUE(memory->writeDWord(addr.area, addr.db_number, addr.offset, test_value));

        uint32_t read_value;
        EXPECT_TRUE(memory->readDWord(addr.area, addr.db_number, addr.offset, read_value));
        EXPECT_EQ(read_value, test_value) << "Failed for value: 0x" << std::hex << test_value;
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
