#include "game.h"
#include "threadManager.h"

int main() {
    Game game;
    game.initializeRandomNpcs();

    std::cout << "\033[1;32mStarting game with 50 random NPCs...\033[0m\n";

    ThreadManager manager(game);
    manager.start();

    return 0;
}
