#ifndef OOP_LABS_UTILS_H
#define OOP_LABS_UTILS_H

#include <vector>
#include <string>

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
template <typename T>
void getCoordinates(const std::string& shapeName, T& shape);

#endif
