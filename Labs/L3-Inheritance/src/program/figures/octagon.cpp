#include "figures/octagon.h"

Octagon::Octagon() { vertices.resize(8); }
Octagon::Octagon(const Octagon& other) : Figure(other) {}
Octagon::Octagon(Octagon&& other) noexcept : Figure(std::move(other)) {}

Octagon& Octagon::operator=(const Figure& other) {
    Figure::operator=(other);
    return *this;
}

Octagon& Octagon::operator=(Figure&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}

void Octagon::print(std::ostream& os) const {
    os << "Octagon:\n";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.x << ", " << vertex.y << ")\n";
    }
}

void Octagon::read(std::istream& is) {
    vertices.clear();
    for (int i = 0; i < 8; ++i) {
        double x, y;
        is >> x >> y;
        vertices.emplace_back(x, y);
    }
}

Octagon* Octagon::clone() const {
    return new Octagon(*this);
}