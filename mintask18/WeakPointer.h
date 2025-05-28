#pragma once
#include "ControlBlock.h"
#include "SharedPointer.h"

template <typename T> class WeakPointer {
    ControlBlock<T> *control_block_ = nullptr;

    void release() noexcept {
        if (control_block_) {
            control_block_->decrement_weak_reference();
            if (control_block_->reference_count() == 0 &&
                control_block_->weak_reference_count() == 0) {
                delete control_block_;
                control_block_ = nullptr;
            }
        }
    }

  public:
    WeakPointer() noexcept : control_block_(nullptr) {
    }

    WeakPointer(const WeakPointer &other) noexcept : control_block_(other.control_block_) {
        if (control_block_) {
            control_block_->increment_weak_reference();
        }
    }

    WeakPointer &operator=(const WeakPointer &other) noexcept {
        if (this != &other) {
            release();
            control_block_ = other.control_block_;
            if (control_block_) {
                control_block_->increment_weak_reference();
            }
        }
        return *this;
    }

    WeakPointer(const SharedPointer<T> &other) noexcept
        : control_block_(other.control_block_) {
        if (control_block_) {
            control_block_->increment_weak_reference();
        }
    }

    WeakPointer &operator=(const SharedPointer<T> &other) noexcept {
        release();
        control_block_ = other.control_block_;
        if (control_block_) {
            control_block_->increment_weak_reference();
        }
        return *this;
    }

    WeakPointer &operator=(std::nullptr_t) noexcept {
        release();
        control_block_ = nullptr;
        return *this;
    }

    WeakPointer(WeakPointer &&other) noexcept : control_block_(other.control_block_) {
        other.control_block_ = nullptr;
    }

    WeakPointer &operator=(WeakPointer &&other) noexcept {
        if (this != &other) {
            release();
            control_block_ = other.control_block_;
            other.control_block_ = nullptr;
        }
        return *this;
    }

    explicit WeakPointer(SharedPointer<T>&& other) noexcept
        : control_block_(other.control_block_) {
        other.control_block_ = nullptr;
    }


    T *operator->() const noexcept {
        return control_block_ ? control_block_->get() : nullptr;
    }

    T &operator*() const noexcept {
        return *control_block_->get();
    }

    explicit operator bool() const noexcept {
        return control_block_ && control_block_->get();
    }

    bool operator==(const WeakPointer &other) const noexcept {
        return control_block_ == other.control_block_;
    }

    bool operator!=(const WeakPointer &other) const noexcept {
        return !(*this == other);
    }

    bool operator==(std::nullptr_t) const noexcept {
        return control_block_ == nullptr || control_block_->get() == nullptr;
    }

    bool operator!=(std::nullptr_t) const noexcept {
        return !(*this == nullptr);
    }

    SharedPointer<T> lock() const noexcept {
        if (control_block_ && control_block_->reference_count() > 0) {
            return SharedPointer<T>(control_block_);
        }
        return SharedPointer<T>();
    }

    ~WeakPointer() {
        release();
    }
};