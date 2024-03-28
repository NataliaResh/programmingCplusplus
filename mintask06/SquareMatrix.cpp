#include <algorithm>
#include <vector>

class SquareMatrix {
    struct Array {
        double **array = nullptr;
        size_t i;

        Array(double **array, size_t i) : array(array), i(i) {
        }

        double &operator[](size_t j) {
            return array[i][j];
        }
    };

    double **matrix_ = nullptr;
    size_t size_ = 0;

    static double **zeroMatrix(size_t size) {
        double **zero = new double *[size];
        for (size_t i = 0; i < size; i++) {
            zero[i] = new double[size];
            for (size_t j = 0; j < size; j++)
                zero[i][j] = 0;
        }
        return zero;
    }

    void copyMatrix(double **matrix, size_t size) {
        deleteMatrix();
        size_ = size;
        matrix_ = new double *[size];
        for (size_t i = 0; i < size; i++) {
            matrix_[i] = new double[size];
            for (size_t j = 0; j < size; j++)
                matrix_[i][j] = matrix[i][j];
        }
    }

    void deleteMatrix() {
        for (size_t i = 0; i < size_; i++) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
    }

  public:
    const size_t size() const {
        return size_;
    }

    SquareMatrix(int size) : size_(size), matrix_(zeroMatrix(size)) {
    }

    SquareMatrix(std::vector<double> vec) : size_(vec.size()), matrix_(zeroMatrix(vec.size())) {
        for (size_t i = 0; i < size_; i++)
            matrix_[i][i] = vec[i];
    }

    SquareMatrix(std::vector<double> &vec) : size_(vec.size()), matrix_(zeroMatrix(vec.size())) {
        for (size_t i = 0; i < size_; i++)
            matrix_[i][i] = vec[i];
    }

    SquareMatrix(const SquareMatrix &other) {
        copyMatrix(other.matrix_, other.size_);
    }

    SquareMatrix &operator=(const SquareMatrix &other) {
        if (this != &other)
            copyMatrix(other.matrix_, other.size_);
        return *this;
    }

    SquareMatrix(SquareMatrix &&other) {
        copyMatrix(other.matrix_, other.size_);
        other.matrix_ = nullptr;
        other.size_ = 0;
    }

    SquareMatrix &operator=(SquareMatrix &&other) {
        if (this != &other) {
            copyMatrix(other.matrix_, other.size_);
            other.matrix_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    explicit operator double() const {
        double ans = 0;
        for (size_t i = 0; i < size_; i++)
            for (size_t j = 0; j < size_; j++)
                ans += matrix_[i][j];
        return ans;
    }

    SquareMatrix operator+(const SquareMatrix &right) {
        if (size_ != right.size_) {
            exit(1);
        };
        SquareMatrix result = *this;
        for (size_t i = 0; i < size_; i++)
            for (size_t j = 0; j < size_; j++)
                result.matrix_[i][j] = matrix_[i][j] + right.matrix_[i][j];
        return result;
    }

    SquareMatrix operator+=(const SquareMatrix &right) {
        *this = *this + right;
        return *this;
    }

    SquareMatrix operator*(const SquareMatrix &right) {
        if (size_ != right.size_) {
            exit(1);
        };
        SquareMatrix result = SquareMatrix(size_);
        for (size_t i = 0; i < size_; i++)
            for (size_t j = 0; j < size_; j++)
                for (size_t k = 0; k < size_; k++)
                    result.matrix_[i][j] += matrix_[i][k] * right.matrix_[k][j];
        return result;
    }

    SquareMatrix operator*=(const SquareMatrix &right) {
        *this = *this * right;
        return *this;
    }

    SquareMatrix operator*(double right) {
        SquareMatrix result = *this;
        for (size_t i = 0; i < size_; i++)
            for (size_t j = 0; j < size_; j++)
                result.matrix_[i][j] = matrix_[i][j] * right;
        return result;
    }

    SquareMatrix operator*=(double right) {
        *this = *this * right;
        return *this;
    }

    bool operator==(const SquareMatrix &right) {
        if (size_ != right.size_)
            return false;
        for (size_t i = 0; i < size_; i++)
            for (size_t j = 0; j < size_; j++)
                if (matrix_[i][j] != right.matrix_[i][j])
                    return false;
        return true;
    }

    bool operator!=(const SquareMatrix &right) {
        return !(*this == right);
    }

    Array operator[](int i) {
        Array array(matrix_, i);
        return array;
    }

    ~SquareMatrix() {
        deleteMatrix();
    }
};
