#pragma once
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <atomic>
#include "game.h"

class ThreadManager {
    Game& game;
    std::atomic<bool> running{true};
    std::shared_mutex gameMutex;
    std::mutex consoleMutex;

    void moveThread();
    void combatThread();
    void displayThread();

public:
    ThreadManager(Game& g) : game(g) {}

    void start() {
        std::thread move_t(&ThreadManager::moveThread, this);
        std::thread combat_t(&ThreadManager::combatThread, this);
        std::thread display_t(&ThreadManager::displayThread, this);

        // Main thread waits for 30 seconds
        std::this_thread::sleep_for(std::chrono::seconds(30));
        running = false;

        move_t.join();
        combat_t.join();
        display_t.join();

        // Print survivors
        std::lock_guard<std::mutex> console_lock(consoleMutex);
        std::cout << "\nSurvivors after 30 seconds:\n";
        game.printNpcs();
    }
};
