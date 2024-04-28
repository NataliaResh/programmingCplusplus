#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

template <typename T>
class Treap {    
    struct Node {
        T key;
        int priority;
        Node *left = nullptr, *right = nullptr;
        Node() = default;

        Node(T key) : key(key), priority(rand()) {}
        
        Node(T key, int priority) : key(key), priority(priority) {}

        ~Node() {
            delete left;
            delete right;
        }
    };

    Node *root_ = nullptr;

    static Node *copyNode(const Node *node) {
        if (!node)
            return nullptr;
        Node *newNode = new Node(node->key);
        if (node->left) {
            newNode->left = copyNode(node->left);
        }
        if (node->right) {
            newNode->right = copyNode(node->right);
        }
        return newNode;
    }

    static Node *merge(Node *t1, Node *t2) {
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

    static void split(Node *t, T key, Node *&t1, Node *&t2) {
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

    static bool containsImp(T key, Node *node) {
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

    static void getKeysImp(Node *node, vector<T> *keys) {
        if (node->left) {
            getKeysImp(node->left, keys);
        }
        if (node->right) {
            getKeysImp(node->right, keys);
        }
        keys->push_back(node->key);
    }

    static void insertNodes(Treap &t, Node *right) {
        t.insert(right->key, right->priority);
        if (right->left) {
            insertNodes(t, right->left);
        }
        if (right->right) {
            insertNodes(t, right->right);
        }
    }

    void insert(T key, int priority) {
        Node *less, *greater;
        split(root_, key, less, greater);
        less = merge(less, new Node(key, priority));
        root_ = merge(less, greater);
    }
  public:
    Treap() {}

    Treap(const Treap &other) {
        root_ = copyNode(other.root_);
    }

    Treap &operator=(const Treap &other) {
        if (this != &other) {
            delete root_;
            root_ = copyNode(other.root_);
        }
        return *this;
    }

    Treap(Treap &&other) {
        root_ = copyNode(other.root_);
        other.root_ = nullptr;
    }

    Treap &operator=(Treap &&other) {
        if (this != &other) {
            delete root_;
            root_ = copyNode(other.root_);
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
        Node *less, *greater;
        split(root_, key, less, greater);
        less = merge(less, new Node(key));
        root_ = merge(less, greater);
    }

    void remove(T key) {
        Node *less, *equal, *greater;
        split(root_, key, less, greater);
        split(greater, key + 1, equal, greater);
        root_ = merge(less, greater);
    }

    bool contains(T key) {
        return containsImp(key, root_);
    }

    vector<int> *getKeys() {
        vector<int> *keys = new vector<int>;
        if (root_) getKeysImp(root_, keys);
        return keys;
    }

    ~Treap() {
        delete root_;
    }
};


