#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include "figures/figure.h"

class Array {
private:
    std::vector<Figure*> figures;

public:
    void addFigure(Figure* figure);

    void removeFigure(std::size_t index);

    void printAll() const;

    double getTotalArea() const;

    ~Array();
};

#endif
