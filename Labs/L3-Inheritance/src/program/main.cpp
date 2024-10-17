#include <iostream>
#include "array.h"
#include "figures/triangle.h"
#include "figures/rectangle.h"
#include "figures/square.h"
#include <conio.h>
#include <vector>
#include <string>

enum class MenuOption {
    Triangle,
    Rectangle,
    Square,
    End
};

enum class Key {
    Up = 72,
    Down = 80,
    Enter = 13
};

void printMenu(const std::vector<std::string>& options, int selectedIndex) {
    system("cls");
    std::cout << "Use arrow keys to navigate, Enter to select:\n\n";
    for (size_t i = 0; i < options.size(); ++i) {
        if (i == selectedIndex) {
            std::cout << "> " << options[i] << " <\n";
        } else {
            std::cout << "  " << options[i] << "\n";
        }
    }
}

MenuOption getSelectedOption() {
    std::vector<std::string> options = {"Triangle", "Rectangle", "Square", "Results"};
    int selectedIndex = 0;

    while (true) {
        printMenu(options, selectedIndex);
        int key = _getch();

        if (key == 0 || key == 224) {
            key = _getch();
            if (key == static_cast<int>(Key::Up)) {
                selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
            } else if (key == static_cast<int>(Key::Down)) {
                selectedIndex = (selectedIndex + 1) % options.size();
            }
        } else if (key == static_cast<int>(Key::Enter)) {
            return static_cast<MenuOption>(selectedIndex);
        }
    }
}

template <typename T>
void getCoordinates(const std::string& shapeName, T& shape) {
    std::cout << "Enter coordinates for " << shapeName << ":\n";
    std::cin >> shape;
}

int main() {
    Array figures;

    while (true) {
        MenuOption selectedOption = getSelectedOption();
        Figure* figure = nullptr;
        std::string figureName;
        system("cls");
        switch (selectedOption) {
            case MenuOption::Triangle: {
                figure = new Triangle();
                figureName = "Triangle";
                break;
            }
            case MenuOption::Rectangle: {
                figure = new Rectangle();
                figureName = "Rectangle";
                break;
            }
            case MenuOption::Square: {
                figure = new Square();
                figureName = "Square";
                break;
            }
            case MenuOption::End:
                std::cout << "All figures:" << std::endl;
                figures.printAll();

                std::cout << "\nTotal area of all figures:  " << figures.getTotalArea() << std::endl;
                return 0;
        }

        std::cout << "Enter coordinates for " << figureName << ":\n";
        std::cin >> *figure;
        figures.addFigure(figure);
    }

    return 0;
}
