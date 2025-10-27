cmake_minimum_required(VERSION 3.10)

# 查找 gtest
find_package(GTest REQUIRED)

set(INTEGRATION_TEST_SOURCES
     test_st_compiler.cpp
)

# 添加集成测试可执行文件
add_executable(test_integration ${INTEGRATION_TEST_SOURCES})

# 包含路径
target_include_directories(test_integration PRIVATE
    $<BUILD_INTERFACE:${SNAP7_DIR}>
    $<BUILD_INTERFACE:${MODBUS_DIR}>
    $<BUILD_INTERFACE:${ANTLR4_DIR}/antlr4-runtime>
    $<BUILD_INTERFACE:${GENERATED_DIR}>
    $<BUILD_INTERFACE:${FIRMWARE_DIR}>
)

# 链接
target_link_libraries(test_integration
    PRIVATE 
    GTest::gtest 
    GTest::gtest_main 
    core
    pthread
)