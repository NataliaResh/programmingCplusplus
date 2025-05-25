#pragma once

#include <random>
#include <type_traits>
#include <vector>
#include <shared_mutex>
#include <mutex>
#include <memory>

using namespace std;

template<typename T>
class Treap {
    struct Node {
        T key;
        int priority;
        std::shared_ptr<Node> left, right;

        Node() = delete;

        Node(T key, int priority) : key(key), priority(priority) {
        }

        std::shared_ptr<Node> copyNode() {
            std::shared_ptr<Node> newNode = std::make_shared<Node>(key, priority);
            if (left) {
                newNode->left = left->copyNode();
            }
            if (right) {
                newNode->right = right->copyNode();
            }
            return newNode;
        }
    };

    random_device rd_;
    mt19937 generator_;
    uniform_int_distribution<int> dist_;

    mutable std::mutex mutex_;

    std::shared_ptr<Node> root_;

    static std::shared_ptr<Node> merge(std::shared_ptr<Node> t1, std::shared_ptr<Node> t2) {
        if (!t1)
            return t2;
        if (!t2)
            return t1;
        if (t1->priority > t2->priority) {
            t1->right = merge(t1->right, t2);
            return t1;
        } else {
            t2->left = merge(t1, t2->left);
            return t2;
        }
    }

    void split(std::shared_ptr<Node> t, int key, std::shared_ptr<Node> &t1, std::shared_ptr<Node> &t2) {
        if (!t) {
            t1 = t2 = nullptr;
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

    bool containsImp(T key, std::shared_ptr<Node> node) {
        if (!node) {
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

    void getKeysImp(std::shared_ptr<Node> node, vector<T> &keys) {
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

    static void insertNodes(Treap &t, std::shared_ptr<Node> right) {
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
            root_ = nullptr;
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
        other.root_ = nullptr;
    }

    Treap &operator=(Treap &&other) {
        if (this != &other) {
            delete root_;
            root_ = other.root_;
            other.root_ = nullptr;
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
        std::shared_ptr<Node> less, greater;
        split(root_, key, less, greater);
        less = merge(less, std::make_shared<Node>(key, dist_(generator_)));
        root_ = merge(less, greater);
    }

    void remove(T key) {
        std::shared_ptr<Node> less, equal, greater;
        split(root_, key, less, greater);
        split(greater, key + 1, equal, greater);
        root_ = merge(less, greater);
    }

    bool try_remove(T key) {
        const std::lock_guard<std::mutex> lock(mutex_);
        if (root_ == nullptr) {
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
        void getArray(std::shared_ptr<Node> root) {
            if (!root) {
                return;
            }
            array.push_back(root);
            getArray(root->left);
            getArray(root->right);
        }

    public:
        size_t i = 0;
        vector<std::shared_ptr<Node>> array;

        explicit Iterator(std::shared_ptr<Node> node) {
            getArray(node);
            array.push_back(nullptr);
        }

        Node &operator*() const {
            return *(array[i]);
        }

        std::shared_ptr<Node> operator->() const {
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

    Iterator end() { return Iterator(nullptr); }
};
