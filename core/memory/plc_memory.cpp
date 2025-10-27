#include "plc_memory.h"

#include <cstdio>
#include <cstring>

PlcMemory::PlcMemory(const PlcConfig &config)
    : config_(config), memory_pool_(nullptr), is_initialized_(false), input_offset_(0), output_offset_(0), memory_offset_(0), db_offset_(0)
{
}

PlcMemory::~PlcMemory()
{
    cleanup();
}

bool PlcMemory::initialize()
{
    if (is_initialized_)
    {
        return true;
    }

    size_t total_size = config_.input_size +
                        config_.output_size +
                        config_.memory_size +
                        config_.db_count * config_.db_size;

    memory_pool_ = new (std::nothrow) unsigned char[total_size];
    if (!memory_pool_)
    {
        return false;
    }

    // 初始化为 0
    std::memset(memory_pool_, 0, total_size);

    // 计算各区域偏移
    input_offset_ = 0;
    output_offset_ = input_offset_ + config_.input_size;
    memory_offset_ = output_offset_ + config_.output_size;
    db_offset_ = memory_offset_ + config_.memory_size;

    is_initialized_ = true;
    return true;
}

void PlcMemory::cleanup()
{
    if (memory_pool_)
    {
        delete[] memory_pool_;
        memory_pool_ = nullptr;
    }
    is_initialized_ = false;
}

bool PlcMemory::parseAddress(const std::string &addr_str, PlcAddress &addr)
{
    if (addr_str.empty())
        return false;

    std::string str = addr_str;
    for (auto &c : str)
        c = tolower(c); // 转小写

    size_t pos = 0;
    addr.db_number = 0;
    addr.offset = 0;
    addr.bit = -1;
    addr.width = BYTE;
    addr.area = MEMORY; // 默认，后面会覆盖

    // ========== 区分是 % 开头 还是 DB 开头 ==========
    if (pos < str.size() && str[pos] == '%')
    {
        // 全局地址：%IX, %QB, %MW 等
        pos++; // 跳过 %
        return parseGlobalAddress(str, pos, addr);
    }
    else if (pos + 2 <= str.size() && str.compare(pos, 2, "db") == 0)
    {
        // DB 块地址：DB1.DBB10
        return parseDBAddress(str, pos, addr);
    }
    else
    {
        // 不支持其他格式
        return false;
    }
}

// 解析全局地址：%IX, %QB, %MW 等
bool PlcMemory::parseGlobalAddress(const std::string &str, size_t &pos, PlcAddress &addr)
{
    addr.area = MEMORY;
    addr.width = BYTE;

    if (str.compare(pos, 2, "ix") == 0)
    {
        addr.area = INPUT;
        addr.width = BIT;
        pos += 2;
    }
    else if (str.compare(pos, 2, "qx") == 0)
    {
        addr.area = OUTPUT;
        addr.width = BIT;
        pos += 2;
    }
    else if (str.compare(pos, 2, "mx") == 0)
    {
        addr.area = MEMORY;
        addr.width = BIT;
        pos += 2;
    }
    else if (pos < str.size() && str[pos] == 'i')
    {
        addr.area = INPUT;
        pos += 1;
        if (pos < str.size())
        {
            if (str[pos] == 'b')
            {
                addr.width = BYTE;
                pos++;
            }
            else if (str[pos] == 'w')
            {
                addr.width = WORD;
                pos++;
            }
            else if (str[pos] == 'd')
            {
                addr.width = DWORD;
                pos++;
            }
            else
                return false;
        }
    }
    else if (pos < str.size() && str[pos] == 'q')
    {
        addr.area = OUTPUT;
        pos += 1;
        if (pos < str.size())
        {
            if (str[pos] == 'b')
            {
                addr.width = BYTE;
                pos++;
            }
            else if (str[pos] == 'w')
            {
                addr.width = WORD;
                pos++;
            }
            else if (str[pos] == 'd')
            {
                addr.width = DWORD;
                pos++;
            }
            else
                return false;
        }
    }
    else if (pos < str.size() && str[pos] == 'm')
    {
        addr.area = MEMORY;
        pos += 1;
        if (pos < str.size())
        {
            if (str[pos] == 'b')
            {
                addr.width = BYTE;
                pos++;
            }
            else if (str[pos] == 'w')
            {
                addr.width = WORD;
                pos++;
            }
            else if (str[pos] == 'd')
            {
                addr.width = DWORD;
                pos++;
            }
            else
                return false;
        }
    }
    else
    {
        return false;
    }

    return parseOffsetAndBit(str, pos, addr);
}

