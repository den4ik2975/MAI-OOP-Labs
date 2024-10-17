#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <vector>
#include <algorithm>

class Figure {
protected:
    std::vector<std::pair<double, double>> vertices;

public:
    Figure() = default;
    Figure(const Figure& other) = default;
    Figure(Figure&& other) noexcept = default;
    virtual ~Figure() = default;

    virtual std::pair<double, double> getCenter() const = 0;
    virtual explicit operator double() const = 0;

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

        // Создаем копии векторов вершин для сортировки
        auto thisVertices = vertices;
        auto otherVertices = otherFigure.vertices;

        // Сортируем вершины
        std::sort(thisVertices.begin(), thisVertices.end());
        std::sort(otherVertices.begin(), otherVertices.end());

        // Сравниваем отсортированные вершины
        return thisVertices == otherVertices;
    }
};

#endif