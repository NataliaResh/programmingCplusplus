#pragma once
#include "MaxCountInstances.h"
#include <cstddef>

template <typename T, size_t limit> struct Counter {
    static inline size_t objects;

    void incObjects() {
        if (objects >= limit)
            throw MaxCountInstances(limit);
        ++objects;
    }

    Counter() {
        incObjects();
    }

    Counter(const Counter&) {
        incObjects();
    }

    ~Counter() {
        --objects;
    }
};
