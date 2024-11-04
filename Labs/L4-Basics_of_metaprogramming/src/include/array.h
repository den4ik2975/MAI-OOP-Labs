// array.h
#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <vector>
#include <iostream>

template<typename T>
class Array {
private:
    std::vector<std::shared_ptr<T>> data_;

public:
    void push_back(std::shared_ptr<T> figure) {
        data_.push_back(figure);
    }

    void remove(size_t index) {
        if (index < data_.size()) {
            data_.erase(data_.begin() + index);
        }
    }

    double get_total_area() const {
        double total = 0;
        for (const auto& figure : data_) {
            total += static_cast<double>(*figure);
        }
        return total;
    }

    void print_all() const {
        for (const auto& figure : data_) {
            figure->print(std::cout);
            auto center = figure->get_center();
            std::cout << "Area: " << static_cast<double>(*figure) << "\n";
            std::cout << "Center: " << center.get_x() << ' ' << center.get_y() << '\n';
        }
    }

    size_t size() const { return data_.size(); }

    std::shared_ptr<T> operator[](size_t index) {
        return data_[index];
    }
};
#endif
