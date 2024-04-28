#include "../Counter.cpp"
#include <exception>
#include <gtest/gtest.h>
#include <string>
#include <iostream>

using namespace std;

struct Point : Counter<Point, 2> {};


template <typename T>
class Vector : Counter<Vector<T>, 3> {};

void foo(Point*& p2) {
  Point p1;
  p2 = new Point();
}

TEST(Test0, Test0) {
  Point *p2;
  foo(p2);
  Point p3;
  EXPECT_THROW(Point(), MaxCountInstances);
  delete p2;
}

TEST(Test1, Test1) {
  Vector<int> v1;
  Vector<Point> v2;
  Vector<int> v3;
  Vector<int> v4;
  EXPECT_THROW(Vector<int>(), MaxCountInstances);
  Vector<Point> v5;
  Vector<Point> v6 = v5;
  EXPECT_THROW(Vector<Point>(), MaxCountInstances);
}
int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
