#include <iostream>
#include <vector>
#include <string>
#include <termios.h>

#include "array.h"
#include "figures/pentagon.h"
#include "figures/hexagon.h"
#include "figures/octagon.h"
#include "utils.h"


int main() {
    Array figures;

    while (true) {
        MenuOption selectedOption = getSelectedOption();
        Figure* figure = nullptr;
        std::string figureName;
        clearScreen();

        switch (selectedOption) {
            case MenuOption::Pentagon: {
                figure = new Pentagon();
                figureName = "Pentagon";
                break;
            }
            case MenuOption::Hexagon: {
                figure = new Hexagon();
                figureName = "Hexagon";
                break;
            }
            case MenuOption::Octagon: {
                figure = new Octagon();
                figureName = "Octagon";
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
