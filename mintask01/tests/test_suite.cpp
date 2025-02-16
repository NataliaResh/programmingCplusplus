#include "../Treap.cpp" // PR: it is not really nice to include
                        // source files somwhere
                        // maybe we can split our class to source and header part?
#include <exception>
#include <gtest/gtest.h>
#include <string>

using namespace std;

void test(vector<int> keys) {
    Treap t = Treap(); // PR: this is value init for class
                       // in this case it works fine and default destructor called
                       // but we don't like this method of initialization for classes
                       // you need to consider too many nuances 
                       // to make it work correctly
                       // I recommend to avoid value init for non tmp classes
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
    ::testing::InitGoogleTest(&argc, argv); // PR '::somename' it is just synonimous
                                            // for global namespace and it is redundant
    return RUN_ALL_TESTS();
}
