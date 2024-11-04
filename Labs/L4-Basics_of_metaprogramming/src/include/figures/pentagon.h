// pentagon.h
#ifndef PENTAGON_H
#define PENTAGON_H
#include "figure.h"
#include "iostream"

template<Scalar T>
class Pentagon : public Figure<T> {
public:
    Pentagon() {
        this->vertices_.resize(5);
        for(auto& vertex : this->vertices_) {
            vertex = std::make_unique<Point<T>>();
        }
    }

    void print(std::ostream& os) const override {
        os << "Pentagon:\n";
        for(size_t i = 0; i < this->vertices_.size(); ++i) {
            os << "Vertex " << i << ": ("
               << this->vertices_[i]->get_x() << ", "
               << this->vertices_[i]->get_y() << ")\n";
        }
    }

    void read(std::istream& is) override {
        for(size_t i = 0; i < 5; ++i) {
            T x, y;
            is >> x >> y;
            this->vertices_[i] = std::make_unique<Point<T>>(x, y);
        }
    }
};
#endif
/*
x = [1, 0.309, -0.809, -0.809, 0.309]
y = [0, 0.951, 0.588, -0.588, -0.951]
1 0
0.309 0.951
-0.809 0.588
-0.809 -0.588
0.309 -0.951
 */