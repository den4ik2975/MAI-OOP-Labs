// hexagon.h
#ifndef HEXAGON_H
#define HEXAGON_H
#include "figure.h"

template<Scalar T>
class Hexagon : public Figure<T> {
public:
    Hexagon() {
        this->vertices_.resize(6);
        for(auto& vertex : this->vertices_) {
            vertex = std::make_unique<Point<T>>();
        }
    }

    void print(std::ostream& os) const override {
        os << "Hexagon:\n";
        for(size_t i = 0; i < this->vertices_.size(); ++i) {
            os << "Vertex " << i << ": ("
               << this->vertices_[i]->get_x() << ", "
               << this->vertices_[i]->get_y() << ")\n";
        }
    }

    void read(std::istream& is) override {
        for(size_t i = 0; i < 6; ++i) {
            T x, y;
            is >> x >> y;
            this->vertices_[i] = std::make_unique<Point<T>>(x, y);
        }
        this->center_ = std::make_unique<Point<T>>(this->get_center());
    }
};
#endif
