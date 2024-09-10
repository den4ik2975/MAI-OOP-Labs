#include <iostream>
#include "headers/counter.h"

int main() {
    long long a, b;
    std::cout << "enter a: ";
    std::cin >> a;
    std::cout << "enter b: ";
    std::cin >> b;



    std::cout << countOnes(a, b) << std::endl;
    return 0;
}