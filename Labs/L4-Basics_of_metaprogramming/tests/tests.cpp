#include <gtest/gtest.h>
#include <sstream>

#include "array.h"
#include "figures/figure.h"
#include "figures/pentagon.h"
#include "figures/hexagon.h"
#include "figures/octagon.h"


class PentagonTest : public ::testing::Test {
protected:
    std::shared_ptr<Figure<double>> pentagon1 = std::make_shared<Pentagon<double>>();
    std::shared_ptr<Figure<double>> pentagon2 = std::make_shared<Pentagon<double>>();
    std::shared_ptr<Figure<double>> pentagon3 = std::make_shared<Pentagon<double>>();
};


TEST_F(PentagonTest, ReadAndPrint) {
    std::stringstream input("1 0 0.309 0.951 -0.809 0.588 -0.809 -0.588 0.309 -0.951");
    std::stringstream output;

    pentagon1->read(input);
    pentagon1->print(output);

    auto center = pentagon1->get_center();
    EXPECT_NEAR(center.get_x(), 0, 1e-4);
    EXPECT_NEAR(center.get_y(), 0, 1e-4);
}

TEST_F(PentagonTest, Area) {
    std::stringstream input("1 0 0.309 0.951 -0.809 0.588 -0.809 -0.588 0.309 -0.951");
    std::stringstream output;

    pentagon1->read(input);
    pentagon1->print(output);

    EXPECT_NEAR(static_cast<double>(*pentagon1), 2.37774, 1e-4);
}

TEST_F(PentagonTest, Print) {
    std::stringstream input("1 0 0.309 0.951 -0.809 0.588 -0.809 -0.588 0.309 -0.951");
    std::stringstream output;

    pentagon1->read(input);
    pentagon1->print(output);

    EXPECT_EQ(output.str(), "Pentagon:\nVertex 0: (1, 0)\nVertex 1: (0.309, 0.951)\nVertex 2: (-0.809, 0.588)\nVertex 3: (-0.809, -0.588)\nVertex 4: (0.309, -0.951)\n");
}

TEST_F(PentagonTest, Equality) {
    std::stringstream input1("1 0 0.309 0.951 -0.809 0.588 -0.809 -0.588 0.309 -0.951");
    std::stringstream input2("1 0 0.309 0.951 -0.809 0.588 -0.809 -0.588 0.309 -0.951");
    std::stringstream input3("0.0 2.0 -1.9021 0.618 -1.1756 -1.618 1.1756 -1.618 1.9021 0.618");

    pentagon1->read(input1);
    pentagon2->read(input2);
    pentagon3->read(input2);

    EXPECT_EQ(*pentagon1, *pentagon2);
    EXPECT_NE(*pentagon1, *pentagon3);
}


class HexagonTest : public ::testing::Test {
protected:
    std::shared_ptr<Figure<double>> hexagon1 = std::make_shared<Hexagon<double>>();
    std::shared_ptr<Figure<double>> hexagon2 = std::make_shared<Hexagon<double>>();
    std::shared_ptr<Figure<double>> hexagon3 = std::make_shared<Hexagon<double>>();
};

TEST_F(HexagonTest, ReadAndPrint) {
    std::stringstream input("1 0 0.5 0.866 -0.5 0.866 -1 0 -0.5 -0.866 0.5 -0.866");
    std::stringstream output;

    hexagon1->read(input);
    hexagon1->print(output);

    EXPECT_EQ(output.str(), "Hexagon:\nVertex 0: (1, 0)\nVertex 1: (0.5, 0.866)\nVertex 2: (-0.5, 0.866)\nVertex 3: (-1, 0)\nVertex 4: (-0.5, -0.866)\nVertex 5: (0.5, -0.866)\n");
}

TEST_F(HexagonTest, GetCenter) {
    std::stringstream input("1 0 0.5 0.866 -0.5 0.866 -1 0 -0.5 -0.866 0.5 -0.866");
    hexagon1->read(input);

    auto center = hexagon1->get_center();
    EXPECT_NEAR(center.get_x(), 0, 1e-4);
    EXPECT_NEAR(center.get_y(), 0, 1e-4);
}

