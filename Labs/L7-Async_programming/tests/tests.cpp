#include <gtest/gtest.h>
#include "game.h"
#include "npc.h"
#include <chrono>
#include <thread>

// Test fixture for Game tests
class GameTest : public ::testing::Test {
protected:
    Game game;
};

// NPC Base Class Tests
TEST(NPCTest, CreationAndBasicProperties) {
    Knight knight(10, 20);
    EXPECT_EQ(knight.getX(), 10);
    EXPECT_EQ(knight.getY(), 20);
    EXPECT_TRUE(knight.isAlive());
    EXPECT_EQ(knight.getSymbol(), 'K');
}

TEST(NPCTest, Movement) {
    Knight knight(0, 0);
    knight.move(5, 5);
    EXPECT_EQ(knight.getX(), 5);
    EXPECT_EQ(knight.getY(), 5);
}

TEST(NPCTest, Kill) {
    Knight knight(0, 0);
    EXPECT_TRUE(knight.isAlive());
    knight.kill();
    EXPECT_FALSE(knight.isAlive());
}

// Knight Specific Tests
TEST(KnightTest, Properties) {
    Knight knight(0, 0);
    EXPECT_EQ(knight.getMoveDistance(), 30);
    EXPECT_EQ(knight.getKillDistance(), 10);
    EXPECT_EQ(knight.getSymbol(), 'K');
}

// Elf Specific Tests
TEST(ElfTest, Properties) {
    Elf elf(0, 0);
    EXPECT_EQ(elf.getMoveDistance(), 10);
    EXPECT_EQ(elf.getKillDistance(), 50);
    EXPECT_EQ(elf.getSymbol(), 'E');
}

// Bandit Specific Tests
TEST(BanditTest, Properties) {
    Bandit bandit(0, 0);
    EXPECT_EQ(bandit.getMoveDistance(), 10);
    EXPECT_EQ(bandit.getKillDistance(), 10);
    EXPECT_EQ(bandit.getSymbol(), 'B');
}

// Game Class Tests
TEST_F(GameTest, GameInitialization) {
    // Verify game creates without crashing
    Game newGame;
}

// Dice Roll Test
TEST(NPCTest, DiceRollRange) {
    for (int i = 0; i < 100; ++i) {
        int roll = NPC::rollDice();
        EXPECT_GE(roll, 1);
        EXPECT_LE(roll, 6);
    }
}

// Position Bounds Test
TEST(NPCTest, PositionBounds) {
    Knight knight(99, 99);  // Maximum valid position
    EXPECT_EQ(knight.getX(), 99);
    EXPECT_EQ(knight.getY(), 99);
}

// NPC Combat Range Test
TEST(NPCTest, CombatRanges) {
    Knight knight(0, 0);
    Elf elf(0, 0);
    Bandit bandit(0, 0);

    // Verify each class has the correct combat ranges
    EXPECT_EQ(knight.getKillDistance(), 10);
    EXPECT_EQ(elf.getKillDistance(), 50);
    EXPECT_EQ(bandit.getKillDistance(), 10);
}

// Movement Range Test
TEST(NPCTest, MovementRanges) {
    Knight knight(0, 0);
    Elf elf(0, 0);
    Bandit bandit(0, 0);

    // Verify each class has the correct movement ranges
    EXPECT_EQ(knight.getMoveDistance(), 30);
    EXPECT_EQ(elf.getMoveDistance(), 10);
    EXPECT_EQ(bandit.getMoveDistance(), 10);
}

// Symbol Consistency Test
TEST(NPCTest, SymbolConsistency) {
    Knight knight(0, 0);
    Elf elf(0, 0);
    Bandit bandit(0, 0);

    EXPECT_EQ(knight.getSymbol(), 'K');
    EXPECT_EQ(elf.getSymbol(), 'E');
    EXPECT_EQ(bandit.getSymbol(), 'B');
}


class GameExecutionTest : public ::testing::Test {
protected:
    // Helper method to count alive NPCs
    int countAliveNPCs(const Game& game) {
        int aliveCount = 0;
        for (const auto& npc : game.getNPCs()) {
            if (npc->isAlive()) {
                aliveCount++;
            }
        }
        return aliveCount;
    }
};

TEST_F(GameExecutionTest, NPCReductionOverTime) {
    Game game(5); // 5 seconds duration

    // Get initial count
    int initialCount = countAliveNPCs(game);
    EXPECT_EQ(initialCount, 50); // Verify initial NPC count

    // Start
    std::thread gameThread([&game]() {
        game.run();
    });

    // Wait for game to finish
    gameThread.join();

    // Get final count
    int finalCount = countAliveNPCs(game);

    // Verify that some NPCs have been eliminated
    EXPECT_LT(finalCount, initialCount);
    std::cout << "Initial NPCs: " << initialCount << ", Surviving NPCs: " << finalCount << std::endl;
}

// Test short battle
TEST_F(GameExecutionTest, ShortBattleScenario) {
    Game game(2); // 2 seconds duration

    int initialCount = countAliveNPCs(game);

    auto startTime = std::chrono::steady_clock::now();

    std::thread gameThread([&game]() {
        game.run();
    });

    gameThread.join();

    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

    int finalCount = countAliveNPCs(game);
    // 3 secs for handling sleep
    EXPECT_LT(finalCount, initialCount);
    EXPECT_GE(duration.count(), 5);
    EXPECT_LE(duration.count(), 5);
}

// Complex test
TEST_F(GameExecutionTest, ComplexGameScenario) {
    Game game(3); // 3 secs

    // Verify initial state
    int initialCount = countAliveNPCs(game);
    EXPECT_EQ(initialCount, 50);

    // Track start time
    auto startTime = std::chrono::steady_clock::now();

    // Run game
    std::thread gameThread([&game]() {
        game.run();
    });

    gameThread.join();

    // Track end time
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

    // Final count
    int finalCount = countAliveNPCs(game);

    // Verify:
    // 1. Duration was approximately correct (+3 secs for start)
    EXPECT_GE(duration.count(), 6);
    EXPECT_LE(duration.count(), 7);

    // 2. NPCs were eliminated
    EXPECT_LT(finalCount, initialCount);

    // 3. We still have some survivors
    EXPECT_GT(finalCount, 0);

    // Output detailed results
    std::cout << "Test results:" << std::endl
              << "Initial NPCs: " << initialCount << std::endl
              << "Final NPCs: " << finalCount << std::endl
              << "Duration: " << duration.count() << " seconds" << std::endl;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
