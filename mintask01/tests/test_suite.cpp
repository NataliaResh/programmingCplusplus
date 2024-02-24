#include "../Treap.cpp"
#include <exception>
#include <gtest/gtest.h>
#include <string>

using namespace std;

void test(vector<int> keys, vector<int> priorities, vector<int> expectedKeys) {
    Treap *t = new Treap();
    for (int i = 0; i < keys.size(); i++) {
        t->insert(keys[i], priorities[i]);
    }
    vector<int> *currentKeys = t->getKeys();
    EXPECT_EQ(expectedKeys.size(), currentKeys->size());
    for (int i = 0; i < expectedKeys.size(); i++) {
        EXPECT_EQ(expectedKeys[i], currentKeys->at(i));
    }
    delete t;
    delete currentKeys;
}

TEST(Test0, Test0) {
    vector<int> keys = {1, 2, 3, 4, 5, 6, 7};
    vector<int> priorities = {1, 3, 7, 2, 5, 6, 4};
    vector<int> expectedKeys = {1, 2, 4, 5, 7, 6, 3};
    test(keys, priorities, expectedKeys);
}

TEST(Test1, Test1) {
    vector<int> keys = {1, 2, 3, 4, 5, 6, 7};
    vector<int> priorities = {2, 1, 4, 3, 5, 7, 6};
    vector<int> expectedKeys = {2, 1, 4, 3, 5, 7, 6};
    test(keys, priorities, expectedKeys);
}

TEST(Test2, Test2) {
    vector<int> keys = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> priorities = {4, 2, 8, 5, 10, 6, 3, 9, 1, 7};
    vector<int> expectedKeys = {2, 1, 4, 3, 7, 6, 9, 10, 8, 5};
    test(keys, priorities, expectedKeys);
}

TEST(Test3, Test3) {
    vector<int> keys = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> priorities = {1, 5, 4, 10, 8, 6, 9, 3, 2, 7};
    vector<int> expectedKeys = {1, 3, 2, 6, 5, 9, 8, 10, 7, 4};
    test(keys, priorities, expectedKeys);
}

TEST(Test4, Test4) {
    vector<int> keys = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    vector<int> priorities = {3, 5, 7, 12, 8, 14, 1, 9, 4, 15, 11, 2, 13, 6, 10};
    vector<int> expectedKeys = {1, 2, 3, 5, 4, 7, 9, 8, 6, 12, 11, 14, 15, 13, 10};
    test(keys, priorities, expectedKeys);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
