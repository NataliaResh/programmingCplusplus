#include "../ScopedPointer.cpp"
#include <exception>
#include <gtest/gtest.h>
#include <string>

using namespace std;

struct Triple { int x; int y; int z; };

void testCopy() {
  ScopedPointerCopy sp{new Triple{13, 42, 1}};
  ScopedPointerCopy sp2 = sp;
  sp2->x = 1;
  EXPECT_EQ(sp->x, 13);
}

void testMove() {
  ScopedPointerMove sp{new Triple{13, 42, 1}};
  ScopedPointerMove sp2 = std::move(sp);
  sp2->x = 1;
  EXPECT_EQ(sp2->x, 1);
}

TEST(Test0, Test0) {
  testCopy();
}

TEST(Test1, Test1) {
  testMove();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
