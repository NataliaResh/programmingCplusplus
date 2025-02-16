#include "../Line.cpp" // PR: including source files looks very strange
                       // maybe we can say that this file is header?
#include <exception>
#include <gtest/gtest.h>

using namespace std;

TEST(Test0, Test0) {
    Point p1 = Point(-2, -1), p2 = Point(4, 3);
    Line line = Line(p1, p2);
    Line *pLine = line.perpendicular(Point(-1,  4));
    Point p = *line.intersection(*pLine);
    Point expPoint = Point(1, 1);
    ASSERT_TRUE(expPoint == p);
    delete pLine;
}

TEST(Test1, Test1) {
    Line lineY = Line(0, 0), lineX = Line(1, 0, 0);
    Point o = *lineY.intersection(lineX);
    Point expPoint = Point(0, 0);
    ASSERT_TRUE(expPoint == o);
}

TEST(Test2, Test2) {
    Line line1 = Line(1, 0, -1);
    Line line2 = Line(1, 0, -2);
    ASSERT_TRUE(line1.intersection(line2) == nullopt);
}

TEST(Test3, Test3) {
    Line line1 = Line(1, 2);
    Point p1 = Point(3, -2), p2 = Point(3, 100);
    Line line2 = Line(p1, p2);
    Point p = *line1.intersection(line2);
    Point expPoint = Point(3, 5);
    ASSERT_TRUE(expPoint == p);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); // PR: again redundant '::'
    return RUN_ALL_TESTS();
}
