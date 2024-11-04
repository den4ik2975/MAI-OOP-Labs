// point.h
#ifndef POINT_H
#define POINT_H

#include <concepts>

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template<Scalar T>
class Point {
private:
    T x_, y_;

public:
    Point(T x = 0, T y = 0) : x_(x), y_(y) {}

    T get_x() const { return x_; }
    T get_y() const { return y_; }

    void set_x(T x) { x_ = x; }
    void set_y(T y) { y_ = y; }

    bool operator<(const Point& other) const {
        if (x_ == other.x_) return y_ < other.y_;
        return x_ < other.x_;
    }

    bool operator==(const Point& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }
};
#endif
