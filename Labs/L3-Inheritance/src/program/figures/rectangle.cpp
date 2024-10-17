#include "figures/rectangle.h"


Rectangle::Rectangle() { vertices.resize(4); }

Rectangle::Rectangle(const Rectangle& other) : Figure(other) {}

Rectangle::Rectangle(Rectangle&& other) noexcept : Figure(std::move(other)) {}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    Figure::operator=(other);
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}


std::pair<double, double> Rectangle::getCenter() const {
    double x = (vertices[0].first + vertices[1].first + vertices[2].first+ vertices[3].first) / 4;
    double y = (vertices[0].second + vertices[1].second + vertices[2].second + vertices[3].second) / 4;

    return {x, y};
}

Rectangle::operator double() const {
    // Ищем ширину. Так как координаты не отсортированы, нужно найти разные

    double width = std::abs(vertices[0].first -
        (vertices[1].first != vertices[0].first ? vertices[1].first : vertices[2].first));
    double height = std::abs(vertices[0].second -
        (vertices[1].second != vertices[0].second ? vertices[1].second : vertices[2].second));

    return width * height;
}

void Rectangle::print(std::ostream& os) const {
    os << "Rectangle:\n";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.first << ", " << vertex.second << ")\n";
    }
}

void Rectangle::read(std::istream& is) {
    vertices.clear();
    for (int i = 0; i < 4; ++i) {
        double x, y;
        is >> x >> y;
        vertices.emplace_back(x, y);
    }
}
Figure* Rectangle::clone() const {
    return new Rectangle(*this);
}