// 解析 DB 地址：DB1.DBB10.7
bool PlcMemory::parseDBAddress(const std::string &str, size_t &pos, PlcAddress &addr)
{
    if (pos + 2 > str.size() || str.compare(pos, 2, "db") != 0)
        return false;

    pos += 2; // 跳过 "db"
    addr.area = DATA_BLOCK;

    // 解析 DB 编号
    size_t num_start = pos;
    while (pos < str.size() && isdigit(str[pos]))
        pos++;

    if (num_start == pos)
        return false; // 没有 DB 号

    try
    {
        addr.db_number = std::stoi(str.substr(num_start, pos - num_start));
    }
    catch (...)
    {
        return false;
    }

    // 跳过点号
    if (pos < str.size() && str[pos] == '.')
        pos++;
    else
        return false;

    // 解析 DB 区域：dbx, dbb, dbw, dbd
    if (pos + 3 > str.size())
        return false;

    if (str.compare(pos, 3, "dbx") == 0)
    {
        addr.width = BIT;
        pos += 3;
    }
    else if (str.compare(pos, 3, "dbb") == 0)
    {
        addr.width = BYTE;
        pos += 3;
    }
    else if (str.compare(pos, 3, "dbw") == 0)
    {
        addr.width = WORD;
        pos += 3;
    }
    else if (str.compare(pos, 3, "dbd") == 0)
    {
        addr.width = DWORD;
        pos += 3;
    }
    else
    {
        return false;
    }

    return parseOffsetAndBit(str, pos, addr);
}

// 统一解析 offset 和 bit，如 "100", "15.7"
bool PlcMemory::parseOffsetAndBit(const std::string &str, size_t &pos, PlcAddress &addr)
{
    size_t num_start = pos;
    while (pos < str.size() && (isdigit(str[pos]) || str[pos] == '.'))
        pos++;

    std::string num_str = str.substr(num_start, pos - num_start);
    if (num_str.empty())
        return false;

    size_t dot_pos = num_str.find('.');
    if (dot_pos != std::string::npos)
    {
        try
        {
            addr.offset = std::stoi(num_str.substr(0, dot_pos));
            addr.bit = std::stoi(num_str.substr(dot_pos + 1));
            if (addr.bit < 0 || addr.bit > 7)
                return false;
            // 如果是位访问，强制设置为BIT宽度（即使原为WORD/DWORD）
            addr.width = BIT;
        }
        catch (...)
        {
            return false;
        }
    }
    else
    {
        try
        {
            addr.offset = std::stoi(num_str);
            addr.bit = -1; // 无位访问
        }
        catch (...)
        {
            return false;
        }
    }

    return true;
}

bool PlcMemory::readBit(MemoryArea area, int db_num, size_t byte_offset, int bit_offset, bool &value)
{
    if (bit_offset < 0 || bit_offset > 7)
    {
        return false;
    }

    uint8_t byte_val;
    if (!readByte(area, db_num, byte_offset, byte_val))
    {
        return false;
    }

    value = (byte_val >> bit_offset) & 1;
    return true;
}

