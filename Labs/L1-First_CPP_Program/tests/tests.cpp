#include <gtest/gtest.h>
#include "../src/headers/counter.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(countOnes(2,7)==11);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}