#include "dev_manager.h"

#include <fstream>
#include <iostream>

using json = nlohmann::json;

static constexpr const char *KEY_DEVICE_LIST = "DeviceList";

static constexpr const char *KEY_ID = "Id";
static constexpr const char *KEY_NAME = "Name";
static constexpr const char *KEY_DESCR = "Descr";
static constexpr const char *KEY_BUS_TYPE = "BusType";

static constexpr const char *KEY_CONFIG = "Config";
static constexpr const char *KEY_IP_ADDRESS = "IPAddress";
static constexpr const char *KEY_PORT = "Port";
static constexpr const char *KEY_TIMEOUT_MS = "TimeoutMs";
static constexpr const char *KEY_MAX_RETRIES = "MaxRetries";
static constexpr const char *KEY_READ_BUFFER_SIZE = "ReadBufferSize";
static constexpr const char *KEY_WRITE_BUFFER_SIZE = "WriteBufferSize";
static constexpr const char *KEY_RACK = "Rack";
static constexpr const char *KEY_SLOT = "Slot";

static constexpr const char *KEY_BLOCK_LIST = "BlockList";
static constexpr const char *KEY_BLOCK_INDEX = "Index";
static constexpr const char *KEY_DB_NUMBER = "DBNumber";
static constexpr const char *KEY_OFFSET = "Offset";
static constexpr const char *KEY_SIZE = "Size";
static constexpr const char *KEY_READ_ONLY = "ReadOnly";
static constexpr const char *KEY_TYPE = "Type";
static constexpr const char *KEY_VARIABLE_LIST = "VariableList";

DevManager::DevManager()
{
}

DevManager::~DevManager()
{
    removeAll();
}

void DevManager::request(void)
{
    for (const auto &dev : devMap)
    {
        dev.second->readRequest();
        dev.second->writeRequest();
    }
}

void DevManager::response(void)
{
    for (const auto &dev : devMap)
    {
        dev.second->readResponse();
        dev.second->writeResponse();
    }
}

bool DevManager::addDevice(DevClient *client)
{
    if (devMap.find(client->name()) != devMap.end())
        return false;
    devMap.emplace(client->name(), client);
    return true;
}

std::vector<DevClient *> DevManager::deviceList()
{
    std::vector<DevClient *> list;
    list.reserve(devMap.size()); // 提前分配内存，提升性能

    for (const auto &pair : devMap)
    {
        list.push_back(pair.second);
    }

    return list;
}

DevClient *DevManager::inquireDevice(std::string devName, char **read, uint16_t *read_bytes, char **write, uint16_t *write_bytes)
{
    if (devMap.find(devName) == devMap.end())
        return nullptr;

    auto it = devMap.find(devName);
    auto dev = it->second;
    if (read != nullptr)
    {
        *read = static_cast<char *>(dev->readBuff());
    }
    if (write != nullptr)
    {
        *write = static_cast<char *>(dev->writeBuff());
    }
    if (read_bytes)
    {
        *read_bytes = dev->m_readBytes;
    }
    if (write_bytes)
    {
        *write_bytes = dev->m_writeBytes;
    }
    return dev;
}

bool DevManager::checkDeviceState(std::string devName)
{
    if (devMap.find(devName) == devMap.end())
        return false;

    auto it = devMap.find(devName);
    auto dev = it->second;
    if (dev->state() == DevClient::ConnectedState)
    {
        return true;
    }
    return false;
}

void DevManager::removeAll()
{
    auto it = devMap.begin();
    while (it != devMap.end())
    {
        delete it->second; // 释放指针内存
        it = devMap.erase(it);
    }
    devMap.clear();
}

