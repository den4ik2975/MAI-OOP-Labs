#include "visitor.h"

void CombatVisitor::visit(Bandit& bandit) {
    if (auto* elf = dynamic_cast<Elf*>(opponent)) {
        killed = true;  // Elf dies against Bandit
    }
    else if (auto* knight = dynamic_cast<Knight*>(opponent)) {
        // Nothing
    }
}

void CombatVisitor::visit(Knight& knight) {
    if (auto* bandit = dynamic_cast<Bandit*>(opponent)) {
        killed = true;  // Bandit dies against Knight
    }
    else if (auto* elf = dynamic_cast<Elf*>(opponent)) {
        // Nothing
    }
}

void CombatVisitor::visit(Elf& elf) {
    if (auto* knight = dynamic_cast<Knight*>(opponent)) {
        killed = true;  // Knight dies against Elf
    }
    else if (auto* bandit = dynamic_cast<Bandit*>(opponent)) {
        // Nothing
    }
}
