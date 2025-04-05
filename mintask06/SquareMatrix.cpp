#include "SquareMatrix.h"

SquareMatrix::Array::Array(double **array, size_t i) : array(array), i(i) {
}

double &SquareMatrix::Array::operator[](size_t j) {
    return array[i][j];
}

double **SquareMatrix::zeroMatrix(size_t size) {
    double **zero = new double *[size];
    for (size_t i = 0; i < size; i++) {
        zero[i] = new double[size];
        for (size_t j = 0; j < size; j++)
            zero[i][j] = 0;
    }
    return zero;
}

void SquareMatrix::copyMatrix(double **matrix, size_t size) {
    deleteMatrix();
    size_ = size;
    matrix_ = new double *[size];
    for (size_t i = 0; i < size; i++) {
        matrix_[i] = new double[size];
        for (size_t j = 0; j < size; j++)
            matrix_[i][j] = matrix[i][j];
    }
}

void SquareMatrix::deleteMatrix() {
    if (matrix_ == nullptr) {
        return;
    }
    for (size_t i = 0; i < size_; i++) {
        delete[] matrix_[i];
    }
    delete[] matrix_; 
}

size_t SquareMatrix::size() const {
    return size_;
}

SquareMatrix::SquareMatrix(int size) : size_(size), matrix_(zeroMatrix(size)) {
}

SquareMatrix::SquareMatrix(std::vector<double> &vec)
    : size_(vec.size()), matrix_(zeroMatrix(vec.size())) {
    for (size_t i = 0; i < size_; i++)
        matrix_[i][i] = vec[i];
}

SquareMatrix::SquareMatrix(std::vector<double> &&vec)
    : size_(vec.size()), matrix_(zeroMatrix(vec.size())) {
    for (size_t i = 0; i < size_; i++)
        matrix_[i][i] = vec[i];
}

SquareMatrix::SquareMatrix(const SquareMatrix &other) {
    copyMatrix(other.matrix_, other.size_);
}

SquareMatrix &SquareMatrix::operator=(const SquareMatrix &other) {
    if (this != &other)
        copyMatrix(other.matrix_, other.size_);
    return *this;
}

SquareMatrix::SquareMatrix(SquareMatrix &&other) {
    deleteMatrix();
    matrix_ = other.matrix_;
    size_ = other.size_;
    other.matrix_ = nullptr;
    other.size_ = 0;
}

SquareMatrix &SquareMatrix::operator=(SquareMatrix &&other) {
   if (this != &other) {
       deleteMatrix();
       matrix_ = other.matrix_;
       size_ = other.size_;
       other.matrix_ = nullptr;
       other.size_ = 0;
   }
    return *this;
}

SquareMatrix::operator double() const {
    double ans = 0;
    for (size_t i = 0; i < size_; i++)
        for (size_t j = 0; j < size_; j++)
            ans += matrix_[i][j];
    return ans;
}

SquareMatrix operator+(const SquareMatrix& left, const SquareMatrix &right) {
    if (left.size_ != right.size_) {
        exit(1);
    };
    SquareMatrix result = left;
    for (size_t i = 0; i < left.size_; i++)
        for (size_t j = 0; j < left.size_; j++)
            result.matrix_[i][j] = left.matrix_[i][j] + right.matrix_[i][j];
    return result;
}

SquareMatrix SquareMatrix::operator+=(const SquareMatrix &right) {
    *this = *this + right;
    return *this;
}

SquareMatrix operator*(const SquareMatrix& left, const SquareMatrix &right) {
    if (left.size_ != right.size_) {
        exit(1);
    };
    SquareMatrix result = SquareMatrix(left.size_);
    for (size_t i = 0; i < left.size_; i++)
        for (size_t j = 0; j < left.size_; j++)
            for (size_t k = 0; k < left.size_; k++)
                result.matrix_[i][j] += left.matrix_[i][k] * right.matrix_[k][j];
    return result;
}

SquareMatrix SquareMatrix::operator*=(const SquareMatrix &right) {
    *this = *this * right;
    return *this;
}

SquareMatrix SquareMatrix::operator*(double right) {
    SquareMatrix result = *this;
    for (size_t i = 0; i < size_; i++)
        for (size_t j = 0; j < size_; j++)
            result.matrix_[i][j] = matrix_[i][j] * right;
    return result;
}

SquareMatrix operator*(double left, SquareMatrix& matrix) {
    return matrix * left;
}

SquareMatrix SquareMatrix::operator*=(double right) {
    *this = *this * right;
    return *this;
}

bool operator==(const SquareMatrix& left, const SquareMatrix &right) {
    if (left.size_ != right.size_)
        return false;
    for (size_t i = 0; i < left.size_; i++)
        for (size_t j = 0; j < left.size_; j++)
            if (left.matrix_[i][j] != right.matrix_[i][j])
                return false;
    return true;
}

bool operator!=(const SquareMatrix& left, const SquareMatrix &right) {
    return !(left == right);
}

SquareMatrix::Array SquareMatrix::operator[](int i) {
    Array array(matrix_, i);
    return array;
}

SquareMatrix::~SquareMatrix() {
    deleteMatrix();
}
