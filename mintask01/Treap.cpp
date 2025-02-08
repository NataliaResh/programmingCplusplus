#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Treap {
    static minstd_rand generator;
    struct Node {
        int key, priority;
        Node *left = nullptr, *right = nullptr;
        
        Node() = default;
        
        Node(int key) : key(key), priority(generator()) {}
        
        Node(int key, int priority) : key(key), priority(priority) {}

        ~Node() {
            delete left;
            delete right;
        }
    };

    Node *root_ = nullptr;

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

    static void split(Node *t, int key, Node *&t1, Node *&t2) {
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

    static bool containsImp(int key, Node *node) {
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

    static void getKeysImp(Node *node, vector<int> &keys) {
        if (node->left) {
            getKeysImp(node->left, keys);
        }
        if (node->right) {
            getKeysImp(node->right, keys);
        }
        keys.push_back(node->key);
    }

 public:
    Treap() = default;
    
    void insert(int key) {
        Node *less, *greater;
        split(root_, key, less, greater);
        less = merge(less, new Node(key));
        root_ = merge(less, greater);
    }

    void remove(int key) {
        Node *less, *equal, *greater;
        split(root_, key, less, greater);
        split(greater, key + 1, equal, greater);
        root_ = merge(less, greater);
    }

    bool contains(int key) {
        return containsImp(key, root_);
    }

    vector<int> getKeys() {
        vector<int> keys;
        getKeysImp(root_, keys);
        return keys;
    }

    ~Treap() {
        delete root_;
    }
};

minstd_rand Treap::generator;
