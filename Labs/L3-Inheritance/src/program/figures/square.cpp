#include "figures/square.h"

void Square::print(std::ostream& os) const {
    os << "Square:\n";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.first << ", " << vertex.second << ")\n";
    }
}
