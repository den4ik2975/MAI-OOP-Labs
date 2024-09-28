#include <gtest/gtest.h>
#include "../src/include/decimal.h"

TEST(DecimalTest, Constructor) {
    Decimal a;
    EXPECT_EQ(a.toString(), "0");

    Decimal b(5, 3);
    EXPECT_EQ(b.toString(), "33333");

    Decimal c({1, 2, 3, 4, 5});
    EXPECT_EQ(c.toString(), "12345");

    Decimal d("67890");
    EXPECT_EQ(d.toString(), "67890");
}

TEST(DecimalTest, Addition) {
    Decimal a({1, 2, 3, 4, 5});
    Decimal b("67890");
    Decimal c = a.add(b);
    EXPECT_EQ(c.toString(), "80235");

    Decimal d({1, 2, 3, 4, 5});
    Decimal e("67890");
    d.addAssign(e);
    EXPECT_EQ(d.toString(), "80235");
}

TEST(DecimalTest, Subtraction) {
    Decimal a("67890");
    Decimal b({1, 2, 3, 4, 5});
    Decimal c = a.subtract(b);
    EXPECT_EQ(c.toString(), "55545");

    Decimal a1("1000000");
    Decimal b1("1");
    Decimal c1 = a1.subtract(b1);
    EXPECT_EQ(c1.toString(), "999999");

    Decimal d("67890");
    Decimal e({1, 2, 3, 4, 5});
    d.subtractAssign(e);
    EXPECT_EQ(d.toString(), "55545");
}

TEST(DecimalTest, Comparison) {
    Decimal a({1, 2, 3, 4, 5});
    Decimal b("67890");
    EXPECT_TRUE(a.isLessThan(b));
    EXPECT_FALSE(a.isGreaterThan(b));
    EXPECT_FALSE(a.isEqualTo(b));

    Decimal a1("555");
    Decimal b1("555");
    EXPECT_FALSE(a1.isLessThan(b1));
    EXPECT_FALSE(a1.isGreaterThan(b1));
    EXPECT_TRUE(a1.isEqualTo(b1));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
