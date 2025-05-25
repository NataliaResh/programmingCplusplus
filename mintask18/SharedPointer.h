#include "ControlBlock.h"

template<typename T>
class SharedPointer {
    ControlBlock<T> *control_block_;

    explicit SharedPointer(ControlBlock<T> *control_block) : control_block_(control_block) {
        if (control_block_) {
            control_block_->increment_reference();
        }
    }

    void release() noexcept {
        if (control_block_) {
            control_block_->decrement_reference();
            if (control_block_->reference_count() == 0) {
                delete control_block_;
            }
            control_block_ = nullptr;
        }
    }

public:
    template<typename... Args>
    static SharedPointer<T> make_shared(Args &&... args) {
        auto *control_block = new ControlBlock<T>(std::forward<Args>(args)...);
        return SharedPointer<T>(control_block);
    }

    SharedPointer() noexcept: control_block_(nullptr) {}

    explicit SharedPointer(T *ptr) : control_block_(ptr ? new ControlBlock<T>(ptr) : nullptr) {
        if (control_block_) {
            control_block_->increment_reference();
        }
    }

    SharedPointer(const SharedPointer &other) noexcept: control_block_(other.control_block_) {
        if (control_block_) {
            control_block_->increment_reference();
        }
    }

    SharedPointer &operator=(const SharedPointer &other) noexcept {
        if (this != &other) {
            release();
            control_block_ = other.control_block_;
            if (control_block_) {
                control_block_->increment_reference();
            }
        }
        return *this;
    }

    SharedPointer &operator=(std::nullptr_t) noexcept {
        release();
        control_block_ = nullptr;
        return *this;
    }

    SharedPointer(SharedPointer &&other) noexcept: control_block_(other.control_block_) {
        other.control_block_ = nullptr;
    }

    SharedPointer &operator=(SharedPointer &&other) noexcept {
        if (this != &other) {
            release();
            control_block_ = other.control_block_;
            other.control_block_ = nullptr;
        }
        return *this;
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

    bool operator==(const SharedPointer &other) const noexcept {
        return control_block_ == other.control_block_;
    }

    bool operator!=(const SharedPointer &other) const noexcept {
        return !(*this == other);
    }

    bool operator==(std::nullptr_t) const noexcept {
        return control_block_ == nullptr || control_block_->get() == nullptr;
    }

    bool operator!=(std::nullptr_t) const noexcept {
        return !(*this == nullptr);
    }

    T *get() const noexcept {
        return control_block_ ? control_block_->get() : nullptr;
    }

    ~SharedPointer() {
        release();
    }
};