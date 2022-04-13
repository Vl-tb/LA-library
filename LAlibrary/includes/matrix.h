#ifndef LA_LIBRARY_MATRIX_H
#define LA_LIBRARY_MATRIX_H

#include <vector>
#include "vector.h"

template<typename T>
class Vector;

template<typename T>
class Matrix
{
public:
    Matrix(int cols, int rows);
    Matrix(int dim);
    Matrix(std::vector<std::vector<T>>);


    Matrix(const Matrix &) = default;
    Matrix &operator=(const Matrix &) = delete;
    Matrix(Matrix &&) = default;
    Matrix &operator=(Matrix &&) = delete;
    ~Matrix() = default;

    std::vector<int> shape;
    Vector<Vector<T>> matrix;

    Matrix<T> &operator+(const Matrix<T> &);
    Matrix<T> &operator-(const Matrix<T> &);
    Matrix<T> &operator==(const Matrix<T> &);
    Matrix<T> &operator*(T koef);
    Matrix<T> &operator/(T koef);
    Vector<T> &operator[](int row);
    std::ostream& print(std::ostream& os);
    Matrix<T> &mul(const Matrix<T> &);
    Matrix<T> &mul(const Vector<T> &);
    Matrix<T> &inverse();
    Matrix<T> &transpose();
    Matrix<T> &det();
    Matrix<T> &fill(T num);
    bool add_comp(const Matrix<T> &);
    bool mul_comp(const Matrix<T> &);
    bool isnull();
    bool isident();
    T minor(int col, int row);
    T cofactor(int col, int row);

};

template<typename T> std::ostream &operator<<(std::ostream& os, const Matrix<T>& mx);
#endif //LA_LIBRARY_MATRIX_H