void DevManager::readDeviceBlock(nlohmann::json &reader, DevClient::eBusType busType, sDeviceBlock &devBlock)
{
    devBlock.index = reader.value(KEY_BLOCK_INDEX, 0u);
    devBlock.dbNum = reader.value(KEY_DB_NUMBER, 0u);
    devBlock.offset = reader.value(KEY_OFFSET, 0u);
    devBlock.bytes = reader.value(KEY_SIZE, 0u);
    devBlock.bReadOnly = reader.value(KEY_READ_ONLY, true);

    std::string typeStr = reader.value(KEY_TYPE, "");
    if (busType == DevClient::MODBUS)
    {
        if (typeStr == "DiscreteInputs")
            devBlock.group = 1;
        else if (typeStr == "Coils")
            devBlock.group = 2;
        else if (typeStr == "InputRegister")
            devBlock.group = 3;
        else if (typeStr == "HoldingRegister")
            devBlock.group = 4;
        else
            devBlock.group = 0;
    }
    else if (busType == DevClient::SNAP7)
    {
        if (typeStr == "S7AreaPE")
            devBlock.group = 0x81;
        else if (typeStr == "S7AreaPA")
            devBlock.group = 0x82;
        else if (typeStr == "S7AreaMK")
            devBlock.group = 0x83;
        else if (typeStr == "S7AreaDB")
            devBlock.group = 0x84;
        else if (typeStr == "S7AreaCT")
            devBlock.group = 0x1C;
        else if (typeStr == "S7AreaTM")
            devBlock.group = 0x1D;
        else
            devBlock.group = 0;
    }

    if (reader.contains(KEY_VARIABLE_LIST) && reader[KEY_VARIABLE_LIST].is_array())
    {
        for (auto &item : reader[KEY_VARIABLE_LIST])
        {
            sDeviceItem var;
            readDeviceItem(item, var);
            devBlock.blockItemList.push_back(var);
        }
    }
}

void DevManager::writeDeviceBlock(nlohmann::json &writer, DevClient::eBusType busType, sDeviceBlock &devBlock)
{
    writer[KEY_BLOCK_INDEX] = devBlock.index;
    writer[KEY_DB_NUMBER] = devBlock.dbNum;
    writer[KEY_OFFSET] = devBlock.offset;
    writer[KEY_SIZE] = devBlock.bytes;
    writer[KEY_READ_ONLY] = devBlock.bReadOnly;

    std::string typeStr = "";
    if (busType == DevClient::MODBUS)
    {
        if (devBlock.group == 1)
            typeStr = "DiscreteInputs";
        else if (devBlock.group == 2)
            typeStr = "Coils";
        else if (devBlock.group == 3)
            typeStr = "InputRegister";
        else if (devBlock.group == 4)
            typeStr = "HoldingRegister";
        else
            typeStr = "Unknown";
    }
    else if (busType == DevClient::SNAP7)
    {
        switch (devBlock.group)
        {
        case 0x81:
            typeStr = "S7AreaPE";
            break;
        case 0x82:
            typeStr = "S7AreaPA";
            break;
        case 0x83:
            typeStr = "S7AreaMK";
            break;
        case 0x84:
            typeStr = "S7AreaDB";
            break;
        case 0x1C:
            typeStr = "S7AreaCT";
            break;
        case 0x1D:
            typeStr = "S7AreaTM";
            break;
        default:
            typeStr = "Unknown";
            break;
        }
    }
    writer[KEY_TYPE] = typeStr;

    if (!devBlock.blockItemList.empty())
    {
        json jVars = json::array();
        for (auto &item : devBlock.blockItemList)
        {
            json jItem;
            writeDeviceItem(jItem, item);
            jVars.push_back(jItem);
        }
        writer[KEY_VARIABLE_LIST] = jVars;
    }
}

void DevManager::readDeviceItem(nlohmann::json &reader, sDeviceItem &devItem)
{
    devItem.index = reader.value(KEY_BLOCK_INDEX, 0u);
    devItem.name = reader.value(KEY_NAME, "");
    devItem.bytes = reader.value(KEY_SIZE, 0u);
}

void DevManager::writeDeviceItem(nlohmann::json &writer, sDeviceItem &devItem)
{
    writer[KEY_BLOCK_INDEX] = devItem.index;
    writer[KEY_NAME] = devItem.name;
    writer[KEY_SIZE] = devItem.bytes;
}

DevClient::eBusType DevManager::stringToBusType(const std::string &type)
{
    if (type == "MODBUS")
        return DevClient::MODBUS;
    if (type == "SNAP7")
        return DevClient::SNAP7;
    return DevClient::INVALID;
}

std::string DevManager::busTypeToString(DevClient::eBusType type)
{
    switch (type)
    {
    case DevClient::MODBUS:
        return "MODBUS";
    case DevClient::SNAP7:
        return "SNAP7";
    default:
        return "INVALID";
    }
}

