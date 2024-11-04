// figure.h
#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>

#include "../point.h"

template<Scalar T>
class Figure {
protected:
    std::vector<std::unique_ptr<Point<T>>> vertices_;
    std::unique_ptr<Point<T>> center_;

public:
    Figure() : center_(std::make_unique<Point<T>>()) {}
    virtual ~Figure() = default;

    // Add new accessor methods
    size_t get_vertices_count() const {
        return vertices_.size();
    }

    Point<T> get_vertex(size_t index) const {
        if (index >= vertices_.size()) {
            throw std::out_of_range("Vertex index out of range");
        }
        return *vertices_[index];
    }

    Point<T> get_center() const {
        T x = 0, y = 0;
        for (const auto& vertex : vertices_) {
            x += vertex->get_x();
            y += vertex->get_y();
        }
        auto center_x = x / vertices_.size();
        auto center_y = y / vertices_.size();
        return Point<T>(std::round(center_x * 100000.0) / 100000.0, std::round(center_y * 100000.0) / 100000.0);
    }

    virtual explicit operator double() const {
        double area = 0.0;
        int j = vertices_.size() - 1;

        for (size_t i = 0; i < vertices_.size(); i++) {
            area += (vertices_[j]->get_x() + vertices_[i]->get_x()) *
                    (vertices_[j]->get_y() - vertices_[i]->get_y());
            j = i;
        }
        return std::abs(area / 2.0);
    }

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    virtual bool operator==(const Figure& other) const {
        if (typeid(*this) != typeid(other)) return false;
        return static_cast<double>(*this) == static_cast<double>(other);
    }
};
#endif
