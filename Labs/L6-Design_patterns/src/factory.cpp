#include "factory.h"

std::shared_ptr<Npc> NpcFactory::createNpc(const std::string& type, const std::string& name, int x, int y) {
    if (type == "Bandit") return std::make_shared<Bandit>(name, x, y);
    if (type == "Knight") return std::make_shared<Knight>(name, x, y);
    if (type == "Elf") return std::make_shared<Elf>(name, x, y);
    throw std::runtime_error("Unknown NPC type");
}
