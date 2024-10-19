#include "figures/hexagon.h"

Hexagon::Hexagon() { vertices.resize(6); }
Hexagon::Hexagon(const Hexagon& other) : Figure(other) {}
Hexagon::Hexagon(Hexagon&& other) noexcept : Figure(std::move(other)) {}

Hexagon& Hexagon::operator=(const Figure& other) {
    Figure::operator=(other);
    return *this;
}

Hexagon& Hexagon::operator=(Figure&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}

void Hexagon::print(std::ostream& os) const {
    os << "Hexagon:\n";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.x << ", " << vertex.y << ")\n";
    }
}

void Hexagon::read(std::istream& is) {
    vertices.clear();
    for (int i = 0; i < 6; ++i) {
        double x, y;
        is >> x >> y;
        vertices.emplace_back(x, y);
    }
}

Figure* Hexagon::clone() const {
    return new Hexagon(*this);
}