#include <gtest/gtest.h>
#include <sstream>

#include "array.h"
#include "figures/figure.h"
#include "figures/pentagon.h"
#include "figures/hexagon.h"
#include "figures/octagon.h"


class PentagonTest : public ::testing::Test {
protected:
    Pentagon pentagon1;
    Pentagon pentagon2;
    Pentagon pentagon3;
};


TEST_F(PentagonTest, ReadAndPrint) {
    std::stringstream input("0 0 2 -2 4 0 4 4 0 4");
    std::stringstream output;

    pentagon1.read(input);
    pentagon1.print(output);

    auto center = pentagon1.getCenter();
    EXPECT_NEAR(center.x, 2.0, 1e-6);
    EXPECT_NEAR(center.y, 1.2, 1e-6);
}

TEST_F(PentagonTest, Area) {
    std::stringstream input("0 0 2 -2 4 0 4 4 0 4");
    std::stringstream output;

    pentagon1.read(input);
    pentagon1.print(output);

    EXPECT_NEAR(static_cast<double>(pentagon1), 20.0, 1e-6);
}

TEST_F(PentagonTest, Print) {
    std::stringstream input("0 0 2 -2 4 0 4 4 0 4");
    std::stringstream output;
    Pentagon Pentagon;

    Pentagon.read(input);
    Pentagon.print(output);

    EXPECT_EQ(output.str(), "Pentagon:\n(0, 0)\n(2, -2)\n(4, 0)\n(4, 4)\n(0, 4)\n");
}

TEST_F(PentagonTest, Clone) {
    std::stringstream input("0 0 2 -2 4 0 4 4 0 4");
    std::stringstream output;

    pentagon1.read(input);
    pentagon1.print(output);

    std::unique_ptr<Figure> cloned(pentagon1.clone());
    EXPECT_EQ(typeid(*cloned), typeid(Pentagon));
    EXPECT_EQ(*cloned, pentagon1);
}

TEST_F(PentagonTest, Equality) {
    std::stringstream input1("0 0 2 -2 4 0 4 4 0 4");
    std::stringstream output1;

    pentagon1.read(input1);
    pentagon1.print(output1);

    std::stringstream input2("0 0 2 -2 4 0 4 4 0 4");
    std::stringstream output2;

    pentagon2.read(input2);
    pentagon2.print(output2);

    EXPECT_EQ(pentagon1, pentagon2);

    std::stringstream input3("0 0 2 -4 4 0 4 4 0 4");
    std::stringstream output3;

    pentagon3.read(input2);
    pentagon3.print(output2);

    EXPECT_NE(pentagon1, pentagon3);
}


class HexagonTest : public ::testing::Test {
protected:
    Hexagon hexagon1;
    Hexagon hexagon2;
    Hexagon hexagon3;
};

TEST_F(HexagonTest, ReadAndPrint) {
    std::stringstream input("0 0 2 -2 4 0 4 4 2 6 0 4");
    std::stringstream output;

    hexagon1.read(input);
    hexagon1.print(output);

    EXPECT_EQ(output.str(), "Hexagon:\n(0, 0)\n(2, -2)\n(4, 0)\n(4, 4)\n(2, 6)\n(0, 4)\n");
}

TEST_F(HexagonTest, GetCenter) {
    std::stringstream input("0 0 2 -2 4 0 4 4 2 6 0 4");
    hexagon1.read(input);

    auto center = hexagon1.getCenter();
    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 2.0);
}

TEST_F(HexagonTest, Area) {
    std::stringstream input("0 0 2 -2 4 0 4 4 2 6 0 4");
    hexagon1.read(input);

    EXPECT_DOUBLE_EQ(static_cast<double>(hexagon1), 24.0);
}


