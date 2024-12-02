// main.cpp
#include <iostream>
#include <iomanip>
#include "game.h"
#include "factory.h"
#include "utils.h"

// Function to configure terminal for raw input

int main() {
    Game game;

    // Add observers
    game.addObserver(std::make_shared<ConsoleObserver>());
    game.addObserver(std::make_shared<FileObserver>());

    enableRawMode();
    int selectedOption = 1;
    bool running = true;

    while (running) {
        printMenu(selectedOption);
        char key = getArrowKey();

        if (key == 'U' && selectedOption > 0) selectedOption--;
        else if (key == 'U' && selectedOption == 0) selectedOption = 5;
        else if (key == 'D' && selectedOption < 5) selectedOption++;
        else if (key == 'D' && selectedOption == 5) selectedOption = 0;
        else if (key == '\n') {
            switch(selectedOption) {
                case 1: {
                    addNpcMenu(game);
                    break;
                }
                case 2: {
                    disableRawMode();
                    std::cout << "\n\x1B[34mCurrent NPCs:\033[0m\n";
                    game.printNpcs();
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(100, '\n');
                    std::cin.get();
                    enableRawMode();
                    break;
                }
                case 3: {
                    disableRawMode();
                    double range;
                    std::cout << "\x1B[34mEnter combat range: \033[0m";
                    std::cin >> range;
                    std::cout << "\n\x1B[31mStarting combat...\033[0m\n";
                    game.combat(range);
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(100, '\n');
                    std::cin.get();
                    enableRawMode();
                    break;
                }
                case 4: {
                    disableRawMode();
                    std::string filename;
                    std::cout << "\x1B[34mEnter filename to save: \033[0m";
                    std::cin >> filename;
                    game.saveToFile(filename);
                    std::cout << "\033[1;32mGame saved to " << filename << "\033[0m" << std::endl;
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(100, '\n');
                    std::cin.get();
                    enableRawMode();
                    break;
                }
                case 5: {
                    disableRawMode();
                    std::string filename;
                    std::cout << "\x1B[34mEnter filename to load: \033[0m";
                    std::cin >> filename;
                    try {
                        game.loadFromFile(filename);
                        std::cout << "\033[1;32mGame loaded from \033[0m" << filename << std::endl;
                    } catch (const std::exception& e) {
                        std::cout << "\x1B[31mError loading file: \033[0m" << e.what() << std::endl;
                    }
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(100, '\n');
                    std::cin.get();
                    enableRawMode();
                    break;
                }
                case 0:
                    running = false;
                    break;
            }
        }
    }

    disableRawMode();
    std::cout << "\x1B[34mExiting...\033[0m\n";
    return 0;
}
