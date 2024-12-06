#include "threadManager.h"
#include <random>

const int MAP_SIZE = 50;

void ThreadManager::moveThread() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1, 1);

    while (running) {
        std::shared_lock<std::shared_mutex> lock(gameMutex);
        for (auto& npc : game.getNpcs()) {
            if (npc->isAlive()) {
                int moveDistance = npc->getMoveDistance();
                int dx = dis(gen) * moveDistance;
                int dy = dis(gen) * moveDistance;
                npc->move(dx, dy);
            }
        }
        // A little break
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void ThreadManager::combatThread() {
    while (running) {
        std::unique_lock<std::shared_mutex> lock(gameMutex);
        auto& npcs = game.getNpcs();

        for (size_t i = 0; i < npcs.size(); ++i) {
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (!npcs[i]->isAlive() || !npcs[j]->isAlive()) continue;

                if (npcs[i]->getDistance(*npcs[j]) <= npcs[i]->getKillDistance()) {
                    int attack = npcs[i]->rollDice();
                    int defense = npcs[j]->rollDice();

                    if (attack > defense) {
                        npcs[j]->kill();
                        std::lock_guard<std::mutex> console_lock(consoleMutex);
                        std::cout << npcs[i]->getName() << " killed " << npcs[j]->getName() << "\n";
                    }
                }
            }
        }
        // A little break
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}



void ThreadManager::displayThread() {
    while (running) {
        std::shared_lock<std::shared_mutex> lock(gameMutex);
        std::lock_guard<std::mutex> console_lock(consoleMutex);

        // Clear screen
        // system("clear");
        std::cout << "\033[2J\033[H";

        // Create empty map using vector of strings
        std::vector<std::string> map(MAP_SIZE, std::string(MAP_SIZE, ' '));

        // Fill map with NPCs
        for (const auto& npc : game.getNpcs()) {
            if (npc->isAlive()) {
                int x = npc->getX();
                int y = npc->getY();
                if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
                    map[y][x] = npc->getLetterType()[0];
                }
            }
        }

        std::cout << '+' << std::string(MAP_SIZE, '-') << '+' << '\n';

        // Print map with side borders
        for (const auto& row : map) {
            std::cout << '|' << row << '|' << '\n';
        }

        // Print bottom border
        std::cout << '+' << std::string(MAP_SIZE, '-') << '+' << '\n';

        std::this_thread::sleep_for(std::chrono::seconds(1));

    }
}
