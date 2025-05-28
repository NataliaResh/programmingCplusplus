#include "../Treap.h"
#include <exception>
#include <gtest/gtest.h>
#include <iostream>
#include <thread>
#include "../WeakPointer.h"

using namespace std;

void test(vector<int> keys) {
    Treap t = Treap<int>();
    for (int key : keys) {
        t.insert(key);
    }
    vector<int> currentKeys = t.getKeys();
    EXPECT_EQ(keys.size(), currentKeys.size());
    for (int i = 0; i < currentKeys.size(); i++) {
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
    while (it != t.end()) {
        std::cout << it->key << " ";
        ++it;
    }
    std::cout << "\n";
    for (auto &&el: t) {
        std::cout << el.key << " ";
    }
    std::cout << "\n";
}

Treap<int> createTreap(int size) {
    if (size <= 0) {
        return {};
    }
    Treap result = Treap<int>();
    for (int i = 0; i < size; i++) {
        result.insert(i);
    }
    return result;
}

void testMove(vector<int> keys1, vector<int> keys2) {
    Treap t1 = Treap<int>();
    for (int i : keys1) {
        t1.insert(i);
    }

    Treap t2 = Treap<int>();
    for (int i : keys2) {
        t2.insert(i);
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

TEST(Test7, Test7) {
    Treap<size_t> treap;
    const size_t iters = 100;
    size_t count_removed = 0;

    std::thread producer([&] {
        for (size_t i = 0; i < iters; ++i) {
            treap.insert(i);
        }
    });

    std::thread consumer([&] {
        while(count_removed < iters) {
            if (treap.try_remove(count_removed)) {
                count_removed++;
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(10));
            }
        }
    });

    producer.join();
    consumer.join();
    EXPECT_EQ(count_removed, iters);
}

TEST(Test8, Test8) {
    Treap<size_t> treap;
    const size_t iters = 1000;
    std::mutex mtx;
    std::condition_variable cv;
    bool finished = false;
    size_t count_removed = 0;

    std::thread producer([&] {
        for (size_t i = 0; i < iters; ++i) {
            treap.insert(i);
        }
        {
            std::lock_guard lock(mtx);
            finished = true;
        }
        cv.notify_one();
    });

    std::thread consumer([&] {
        std::unique_lock lock(mtx);
        while (!finished) {
            cv.wait(lock);
        }

        for (size_t i = 0; i < iters; ++i) {
            ASSERT_TRUE(treap.try_remove(i));
            count_removed++;
        }
    });

    producer.join();
    consumer.join();
    EXPECT_EQ(count_removed, iters);
}

template <typename T>
struct LinkedList {
    struct Node {
        T key;
        SharedPointer<Node> next = SharedPointer<Node>();
        WeakPointer<Node> prev = SharedPointer<Node>();
        explicit Node (T key) : key(key) {}
        ~Node() {
            std::cout << "delete node " << key << "\n";
        }
    };
    SharedPointer<Node> root = SharedPointer<Node>();

    void add(T key) {
        auto node = SharedPointer<Node>(new Node(key));
        if (root == nullptr) {
            root = node;
        } else {
            SharedPointer<Node> tmp = root;
            while(tmp->next) {
                tmp = tmp->next;
            }
            tmp->next = node;
            node->prev = tmp;
        }
    }
    T pop() {
        SharedPointer<Node> tail = root;
        SharedPointer<Node> tmp = tail->next;
        while(tmp != nullptr) {
            tail = tmp;
            tmp = tmp->next;
        }
        tmp->prev = WeakPointer<Node>();
        tail->next = SharedPointer<Node>();
    }

    ~LinkedList() {
    }
};

TEST(SimpleTestWeakPointer, SimpleTestWeakPointer) {
    auto ptr = SharedPointer<int>(new int(42));
    WeakPointer<int> weak_ptr = ptr;
    auto lock_ptr = weak_ptr.lock();
    EXPECT_EQ(ptr.count_use(), 2);
}

TEST(SimpleTestWeakPointer2, SimpleTestWeakPointer2) {
    LinkedList<size_t> list;
    list.add(1);
    EXPECT_EQ(list.root.count_use(), 1);
}

TEST(SimpleTestWeakPointer3, SimpleTestWeakPointer3) {
    LinkedList<size_t> list;
    list.add(1);
    list.add(2);
    EXPECT_EQ(list.root.count_use(), 1);
}
//
//TEST(TestWeakPointer, TestWeakPointer) {
//    LinkedList<size_t> list;
//    const size_t iters = 100;
//    size_t count_removed = 0;
//
//    std::thread producer([&] {
//        for (size_t i = 0; i < iters; ++i) {
//            list.add(i);
//        }
//    });
//
////    std::thread consumer([&] {
////        while(count_removed < iters) {
////            if (list.pop()) {
////                count_removed++;
////                std::this_thread::sleep_for(
////                    std::chrono::milliseconds(10));
////            }
////        }
////    });
////
//    producer.join();
////    consumer.join();
//    //EXPECT_EQ(count_removed, iters);
//}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
