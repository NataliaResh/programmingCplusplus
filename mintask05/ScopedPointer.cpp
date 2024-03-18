template <typename T> class ScopedPointer {
    T* pointer;

  public:
    ScopedPointer(T* raw) : pointer(raw) {
    }

    ScopedPointer(const ScopedPointer& other) {
    }

    ScopedPointer(ScopedPointer&& other) {
    }

    ScopedPointer& operator=(const ScopedPointer& other) {
        return *this;
    }

    ScopedPointer& operator=(ScopedPointer&& other) {
        return *this;
    }

    T* operator->() {
        return pointer;
    }

    const T* operator->() const {
        return pointer;
    }

    ~ScopedPointer() {
        delete pointer;
    }
};
