# CMake 最低版本号要求
cmake_minimum_required(VERSION 2.8)

# 项目信息
set(GLOB_PRONAME "w21Demons")
set(GLOB_EXECNAME ${GLOB_PRONAME}_exp)
project(GLOB_PRONAME)
set(APP_VERSION_MAJOR 1)
set(APP_VERSION_MINOR 00)

# 运行平台参数设置
set(SYSROOT_LIB_DIRNAME     lib)
set(SYSROOT_BIN_DIRNAME     bin)
set(SYSROOT_TOOLS_DIRNAME   tools)
set(SYSROOT_DIRNAME         target)
set(SYSROOT_DIR             ${CMAKE_BINARY_DIR}/${SYSROOT_DIRNAME})         # 编译结果对应到运行平台的根文件路径

# 设置编译参数
#set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_BUILD_TYPE "Release")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-D_DEBUG)
endif()

# 设置编译工具链
set(COMPILER_PREFIX "")
set(CMAKE_C_COMPILER ${COMPILER_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${COMPILER_PREFIX}g++)

# 加入配置文件 用于处理 CMake 对源码的设置
configure_file("${PROJECT_SOURCE_DIR}/source/config.h.in" "${PROJECT_BINARY_DIR}/source/config.h")

# 设置头文件
include_directories(
    ${CMAKE_BINARY_DIR}/source/
	${CMAKE_SOURCE_DIR}/include/
    ${CMAKE_SOURCE_DIR}/source/
    ${CMAKE_SOURCE_DIR}/example/controller/
)

# 添加子目录
add_subdirectory(example)
