# test/CMakeLists.txt
# 所有测试的总入口

cmake_minimum_required(VERSION 3.10)

# 添加单元测试
add_subdirectory(unit)
add_subdirectory(integration)