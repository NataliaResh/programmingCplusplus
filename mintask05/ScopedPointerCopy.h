template <typename T> class ScopedPointerCopy {
    T* pointer;

  public:
    ScopedPointerCopy(T* raw) : pointer(raw) {
    }

    ScopedPointerCopy(const ScopedPointerCopy& other) {
        pointer = new T(*other.pointer);
    }

    ScopedPointerCopy& operator=(const ScopedPointerCopy& other) {
        if (pointer != other.pointer) {
            *pointer = *other.pointer;
        }
        return *this;
    }

    T* operator->() {
        return pointer;
    }

    const T* operator->() const {
        return pointer;
    }

    ~ScopedPointerCopy() {
        delete pointer;
    }
};
