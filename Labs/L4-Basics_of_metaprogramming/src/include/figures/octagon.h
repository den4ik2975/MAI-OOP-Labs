// octagon.h
#ifndef OCTAGON_H
#define OCTAGON_H

#include "figure.h"

template<Scalar T>
class Octagon : public Figure<T> {
public:
    Octagon() {
        this->vertices_.resize(8);
        for(auto& vertex : this->vertices_) {
            vertex = std::make_unique<Point<T>>();
        }
    }

    void print(std::ostream& os) const override {
        os << "Octagon:\n";
        for(size_t i = 0; i < this->vertices_.size(); ++i) {
            os << "Vertex " << i << ": ("
               << this->vertices_[i]->get_x() << ", "
               << this->vertices_[i]->get_y() << ")\n";
        }
    }

    void read(std::istream& is) override {
        for(size_t i = 0; i < 8; ++i) {
            T x, y;
            is >> x >> y;
            this->vertices_[i] = std::make_unique<Point<T>>(x, y);
        }
        this->center_ = std::make_unique<Point<T>>(this->get_center());
    }
};
#endif