TEST_F(HexagonTest, Area) {
    std::stringstream input("1 0 0.5 0.866 -0.5 0.866 -1 0 -0.5 -0.866 0.5 -0.866");
    hexagon1->read(input);

    EXPECT_NEAR(static_cast<double>(*hexagon1), 2.598, 1e-4);
}


TEST_F(HexagonTest, Equality) {
    std::stringstream input1("1 0 0.5 0.866 -0.5 0.866 -1 0 -0.5 -0.866 0.5 -0.866");
    std::stringstream input2("1 0 0.5 0.866 -0.5 0.866 -1 0 -0.5 -0.866 0.5 -0.866");
    std::stringstream input3("0.0 2.0 -1.7321 1.0 -1.7321 -1.0 -0.0 -2.0 1.7321 -1.0 1.7321 1.0");

    hexagon1->read(input1);
    hexagon2->read(input2);
    hexagon3->read(input3);

    EXPECT_TRUE(*hexagon1 == *hexagon2);
    EXPECT_FALSE(*hexagon1 == *hexagon3);
}


class OctagonTest : public ::testing::Test {
protected:
    std::shared_ptr<Figure<double>> octagon1 = std::make_shared<Octagon<double>>();
    std::shared_ptr<Figure<double>> octagon2 = std::make_shared<Octagon<double>>();;
    std::shared_ptr<Figure<double>> octagon3 = std::make_shared<Octagon<double>>();;
};

TEST_F(OctagonTest, ReadAndPrint) {
    std::stringstream input("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    std::stringstream output;

    octagon1->read(input);
    octagon1->print(output);

    EXPECT_EQ(output.str(), "Octagon:\nVertex 0: (1, 0)\nVertex 1: (0.707, 0.707)\nVertex 2: (0, 1)\nVertex 3: (-0.707, 0.707)\nVertex 4: (-1, 0)\nVertex 5: (-0.707, -0.707)\nVertex 6: (0, -1)\nVertex 7: (0.707, -0.707)\n");
}

TEST_F(OctagonTest, GetCenter) {
    std::stringstream input("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    octagon1->read(input);

    auto center = octagon1->get_center();
    EXPECT_NEAR(center.get_x(), 0.0, 1e-4);
    EXPECT_NEAR(center.get_y(), 0.0, 1e-4);
}

TEST_F(OctagonTest, Area) {
    std::stringstream input("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    octagon1->read(input);

    EXPECT_NEAR(static_cast<double>(*octagon1), 2.828, 1e-4);
}


TEST_F(OctagonTest, Equality) {
    std::stringstream input1("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    std::stringstream input2("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    std::stringstream input3("0.0 2.0 -1.4142 1.4142 -2.0 0.0 -1.4142 -1.4142 -0.0 -2.0 1.4142 -1.4142 2.0 -0.0 1.4142 1.4142 ");

    octagon1->read(input1);
    octagon2->read(input2);
    octagon3->read(input3);

    EXPECT_TRUE(*octagon1 == *octagon2);
    EXPECT_FALSE(*octagon1 == *octagon3);
}

class ArrayTest : public ::testing::Test {
protected:
    Array<Figure<double> > figures;
    std::shared_ptr<Figure<double>> pentagon = std::make_shared<Pentagon<double>>();
    std::shared_ptr<Figure<double>> hexagon = std::make_shared<Hexagon<double>>();
    std::shared_ptr<Figure<double>> octagon = std::make_shared<Octagon<double>>();
};

TEST_F(ArrayTest, TotalArea) {
    std::stringstream input1("1 0 0.309 0.951 -0.809 0.588 -0.809 -0.588 0.309 -0.951");
    std::stringstream input2("1 0 0.5 0.866 -0.5 0.866 -1 0 -0.5 -0.866 0.5 -0.866");
    std::stringstream input3("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");

    pentagon->read(input1);
    hexagon->read(input2);
    octagon->read(input3);

    figures.push_back(hexagon);
    figures.push_back(octagon);
    figures.push_back(pentagon);

    EXPECT_NEAR(figures.get_total_area(), 7.80374, 1e-4);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

