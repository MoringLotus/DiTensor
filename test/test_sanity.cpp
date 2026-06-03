#include <gtest/gtest.h>

// 一个绝对会成功的测试
TEST(SanityCheck, TruePasses) {
    EXPECT_TRUE(true);
}

// 一个故意用来测试失败的用例（可选：验证完可以删掉或改成 true）
TEST(SanityCheck, QuickFail) {
    EXPECT_EQ(1 + 1, 2); 
}