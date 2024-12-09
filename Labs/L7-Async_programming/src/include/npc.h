#pragma once
#include <mutex>
#include <shared_mutex>
#include <random>

class NPC {
protected:
    int x, y;
    bool alive;
    char symbol;
    std::shared_mutex mutex;

public:
    NPC(int startX, int startY, char sym)
        : x(startX), y(startY), alive(true), symbol(sym) {}

    virtual ~NPC() = default;

    virtual int getMoveDistance() const = 0;
    virtual int getKillDistance() const = 0;

    bool isAlive() const { return alive; }
    void kill() { alive = false; }

    int getX() const { return x; }
    int getY() const { return y; }
    char getSymbol() const { return symbol; }

    void move(int newX, int newY) {
        std::lock_guard<std::shared_mutex> lock(mutex);
        x = newX;
        y = newY;
    }

    static int rollDice() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(1, 6);
        return dis(gen);
    }
};

class Knight : public NPC {
public:
    Knight(int x, int y) : NPC(x, y, 'K') {}
    int getMoveDistance() const override { return 30; }
    int getKillDistance() const override { return 10; }
};

class Elf : public NPC {
public:
    Elf(int x, int y) : NPC(x, y, 'E') {}
    int getMoveDistance() const override { return 10; }
    int getKillDistance() const override { return 50; }
};

class Bandit : public NPC {
public:
    Bandit(int x, int y) : NPC(x, y, 'B') {}
    int getMoveDistance() const override { return 10; }
    int getKillDistance() const override { return 10; }
};