TEST_F(HexagonTest, Clone) {
    std::stringstream input("0 0 2 -2 4 0 4 4 2 6 0 4");
    hexagon1.read(input);

    std::unique_ptr<Figure> clonedFigure(hexagon1.clone());

    EXPECT_EQ(clonedFigure->getCenter(), hexagon1.getCenter());
    EXPECT_DOUBLE_EQ(static_cast<double>(*clonedFigure), static_cast<double>(hexagon1));
}

TEST_F(HexagonTest, Equality) {
    std::stringstream input1("0 0 2 -2 4 0 4 4 2 6 0 4");
    std::stringstream input2("0 0 2 -2 4 0 4 4 2 6 0 4");
    std::stringstream input3("0 0 2 -2 4 0 4 4 2 10 0 4");

    hexagon1.read(input1);
    hexagon2.read(input2);
    hexagon3.read(input3);

    EXPECT_TRUE(hexagon1 == hexagon2);
    EXPECT_FALSE(hexagon1 == hexagon3);
}


class OctagonTest : public ::testing::Test {
protected:
    Octagon octagon1;
    Octagon octagon2;
    Octagon octagon3;
};

TEST_F(OctagonTest, ReadAndPrint) {
    std::stringstream input("0 0 2 -2 4 -2 6 0 6 4 4 6 2 6 0 4");
    std::stringstream output;

    octagon1.read(input);
    octagon1.print(output);

    EXPECT_EQ(output.str(), "Octagon:\n(0, 0)\n(2, -2)\n(4, -2)\n(6, 0)\n(6, 4)\n(4, 6)\n(2, 6)\n(0, 4)\n");
}

TEST_F(OctagonTest, GetCenter) {
    std::stringstream input("0 0 2 -2 4 -2 6 0 6 4 4 6 2 6 0 4");
    octagon1.read(input);

    auto center = octagon1.getCenter();
    EXPECT_DOUBLE_EQ(center.x, 3.0);
    EXPECT_DOUBLE_EQ(center.y, 2.0);
}

TEST_F(OctagonTest, Area) {
    std::stringstream input("0 0 2 -2 4 -2 6 0 6 4 4 6 2 6 0 4");
    octagon1.read(input);

    EXPECT_DOUBLE_EQ(static_cast<double>(octagon1), 40.0);
}


TEST_F(OctagonTest, Clone) {
    std::stringstream input("0 0 2 -2 4 -2 6 0 6 4 4 6 2 6 0 4");
    octagon1.read(input);

    std::unique_ptr<Figure> clonedFigure(octagon1.clone());

    EXPECT_EQ(clonedFigure->getCenter(), octagon1.getCenter());
    EXPECT_DOUBLE_EQ(static_cast<double>(*clonedFigure), static_cast<double>(octagon1));
}

TEST_F(OctagonTest, Equality) {
    std::stringstream input1("0 0 2 -2 4 -2 6 0 6 4 4 6 2 6 0 4");
    std::stringstream input2("0 0 2 -2 4 -2 6 0 6 4 4 6 2 6 0 4");
    std::stringstream input3("0 0 2 -2 4 -2 6 0 6 4 4 6 2 10 0 4");

    octagon1.read(input1);
    octagon2.read(input2);
    octagon3.read(input3);

    EXPECT_TRUE(octagon1 == octagon2);
    EXPECT_FALSE(octagon1 == octagon3);
}

class ArrayTest : public ::testing::Test {
protected:
    Array figures;
    Pentagon pentagon;
    Hexagon hexagon;
    Octagon octagon;
};

TEST_F(ArrayTest, TotalArea) {
    std::stringstream input1("0 0 2 -2 4 0 4 4 0 4");
    std::stringstream input2("0 0 2 -2 4 0 4 4 2 6 0 4");
    std::stringstream input3("0 0 2 -2 4 -2 6 0 6 4 4 6 2 6 0 4");

    pentagon.read(input1);
    hexagon.read(input2);
    octagon.read(input3);

    figures.addFigure(&hexagon);
    figures.addFigure(&octagon);
    figures.addFigure(&pentagon);

    EXPECT_EQ(figures.getTotalArea(), 84);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}