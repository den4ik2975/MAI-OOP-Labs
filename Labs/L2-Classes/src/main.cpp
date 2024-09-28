#include <iostream>
#include <string>
#include <iomanip>
#include "include/decimal.h"

Decimal getDecimalInput(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        try {
            return Decimal(input);
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input. Please enter a valid decimal number." << '\n';
        }
    }
}

int main() {
    while (true) {
        std::cout << "Enter two Decimal values" << '\n';
        Decimal a = getDecimalInput("First Decimal: ");
        Decimal b = getDecimalInput("Second Decimal: ");

        std::cout << "\nOperations:\n";
        std::cout << "──────────────────────────────────────────────────────────" << '\n';

        const int fieldWidth = 50;
        // Addition
        std::cout << "a + b = " << std::right << std::setw(fieldWidth) << a.add(b).toString() << '\n';
        std::cout << "──────────────────────────────────────────────────────────" << '\n';

        // Subtraction
        try {
            std::string res = a.subtract(b).toString();
            std::cout << "a - b = " << std::right << std::setw(fieldWidth) << res << '\n';
        } catch (const std::invalid_argument& e) {
            std::cout << "a - b: " << std::right << std::setw(fieldWidth + 1) << e.what() << '\n';
        }

        try {
            std::string res = b.subtract(a).toString();
            std::cout << "b - a = " << std::right << std::setw(fieldWidth) << res << '\n';
        } catch (const std::invalid_argument& e) {
            std::cout << "b - a: " << std::right << std::setw(fieldWidth + 1) << e.what() << '\n';
        }
        std::cout << "──────────────────────────────────────────────────────────" << '\n';

        // Comparison
        std::cout << "a > b: " << std::right << std::setw(fieldWidth + 1) << (a.isGreaterThan(b) ? "true" : "false") << '\n';
        std::cout << "a < b: " << std::right << std::setw(fieldWidth + 1) << (a.isLessThan(b) ? "true" : "false") << '\n';
        std::cout << "a == b: " << std::right << std::setw(fieldWidth) << (a.isEqualTo(b) ? "true" : "false") << '\n';
        std::cout << "──────────────────────────────────────────────────────────" << '\n';

        // Addition assignment
        Decimal c = a;
        c.addAssign(b);
        std::cout << "c = a; c += b; c = " << std::right << std::setw(fieldWidth - 11) << c.toString() << '\n';

        // Subtraction assignment
        Decimal d = a;
        try {
            d.subtractAssign(b);
            std::cout << "d = a; d -= b; d = " << std::right << std::setw(fieldWidth - 11) << d.toString() << '\n';
        } catch (const std::invalid_argument& e) {
            std::cout << "d = a; d -= b: " << std::right << std::setw(fieldWidth - 7) << e.what() << '\n';
        }
        std::cout << "──────────────────────────────────────────────────────────" << '\n';

        // Size
        std::cout << "Size of a: " << std::right << std::setw(fieldWidth - 3) << a.size() << '\n';
        std::cout << "Size of b: " << std::right << std::setw(fieldWidth - 3) << b.size()  <<  '\n';
        std::cout << "──────────────────────────────────────────────────────────" << '\n';

        // Ask if the user wants to continue
        std::string continue_input;
        std::cout << "\nDo you want to continue? (y/n): ";
        std::getline(std::cin, continue_input);
        if (continue_input != "y" && continue_input != "Y") {
            break;
        }
        std::cout << '\n';
    }

    return 0;
}
