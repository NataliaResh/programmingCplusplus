#pragma once
#include <algorithm>
#include <vector>


class SquareMatrix {
    struct Array {
        double **array = nullptr;
        size_t i;

        Array(double **array, size_t i);

        double &operator[](size_t j);
    };

    double **matrix_ = nullptr;
    size_t size_ = 0;

    static double **zeroMatrix(size_t size);

    void copyMatrix(double **matrix, size_t size);

    void deleteMatrix();

  public:
    size_t size() const;

    SquareMatrix(int size);
     
    SquareMatrix(std::vector<double> &vec);
    
    SquareMatrix(std::vector<double> &&vec);

    SquareMatrix(const SquareMatrix &other);

    SquareMatrix &operator=(const SquareMatrix &other);

    SquareMatrix(SquareMatrix &&other);

    SquareMatrix &operator=(SquareMatrix &&other);

    explicit operator double() const;

    friend SquareMatrix operator+(const SquareMatrix& left, const SquareMatrix &right);

    SquareMatrix operator+=(const SquareMatrix &right);

    friend SquareMatrix operator*(const SquareMatrix& left, const SquareMatrix &right);

    SquareMatrix operator*=(const SquareMatrix &right);

    SquareMatrix operator*(double right);

    friend SquareMatrix operator*(double left, SquareMatrix& matrix);

    SquareMatrix operator*=(double right);

    friend bool operator==(const SquareMatrix& left, const SquareMatrix &right);

    friend bool operator!=(const SquareMatrix& left, const SquareMatrix &right);

    Array operator[](int i);

    ~SquareMatrix();
};

SquareMatrix operator*(double left, SquareMatrix& matrix);

SquareMatrix operator+(const SquareMatrix& left, const SquareMatrix& right);

SquareMatrix operator*(const SquareMatrix& left, const SquareMatrix& right);

bool operator==(const SquareMatrix& left, const SquareMatrix& right);

bool operator!=(const SquareMatrix& left, const SquareMatrix& right);
