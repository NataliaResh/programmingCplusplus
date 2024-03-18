#include "../Treap.cpp"
#include <exception>
#include <gtest/gtest.h>
#include <string>

using namespace std;

void test(vector<int> keys, vector<int> priorities, vector<int> expectedKeys) {
    Treap t = Treap();
    for (int i = 0; i < keys.size(); i++) {
        t.insert(keys[i], priorities[i]);
    }
    vector<int> *currentKeys = t.getKeys();
    EXPECT_EQ(expectedKeys.size(), currentKeys->size());
    for (int i = 0; i < expectedKeys.size(); i++) {
        EXPECT_EQ(expectedKeys[i], currentKeys->at(i));
    }
    Treap t2 = Treap(t);
    t2.insert(20, 2);
    EXPECT_EQ(t.contains(20), false);
    EXPECT_EQ(t2.contains(20), true);
    Treap t3 = Treap();
    t3 = t;
    t3.insert(20, 20);
    EXPECT_EQ(t.contains(20), false);
    EXPECT_EQ(t3.contains(20), true);
    EXPECT_EQ(t3.contains(20), true);

    delete currentKeys;
}

Treap createTreap(int size) {
    if (size <= 0) {
      return Treap();
    }
    Treap result = Treap();
    for (int i = 0; i < size; i++) {
       result.insert(i, i);
    }
    return result;
}

void testMove(vector<int> keys1, vector<int> priorities1, vector<int> keys2, vector<int> priorities2) {
    Treap t1 = Treap();
    for (int i = 0; i < keys1.size(); i++) {
        t1.insert(keys1[i], priorities1[i]);
    }

    Treap t2 = Treap();
    for (int i = 0; i < keys2.size(); i++) {
        t2.insert(keys2[i], priorities2[i]);
    }
    
    Treap t3 = t1 + t2;
    EXPECT_EQ(t3.contains(3), true);
    EXPECT_EQ(t1.contains(8), false);
}

void testMove2() {
  cout << createTreap(10).contains(5) << "\n";
}
TEST(Test0, Test0) {
    vector<int> keys = {1, 2, 3, 4, 5, 6, 7};
    vector<int> priorities = {1, 30, 7, 2, 5, 6, 4};
    vector<int> expectedKeys = {1, 4, 5, 7, 6, 3, 2};
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

TEST(Test5, Test5) {
    vector<int> keys1 = {1, 2, 3, 4, 5, 6, 7};
    vector<int> priorities1 = {3, 30, 20, 5, 12, 15, 10};
    vector<int> keys2 = {8, 9, 10, 11};
    vector<int> priorities2 = {13, 1, 7, 4};

    testMove(keys1, priorities1, keys2, priorities2);
}

TEST(Test6, Test6) {
  testMove2();
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
