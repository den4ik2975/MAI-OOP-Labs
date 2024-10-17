#include <gtest/gtest.h>
#include <sstream>

#include "array.h"
#include "figures/figure.h"
#include "figures/triangle.h"
#include "figures/square.h"
#include "figures/rectangle.h"


class RectangleTest : public ::testing::Test {
protected:
    Rectangle rectangle1;
    Rectangle rectangle2;
    Rectangle rectangle3;
};


TEST_F(RectangleTest, ReadAndPrint) {
    std::stringstream input("0 0 4 0 4 3 0 3");
    std::stringstream output;

    rectangle1.read(input);
    rectangle1.print(output);

    auto center = rectangle1.getCenter();
    EXPECT_NEAR(center.first, 2.0, 1e-6);
    EXPECT_NEAR(center.second, 1.5, 1e-6);
}

TEST_F(RectangleTest, Area) {
    std::stringstream input("0 0 4 0 4 3 0 3");
    std::stringstream output;

    rectangle1.read(input);
    rectangle1.print(output);

    EXPECT_NEAR(static_cast<double>(rectangle1), 12.0, 1e-6);
}

TEST_F(RectangleTest, Print) {
    std::stringstream input("0 0 2 0 2 2 0 2");
    std::stringstream output;
    Rectangle rectangle;

    rectangle.read(input);
    rectangle.print(output);

    EXPECT_EQ(output.str(), "Rectangle:\n(0, 0)\n(2, 0)\n(2, 2)\n(0, 2)\n");
}

TEST_F(RectangleTest, Clone) {
    std::stringstream input("0 0 4 0 4 3 0 3");
    std::stringstream output;

    rectangle1.read(input);
    rectangle1.print(output);

    std::unique_ptr<Figure> cloned(rectangle1.clone());
    EXPECT_EQ(typeid(*cloned), typeid(Rectangle));
    EXPECT_EQ(*cloned, rectangle1);
}

TEST_F(RectangleTest, Equality) {
    std::stringstream input1("0 0 4 0 4 3 0 3");
    std::stringstream output1;

    rectangle1.read(input1);
    rectangle1.print(output1);

    std::stringstream input2("0 0 4 0 4 3 0 3");
    std::stringstream output2;

    rectangle2.read(input2);
    rectangle2.print(output2);

    EXPECT_EQ(rectangle1, rectangle2);

    std::stringstream input3("0 0 5 0 5 4 0 4");
    std::stringstream output3;

    rectangle3.read(input2);
    rectangle3.print(output2);

    EXPECT_NE(rectangle1, rectangle3);
}


class TriangleTest : public ::testing::Test {
protected:
    Triangle triangle1;
    Triangle triangle2;
    Triangle triangle3;
};

TEST_F(TriangleTest, DefaultConstructor) {
    EXPECT_EQ(triangle1.getCenter(), std::make_pair(0.0, 0.0));
    EXPECT_DOUBLE_EQ(static_cast<double>(triangle1), 0.0);
}

TEST_F(TriangleTest, ReadAndPrint) {
    std::stringstream input("0 0 3 0 0 4");
    std::stringstream output;

    triangle1.read(input);
    triangle1.print(output);

    EXPECT_EQ(output.str(), "Triangle:\n(0, 0)\n(3, 0)\n(0, 4)\n");
}

TEST_F(TriangleTest, GetCenter) {
    std::stringstream input("0 0 4 0 2 4");
    triangle1.read(input);

    auto center = triangle1.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 2.0);
    EXPECT_DOUBLE_EQ(center.second, 4.0 / 3.0);
}

TEST_F(TriangleTest, Area) {
    std::stringstream input("0 0 3 0 0 4");
    triangle1.read(input);

    EXPECT_DOUBLE_EQ(static_cast<double>(triangle1), 6.0);
}


TEST_F(TriangleTest, Clone) {
    std::stringstream input("0 0 3 0 0 4");
    triangle1.read(input);

    std::unique_ptr<Figure> clonedFigure(triangle1.clone());

    EXPECT_EQ(clonedFigure->getCenter(), triangle1.getCenter());
    EXPECT_DOUBLE_EQ(static_cast<double>(*clonedFigure), static_cast<double>(triangle1));
}

TEST_F(TriangleTest, Equality) {
    std::stringstream input1("0 0 3 0 0 4");
    std::stringstream input2("0 0 3 0 0 4");
    std::stringstream input3("0 0 4 0 0 3");

    triangle1.read(input1);
    triangle2.read(input2);
    triangle3.read(input3);

    EXPECT_TRUE(triangle1 == triangle2);
    EXPECT_FALSE(triangle1 == triangle3);
}


class SquareTest : public ::testing::Test {
protected:
    Square square1;
    Square square2;
    Square square3;
};

TEST_F(SquareTest, ReadAndPrint) {
    std::stringstream input("0 0 2 0 2 2 0 2");
    std::stringstream output;

    square1.read(input);
    square1.print(output);

    EXPECT_EQ(output.str(), "Square:\n(0, 0)\n(2, 0)\n(2, 2)\n(0, 2)\n");
}

TEST_F(SquareTest, GetCenter) {
    std::stringstream input("0 0 2 0 2 2 0 2");
    square1.read(input);

    auto center = square1.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 1.0);
    EXPECT_DOUBLE_EQ(center.second, 1.0);
}

TEST_F(SquareTest, Area) {
    std::stringstream input("0 0 2 0 2 2 0 2");
    square1.read(input);

    EXPECT_DOUBLE_EQ(static_cast<double>(square1), 4.0);
}


TEST_F(SquareTest, Clone) {
    std::stringstream input("0 0 2 0 2 2 0 2");
    square1.read(input);

    std::unique_ptr<Figure> clonedFigure(square1.clone());

    EXPECT_EQ(clonedFigure->getCenter(), square1.getCenter());
    EXPECT_DOUBLE_EQ(static_cast<double>(*clonedFigure), static_cast<double>(square1));
}

TEST_F(SquareTest, Equality) {
    std::stringstream input1("0 0 2 0 2 2 0 2");
    std::stringstream input2("0 0 2 0 2 2 0 2");
    std::stringstream input3("0 0 3 0 3 3 0 3");

    square1.read(input1);
    square2.read(input2);
    square3.read(input3);

    EXPECT_TRUE(square1 == square2);
    EXPECT_FALSE(square1 == square3);
}

class ArrayTest : public ::testing::Test {
protected:
    Array figures;
    Triangle triangle;
    Rectangle rectangle;
    Square square;
};

TEST_F(ArrayTest, TotalArea) {
    std::stringstream input1("1 1 3 1 2 3");
    std::stringstream input2("4 1 6 1 4 3 6 3");
    std::stringstream input3("7 1 10 1 7 5 10 5");

    triangle.read(input1);
    square.read(input2);
    rectangle.read(input3);

    figures.addFigure(&triangle);
    figures.addFigure(&square);
    figures.addFigure(&rectangle);

    EXPECT_EQ(figures.getTotalArea(), 18);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}