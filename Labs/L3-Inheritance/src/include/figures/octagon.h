#ifndef OOP_LABS_OCTAGON_H
#define OOP_LABS_OCTAGON_H

#include "figure.h"

class Octagon : public Figure {
public:
    Octagon();
    Octagon(const Octagon& other);
    Octagon(Octagon&& other) noexcept;

    Octagon& operator=(const Figure& other) override;
    Octagon& operator=(Figure&& other) noexcept override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Octagon* clone() const override;
};

#endif
