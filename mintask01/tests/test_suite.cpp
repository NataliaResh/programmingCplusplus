#include "../Treap.cpp"
#include <exception>
#include <gtest/gtest.h>
#include <string>

using namespace std;

void test(vector<int> keys) {
    Treap t = Treap();
    for (int i = 0; i < keys.size(); i++) {
        t.insert(keys[i]);
    }
    vector<int> currentKeys = t.getKeys();
    EXPECT_EQ(keys.size(), currentKeys.size());
    for (int i = 0; i < currentKeys.size(); i++) {
        EXPECT_TRUE(t.contains(keys[i]));
    }
}

TEST(Test0, Test0) {
    vector<int> keys = {1, 2, 3, 4, 5, 6, 7}; 
    test(keys);
}

TEST(Test1, Test1) {
    vector<int> keys = {1, 2, 3, 4, 5, 6, 7};
    test(keys);
}

TEST(Test2, Test2) {
    vector<int> keys = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    test(keys);
}

TEST(Test3, Test3) {
    vector<int> keys = {0, 2, 3, 4, 5, 6, 8, 1, 9, 10, 11, 12, 13, 14, 15};
    test(keys);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
