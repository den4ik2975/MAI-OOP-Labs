#include <gtest/gtest.h>
#include "memory_container.h"

// Test struct
struct TestStruct {
    int x;
    double y;
    std::string str;

    TestStruct(int x_ = 0, double y_ = 0.0, std::string str_ = "")
        : x(x_), y(y_), str(str_) {}

    bool operator==(const TestStruct& other) const {
        return x == other.x && y == other.y && str == other.str;
    }
};

// Test with simple types (int)
TEST(DynamicArrayTest, IntegerOperations) {
    fixed_memory_resource memResource(1024);
    dynamic_array<int> arr(&memResource);

    EXPECT_EQ(arr.size(), 0);

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    EXPECT_EQ(arr.size(), 3);

    auto it = arr.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
}

// Test with complex type/struct
TEST(DynamicArrayTest, CustomStructOperations) {
    fixed_memory_resource memResource(2048);
    dynamic_array<TestStruct> arr(&memResource);

    arr.push_back(TestStruct(1, 1.1, "one"));
    arr.push_back(TestStruct(2, 2.2, "two"));

    EXPECT_EQ(arr.size(), 2);

    auto it = arr.begin();
    EXPECT_EQ(it->x, 1);
    EXPECT_EQ(it->y, 1.1);
    EXPECT_EQ(it->str, "one");
}

// Test for memory_resource
TEST(MemoryResourceTest, AllocationDeallocation) {
    fixed_memory_resource memResource(1024);

    void* p1 = memResource.allocate(256, alignof(std::max_align_t));
    EXPECT_NE(p1, nullptr);

    void* p2 = memResource.allocate(256, alignof(std::max_align_t));
    EXPECT_NE(p2, nullptr);

    memResource.deallocate(p1, 256, alignof(std::max_align_t));
    memResource.deallocate(p2, 256, alignof(std::max_align_t));

    // Checking if we can allocate memory again
    void* p3 = memResource.allocate(512, alignof(std::max_align_t));
    EXPECT_NE(p3, nullptr);
}

// Test for iterators
TEST(IteratorTest, BasicOperations) {
    fixed_memory_resource memResource(1024);
    dynamic_array<int> arr(&memResource);

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    // Test operator++
    auto it = arr.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    it++;
    EXPECT_EQ(*it, 3);

    // Test comparing iterators
    EXPECT_TRUE(arr.begin() != arr.end());
    EXPECT_TRUE(it != arr.begin());
}

// Test for edge cases
TEST(DynamicArrayTest, EdgeCases) {
    fixed_memory_resource memResource(64);
    dynamic_array<int> arr(&memResource);

    // Empty array test
    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.begin() == arr.end());

    // Tests pop_back() on empty array
    arr.pop_back();

    // Test allocate more memory than available
    EXPECT_THROW({
        for(int i = 0; i < 1000; ++i) {
            arr.push_back(i);
        }
    }, std::bad_alloc);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
