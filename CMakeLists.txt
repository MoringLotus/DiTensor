cmake_minimum_required(VERSION 3.18)
project(DiTensor VERSION 0.1.0 LANGUAGES CXX C)

# 编译选项设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 开启核心库和测试的开关
option(BUILD_TESTS "Build DiTensor tests" ON)

# --- 1. 引入 Google Test (FetchContent 方式) ---
if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/heads/main.zip
    )
    # 对于 Windows/MSVC 建议设置, Linux/macOS 忽略
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# --- 2. 包含子目录 ---
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(csrc)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()