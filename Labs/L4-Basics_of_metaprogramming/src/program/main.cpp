#include <iostream>
#include <memory>
#include "array.h"
#include "figures/figure.h"
#include "figures/pentagon.h"
#include "figures/hexagon.h"
#include "figures/octagon.h"
#include "utils.h"

int main() {
    Array<Figure<double> > figures;  // Note the space between > >

    while (true) {
        MenuOption selectedOption = getSelectedOption();
        std::shared_ptr<Figure<double>> figure;
        std::string figureName;
        clearScreen();

        switch (selectedOption) {
            case MenuOption::Pentagon: {
                figure = std::make_shared<Pentagon<double>>();
                figureName = "Pentagon";
                break;
            }
            case MenuOption::Hexagon: {
                figure = std::make_shared<Hexagon<double>>();
                figureName = "Hexagon";
                break;
            }
            case MenuOption::Octagon: {
                figure = std::make_shared<Octagon<double>>();
                figureName = "Octagon";
                break;
            }
            case MenuOption::End:
                std::cout << "All figures:" << std::endl;
                figures.print_all();
                std::cout << "\nTotal area of all figures: " << figures.get_total_area() << std::endl;
                return 0;
        }

        if (getCoordinates<double>(figureName, figure)) {
            figures.push_back(figure);
            std::cout << "Figure added successfully!\n";
        } else {
            std::cout << "Figure was not added due to validation failure.\n";
        }
    }

    return 0;
}
