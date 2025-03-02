#include "../Line.h" // PR: including source files looks very strange
                       // maybe we can say that this file is header?
#include <exception>
#include <gtest/gtest.h>

using namespace std;

TEST(Test0, Test0) {
    Point p1 = Point(-2, -1), p2 = Point(4, 3);
    Line line = Line(p1, p2);
    Line pLine = line.perpendicular(Point(-1,  4));
    auto p = line.intersection(pLine);
    if (!p.has_value()) {
        ASSERT_FALSE(true);
    }
    Point expPoint = Point(1, 1);
    ASSERT_TRUE(expPoint == p);
}

TEST(Test1, Test1) {
    Line lineY = Line(0, 0), lineX = Line(1, 0, 0);
    auto o = lineY.intersection(lineX);
    if (!o.has_value()) {
        FAIL();
    }
    Point expPoint = Point(0, 0);
    ASSERT_TRUE(expPoint == o.value());
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
    auto p = line1.intersection(line2);
    if (!p.has_value()) {
        FAIL();
    }
    Point expPoint = Point(3, 5);
    ASSERT_TRUE(expPoint == p);
}

TEST(Test4, Test4) {
    optional<Line> line = Line::createLineFromCoeffs(0, 0, 0);
    ASSERT_TRUE(line == nullopt);
}

TEST(Test5, Test5) {
    optional<Line> line = Line::createLineFromCoeffs(1, 0, 0);
    ASSERT_FALSE(line == nullopt);
}

TEST(Test6, Test6) {
    Point p1{1, 2}, p2{1, 2};
    auto line = Line::createLineFromPoints(p1, p2);
    ASSERT_TRUE(line == nullopt);
}

TEST(Test7, Test7) {
    Point p1{1, 2}, p2{1, 3};
    auto line = Line::createLineFromPoints(p1, p2);
    ASSERT_FALSE(line == nullopt);
}

TEST(ReviewTest, TrickyFloats) {
    auto line = Line::createLineFromCoeffs(1e-7, 1e-7, 1e-7);

    ASSERT_TRUE(line != std::nullopt);

    // check that given line coeffs are not zeroes at once with given prescision
    // but in this example all coeffs will be zeroes(
    ASSERT_TRUE((std::fabs(line->a()) + std::fabs(line->b()) + std::fabs(line->c())) > e);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv); // PR: again redundant '::'
    return RUN_ALL_TESTS();
}
