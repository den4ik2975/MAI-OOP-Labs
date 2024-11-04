
#include "utils.h"
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include "figures/pentagon.h"
#include "figures/hexagon.h"
#include "figures/octagon.h"
#include "checker.h"


char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void printMenu(const std::vector<std::string>& options, int selectedIndex) {
    clearScreen();
    std::cout << "Use arrow keys to navigate, Enter to select:\n\n";
    for (size_t i = 0; i < options.size(); ++i) {
        if (i == selectedIndex) {
            std::cout << "> " << options[i] << " <\n";
        } else {
            std::cout << "  " << options[i] << "\n";
        }
    }
}

void waitForKeyPress() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}


MenuOption getSelectedOption() {
    std::vector<std::string> options = {"Pentagon", "Hexagon", "Octagon", "End"};
    int selectedIndex = 0;

    while (true) {
        printMenu(options, selectedIndex);
        char key = getch();

        if (key == 27) {
            key = getch();
            if (key == 91) {
                key = getch();
                if (key == static_cast<char>(Key::Up)) {
                    selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
                } else if (key == static_cast<char>(Key::Down)) {
                    selectedIndex = (selectedIndex + 1) % options.size();
                }
            }
        } else if (key == static_cast<char>(Key::Enter)) {
            return static_cast<MenuOption>(selectedIndex);
        }
    }
}

