#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <vector>
#include <algorithm>

class Point {
public:
    double x, y;

    explicit Point(double x = 0, double y = 0) : x(x), y(y) {}

    bool operator<(const Point& other) const {
        if (x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};



class Figure {
protected:
    std::vector<Point> vertices;

public:
    Figure() = default;
    Figure(const Figure& other) = default;
    Figure(Figure&& other) noexcept = default;
    virtual ~Figure() = default;

    // Подсчет центра не отличается
    virtual Point getCenter() const {
        double x = 0;
        double y = 0;

        for (auto vertice : vertices) {
            x += vertice.x;
            y += vertice.y;
        }

        return Point(x / vertices.size(), y / vertices.size());
    }

    // Так же как и подсчет площади (Теорема Гаусса)
    virtual explicit operator double() const {
        double area = 0.0;
        int j = vertices.size() - 1;

        for (int i = 0; i < vertices.size(); i++) {
            area += (vertices[j].x + vertices[i].x) * (vertices[j].y - vertices[i].y);
            j = i;
        }

        return std::abs(area / 2.0);
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure& figure){
        figure.print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure& figure){
        figure.read(is);
        return is;
    }

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    virtual Figure* clone() const = 0;

    virtual Figure& operator=(const Figure& other) = default;
    virtual Figure& operator=(Figure&& other) noexcept = default;
    virtual bool operator==(const Figure& other) const {
        if (typeid(*this) != typeid(other)) {
            return false;
        }
        const auto& otherFigure = static_cast<const Figure&>(other);
        if (vertices.size() != otherFigure.vertices.size()) {
            return false;
        }

        auto thisVertices = vertices;
        auto otherVertices = otherFigure.vertices;

        std::sort(thisVertices.begin(), thisVertices.end());
        std::sort(otherVertices.begin(), otherVertices.end());

        return thisVertices == otherVertices;
    }
};

#endif