bool PlcMemory::writeBit(MemoryArea area, int db_num, size_t byte_offset, int bit_offset, bool value)
{
    if (bit_offset < 0 || bit_offset > 7)
    {
        return false;
    }

    // 先读再改再写，保证原子性
    std::unique_lock<std::shared_mutex> lock(mutex_);

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

bool PlcMemory::readBytes(MemoryArea area, int db_num, size_t start_offset, size_t size, void *buffer)
{
    if (!buffer || size == 0)
    {
        return false;
    }

    std::shared_lock<std::shared_mutex> lock(mutex_); // 共享读锁

    if (!isValidAccess(area, db_num, start_offset, size))
    {
        return false;
    }

    unsigned char *src = getAreaBase(area, db_num) + start_offset;
    std::memcpy(buffer, src, size);
    return true;
}

bool PlcMemory::writeBytes(MemoryArea area, int db_num, size_t start_offset, size_t size, const void *buffer)
{
    if (!buffer || size == 0)
    {
        return false;
    }

    std::unique_lock<std::shared_mutex> lock(mutex_); // 独占写锁

    if (!isValidAccess(area, db_num, start_offset, size))
    {
        return false;
    }

    unsigned char *dst = getAreaBase(area, db_num) + start_offset;
    std::memcpy(dst, buffer, size);
    return true;
}

bool PlcMemory::readByte(MemoryArea area, int db_num, size_t offset, uint8_t &value)
{
    return readBytes(area, db_num, offset, 1, &value);
}

bool PlcMemory::writeByte(MemoryArea area, int db_num, size_t offset, uint8_t value)
{
    return writeBytes(area, db_num, offset, 1, &value);
}

bool PlcMemory::readWord(MemoryArea area, int db_num, size_t offset, uint16_t &value)
{
    uint8_t buf[2];
    if (!readBytes(area, db_num, offset, 2, buf))
    {
        return false;
    }
    // 小端：低字节在前
    value = (static_cast<uint16_t>(buf[1]) << 8) | buf[0];
    return true;
}

bool PlcMemory::writeWord(MemoryArea area, int db_num, size_t offset, uint16_t value)
{
    uint8_t buf[2];
    buf[0] = static_cast<uint8_t>(value & 0xFF);        // 低字节
    buf[1] = static_cast<uint8_t>((value >> 8) & 0xFF); // 高字节
    return writeBytes(area, db_num, offset, 2, buf);
}

bool PlcMemory::readDWord(MemoryArea area, int db_num, size_t offset, uint32_t &value)
{
    uint8_t buf[4];
    if (!readBytes(area, db_num, offset, 4, buf))
    {
        return false;
    }
    value = (static_cast<uint32_t>(buf[3]) << 24) |
            (static_cast<uint32_t>(buf[2]) << 16) |
            (static_cast<uint32_t>(buf[1]) << 8) |
            buf[0];
    return true;
}

bool PlcMemory::writeDWord(MemoryArea area, int db_num, size_t offset, uint32_t value)
{
    uint8_t buf[4];
    buf[0] = static_cast<uint8_t>(value & 0xFF);
    buf[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    buf[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
    buf[3] = static_cast<uint8_t>((value >> 24) & 0xFF);
    return writeBytes(area, db_num, offset, 4, buf);
}

size_t PlcMemory::getAreaSize(MemoryArea area) const
{
    switch (area)
    {
    case INPUT:
        return config_.input_size;
    case OUTPUT:
        return config_.output_size;
    case MEMORY:
        return config_.memory_size;
    case DATA_BLOCK:
        // DATA_BLOCK 区域总大小 = DB数量 × 单个DB大小
        return config_.db_count * config_.db_size;
    default:
        return 0;
    }
}

bool PlcMemory::saveToPersistentStorage()
{
    if (!config_.enable_persistence || !is_initialized_)
    {
        return false;
    }

    std::shared_lock<std::shared_mutex> lock(mutex_); // 只读锁

    FILE *fp = fopen(config_.persistent_file.c_str(), "wb");
    if (!fp)
        return false;

    // 1. 保存 M 区
    size_t m_size = config_.memory_size;
    if (m_size > 0)
    {
        unsigned char *m_src = memory_pool_ + memory_offset_;
        fwrite(m_src, 1, m_size, fp);
    }

    // 2. 保存所有 DB 区（DB1 ~ DBn）
    size_t db_total_size = config_.db_count * config_.db_size;
    if (db_total_size > 0)
    {
        unsigned char *db_src = memory_pool_ + db_offset_;
        fwrite(db_src, 1, db_total_size, fp);
    }

    fclose(fp);
    return true;
}

bool PlcMemory::loadFromPersistentStorage()
{
    if (!config_.enable_persistence || !is_initialized_)
    {
        return false;
    }

    std::unique_lock<std::shared_mutex> lock(mutex_); // 写锁

    FILE *fp = fopen(config_.persistent_file.c_str(), "rb");
    if (!fp)
        return false;

    bool success = false;
    do
    {
        // 1. 加载 M 区
        size_t m_size = config_.memory_size;
        if (m_size > 0)
        {
            unsigned char *m_dst = memory_pool_ + memory_offset_;
            size_t read = fread(m_dst, 1, m_size, fp);
            if (read != m_size)
                break;
        }

        // 2. 加载 DB 区
        size_t db_total_size = config_.db_count * config_.db_size;
        if (db_total_size > 0)
        {
            unsigned char *db_dst = memory_pool_ + db_offset_;
            size_t read = fread(db_dst, 1, db_total_size, fp);
            if (read != db_total_size)
                break;
        }
        success = true;
    } while (false);

    fclose(fp);
    return success;
}

PlcConfig PlcMemory::getPlcConfig() const
{
    return config_;
}

unsigned char *PlcMemory::getAreaBase(MemoryArea area, int db_num) const
{
    switch (area)
    {
    case INPUT:
        return memory_pool_ + input_offset_;
    case OUTPUT:
        return memory_pool_ + output_offset_;
    case MEMORY:
        return memory_pool_ + memory_offset_;
    case DATA_BLOCK:
        if (db_num < 1 || static_cast<size_t>(db_num) > config_.db_count)
        {
            return nullptr;
        }
        return memory_pool_ + db_offset_ + (db_num - 1) * config_.db_size;
    default:
        return nullptr;
    }
}

bool PlcMemory::isValidAccess(MemoryArea area, int db_num, size_t offset, size_t size) const
{
    if (!is_initialized_ || !memory_pool_)
    {
        return false;
    }

    unsigned char *base = getAreaBase(area, db_num);
    if (!base)
    {
        return false;
    }

    size_t area_size = 0;
    switch (area)
    {
    case INPUT:
        area_size = config_.input_size;
        break;
    case OUTPUT:
        area_size = config_.output_size;
        break;
    case MEMORY:
        area_size = config_.memory_size;
        break;
    case DATA_BLOCK:
        area_size = config_.db_size;
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
