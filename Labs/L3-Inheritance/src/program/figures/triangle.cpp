#include <iostream>
#include <vector>
#include <cmath>
#include "figures/triangle.h"


Triangle::Triangle() { vertices.resize(3); }
Triangle::Triangle(const Triangle& other) : Figure(other) {}
Triangle::Triangle(Triangle&& other) noexcept : Figure(std::move(other)) {}

Triangle& Triangle::operator=(const Figure& other) {
    Figure::operator=(other);
    return *this;
}
Triangle& Triangle::operator=(Figure&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}

std::pair<double, double> Triangle::getCenter() const {
    double x = (vertices[0].first + vertices[1].first + vertices[2].first) / 3;
    double y = (vertices[0].second + vertices[1].second + vertices[2].second) / 3;
    return {x, y};
}

Triangle::operator double() const {
    // Используем детерминант

    double a = vertices[0].first * (vertices[1].second - vertices[2].second);
    double b = vertices[1].first * (vertices[2].second - vertices[0].second);
    double c = vertices[2].first * (vertices[0].second - vertices[1].second);

    double s = std::abs((a + b + c) / 2);

    return s;
}

void Triangle::print(std::ostream& os) const {
    os << "Triangle:\n";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.first << ", " << vertex.second << ")\n";
    }
}


void Triangle::read(std::istream& is) {
    vertices.clear();
    for (int i = 0; i < 3; ++i) {
        double x, y;
        is >> x >> y;
        vertices.emplace_back(x, y);
    }
}


Figure* Triangle::clone() const {
    return new Triangle(*this);
}