bool DevManager::load(const std::string fileName, tDeviceNodeList &deviceNodeList)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open config file " << fileName << std::endl;
        return false;
    }

    json j;
    try
    {
        file >> j;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: Failed to parse JSON: " << e.what() << std::endl;
        return false;
    }

    deviceNodeList.clear();

    if (!j.contains(KEY_DEVICE_LIST) || !j[KEY_DEVICE_LIST].is_array())
    {
        std::cerr << "Error: Invalid format, '" << KEY_DEVICE_LIST << "' missing or not array." << std::endl;
        return false;
    }

    for (auto &jDev : j[KEY_DEVICE_LIST])
    {
        sDeviceNode node{};
        node.id = jDev.value(KEY_ID, 0u);
        node.name = jDev.value(KEY_NAME, "Unknown");
        node.descr = jDev.value(KEY_DESCR, "");

        std::string busTypeStr = jDev.value(KEY_BUS_TYPE, "INVALID");
        node.busType = stringToBusType(busTypeStr);
        if (node.busType == DevClient::INVALID)
        {
            std::cerr << "Warning: Unknown BusType '" << busTypeStr << "' for device Id=" << node.id << std::endl;
            continue;
        }

        auto &cfg = jDev[KEY_CONFIG];
        node.ipAddress = cfg.value(KEY_IP_ADDRESS, "127.0.0.1");
        node.port = cfg.value(KEY_PORT, 502);
        node.timeout = cfg.value(KEY_TIMEOUT_MS, 3000);
        node.retry = cfg.value(KEY_MAX_RETRIES, 3);
        node.readBytes = cfg.value(KEY_READ_BUFFER_SIZE, 750);
        node.writeBytes = cfg.value(KEY_WRITE_BUFFER_SIZE, 246);
        node.rack = cfg.value(KEY_RACK, 0);
        node.slot = cfg.value(KEY_SLOT, 1);

        if (jDev.contains(KEY_BLOCK_LIST) && jDev[KEY_BLOCK_LIST].is_array())
        {
            for (auto &jBlock : jDev[KEY_BLOCK_LIST])
            {
                sDeviceBlock block;
                readDeviceBlock(jBlock, node.busType, block);

                if (block.bReadOnly)
                    node.blockListRead.push_back(block);
                else
                    node.blockListWrite.push_back(block);
            }
        }

        deviceNodeList.push_back(node);
    }

    return true;
}

bool DevManager::save(const std::string fileName, tDeviceNodeList &deviceNodeList)
{
    json j;

    json jDevices = json::array();
    for (auto &node : deviceNodeList)
    {
        json jDev;

        jDev[KEY_ID] = node.id;
        jDev[KEY_NAME] = node.name;
        jDev[KEY_DESCR] = node.descr;
        jDev[KEY_BUS_TYPE] = busTypeToString(node.busType);

        json cfg;
        cfg[KEY_IP_ADDRESS] = node.ipAddress;
        cfg[KEY_PORT] = node.port;
        cfg[KEY_TIMEOUT_MS] = node.timeout;
        cfg[KEY_MAX_RETRIES] = node.retry;
        cfg[KEY_READ_BUFFER_SIZE] = node.readBytes;
        cfg[KEY_WRITE_BUFFER_SIZE] = node.writeBytes;
        cfg[KEY_RACK] = node.rack;
        cfg[KEY_SLOT] = node.slot;
        jDev[KEY_CONFIG] = cfg;

        json jBlocks = json::array();
        for (auto &block : node.blockListRead)
        {
            json jBlock;
            writeDeviceBlock(jBlock, node.busType, block);
            jBlocks.push_back(jBlock);
        }
        for (auto &block : node.blockListWrite)
        {
            json jBlock;
            writeDeviceBlock(jBlock, node.busType, block);
            jBlock[KEY_READ_ONLY] = false;
            jBlocks.push_back(jBlock);
        }
        jDev[KEY_BLOCK_LIST] = jBlocks;

        jDevices.push_back(jDev);
    }

    j[KEY_DEVICE_LIST] = jDevices;

    std::ofstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot create file " << fileName << std::endl;
        return false;
    }

    file << j.dump(4);
    file.close();

    return true;
}
