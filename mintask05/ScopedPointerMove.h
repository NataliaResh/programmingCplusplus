template <typename T> class ScopedPointerMove {
    T* pointer;

  public:
    ScopedPointerMove(T* raw) : pointer(raw) {
    }

    ScopedPointerMove(const ScopedPointerMove& other) = delete;

    ScopedPointerMove& operator=(const ScopedPointerMove& other) = delete;

    ScopedPointerMove(ScopedPointerMove&& other) {
        pointer = other.pointer;
        other.pointer = nullptr;
    }

    ScopedPointerMove& operator=(ScopedPointerMove&& other) {
        if (pointer != other.pointer) {
            pointer = other.pointer;
            other.pointer = nullptr;
        }
        return *this;
    }

    T* operator->() {
        return pointer;
    }

    const T* operator->() const {
        return pointer;
    }

    ~ScopedPointerMove() {
        delete pointer;
    }
};
