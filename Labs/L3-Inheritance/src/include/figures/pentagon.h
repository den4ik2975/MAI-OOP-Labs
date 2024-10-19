#ifndef OOP_LABS_PENTAGON_H
#define OOP_LABS_PENTAGON_H

#include "figure.h"

class Pentagon : public Figure {
public:
    Pentagon();
    Pentagon(const Pentagon& other);
    Pentagon(Pentagon&& other) noexcept;

    Pentagon& operator=(const Figure& other) override;
    Pentagon& operator=(Figure&& other) noexcept override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Pentagon* clone() const override;
};

#endif