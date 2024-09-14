#include <iostream>
#include <cstdint>
#include "headers/counter.h"

int main() {
    int64_t a, b;
    std::cout << "Enter a: ";
    std::cin >> a;
    std::cout << "Enter b: ";
    std::cin >> b;

    std::cout << "The answer is: " << CountOnes(a, b) << std::endl;
    return 0;
}
