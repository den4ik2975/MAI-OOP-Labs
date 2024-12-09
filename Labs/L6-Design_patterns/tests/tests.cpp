#include <gtest/gtest.h>
#include "game.h"
#include "factory.h"
#include "npc.h"
#include "visitor.h"
#include "observer.h"
#include <sstream>
#include <fstream>

// Test NPC creation and basic properties
TEST(NpcTest, BasicProperties) {
    auto bandit = std::make_shared<Bandit>("Bob", 100, 200);
    EXPECT_EQ(bandit->getName(), "Bob");
    EXPECT_EQ(bandit->getX(), 100);
    EXPECT_EQ(bandit->getY(), 200);
    EXPECT_EQ(bandit->getType(), "Bandit");
    EXPECT_EQ(bandit->getEmojiType(), "🔫");
}

// Test distance calculation
TEST(NpcTest, DistanceCalculation) {
    auto npc1 = std::make_shared<Bandit>("Bob", 0, 0);
    auto npc2 = std::make_shared<Knight>("Alice", 3, 4);
    EXPECT_DOUBLE_EQ(npc1->getDistance(*npc2), 5.0);
}

// Test NPC Factory
TEST(FactoryTest, CreateNpc) {
    auto bandit = NpcFactory::createNpc("Bandit", "Bob", 100, 200);
    auto knight = NpcFactory::createNpc("Knight", "Alice", 300, 400);
    auto elf = NpcFactory::createNpc("Elf", "Charlie", 50, 50);

    EXPECT_EQ(bandit->getType(), "Bandit");
    EXPECT_EQ(knight->getType(), "Knight");
    EXPECT_EQ(elf->getType(), "Elf");

    EXPECT_THROW(NpcFactory::createNpc("InvalidType", "Test", 0, 0), std::runtime_error);
}

// Test Game NPC management
TEST(GameTest, AddNpc) {
    Game game;
    auto npc = NpcFactory::createNpc("Bandit", "Bob", 100, 200);
    game.addNpc(npc);

    // Test invalid coordinates
    auto invalidNpc = NpcFactory::createNpc("Bandit", "Invalid", 600, 600);
    game.addNpc(invalidNpc);  // Should not be added due to invalid coordinates
}

// Test Combat System
TEST(GameTest, CombatSystem) {
    Game game;

    // Setup: Knight kills Bandit, Elf kills Knight
    game.addNpc(NpcFactory::createNpc("Knight", "Knight1", 10, 10));
    game.addNpc(NpcFactory::createNpc("Bandit", "Bandit1", 10, 10));
    game.addNpc(NpcFactory::createNpc("Elf", "Elf1", 10, 10));

    game.combat(20.0);  // Combat within range 20
}

// Test Observer Pattern
class TestObserver : public Observer {
public:
    std::vector<std::pair<std::string, std::string>> kills;
    void onKill(const std::string& killer, const std::string& victim) override {
        kills.push_back({killer, victim});
    }
};

TEST(ObserverTest, KillNotification) {
    Game game;
    auto observer = std::make_shared<TestObserver>();
    game.addObserver(observer);

    auto knight = NpcFactory::createNpc("Knight", "Knight1", 10, 10);
    auto bandit = NpcFactory::createNpc("Bandit", "Bandit1", 10, 10);

    game.addNpc(knight);
    game.addNpc(bandit);

    game.combat(20.0);

    EXPECT_FALSE(observer->kills.empty());
}

// Test File Operations
TEST(GameTest, SaveLoadOperations) {
    Game game;
    const std::string testFile = "test_save.txt";

    // Add some NPCs
    game.addNpc(NpcFactory::createNpc("Knight", "Knight1", 100, 100));
    game.addNpc(NpcFactory::createNpc("Bandit", "Bandit1", 200, 200));

    // Test save
    game.saveToFile(testFile);
    EXPECT_TRUE(std::ifstream(testFile).good());

    // Test load
    Game loadedGame;
    loadedGame.loadFromFile(testFile);

    // Clean up
    std::remove(testFile.c_str());

    // Test invalid file
    EXPECT_THROW(game.loadFromFile("nonexistent.txt"), std::runtime_error);
}

// Test Combat Visitor
TEST(VisitorTest, CombatRules) {
    // Test Bandit vs Elf (Bandit kills Elf)
    auto bandit = std::make_shared<Bandit>("Bandit1", 0, 0);
    auto elf = std::make_shared<Elf>("Elf1", 0, 0);
    CombatVisitor banditVisitor(elf.get(), 10.0);
    bandit->accept(banditVisitor);
    EXPECT_TRUE(banditVisitor.isKilled());  // Elf should die

    // Test Elf vs Knight (Elf kills Knight)
    auto knight = std::make_shared<Knight>("Knight1", 0, 0);
    CombatVisitor elfVisitor(knight.get(), 10.0);
    elf->accept(elfVisitor);
    EXPECT_TRUE(elfVisitor.isKilled());     // Knight should die

    // Test Knight vs Bandit (Knight kills Bandit)
    CombatVisitor knightVisitor(bandit.get(), 10.0);
    knight->accept(knightVisitor);
    EXPECT_TRUE(knightVisitor.isKilled());  // Bandit should die
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
