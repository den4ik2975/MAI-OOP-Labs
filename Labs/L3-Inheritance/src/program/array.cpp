#include "array.h"
#include "figures/figure.h"
#include <iostream>

Array::~Array() {
    for (auto& figure : figures) {
        delete figure;
    }
}

void Array::addFigure(Figure* figure) {
    figures.push_back(figure->clone());
}

void Array::removeFigure(std::size_t index) {
    if (index < figures.size()) {
        delete figures[index];
        figures.erase(figures.begin() + index);
    }
}

void Array::printAll() const {
    for (const auto& figure : figures) {
        std::cout << *figure << std::endl;
        auto center = figure->getCenter();
        std::cout << "Center: (" << center.x << ", " << center.y << ")" << std::endl;
        std::cout << "Area: " << static_cast<double>(*figure) << std::endl;
        std::cout << std::endl;
    }
}

double Array::getTotalArea() const {
    double total = 0;
    for (const auto& figure : figures) {
        total += static_cast<double>(*figure);
    }
    return total;
}



