#pragma once

#include <random>
#include <type_traits>
#include <vector>
#include <shared_mutex>
#include <mutex>
#include <memory>
#include "SharedPointer.h"

using namespace std;

template<typename T>
class Treap {
    struct Node {
        T key;
        int priority;
        SharedPointer<Node> left, right;

        Node() = delete;

        Node(T key, int priority) : key(key), priority(priority) {
        }

        SharedPointer<Node> copyNode() {
            SharedPointer<Node> newNode = SharedPointer<Node>::make_shared(key, priority);
            if (left != nullptr) {
                newNode->left = left->copyNode();
            }
            if (right != nullptr) {
                newNode->right = right->copyNode();
            }
            return newNode;
        }
    };

    random_device rd_;
    mt19937 generator_;
    uniform_int_distribution<int> dist_;

    mutable std::mutex mutex_;

    SharedPointer<Node> root_;

    static SharedPointer<Node> merge(SharedPointer<Node> t1, SharedPointer<Node> t2) {
        if (t1 == nullptr)
            return t2;
        if (t2 == nullptr)
            return t1;
        if (t1->priority > t2->priority) {
            t1->right = merge(t1->right, t2);
            return t1;
        } else {
            t2->left = merge(t1, t2->left);
            return t2;
        }
    }

    void split(SharedPointer<Node> t, int key, SharedPointer<Node> &t1, SharedPointer<Node> &t2) {
        if (t == nullptr) {
            t1 = t2 = SharedPointer<Node>();
            return;
        }
        if (t->key < key) {
            split(t->right, key, t->right, t2);
            t1 = t;
        } else {
            split(t->left, key, t1, t->left);
            t2 = t;
        }
    }

    bool containsImp(T key, SharedPointer<Node> node) {
        if (node == nullptr) {
            return false;
        }
        if (node->key == key) {
            return true;
        }
        if (key < node->key) {
            return containsImp(key, node->left);
        } else {
            return containsImp(key, node->right);
        }
    }

    void getKeysImp(SharedPointer<Node> node, vector<T> &keys) {
        if (node == nullptr) {
            return;
        }
        if (node->left) {
            getKeysImp(node->left, keys);
        }
        if (node->right) {
            getKeysImp(node->right, keys);
        }
        keys.push_back(node->key);
    }

    static void insertNodes(Treap &t, SharedPointer<Node> right) {
        t.insert(right->key);
        if (right->left) {
            insertNodes(t, right->left);
        }
        if (right->right) {
            insertNodes(t, right->right);
        }
    }

    void copy(const Treap &other) {
        if (other.root_ == nullptr) {
            root_ = SharedPointer<Node>();
        } else {
            root_ = other.root_->copyNode();
        }
    }

public:
    Treap() : generator_(rd_()) {}

    Treap(const Treap &other) {
        const std::lock_guard<std::mutex> lock(mutex_);
        copy(other);
    }

    Treap &operator=(const Treap &other) {
        if (this != &other) {
            std::scoped_lock lock{mutex_, other.mutex_};
            copy(other);
        }
        return *this;
    }


    Treap(Treap &&other) {
        root_ = other.root_;
        other.root_ = SharedPointer<Node>();
    }

    Treap &operator=(Treap &&other) {
        if (this != &other) {
            delete root_;
            root_ = other.root_;
            other.root_ = SharedPointer<Node>();
        }
        return *this;
    }

    Treap operator+(const Treap &right) {
        Treap result = *this;
        insertNodes(result, right.root_);
        return result;
    }

    void insert(T key) {
        const std::lock_guard<std::mutex> lock(mutex_);
        SharedPointer<Node> less, greater;
        split(root_, key, less, greater);
        less = merge(less, SharedPointer<Node>::make_shared(key, dist_(generator_)));
        root_ = merge(less, greater);
    }

    void remove(T key) {
        SharedPointer<Node> less, equal, greater;
        split(root_, key, less, greater);
        split(greater, key + 1, equal, greater);
        root_ = merge(less, greater);
    }

    bool try_remove(T key) {
        const std::lock_guard<std::mutex> lock(mutex_);
        if (root_ == SharedPointer<Node>()) {
            return false;
        }
        remove(key);
        return true;
    }

    bool contains(T key) {
        const std::lock_guard<std::mutex> lock(mutex_);
        return containsImp(key, root_);
    }

    vector<T> getKeys() {
        const std::lock_guard<std::mutex> lock(mutex_);
        vector<T> keys;
        getKeysImp(root_, keys);
        return keys;
    }

    class Iterator {
    private:
        void getArray(SharedPointer<Node> root) {
            if (root == nullptr) {
                return;
            }
            array.push_back(root);
            getArray(root->left);
            getArray(root->right);
        }

    public:
        size_t i = 0;
        vector<SharedPointer<Node>> array;

        explicit Iterator(SharedPointer<Node> node) {
            getArray(node);
            array.push_back(SharedPointer<Node>());
        }

        Node &operator*() const {
            return *(array[i]);
        }

        SharedPointer<Node> operator->() const {
            return array[i];
        };

        bool operator==(const Iterator &other) const {
            return array[i] == other.array[other.i];
        }

        bool operator!=(const Iterator &other) const {
            return array[i] != other.array[other.i];
        }

        Iterator &operator++() {
            ++i;
            return *this;
        };
    };

    Iterator begin() {
        const std::lock_guard<std::mutex> lock(mutex_);
        return Iterator(root_);
    }

    Iterator end() { return Iterator(SharedPointer<Node>()); }
};
