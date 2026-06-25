include(FetchContent)

# ===== GoogleTest =====
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

# 防止 gtest 自己改 CMAKE_CXX_STANDARD
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
