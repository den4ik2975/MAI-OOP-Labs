// visitor.cpp
#include "visitor.h"

void CombatVisitor::visit(Bandit& bandit) {
    if (auto* elf = dynamic_cast<Elf*>(opponent)) {
        // Nothing
    }
    if (auto* knight = dynamic_cast<Knight*>(opponent)) {
        killed = true;  // Bandit dies against Knight
    }
}

void CombatVisitor::visit(Knight& knight) {
    if (auto* bandit = dynamic_cast<Bandit*>(opponent)) {
        // Nothing
    }
    if (auto* elf = dynamic_cast<Elf*>(opponent)) {
        killed = true;  // Knight dies against Elf
    }
}

void CombatVisitor::visit(Elf& elf) {
    if (auto* bandit = dynamic_cast<Bandit*>(opponent)) {
        killed = true;
    }
    if (auto* knight = dynamic_cast<Knight*>(opponent)) {
        // Nothing
    }
}
