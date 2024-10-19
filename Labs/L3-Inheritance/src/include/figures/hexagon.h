#ifndef OOP_LABS_HEXAGON_H
#define OOP_LABS_HEXAGON_H
#include "figures/figure.h"

class Hexagon : public Figure {
public:
    Hexagon();
    Hexagon(const Hexagon& other);
    Hexagon(Hexagon&& other) noexcept;

    Hexagon& operator=(const Figure& other) override;
    Hexagon& operator=(Figure&& other) noexcept override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Figure* clone() const override;
};

#endif
