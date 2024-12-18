#include <iostream>
#include <iomanip>
#include <termios.h>
#include <unistd.h>
#include "game.h"
#include "factory.h"


const int ART_WIDTH = 35;
const int PADDING = 5;


// Function to configure terminal for raw input
void enableRawMode() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

// Function to restore terminal settings
void disableRawMode() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

// Function to read arrow key input
char getArrowKey() {
    char c;
    read(STDIN_FILENO, &c, 1);

    if (c == '\033') {
        char seq[2];
        read(STDIN_FILENO, &seq[0], 1);
        read(STDIN_FILENO, &seq[1], 1);

        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return 'U'; // Up
                case 'B': return 'D'; // Down
                case 'C': return 'R'; // Right
                case 'D': return 'L'; // Left
            }
        }
    }
    return c;
}

void printMenu(int selectedOption) {
    system("clear");
    std::cout << R"(
      ____        _                         ______    _          ____
     |  _ \      | |                       |  ____|  | |        |___ \
     | |_) | __ _| | __ _  __ _ _   _ _ __ | |__ __ _| |_ ___    __) |
     |  _ < / _` | |/ _` |/ _` | | | | '__||  __/ _` | __/ _ \  |__ <
     | |_) | (_| | | (_| | (_| | |_| | |    | | | (_| | || __/  ___) |
     |____/ \__,_|_|\__,_|\__, |\__,_|_|    |_| \__,_|\__\___| |____/
                           __/ |
                          |___/
    )" << "\n";
    std::cout << (selectedOption == 1 ? "> " : "  ") << "Add new NPC\n";
    std::cout << (selectedOption == 2 ? "> " : "  ") << "Print all NPCs\n";
    std::cout << (selectedOption == 3 ? "> " : "  ") << "Start combat mode\n";
    std::cout << (selectedOption == 4 ? "> " : "  ") << "Save to file\n";
    std::cout << (selectedOption == 5 ? "> " : "  ") << "Load from file\n";
    std::cout << (selectedOption == 0 ? "> " : "  ") << "Exit\n";
    std::cout << "\nUse arrow keys to navigate, Enter to select\n";
}

void addNpcMenu(Game& game) {
    system("clear");
    std::string type, name;
    int x, y;
    int selectedType = 1;
    bool typeSelected = false;
    const int NUM_TYPES = 3;

    // Store ASCII arts in an array
    std::vector<std::string> npcNames = {"Elf", "Knight", "Bandit"};
    std::vector<std::string> asciiArts = {

        "                              \n"
        "           4$$-.              \n"
        "           4   \".            \n"
        "           4    ^.            \n"
        "           4     $            \n"
        "           4     'b           \n"
        "           4      \"b.        \n"
        "           4        $         \n"
        "           4        $r        \n"
        "           4        $F        \n"
        "-$b========4========$b====*P=-\n"
        "           4       *$$F       \n"
        "           4        $$\"       \n"
        "           4       .$F        \n"
        "           4       dP         \n"
        "           4      F           \n"
        "           4     @            \n"
        "           4    .             \n"
        "           J.                 \n"
        "          '$$                 \n"
        "                              \n"
        "                              \n"
        "                              \n",

        "           |^^^|\n"
        "            }_{\n"
        "            }_{\n"
        "        /|_/---\\_|\\\n"
        "        I _|\\_/|_ I\n"
        "        \\| |   | |/\n"
        "           |   |\n"
        "           |   |\n"
        "           |   |\n"
        "           |   |\n"
        "           |   |\n"
        "           |   |\n"
        "           |   |\n"
        "           |   |\n"
        "           |   |\n"
        "           |   |\n"
        "           |   |\n"
        "           |   |\n"
        "           |   |\n"
        "           \\   /\n"
        "            \\ /\n"
        "             Y\n",

        "                       \n"
        "          ^            \n"
        "         | |           \n"
        "       @#####@         \n"
        "     (###   ###)-.     \n"
        "   .(###     ###) \\   \n"
        "   /  (###   ###)   )  \n"
        " (=-  .@#####@|_--\"   \n"
        " /\\    \\_|l|_/ (\\   \n"
        "(=-\\     |l|    /     \n"
        " \\  \\.___|l|___/     \n"
        " /\\      |_|   /      \n"
        "(=-\\._________/\\     \n"
        " \\             /      \n"
        "   \\._________/       \n"
        "     #  ----  #        \n"
        "     #   __   #        \n"
        "     \\########/       \n"
        "                       \n"
        "         V             \n"
        "             V         \n"
        "           V,          \n"
        "                       \n",
    };

    while (!typeSelected) {
        system("clear");

        std::vector<std::stringstream> artLines(22); // Assuming max height of 22 lines

        // Modify the art display code:
        for (int i = 0; i < NUM_TYPES; i++) {
            std::istringstream artStream(asciiArts[i]);
            std::string line;
            int lineNum = 0;
            while (std::getline(artStream, line) && lineNum < 22) {
                // Pad the line to fixed width
                line.resize(ART_WIDTH, ' ');

                artLines[lineNum] << (i == selectedType - 1 ? "\033[1;32m" : "")
                                 << line << (i == selectedType - 1 ? "\033[0m" : "")
                                 << std::string(PADDING, ' ');
                lineNum++;
            }
        }

        // Display all ASCII arts horizontally
        for (const auto& line : artLines) {
            std::cout << line.str() << '\n';
        }

        std::cout << "\n\n";

        // Print names on the same line with proper centering
        for (int i = 0; i < NUM_TYPES; i++) {
            int padding = ((ART_WIDTH - npcNames[i].length()) / 2);
            if (i == selectedType - 1) {
                std::cout << "\033[1;32m";
            }
            // Messy shit here, but it looks nice in console :)
            if (i == 1)
            {
                std::cout << std::string(padding - 5, ' ')
                          << npcNames[i]
                          << std::string(ART_WIDTH - padding - npcNames[i].length() + 3, ' ')
                          << std::string(PADDING, ' ');
            } else
            {
                std::cout << std::string(padding - 6, ' ')
                          << npcNames[i]
                          << std::string(ART_WIDTH - padding - npcNames[i].length() + 7, ' ')
                          << std::string(PADDING, ' ');
            }
            if (i == selectedType - 1) {
                std::cout << "\033[0m";
            }
        }
        std::cout << "\n";

        std::cout << "\n\nUse Left/Right arrows to select, Enter to confirm\n";

        char key = getArrowKey();
        if (key == 'L') {
            selectedType = (selectedType - 2 + NUM_TYPES) % NUM_TYPES + 1;
        }
        else if (key == 'R') {
            selectedType = selectedType % NUM_TYPES + 1;
        }
        else if (key == '\n') {
            typeSelected = true;
            type = npcNames[selectedType - 1];
        }
    }

    // Rest of the function remains the same
    disableRawMode();
    std::cout << "\x1B[34mEnter name: \033[0m";
    std::cin >> name;

    std::cout << "\x1B[34mEnter X and Y coordinates (0-500) separated by space: \033[0m";
    while (!(std::cin >> x >> y) || x < 0 || x > 500 || y < 0 || y > 500) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\x1B[31mInvalid coordinates! Please enter numbers between 0 and 500: \033[0m";
    }

    try {
        game.addNpc(NpcFactory::createNpc(type, name, x, y));
        std::cout << "\033[1;32mNPC added successfully!\033[0m\n";
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    } catch (const std::exception& e) {
        std::cout << "\x1B[31mError: " << e.what() << "\033[0m" << std::endl;
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }


    enableRawMode();
}

void handlePrintNpcs(Game& game) {
    disableRawMode();
    std::cout << "\n\x1B[34mCurrent NPCs:\033[0m\n";
    game.printNpcs();
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    enableRawMode();
}

void handleCombatMode(Game& game) {
    disableRawMode();
    double range;
    bool validRange = false;

    do {
        std::cout << "\x1B[34mEnter combat range (0-2000): \033[0m";
        if (std::cin >> range) {
            if (range >= 0 && range <= 2000) {
                validRange = true;
            } else {
                std::cout << "\x1B[31mInvalid range! Please enter a value between 0 and 2000.\033[0m\n";
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\x1B[31mInvalid input! Please enter a number.\033[0m\n";
        }
    } while (!validRange);

    std::cout << "\n\x1B[31mStarting combat...\033[0m\n";
    game.combat(range);
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(100, '\n');
    std::cin.get();
    enableRawMode();
}

void handleSaveGame(Game& game) {
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
}

void handleLoadGame(Game& game) {
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
}
