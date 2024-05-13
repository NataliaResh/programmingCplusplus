#include "../Treap.cpp"
#include <exception>
#include <gtest/gtest.h>
#include <string>
#include <iostream>

using namespace std;

void test(vector<int> keys) {
    Treap t = Treap<int>();
    for (int i = 0; i < keys.size(); i++) {
        t.insert(keys[i]);
    }
    vector<int> *currentKeys = t.getKeys();
    EXPECT_EQ(keys.size(), currentKeys->size());
    for (int i = 0; i < currentKeys->size(); i++) {
        EXPECT_EQ(t.contains(keys[i]), true);
    }
    Treap t2 = Treap(t);
    t2.insert(20);
    EXPECT_EQ(t.contains(20), false);
    EXPECT_EQ(t2.contains(20), true);
    Treap t3 = Treap<int>();
    t3 = t;
    t3.insert(20);
    EXPECT_EQ(t.contains(20), false);
    EXPECT_EQ(t3.contains(20), true);
    EXPECT_EQ(t3.contains(20), true);
    auto it = t.begin();
    while (it != t.end()){
      std::cout << it->key << " ";
      ++it;
    }
    std::cout << "\n";
    for (auto&& el: t) {
      std::cout << el.key << " ";
    }
    std::cout << "\n";
    delete currentKeys;
}

Treap<int> createTreap(int size) {
    if (size <= 0) {
      return Treap<int>();
    }
    Treap result = Treap<int>();
    for (int i = 0; i < size; i++) {
       result.insert(i);
    }
    return result;
}

void testMove(vector<int> keys1, vector<int> keys2) {
    Treap t1 = Treap<int>();
    for (int i = 0; i < keys1.size(); i++) {
        t1.insert(keys1[i]);
    }

    Treap t2 = Treap<int>();
    for (int i = 0; i < keys2.size(); i++) {
        t2.insert(keys2[i]);
    }
    
    Treap t3 = t1 + t2;
    EXPECT_EQ(t3.contains(3), true);
    EXPECT_EQ(t1.contains(8), false);
}

void testMove2() {
    EXPECT_EQ(createTreap(10).contains(5), true);
}
TEST(Test0, Test0) {
    vector<int> keys = {1, 2, 3, 4, 5, 6, 7, 434, 54, 31, 11, 10, 32, 8, 11};
    test(keys);
}

TEST(Test1, Test1) {
    vector<int> keys = {1, 2, 3, 4, 5, 6, 7};
    test(keys);
}

TEST(Test2, Test2) {
    vector<int> keys = {1};
    test(keys);
}

TEST(Test3, Test3) {
    vector<int> keys = {};
    test(keys);
}

TEST(Test4, Test4) {
    vector<int> keys = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    test(keys);
}

TEST(Test5, Test5) {
    vector<int> keys1 = {1, 2, 3, 4, 5, 6, 7};
    vector<int> keys2 = {8, 9, 10, 11};
    testMove(keys1, keys2);
}

TEST(Test6, Test6) {
  testMove2();
}
int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
