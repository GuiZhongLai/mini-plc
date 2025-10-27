#ifndef PLC_MEMORY_H
#define PLC_MEMORY_H

#include <cstddef>
#include <string>
#include <shared_mutex>

// 内存区域
enum MemoryArea
{
    INPUT,     // %I
    OUTPUT,    // %Q
    MEMORY,    // %M
    DATA_BLOCK // DB
};

// 数据宽度（用于地址解析）
enum DataWidth
{
    BIT,
    BYTE,
    WORD, // 2 字节
    DWORD // 4 字节
};

// 地址结构
struct PlcAddress
{
    MemoryArea area; // 区域
    int db_number;   // DB 编号（默认1）
    size_t offset;   // 字节偏移
    int bit;         // 位偏移，-1 表示不是位访问
    DataWidth width; // 访问宽度
};

// 配置结构
struct PlcConfig
{
    size_t input_size;
    size_t output_size;
    size_t memory_size;
    size_t db_count;
    size_t db_size;
    std::string persistent_file;
    bool enable_persistence;

    PlcConfig()
        : input_size(128), output_size(128), memory_size(512), db_count(16), db_size(1024), persistent_file("./plc_persistent.bin"), enable_persistence(true)
    {
    }
};

class PlcMemory
{
public:
    explicit PlcMemory(const PlcConfig &config);
    ~PlcMemory();

    // 禁止拷贝
    PlcMemory(const PlcMemory &) = delete;
    PlcMemory &operator=(const PlcMemory &) = delete;

    /**
     * @brief 初始化内存（分配堆空间）
     * @return 成功返回 true
     */
    bool initialize();

    /**
     * @brief 清理内存
     */
    void cleanup();

    /**
     * @brief 解析字符串地址，如 "%IX0.1", "%IB4", "%QW6", "%MD12", "%DB1.DBD4"
     * @param addr_str 输入字符串
     * @param addr 输出地址结构
     * @return 是否解析成功
     */
    bool parseAddress(const std::string &addr_str, PlcAddress &addr);

    /**
     * @brief 读取位
     * @param area 区域
     * @param db_num DB编号（仅DB区）
     * @param byte_offset 字节偏移
     * @param bit_offset 位偏移 (0-7)
     * @param value 读出的值
     * @return 是否成功
     */
    bool readBit(MemoryArea area, int db_num, size_t byte_offset, int bit_offset, bool &value);

    /**
     * @brief 写入位
     */
    bool writeBit(MemoryArea area, int db_num, size_t byte_offset, int bit_offset, bool value);

    /**
     * @brief 读取多个字节
     * @param area 区域
     * @param db_num DB编号
     * @param start_offset 起始字节偏移
     * @param size 读取字节数
     * @param buffer 输出缓冲区
     * @return 是否成功
     */
    bool readBytes(MemoryArea area, int db_num, size_t start_offset, size_t size, void *buffer);

    /**
     * @brief 写入多个字节
     */
    bool writeBytes(MemoryArea area, int db_num, size_t start_offset, size_t size, const void *buffer);

    /**
     * @brief 读取一个字节
     */
    bool readByte(MemoryArea area, int db_num, size_t offset, uint8_t &value);

    /**
     * @brief 写入一个字节
     */
    bool writeByte(MemoryArea area, int db_num, size_t offset, uint8_t value);

    /**
     * @brief 读取一个字（2字节）
     */
    bool readWord(MemoryArea area, int db_num, size_t offset, uint16_t &value);

    /**
     * @brief 写入一个字
     */
    bool writeWord(MemoryArea area, int db_num, size_t offset, uint16_t value);

    /**
     * @brief 读取双字（4字节）
     */
    bool readDWord(MemoryArea area, int db_num, size_t offset, uint32_t &value);

    /**
     * @brief 写入双字
     */
    bool writeDWord(MemoryArea area, int db_num, size_t offset, uint32_t value);

    /**
     * @brief 获取区域大小
     */
    size_t getAreaSize(MemoryArea area) const;

    /**
     * @brief 保存到持久化文件（掉电保持）
     */
    bool saveToPersistentStorage();

    /**
     * @brief 从持久化文件加载
     */
    bool loadFromPersistentStorage();

    /**
     * @brief 获取配置项
     */
    PlcConfig getPlcConfig() const;

    /**
     * @brief 获取基地址指针
     */
    unsigned char *getAreaBase(MemoryArea area, int db_num) const;

private:
    PlcConfig config_;

    unsigned char *memory_pool_; // 整块内存池
    bool is_initialized_;

    // 各区域偏移
    size_t input_offset_;
    size_t output_offset_;
    size_t memory_offset_;
    size_t db_offset_;

    // 读写锁，共享读，独占写
    mutable std::shared_mutex mutex_;

    /**
     * @brief 检查范围是否有效
     */
    bool isValidAccess(MemoryArea area, int db_num, size_t offset, size_t size) const;

    bool parseGlobalAddress(const std::string &str, size_t &pos, PlcAddress &addr);
    bool parseDBAddress(const std::string &str, size_t &pos, PlcAddress &addr);
    bool parseOffsetAndBit(const std::string &str, size_t &pos, PlcAddress &addr);
};

#endif // PLC_MEMORY_H