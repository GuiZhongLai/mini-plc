#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TON_Timer
{
    bool in_last = false;    // 上次 IN 状态
    bool q = false;          // 输出 Q
    uint32_t pt = 0;         // 预设时间 (ms)
    uint32_t start_time = 0; // 开始计时的时间点
    uint32_t et = 0;         // 当前经过时间
};

enum MemoryArea
{
    INPUT,     // %I
    OUTPUT,    // %Q
    MEMORY,    // %M
    DATA_BLOCK // DB
};

enum DataWidth
{
    BIT,
    BYTE,
    WORD, // 2 字节
    DWORD // 4 字节
};

struct PlcAddress
{
    MemoryArea area; // 区域
    int db_number;   // DB 编号
    size_t offset;   // 字节偏移
    int bit;         // 位偏移，-1 表示不是位访问
    DataWidth width; // 访问宽度
};

extern "C"
{
    void updateCT(uint64_t ct_ms);
    void initializeMemory(size_t i_size, size_t q_size, size_t m_size, size_t db_cnt, size_t db_sz);
    void scan();
    void shutdown();
}

// ==================== 读写函数声明 ====================
bool readBit(MemoryArea area, int db_num, size_t byte_offset, int bit_offset);
uint8_t readByte(MemoryArea area, int db_num, size_t offset);
uint16_t readWord(MemoryArea area, int db_num, size_t offset);
uint32_t readDWord(MemoryArea area, int db_num, size_t offset);
bool writeBit(MemoryArea area, int db_num, size_t byte_offset, int bit_offset, bool value);
bool writeByte(MemoryArea area, int db_num, size_t offset, uint8_t value);
bool writeWord(MemoryArea area, int db_num, size_t offset, uint16_t value);
bool writeDWord(MemoryArea area, int db_num, size_t offset, uint32_t value);

// ==================== 辅助函数声明 ====================
void TON(TON_Timer *inst, bool in, uint32_t pt, bool *q, uint32_t *et);