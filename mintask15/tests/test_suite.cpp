#include "../Container.h"
#include <exception>
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

struct Point {
    int x;
    int y;

    bool operator==(const Point& p) {
        return x == p.x && y == p.y;
    }
};

TEST(Test0, Test0) {
    Container<int, char, Point> c(12, 'c', Point{2, 3});
    EXPECT_EQ(c.getElement<int>(0), 12);
    EXPECT_EQ(c.getElement<char>(1), 'c');
    Point p = Point{2, 3};
    EXPECT_TRUE(c.getElement<Point>(2) == p);
}

TEST(Test1, Test1) {
    Container<int> c(42);
}

TEST(Test2, Test2) {
    Container<> c;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
