#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include "npc.h"
#include "factory.h"
#include "observer.h"
#include "visitor.h"
#include <random>

class Game {
    std::vector<std::shared_ptr<Npc>> npcs;
    std::vector<std::shared_ptr<Observer>> observers;

public:
    void addNpc(std::shared_ptr<Npc> npc) {
        if (npc->getX() >= 0 && npc->getX() <= 500 &&
            npc->getY() >= 0 && npc->getY() <= 500) {
            npcs.push_back(npc);
        }
    }

    void addObserver(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    void notifyKill(const std::string& killer, const std::string& victim) {
        for (auto& observer : observers) {
            observer->onKill(killer, victim);
        }
    }

    void combat(double range) {
        struct KillInfo {
            size_t index;
            std::string victim;
            std::string killer;
        };
        std::vector<KillInfo> killed;

        for (size_t i = 0; i < npcs.size(); ++i) {
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (npcs[i]->getDistance(*npcs[j]) <= range) {
                    CombatVisitor visitor1(npcs[j].get(), range);
                    CombatVisitor visitor2(npcs[i].get(), range);

                    npcs[i]->accept(visitor1);
                    npcs[j]->accept(visitor2);

                    if (visitor1.isKilled()) {
                        killed.push_back({i,
                            npcs[i]->getEmojiType() + ' ' + npcs[i]->getName(),
                            npcs[j]->getEmojiType() + ' ' + npcs[j]->getName()});
                    }
                    if (visitor2.isKilled()) {
                        killed.push_back({j,
                            npcs[j]->getEmojiType() + ' ' + npcs[j]->getName(),
                            npcs[i]->getEmojiType() + ' ' + npcs[i]->getName()});
                    }
                }
            }
        }

        std::sort(killed.begin(), killed.end(),
            [](const KillInfo& a, const KillInfo& b) { return a.index > b.index; });

        for (const auto& kill : killed) {
            notifyKill(kill.victim, kill.killer);
            npcs.erase(npcs.begin() + kill.index);
        }
    }


    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& npc : npcs) {
            file << npc->getType() << " " << npc->getName() << " "
                 << npc->getX() << " " << npc->getY() << std::endl;
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }

        npcs.clear();
        std::string type, name;
        int x, y;

        while (file >> type >> name >> x >> y) {
            addNpc(NpcFactory::createNpc(type, name, x, y));
        }

        if (file.bad()) {
            throw std::runtime_error("Error occurred while reading file: " + filename);
        }
    }


    void printNpcs() const {
        for (const auto& npc : npcs) {
            std::cout << npc->getEmojiType() << " " << npc->getName()
                     << " at (" << npc->getX() << "," << npc->getY() << ")"
                     << std::endl;
        }
    }

    std::vector<std::shared_ptr<Npc>>& getNpcs() { return npcs; }

    void initializeRandomNpcs() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 49);
        std::uniform_int_distribution<> type_dis(0, 2);

        for (int i = 0; i < 50; ++i) {
            int x = dis(gen);
            int y = dis(gen);
            std::string name = "NPC" + std::to_string(i);

            int type = type_dis(gen);
            switch(type) {
            case 0:
                addNpc(std::make_shared<Knight>(name, x, y));
                break;
            case 1:
                addNpc(std::make_shared<Elf>(name, x, y));
                break;
            case 2:
                addNpc(std::make_shared<Bandit>(name, x, y));
                break;
            }
        }
    }
};
