# 收集所有核心源码
file(GLOB_RECURSE CORE_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cu" # 如果未来支持
)
# 生成核心库
add_library(ditensor_core SHARED ${CORE_SOURCES})

# 显式声明包含路径，方便其他 target 链接时自动获取
target_include_directories(ditensor_core PUBLIC ${PROJECT_SOURCE_DIR}/include)

find_package(CUDAToolkit REQUIRED)
target_link_libraries(ditensor_core
    PRIVATE
        CUDA::cudart
)


