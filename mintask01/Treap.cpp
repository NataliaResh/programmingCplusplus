#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Treap {
    //static minstd_rand generator;
    //int key, priority;
    //Treap *left = nullptr, *right = nullptr;
    struct Node {
        int key, priority;
        Node *left = nullptr, *right = nullptr;

        Node(int key, int priority) : key(key), priority(priority) {
        }
    };

    Node *root = nullptr;

    // Treap(int key, Treap *left = nullptr, Treap *right = nullptr) {
    //     this->key = key;
    //     this->priority = generator();
    //     this->left = left;
    //     this->right = right;
    // }

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

    void destruct(Node *node) {
        if (node->left) {
            destruct(node->left);
        }
        if (node->right) {
            destruct(node->right);
        }
        delete node;
    }

  public:
    // Treap() {
    //   root = new Node();
    // }
    void insert(int key, int priority) {
        Node *less, *greater;
        split(root, key, less, greater);
        less = merge(less, new Node(key, priority));
        root = merge(less, greater);
    }

    void remove(int key) {
        Node *less, *equal, *greater;
        split(root, key, less, greater);
        split(greater, key + 1, equal, greater);
        root = merge(less, greater);
    }

    bool contains(int key) {
        return containsImp(key, root);
    }

    vector<int> *getKeys() {
        vector<int> *keys = new vector<int>;
        getKeysImp(root, keys);
        return keys;
    }

    ~Treap() {
        destruct(root);
    }
};

//minstd_rand Treap::generator;

// int main() {
//     vector<int> k = {1, 2, 3, 4, 5, 6, 7};
//     vector<int> p = {25, 14, 31, 26, 45, 72, 54};
//     Treap *t = new Treap();
//     for (int i = 0; i < 7; i++) {
//         t->insert(k[i], p[i]);
//     }
//     vector<int> *a = t->getKeys();
//     for (int i = 0; i < a->size(); i++) {
//         cout << a->at(i) << " ";
//     }
//     cout << "\n";
//     delete t;
//     delete a;
// }
