#include "../Allocator.h"
#include <exception>
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

struct Point {
    int x;
    int y;
};

TEST(Test0, Test0) {
    char memory[2] = {0, 0};
    allocate<0>(memory);
}

TEST(Test1, Test1) {
    char memory[2] = {0, 0};
    allocate<1>(memory, 'a');
    EXPECT_EQ(memory[0], 'a');
}

TEST(Test2, Test2) {
    char memory[2] = {0, 0};
    allocate<2>(memory, 'a');
    EXPECT_EQ(memory[0], 'a');
}

TEST(Test3, Test3) {
    char memory[2] = {0, 0};
    allocate<2>(memory, 'a', 'b');
    EXPECT_EQ(memory[0], 'a');
    EXPECT_EQ(memory[1], 'b');
}

TEST(Test4, Test4) {
    int memory[10];
    allocate<10>(memory, 10, 42, 'a');
    EXPECT_EQ(memory[1], 42);
}

TEST(Test5, Test5) {
    char* memory = new char[12];
    allocate<12>(memory, 'a', Point{3, 4});
    delete[] memory;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
