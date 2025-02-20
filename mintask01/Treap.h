#pragma once
#include <random>
#include <type_traits>
#include <vector>

using namespace std;

class Treap {
  private:
    struct Node {
        int key, priority;
        Node* left = nullptr;
        Node* right = nullptr;

        Node();

        Node(int key, int priority);

        ~Node();
    };
    random_device rd_;
    mt19937 generator_;
    uniform_int_distribution<int> dist_;
    
    Node* root_ = nullptr;

    static Node* merge(Node* t1, Node* t2);

    void split(Node* t, int key, Node*& t1, Node*& t2);

    bool containsImp(int key, Node* node);

    void getKeysImp(Node* node, vector<int>& keys);

  public:
    Treap();

    void insert(int key);

    void remove(int key);

    bool contains(int key);

    vector<int> getKeys();

    ~Treap();
};
