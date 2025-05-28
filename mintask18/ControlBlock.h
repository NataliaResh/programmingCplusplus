#pragma once
#include <atomic>
#include <iostream>
template <typename T> class ControlBlock {
    std::atomic<long> reference_count_{0};
    std::atomic<long> weak_reference_count_{0};

  public:
    template <typename... Args> ControlBlock(Args&&... args) {}

    void increment_reference() noexcept {
        ++reference_count_;
    }

    void decrement_reference() noexcept {
        --reference_count_;
    }

    void increment_weak_reference() noexcept {
        ++weak_reference_count_;
    }

    void decrement_weak_reference() noexcept {
        --weak_reference_count_;
    }

    long reference_count() const noexcept {
        return reference_count_;
    }

    long weak_reference_count() const noexcept {
        return weak_reference_count_;
    }

    virtual void delete_pointer() {}

    virtual T* get() noexcept = 0;

    virtual ~ControlBlock() = default;
};

template <typename T> class ControlBlockWithPointer : public ControlBlock<T> {
    T* pointer_;

  public:
    template <typename... Args>
    ControlBlockWithPointer(Args&&... args) : pointer_(new T(std::forward<Args>(args)...)) {
    }

    ControlBlockWithPointer(T* pointer) : pointer_(pointer) {
    }

    T* get() noexcept {
        return pointer_;
    }

    virtual void delete_pointer() {
        delete pointer_;
    }

    ~ControlBlockWithPointer() {
        delete pointer_;
    }
};

template <typename T> class ControlBlockWithObject : public ControlBlock<T> {
    T object_;

  public:
    template <typename... Args>
    explicit ControlBlockWithObject(Args&&... args) : object_(std::forward<Args>(args)...) {
    }

    T* get() noexcept {
        return &object_;
    }
};