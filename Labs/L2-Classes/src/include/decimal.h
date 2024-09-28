// decimal.h
#ifndef DECIMAL_H
#define DECIMAL_H

#include <cstddef>
#include <initializer_list>
#include <string>

class Decimal {
public:
    Decimal();
    Decimal(const size_t& n, unsigned char t = 0);
    Decimal(const std::initializer_list<unsigned char>& t);
    Decimal(const std::string& t);
    Decimal(const Decimal& other);
    Decimal(Decimal&& other) noexcept;
    virtual ~Decimal() noexcept;

    // Арифметические операции
    Decimal add(const Decimal& other) const;
    Decimal subtract(const Decimal& other) const;

    // Операции сравнения
    bool isGreaterThan(const Decimal& other) const;
    bool isLessThan(const Decimal& other) const;
    bool isEqualTo(const Decimal& other) const;

    // Арифметические операции с присваиванием
    void addAssign(const Decimal& other);
    void subtractAssign(const Decimal& other);

    // Вспомогательные методы
    size_t size() const;
    std::string toString() const;

private:
    unsigned char* digits;
    size_t capacity;
    size_t length;

    // Короче я хз можно ли использовать конструкторы для copy и move, поэтому написал функции на всякий случай
    void resize(size_t newCapacity);
    void copy(const Decimal& other);
    void move(Decimal&& other) noexcept;
};

#endif // DECIMAL_H
