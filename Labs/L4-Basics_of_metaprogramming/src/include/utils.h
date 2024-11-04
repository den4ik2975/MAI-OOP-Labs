// utils.h
#ifndef OOP_LABS_UTILS_H
#define OOP_LABS_UTILS_H

#include <checker.h>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "figures/figure.h"

enum class MenuOption {
    Pentagon,
    Hexagon,
    Octagon,
    End
};

enum class Key {
    Up = 65,
    Down = 66,
    Enter = 10
};

char getch();
void clearScreen();
void printMenu(const std::vector<std::string>& options, int selectedIndex);
MenuOption getSelectedOption();

template<Scalar T>
bool getCoordinates(const std::string& shapeName, std::shared_ptr<Figure<T>>& shape) {
    std::cout << "Enter coordinates for " << shapeName << ":\n";
    shape->read(std::cin);

    // Check if the shape is regular
    if (auto pentagon = std::dynamic_pointer_cast<Pentagon<T>>(shape)) {
        if (!GeometryChecker<T>::is_regular_pentagon(*pentagon)) {
            std::cout << "Error: Not a regular pentagon!\n";
            return false;
        }
    }
    else if (auto hexagon = std::dynamic_pointer_cast<Hexagon<T>>(shape)) {
        if (!GeometryChecker<T>::is_regular_hexagon(*hexagon)) {
            std::cout << "Error: Not a regular hexagon!\n";
            return false;
        }
    }
    else if (auto octagon = std::dynamic_pointer_cast<Octagon<T>>(shape)) {
        if (!GeometryChecker<T>::is_regular_octagon(*octagon)) {
            std::cout << "Error: Not a regular octagon!\n";
            return false;
        }
    }
    return true;
}


#endif
