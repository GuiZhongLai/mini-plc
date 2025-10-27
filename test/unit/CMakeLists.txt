# test/unit/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# 查找 gtest
find_package(GTest REQUIRED)

# 设置测试源文件
set(UNIT_TEST_SOURCES
    test_plc_memory.cpp
    test_snap7_server.cpp
    test_io_module_client.cpp
    # 后续添加其他测试文件
)

# 只创建一个测试可执行文件
add_executable(test_unit ${UNIT_TEST_SOURCES})

# 定义外部库路径
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(SNAP7_DIR ${LIB_DIR}/snap7)
set(MODBUS_DIR ${LIB_DIR}/modbus)
set(ANTLR4_DIR ${LIB_DIR}/antlr4)
# 包含头文件路径
target_include_directories(test_unit PRIVATE
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/core/memory
    ${CMAKE_SOURCE_DIR}/core/comm
    ${SNAP7_DIR}
    ${MODBUS_DIR}
    ${ANTLR4_DIR}/antlr4-runtime
    ${GTEST_INCLUDE_DIRS}
)
# 添加库目录
target_link_directories(test_unit PRIVATE
    ${SNAP7_DIR}
    ${MODBUS_DIR}
    ${ANTLR4_DIR}
)
# 链接所有需要的库 - 使用完整路径
target_link_libraries(test_unit 
    PRIVATE 
    GTest::gtest 
    GTest::gtest_main 
    core
    ${SNAP7_DIR}/libsnap7.so
    ${MODBUS_DIR}/libmodbus.so
    ${ANTLR4_DIR}/libantlr4-runtime.so
    pthread
)