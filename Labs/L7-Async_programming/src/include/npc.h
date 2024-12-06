#pragma once
#include <string>
#include <memory>
#include <cmath>
#include <random>
#include <atomic>

class NpcVisitor;

class Npc {
protected:
    std::string name;
    std::atomic<int> x;
    std::atomic<int> y;
    std::atomic<bool> alive;
    const int moveDistance;
    const int killDistance;

public:
    Npc(const std::string& name, int x, int y, int moveDistance, int killDistance)
        : name(name), x(x), y(y), alive(true), moveDistance(moveDistance), killDistance(killDistance) {}
    virtual ~Npc() = default;

    virtual void accept(NpcVisitor& visitor) = 0;
    virtual std::string getEmojiType() const = 0;
    virtual std::string getLetterType() const = 0;
    virtual std::string getType() const = 0;

    std::string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    bool isAlive() const { return alive; }
    void kill() { alive = false; }
    int getMoveDistance() const { return moveDistance; }
    int getKillDistance() const { return killDistance; }

    void move(int dx, int dy) {
        int newX = x + dx;
        int newY = y + dy;
        if (newX >= 0 && newX < 50 && newY >= 0 && newY < 50) {
            x = newX;
            y = newY;
        }
    }

    int rollDice() const {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(1, 6);
        return dis(gen);
    }

    double getDistance(const Npc& other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        return sqrt(dx*dx + dy*dy);
    }
};

class Bandit : public Npc {
public:
    Bandit(const std::string& name, int x, int y)
        : Npc(name, x, y, 10, 10) {}
    void accept(NpcVisitor& visitor) override;
    std::string getEmojiType() const override { return "🔫"; }
    std::string getLetterType() const override { return "B"; }
    std::string getType() const override { return "Bandit"; }
};

class Knight : public Npc {
public:
    Knight(const std::string& name, int x, int y)
        : Npc(name, x, y, 30, 10) {}
    void accept(NpcVisitor& visitor) override;
    std::string getEmojiType() const override { return "⚔️"; }
    std::string getLetterType() const override { return "K"; }
    std::string getType() const override { return "Knight"; }
};

class Elf : public Npc {
public:
    Elf(const std::string& name, int x, int y)
        : Npc(name, x, y, 10, 50) {}
    void accept(NpcVisitor& visitor) override;
    std::string getEmojiType() const override { return "🏹"; }
    std::string getLetterType() const override { return "E"; }
    std::string getType() const override { return "Elf"; }
};
