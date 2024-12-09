#include "game.h"
#include <cmath>
#include <chrono>
#include <iostream>
#include <iomanip>

Game::Game(int duration) : gameRunning(true), gameDuration(duration) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, MAP_SIZE - 1);
    std::uniform_int_distribution<> type_dis(0, 2);

    for (int i = 0; i < INITIAL_NPC_COUNT; ++i) {
        int x = dis(gen);
        int y = dis(gen);
        int type = type_dis(gen);

        switch (type) {
            case 0:
                npcs.push_back(std::make_shared<Knight>(x, y));
                break;
            case 1:
                npcs.push_back(std::make_shared<Elf>(x, y));
                break;
            case 2:
                npcs.push_back(std::make_shared<Bandit>(x, y));
                break;
        }
    }
}

void Game::run() {
    displayMapWithoutSleep();
    std::cout << "Starting positions above. Game begins in 3 seconds...\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::thread displayThread([this]() { displayMap(); });
    std::thread moveThread([this]() { moveNPCs(); });
    std::thread battleThread([this]() { processBattles(); });

    std::this_thread::sleep_for(std::chrono::seconds(gameDuration));
    gameRunning = false;
    battle_condition.notify_all();  // Notify battle thread to check gameRunning

    moveThread.join();
    battleThread.join();
    displayThread.join();

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "\nGame Over! Survivors:\n";
        int survivors = 0;
        for (const auto& npc : npcs) {
            if (npc->isAlive()) {
                survivors++;
                std::cout << npc->getSymbol() << " at ("
                         << npc->getX() << "," << npc->getY() << ")\n";
            }
        }
        std::cout << "Total survivors: " << survivors << "\n";
    }
}

double Game::calculateDistance(const NPC& npc1, const NPC& npc2) {
    int dx = npc1.getX() - npc2.getX();
    int dy = npc1.getY() - npc2.getY();
    return std::sqrt(dx*dx + dy*dy);
}

void Game::moveNPCs() {
    std::random_device rd;
    std::mt19937 gen(rd());

    while (gameRunning) {
        // Move NPCs
        for (auto& npc : npcs) {
            if (!npc->isAlive()) continue;

            std::uniform_int_distribution<> dis(-npc->getMoveDistance(),
                                              npc->getMoveDistance());
            int newX = std::clamp(npc->getX() + dis(gen), 0, MAP_SIZE - 1);
            int newY = std::clamp(npc->getY() + dis(gen), 0, MAP_SIZE - 1);
            npc->move(newX, newY);
        }

        // Check for potential battles
        for (size_t i = 0; i < npcs.size(); ++i) {
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                auto& npc1 = npcs[i];
                auto& npc2 = npcs[j];

                if (!npc1->isAlive() || !npc2->isAlive()) continue;

                double distance = calculateDistance(*npc1, *npc2);

                if (distance <= npc1->getKillDistance() ||
                    distance <= npc2->getKillDistance()) {
                    {
                        std::lock_guard<std::mutex> lock(battle_queue_mutex);
                        battle_queue.push({npc1, npc2});
                    }
                    battle_condition.notify_one();
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Game::processBattles() {
    while (gameRunning || !battle_queue.empty()) {
        std::unique_lock<std::mutex> lock(battle_queue_mutex);

        if (battle_queue.empty()) {
            if (!gameRunning) break;
            battle_condition.wait_for(lock, std::chrono::milliseconds(500));
            continue;
        }

        BattleTask task = battle_queue.front();
        battle_queue.pop();
        lock.unlock();

        if (task.npc1->isAlive() && task.npc2->isAlive()) {
            int attack = NPC::rollDice();
            int defense = NPC::rollDice();

            {
                std::lock_guard<std::mutex> cout_lock(cout_mutex);
                std::cout << "Battle: " << task.npc1->getSymbol()
                         << "(A:" << attack << ") vs "
                         << task.npc2->getSymbol()
                         << "(D:" << defense << ")\n";
            }

            if (attack > defense) {
                task.npc2->kill();
            } else {
                task.npc1->kill();
            }
        }
    }
}

void Game::displayMap() {
    while (gameRunning) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::vector<std::vector<char>> map(MAP_SIZE,
                                         std::vector<char>(MAP_SIZE, '.'));

        for (const auto& npc : npcs) {
            if (npc->isAlive()) {
                map[npc->getY()][npc->getX()] = npc->getSymbol();
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            //system("clear");  // Use "cls" for Windows
            std::cout << "Map:" << '\n';
            for (const auto& row : map) {
                for (char cell : row) {
                    std::cout << cell;
                }
                std::cout << '\n';
            }
        }
    }
}

void Game::displayMapWithoutSleep()
{
    std::vector<std::vector<char>> map(MAP_SIZE,
                                       std::vector<char>(MAP_SIZE, '.'));

    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            map[npc->getY()][npc->getX()] = npc->getSymbol();
        }
    }

    {
        //system("clear");
        std::cout << "Map!" << '\n';
        for (const auto& row : map) {
            for (char cell : row) {
                std::cout << cell;
            }
            std::cout << '\n';
        }
    }
}
