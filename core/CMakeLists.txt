# core/CMakeLists.txt
# 构建 mini-plc 的核心静态库 libcore.a

cmake_minimum_required(VERSION 3.10)
project(plc_core_library LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -O2 -g)
endif()

set(ANTLR4_GENERATED_SOURCES
    ${GENERATED_DIR}/st_grammarLexer.cpp
    ${GENERATED_DIR}/st_grammarParser.cpp
    ${GENERATED_DIR}/st_grammarBaseVisitor.cpp
    ${GENERATED_DIR}/st_grammarVisitor.cpp
    ${GENERATED_DIR}/st_grammarBaseListener.cpp
    ${GENERATED_DIR}/st_grammarListener.cpp
)

set(ANTLR4_GENERATED_HEADERS
    ${GENERATED_DIR}/st_grammarLexer.h
    ${GENERATED_DIR}/st_grammarParser.h
    ${GENERATED_DIR}/st_grammarBaseVisitor.h
    ${GENERATED_DIR}/st_grammarVisitor.h
    ${GENERATED_DIR}/st_grammarBaseListener.h
    ${GENERATED_DIR}/st_grammarListener.h
)

set(CORE_SOURCES
    memory/plc_memory.cpp
    comm/snap7_server.cpp
    st_compiler/compiler.cpp
    io_module/dev_manager.cpp
    io_module/dev_client.cpp
    io_module/modbus_client.cpp
    io_module/snap7_client.cpp
    ../lib/snap7/snap7.cpp
)

set(CORE_HEADERS
    # core_api.h
    memory/plc_memory.h
    comm/snap7_server.h
    st_compiler/compiler.h
    io_module/dev_manager.h
    io_module/dev_client.h
    io_module/modbus_client.h
    io_module/snap7_client.h
)

# --- 构建静态库 ---
add_library(core STATIC
    ${CORE_SOURCES}
    ${CORE_HEADERS}
    ${ANTLR4_GENERATED_SOURCES}
    ${ANTLR4_GENERATED_HEADERS}
)

# 包含头文件
target_include_directories(core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/memory>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/comm>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/io_module>
    $<BUILD_INTERFACE:${SNAP7_DIR}>
    $<BUILD_INTERFACE:${MODBUS_DIR}>
    $<BUILD_INTERFACE:${JSON_DIR}>
    $<BUILD_INTERFACE:${ANTLR4_DIR}/antlr4-runtime>
    $<BUILD_INTERFACE:${GENERATED_DIR}>
)

# 链接库
target_link_libraries(core PUBLIC
    ${SNAP7_DIR}/libsnap7.so
    ${MODBUS_DIR}/libmodbus.so
    ${ANTLR4_DIR}/libantlr4-runtime.so
    pthread
)
