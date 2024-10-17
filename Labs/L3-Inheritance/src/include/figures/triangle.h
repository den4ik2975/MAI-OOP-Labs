#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"

class Triangle : public Figure {
public:
    Triangle();
    Triangle(const Triangle& other);
    Triangle(Triangle&& other) noexcept;

    Triangle& operator=(const Figure& other) override;
    Triangle& operator=(Figure&& other) noexcept override;

    std::pair<double, double> getCenter() const override;
    explicit operator double() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Figure* clone() const override;
    // bool equals(const Figure* other) const override;
};

#endif // TRIANGLE_H
