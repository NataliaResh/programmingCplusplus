#include <atomic>

template<typename T>
class ControlBlock {
    T* pointer_;
    std::atomic<long> reference_count_{0};

public:
    template<typename... Args>
    explicit ControlBlock(Args&&... args)
            : pointer_(new T(std::forward<Args>(args)...)) {}

    explicit ControlBlock(T* pointer) : pointer_(pointer) {}

    ~ControlBlock() {
        delete pointer_;
    }

    void increment_reference() noexcept { ++reference_count_; }
    void decrement_reference() noexcept { --reference_count_; }

    long reference_count() const noexcept { return reference_count_; }

    T* get() const noexcept { return pointer_; }
};