#pragma once
#include "npc.h"
#include <vector>
#include <memory>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>

struct BattleTask {
    std::shared_ptr<NPC> npc1;
    std::shared_ptr<NPC> npc2;
};

class Game {
private:
    static const int MAP_SIZE = 100;
    static const int INITIAL_NPC_COUNT = 50;
    int gameDuration;

    std::vector<std::shared_ptr<NPC>> npcs;
    std::mutex cout_mutex;
    std::mutex battle_queue_mutex;
    std::condition_variable battle_condition;
    std::queue<BattleTask> battle_queue;
    std::atomic<bool> gameRunning;

    void moveNPCs();
    void processBattles();
    void displayMap();
    void displayMapWithoutSleep();
    double calculateDistance(const NPC& npc1, const NPC& npc2);

public:
    Game(int duration = 30);
    const std::vector<std::shared_ptr<NPC>>& getNPCs() const {
        return npcs;
    }
    void run();
};
