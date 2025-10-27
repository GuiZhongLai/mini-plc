#ifndef DEV_MANAGER_H
#define DEV_MANAGER_H

#include "dev_client.h"
#include <map>
#include <nlohmann/json.hpp>

struct sDeviceItem
{
    uint32_t index = 0;    // 变量索引
    std::string name = ""; // 变量名称
    uint32_t bytes = 0;    // 变量占用的内存大小，单位为byte
};

struct sDeviceBlock
{
    uint32_t index = 0;    // 块索引号
    uint32_t dbNum = 0;    // db块编号
    uint32_t offset = 0;   // 设备访问块的内存偏移地址
    uint32_t bytes = 0;    // 设备访问块的内存大小，单位byte
    uint32_t group = 0;    // 设备访问块的寄存器
    bool bReadOnly = true; // 设备访问块的读/写标识

    std::vector<sDeviceItem> blockItemList; // 变量列表
};

struct sDeviceNode
{
    uint32_t id = 0;                                  // 设备唯一Id
    DevClient::eBusType busType = DevClient::INVALID; // 总线类型
    std::string name = "Example";                     // 设备名称
    std::string descr = "";                           // 设备描述
    std::string ipAddress = "192.168.1.1";            // 设备IP地址
    int port = 502;                                   // 设备端口
    int readBytes = 0;                                // 设备读缓冲区大小
    int writeBytes = 0;                               // 设备写缓冲区大小
    int timeout = 1000;                               // 连接设备超时事件
    int retry = 3;                                    // 重连次数
    int rack = 0;                                     // 机架号
    int slot = 1;                                     // 槽

    std::vector<sDeviceBlock> blockListRead;  // 设备读操作的块集合，等同于DevRequest
    std::vector<sDeviceBlock> blockListWrite; // 设备写操作的块集合，等同于DevRequest
};

typedef std::vector<sDeviceNode> tDeviceNodeList;

class DevManager
{
public:
    DevManager();
    ~DevManager();

private:
    std::map<std::string, DevClient *> devMap;

public:
    void request(void);
    void response(void);

    bool addDevice(DevClient *);
    std::vector<DevClient *> deviceList();

    DevClient *inquireDevice(std::string devName,
                             char **read,
                             uint16_t *read_bytes,
                             char **write,
                             uint16_t *write_bytes);

    bool checkDeviceState(std::string devName);

    void removeAll();

    // 配置加载和保存
private:
    void readDeviceBlock(nlohmann::json &reader, DevClient::eBusType busType, sDeviceBlock &devBlock);
    void writeDeviceBlock(nlohmann::json &writer, DevClient::eBusType busType, sDeviceBlock &devBlock);
    void readDeviceItem(nlohmann::json &reader, sDeviceItem &devItem);
    void writeDeviceItem(nlohmann::json &writer, sDeviceItem &devItem);

    DevClient::eBusType stringToBusType(const std::string &type);
    std::string busTypeToString(DevClient::eBusType type);

public:
    bool load(const std::string fileName, tDeviceNodeList &deviceNodeList);
    bool save(const std::string fileName, tDeviceNodeList &deviceNodeList);
};

#endif