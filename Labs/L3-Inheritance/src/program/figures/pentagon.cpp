#include "figures/pentagon.h"

Pentagon::Pentagon() { vertices.resize(5); }
Pentagon::Pentagon(const Pentagon& other) : Figure(other) {}
Pentagon::Pentagon(Pentagon&& other) noexcept : Figure(std::move(other)) {}

Pentagon& Pentagon::operator=(const Figure& other) {
    Figure::operator=(other);
    return *this;
}

Pentagon& Pentagon::operator=(Figure&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}

void Pentagon::print(std::ostream& os) const {
    os << "Pentagon:\n";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.x << ", " << vertex.y << ")\n";
    }
}

void Pentagon::read(std::istream& is) {
    vertices.clear();
    for (int i = 0; i < 5; ++i) {
        double x, y;
        is >> x >> y;
        vertices.emplace_back(x, y);
    }
}

Pentagon* Pentagon::clone() const {
    return new Pentagon(*this);
}