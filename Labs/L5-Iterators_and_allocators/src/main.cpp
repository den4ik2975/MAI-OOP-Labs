#include "memory_container.h"
#include <string>

struct ComplexType {
    int x;
    double y;
    std::string str;

    ComplexType(int x = 0, double y = 0.0, std::string str = "")
        : x(x), y(y), str(str) {}
};

int main() {
    // Creating resourse size of 1024 bytes
    fixed_memory_resource mem_resource(1024);

    // Test with simple type (int)
    {
        dynamic_array<int> arr(&mem_resource);

        std::cout << "Testing with int:\n";
        for (int i = 0; i < 5; ++i) {
            arr.push_back(i);
        }

        for (const auto& value : arr) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }

    // Test with complex type
    {
        dynamic_array<ComplexType> arr(&mem_resource);

        std::cout << "\nTesting with ComplexType:\n";
        arr.push_back({1, 1.1, "one"});
        arr.push_back({2, 2.2, "two"});

        for (const auto& value : arr) {
            std::cout << "x: " << value.x << ", y: " << value.y
                      << ", str: " << value.str << "\n";
        }
    }

    return 0;
}
