#include "firmware.h"

static uint8_t *memory_pool = nullptr;
static size_t input_size = 0;
static size_t output_size = 0;
static size_t memory_size = 0;
static size_t db_count = 0;
static size_t db_size = 0;

static size_t input_offset = 0;
static size_t output_offset = 0;
static size_t memory_offset = 0;
static size_t db_offset = 0;

static uint64_t current_time_ms = 0;

extern "C"
{
    void updateCT(uint64_t ct_ms)
    {
        current_time_ms = ct_ms;
    }

    void initializeMemory(size_t i_size, size_t q_size, size_t m_size, size_t db_cnt, size_t db_sz)
    {
        if (memory_pool)
            delete[] memory_pool;

        input_size = i_size;
        output_size = q_size;
        memory_size = m_size;
        db_count = db_cnt;
        db_size = db_sz;

        input_offset = 0;
        output_offset = input_offset + input_size;
        memory_offset = output_offset + output_size;
        db_offset = memory_offset + memory_size;

        size_t total = db_offset + db_count * db_size;
        memory_pool = new uint8_t[total]();
    }

    void shutdown()
    {
        if (memory_pool)
        {
            delete[] memory_pool;
            memory_pool = nullptr;
        }
    }
}

void TON(TON_Timer *inst, bool in, uint32_t pt, bool *q, uint32_t *et)
{
    if (!in)
    {
        // IN 为 FALSE：复位
        inst->q = false;
        inst->et = 0;
        inst->in_last = false;
    }
    else
    {
        if (!inst->in_last)
        {
            // IN 从 FALSE → TRUE：启动定时
            inst->start_time = current_time_ms;
            inst->pt = pt;
        }
        // 计算已过时间
        inst->et = (current_time_ms >= inst->start_time)
                       ? (current_time_ms - inst->start_time)
                       : (0xFFFFFFFF - inst->start_time + current_time_ms + 1);

        // 判断是否超时
        if (inst->et >= inst->pt)
        {
            inst->q = true;
        }
    }

    // 更新输出
    *q = inst->q;
    *et = inst->et;

    // 保存当前 IN 状态
    inst->in_last = in;
}

static uint8_t *getAreaBase(MemoryArea area, int db_num)
{
    switch (area)
    {
    case INPUT:
        return memory_pool + input_offset;
    case OUTPUT:
        return memory_pool + output_offset;
    case MEMORY:
        return memory_pool + memory_offset;
    case DATA_BLOCK:
        if (db_num < 1 || static_cast<size_t>(db_num) > db_count)
        {
            return nullptr;
        }
        return memory_pool + db_offset + (db_num - 1) * db_size;
    default:
        return nullptr;
    }
}

static bool isValidAccess(MemoryArea area, int db_num, size_t offset, size_t size)
{
    if (!memory_pool)
    {
        return false;
    }

    uint8_t *base = getAreaBase(area, db_num);
    if (!base)
    {
        return false;
    }

    size_t area_size = 0;
    switch (area)
    {
    case INPUT:
        area_size = input_size;
        break;
    case OUTPUT:
        area_size = output_size;
        break;
    case MEMORY:
        area_size = memory_size;
        break;
    case DATA_BLOCK:
        area_size = db_size;
        break;
    default:
        return false;
    }

    // 检查是否越界
    if (offset + size > area_size)
    {
        return false;
    }

    return true;
}

bool readBit(MemoryArea area, int db_num, size_t byte_offset, int bit_offset)
{
    if (bit_offset < 0 || bit_offset > 7)
    {
        return false;
    }

    uint8_t byte_val = readByte(area, db_num, byte_offset);
    bool value = (byte_val >> bit_offset) & 1;
    return value;
}

uint8_t readByte(MemoryArea area, int db_num, size_t offset)
{
    uint8_t buf = 0;
    if (!readBytes(area, db_num, offset, 1, &buf))
        return 0;
    else
        return buf;
}

bool readBytes(MemoryArea area, int db_num, size_t start_offset, size_t size, void *buffer)
{
    if (!buffer || size == 0)
    {
        return false;
    }

    if (!isValidAccess(area, db_num, start_offset, size))
    {
        return false;
    }

    uint8_t *src = getAreaBase(area, db_num) + start_offset;
    std::memcpy(buffer, src, size);
    return true;
}

uint16_t readWord(MemoryArea area, int db_num, size_t offset)
{
    uint16_t value = 0;
    uint8_t buf[2];
    if (!readBytes(area, db_num, offset, 2, buf))
    {
        return 0;
    }
    // 小端：低字节在前
    value = (static_cast<uint16_t>(buf[1]) << 8) | buf[0];
    return value;
}

uint32_t readDWord(MemoryArea area, int db_num, size_t offset)
{
    uint32_t value = 0;
    uint8_t buf[4];
    if (!readBytes(area, db_num, offset, 4, buf))
    {
        return 0;
    }
    value = (static_cast<uint32_t>(buf[3]) << 24) |
            (static_cast<uint32_t>(buf[2]) << 16) |
            (static_cast<uint32_t>(buf[1]) << 8) |
            buf[0];
    return value;
}

bool writeBit(MemoryArea area, int db_num, size_t byte_offset, int bit_offset, bool value)
{
    if (bit_offset < 0 || bit_offset > 7)
    {
        return false;
    }
    if (!isValidAccess(area, db_num, byte_offset, 1))
    {
        return false;
    }
    unsigned char *addr = getAreaBase(area, db_num) + byte_offset;
    if (value)
    {
        *addr |= (1 << bit_offset);
    }
    else
    {
        *addr &= ~(1 << bit_offset);
    }
    return true;
}

bool writeBytes(MemoryArea area, int db_num, size_t start_offset, size_t size, const void *buffer)
{
    if (!buffer || size == 0)
    {
        return false;
    }

    if (!isValidAccess(area, db_num, start_offset, size))
    {
        return false;
    }

    unsigned char *dst = getAreaBase(area, db_num) + start_offset;
    std::memcpy(dst, buffer, size);
    return true;
}

bool writeByte(MemoryArea area, int db_num, size_t offset, uint8_t value)
{
    return writeBytes(area, db_num, offset, 1, &value);
}

bool writeWord(MemoryArea area, int db_num, size_t offset, uint16_t value)
{
    uint8_t buf[2];
    buf[0] = static_cast<uint8_t>(value & 0xFF);        // 低字节
    buf[1] = static_cast<uint8_t>((value >> 8) & 0xFF); // 高字节
    return writeBytes(area, db_num, offset, 2, buf);
}

bool writeDWord(MemoryArea area, int db_num, size_t offset, uint32_t value)
{
    uint8_t buf[4] = {
        static_cast<uint8_t>(value & 0xFF),
        static_cast<uint8_t>((value >> 8) & 0xFF),
        static_cast<uint8_t>((value >> 16) & 0xFF),
        static_cast<uint8_t>((value >> 24) & 0xFF)};
    return writeBytes(area, db_num, offset, 4, buf);
}