#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Node {
    friend class Treap;

    int key, priority;
    Node *left = nullptr, *right = nullptr;
    Node() = default;

    Node(int key, int priority) : key(key), priority(priority) {
        cout << "Node default constructor\n";
        cout.flush();
    }

    ~Node() {
        if (left) {
            delete left;
        }
        if (right) {
            delete right;
        }
    }
};

class Treap {
    //static minstd_rand generator;

    Node *root_ = nullptr;

    static Node *copyNode(const Node *node) {
        if (!node)
            return nullptr;
        Node *newNode = new Node(node->key, node->priority);
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

    static void getKeysImp(Node *node, vector<int> *keys) {
        if (node->left) {
            getKeysImp(node->left, keys);
        }
        if (node->right) {
            getKeysImp(node->right, keys);
        }
        keys->push_back(node->key);
    }

  public:
    Treap() {
        cout << "Defult constructor\n";
    }

    Treap(const Treap &other) {
        cout << "Copy constructor\n";
        root_ = copyNode(other.root_);
    }

    Treap &operator=(const Treap &other) {
        cout << "Copy assigment constructor\n";
        if (this != &other) {
            delete root_;
            root_ = copyNode(other.root_);
        }
        return *this;
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

    Treap operator+(const Treap &right) {
        Treap result = *this;
        insertNodes(result, right.root_);
        return result;
    }

    void insert(int key, int priority) {
        Node *less, *greater;
        split(root_, key, less, greater);
        less = merge(less, new Node(key, priority));
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

    vector<int> *getKeys() {
        vector<int> *keys = new vector<int>;
        getKeysImp(root_, keys);
        return keys;
    }

    ~Treap() {
        cout << "Destructor\n";
        delete root_;
    }
};

//minstd_rand Treap::generator;
