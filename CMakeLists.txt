# CMakeLists.txt (根目录)

cmake_minimum_required(VERSION 3.10)
project(mini_plc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(ANTLR4_DIR ${LIB_DIR}/antlr4)
set(SNAP7_DIR ${LIB_DIR}/snap7)
set(MODBUS_DIR ${LIB_DIR}/modbus)
set(JSON_DIR ${LIB_DIR})
set(GENERATED_DIR ${CMAKE_SOURCE_DIR}/generated)
set(FIRMWARE_DIR ${CMAKE_SOURCE_DIR}/firmware)

# 构建核心库
add_subdirectory(core)

# 构建测试
enable_testing()
add_subdirectory(test)