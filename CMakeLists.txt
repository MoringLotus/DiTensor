cmake_minimum_required(VERSION 3.14)
project(DiTensor LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(CUDAToolkit REQUIRED)

# ===== 核心库 =====
include_directories(/usr/local/cuda/include)
add_subdirectory(csrc)
# 🛠️ 不管什么 target，全项目所有 cpp 统统强制注入 CUDA 头文件路径


# ===== 测试 =====
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    add_subdirectory(third_party/googletest)
    enable_testing()
    add_subdirectory(test)
endif()
