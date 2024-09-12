#include <gtest/gtest.h>
#include "../src/headers/counter.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(countOnes(2,7)==11);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(countOnes(0,0)==0);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(countOnes(7,7)==3);
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(countOnes(8,8)==1);
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(countOnes(0,63)==192);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}