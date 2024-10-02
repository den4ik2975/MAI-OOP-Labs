// decimal.cpp
#include "../include/decimal.h"
#include <algorithm>
#include <stdexcept>
#include <cstring>
#include <vector>

Decimal::Decimal() : length(1) {
    digits = new unsigned char[1];
    digits[0] = 0;
}


Decimal::Decimal(const size_t& n, unsigned char t) : length(n) {
    if (t > 9) throw std::invalid_argument("Digit must be between 0 and 9");
    digits = new unsigned char[length];
    std::fill_n(digits, length, t);
}


Decimal::Decimal(const std::initializer_list<unsigned char>& t) : length(t.size()) {
    digits = new unsigned char[length];
    std::vector<unsigned char> temp;
    temp.reserve(t.size());

    for (unsigned char it : t) {
        if (it > 9) throw std::invalid_argument("Digit must be between 0 and 9");
        temp.push_back(it);
    }

    std::reverse(temp.begin(), temp.end());

    for (size_t i = 0; i < temp.size(); ++i) {
        digits[i] = temp[i];
    }
}


Decimal::Decimal(const std::string& t) : length(t.length()) {
    digits = new unsigned char[length];
    for (size_t i = 0; i < length; ++i) {
        if (!std::isdigit(t[length - 1 - i])) throw std::invalid_argument("Invalid digit in string");
        digits[i] = t[length - 1 - i] - '0';
    }
}

Decimal::Decimal(const Decimal& other) : length(other.length) {
    digits = new unsigned char[length];
    std::memcpy(digits, other.digits, length * sizeof(unsigned char));
}

Decimal::Decimal(Decimal&& other) noexcept : digits(other.digits), length(other.length) {
    other.digits = nullptr;
    other.length = 0;
}

Decimal::~Decimal() noexcept {
    delete[] digits;
}

void Decimal::copy(const Decimal& other) {
    if (this != &other) {
        delete[] digits;
        length = other.length;
        digits = new unsigned char[length];
        // Ого, в cpp есть функция, которая срет мемами)
        std::memcpy(digits, other.digits, length * sizeof(unsigned char));
    }
}

void Decimal::move(Decimal&& other) noexcept {
    if (this != &other) {
        delete[] digits;
        digits = other.digits;
        length = other.length;
        other.digits = nullptr;
        other.length = 0;
    }
}

Decimal Decimal::add(const Decimal& other) const {
    size_t maxLength = std::max(length, other.length) + 1;
    Decimal result(maxLength, 0);

    unsigned char carry = 0;
    for (size_t i = 0; i < maxLength; ++i) {
        unsigned char sum = carry;
        if (i < length) sum += digits[i];
        if (i < other.length) sum += other.digits[i];

        result.digits[i] = sum % 10;
        carry = sum / 10;
    }

    while (result.length > 1 && result.digits[result.length - 1] == 0) {
        --result.length;
    }

    return result;
}

Decimal Decimal::subtract(const Decimal& other) const {
    if (isLessThan(other)) throw std::invalid_argument("Cannot subtract a larger number");

    Decimal result;
    result.copy(*this);

    for (size_t i = 0; i < other.length; ++i) {
        if (result.digits[i] < other.digits[i]) {
            size_t j = i + 1;
            while (j < result.length && result.digits[j] == 0) {
                result.digits[j] = 9;
                ++j;
            }
            if (j < result.length) {
                --result.digits[j];
            }
            result.digits[i] += 10;
        }
        result.digits[i] -= other.digits[i];
    }

    while (result.length > 1 && result.digits[result.length - 1] == 0) {
        --result.length;
    }

    return result;
}

bool Decimal::isGreaterThan(const Decimal& other) const {
    if (length != other.length) return length > other.length;
    for (size_t i = length; i-- > 0; ) {
        if (digits[i] != other.digits[i]) return digits[i] > other.digits[i];
    }
    return false;
}

bool Decimal::isLessThan(const Decimal& other) const {
    return other.isGreaterThan(*this);
}

bool Decimal::isEqualTo(const Decimal& other) const {
    if (length != other.length) return false;
    return std::memcmp(digits, other.digits, length * sizeof(unsigned char)) == 0;
}

void Decimal::addAssign(const Decimal& other) {
    Decimal result = this->add(other);
    this->move(std::move(result));
}

void Decimal::subtractAssign(const Decimal& other) {
    Decimal result = this->subtract(other);
    this->move(std::move(result));
}

size_t Decimal::size() const {
    return length;
}

std::string Decimal::toString() const {
    std::string result;
    for (size_t i = length; i-- > 0; ) {
        result += std::to_string(digits[i]);
    }
    return result;
}

