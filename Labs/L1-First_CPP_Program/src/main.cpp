#include <iostream>
#include "headers/counter.h"

int main() {
    long long a, b;
    std::cout << "Enter a:       ";
    std::cin >> a;
    std::cout << "Enter b:       ";
    std::cin >> b;



    std::cout << "The answer is: " << countOnes(a, b) << std::endl;
    return 0;
}