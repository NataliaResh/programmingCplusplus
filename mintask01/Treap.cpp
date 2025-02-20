#include "Treap.h"

/*
    PR:
        The main commentary about your solution is here.
        Your data structure is probabilistic, and it's guaranties by time complixety
        depends on 'uniform' distribution of priorities.
        By 'priorities distributed uniformly' we mean that all priorities have the same probability.

        So for Treap it is important to think about priority generation.

        And lets talk about random generators in C++

        Generator - it is deterministic thing that generates sequence
        of numbers which looks like random numbers

        So lets focus on word 'deterministic'. Such generators have
        a special parameter called 'seed'. It is used to generate different sequences

        It means that two runs of generator with the same seeds yields some squences

        For your data structure it means that for one treap sequence of random numbers
        will be the same for every run of program.

        And also here can be problems with 'uniformity' of your sequences. 
        Firstly generator that you use not really good in that.
        It would be better to use mt19937 generator. 

        Also 'uniformity' can be broken by type casts
        Generator yields numbers with type uint32_fast, it means
        that it is guaranteed that on every architecture this number will be 32 bit unsigned integer

        On the other hand standart doesn't specify size of int, it only guaranteed that width of int
        at least 16 bits

        So here can be overflow, and integer overflow architecture dependent thing too. It means
        that we don't know how actually integer will be overflowed.
        And it might leads us to lose of 'uniformity' of random sequences.
        After overflow some numbers will be generated with greater probability than the others

        It's been a long backstory about why working with random numbers is trickier than it seems

        But C++ has nice api for make this work easier!

    */
//static minstd_rand generator; // PR: do we need have global random generator for all treaps?
                              // or it will be better to make this field nonstatic?

// PR: this is just sample function
// remove this function when you get familiar with randomness in C++

Treap::Node::Node() = default;

Treap::Node::Node(int key, int priority) : key(key), priority(priority) {
}

Treap::Node::~Node() {
    delete left;
    delete right;
}

Treap::Node *Treap::merge(Treap::Node *t1, Treap::Node *t2) {
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

void Treap::split(Treap::Node *t, int key, Treap::Node *&t1, Treap::Node *&t2) {
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

bool Treap::containsImp(int key, Treap::Node *node) {
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

void Treap::getKeysImp(Treap::Node *node, vector<int> &keys) {
    if (node->left) {
        getKeysImp(node->left, keys);
    }
    if (node->right) {
        getKeysImp(node->right, keys);
    }
    keys.push_back(node->key);
}

Treap::Treap(): generator_(rd_()) {}

void Treap::insert(int key) {
    Treap::Node *less, *greater;
    split(root_, key, less, greater);
    less = merge(less, new Node(key, dist_(generator_)));
    root_ = merge(less, greater);
}

void Treap::remove(int key) {
    Treap::Node *less, *equal, *greater;
    split(root_, key, less, greater);
    split(greater, key + 1, equal, greater);
    root_ = merge(less, greater);
}

bool Treap::contains(int key) {
    return containsImp(key, root_);
}

vector<int> Treap::getKeys() {
    vector<int> keys;
    getKeysImp(root_, keys);
    return keys;
}

Treap::~Treap() {
    delete root_;
}
