#include "../Container.h"
#include <exception>
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

struct Point {
    int x;
    int y;

    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }

    Point(int x, int y)  noexcept {
        std::cout << "create " << x << "\n";
        this->x = x;
        this->y = y;
    }

    Point(Point&& other) noexcept : x(other.x), y(other.y) {
        std::cout << "move " << x << "\n";
    }

    Point(const Point& other) noexcept {
        x = other.x;
        y = other.y;
        std::cout << "copy " << x << "\n";
    };

    Point& operator=(const Point& other) noexcept {
        std::cout << "===== " << x << "\n";
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
    Point& operator=(Point&& other) noexcept {
        std::cout << "=1==== " << x << "\n";
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    ~Point() {
        std::cout << "destroy\n";
    }
};

TEST(Test0, Test0) {
    Container<int, char, Point> c(12, 'c', Point{3, 3});
    EXPECT_EQ(c.getElement<int>(0), 12);
    EXPECT_EQ(c.getElement<char>(1), 'c');
    auto p = Point{2, 3};
    EXPECT_TRUE(c.getElement<Point>(2) != p);
}

TEST(Test1, Test1) {
    Container<Point> c(Point{1, 2});
}

TEST(Test2, Test2) {
    Container<> c;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
