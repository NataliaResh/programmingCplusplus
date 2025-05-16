#pragma once
#include <random>
#include <type_traits>
#include <vector>

using namespace std;

template <typename T> class Treap {
    struct Node {
        T key;
        int priority{};
        Node *left = nullptr, *right = nullptr;
        Node *parent = nullptr;
        Node() = default;

        Node(T key, int priority) : key(key), priority(priority) {
        }

        ~Node() {
            delete left;
            delete right;
        }

        Node *copyNode() {
            Node *newNode = new Node(key, priority);
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
    Node *root_ = nullptr;

    static Node *merge(Node *t1, Node *t2) {
        if (!t1)
            return t2;
        if (!t2)
            return t1;
        if (t1->priority > t2->priority) {
            t1->right = merge(t1->right, t2);
            t1->right->parent = t1;
            return t1;
        } else {
            t2->left = merge(t1, t2->left);
            t2->left->parent = t2;
            return t2;
        }
    }

    void split(Node *t, int key, Node *&t1, Node *&t2) {
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

    bool containsImp(T key, Node *node) {
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

    void getKeysImp(Node *node, vector<T> &keys) {
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

    static void insertNodes(Treap &t, Node *right) {
        t.insert(right->key);
        if (right->left) {
            insertNodes(t, right->left);
        }
        if (right->right) {
            insertNodes(t, right->right);
        }
    }

    void copy(const Treap &other) {
        delete root_;
        if (other.root_ == nullptr) {
            root_ = nullptr;
        } else {
            root_ = other.root_->copyNode();
        }
    }

  public:
    Treap() : generator_(rd_()) {
    }

    Treap(const Treap &other) {
        copy(other);
    }

    Treap &operator=(const Treap &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    Treap(Treap &&other) noexcept {
        root_ = other.root_;
        other.root_ = nullptr;
    }

    Treap &operator=(Treap &&other) noexcept {
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
        Treap::Node *less, *greater;
        split(root_, key, less, greater);
        less = merge(less, new Node(key, dist_(generator_)));
        root_ = merge(less, greater);
    }

    void remove(T key) {
        Treap::Node *less, *equal, *greater;
        split(root_, key, less, greater);
        split(greater, key + 1, equal, greater);
        equal->right = equal->left = nullptr;
        //delete equal;
        root_ = merge(less, greater);
    }

    bool contains(T key) {
        return containsImp(key, root_);
    }

    vector<T> getKeys() {
        vector<T> keys;
        getKeysImp(root_, keys);
        return keys;
    }

    ~Treap() {
        delete root_;
    }

    class Iterator {
      private:
        Node *current_node_;

        Node *find_left(Node *node) {
            if (node == nullptr) {
                return nullptr;
            }
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }

        void next() {
            if (current_node_ == nullptr) {
                return;
            }
            if (current_node_->right != nullptr) {
                current_node_ = find_left(current_node_->right);
                return;
            }
            Node *parent = current_node_->parent;
            while (parent != nullptr && current_node_ == parent->right) {
                current_node_ = parent;
                parent = parent->parent;
            }
            current_node_ = parent;
        }

      public:
        explicit Iterator(Node *node) {
            current_node_ = find_left(node);
        }

        Node &operator*() const {
            return *current_node_;
        }

        Node *operator->() const {
            return current_node_;
        };

        bool operator==(const Iterator &other) const {
            return current_node_ == other.current_node_;
        }

        bool operator!=(const Iterator &other) const {
            return current_node_ != other.current_node_;
        }

        Iterator &operator++() {
            next();
            return *this;
        };
    };

    Iterator begin() {
        return Iterator(root_);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};
