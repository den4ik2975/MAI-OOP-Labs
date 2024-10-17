#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"
#include <cmath>
#include "rectangle.h"

// Частный случай прямоугольника, нового кода писать не надо
class Square : public Rectangle {
public:
    void print(std::ostream& os) const override;
};
#endif //SQUARE_H
