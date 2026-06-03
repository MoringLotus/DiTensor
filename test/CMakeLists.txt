file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(ditensor_test ${TEST_SOURCES})

# 链接核心库、gtest 主函数库和 gtest 核心库
target_link_libraries(ditensor_test 
    PRIVATE 
        ditensor_core
        gtest
        gtest_main
)

# 注册到 ctest
add_test(NAME ditensor_run_tests COMMAND ditensor_test)