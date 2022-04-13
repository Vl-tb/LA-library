#ifndef LA_LIBRARY_MATRIX_H
#define LA_LIBRARY_MATRIX_H

#include <vector>
#include "vector.h"

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

    Matrix &operator+(const Matrix &);
    Matrix &operator-(const Matrix &);
    Matrix &operator==(const Matrix &);
    Matrix &operator*(T koef);
    Matrix &operator/(T koef);
    Vector &operator[](int row);
    ostream &operator<<(ostream& os, const Matrix& mx);
    Matrix &mul(const Matrix &);
    Matrix &mul(const Vector &);
    Matrix &inverse();
    Matrix &transpose();
    Matrix &det();
    bool add_comp(const Matrix &);
    bool mul_comp(const Matrix &);
    bool isnull();
    bool isident();
    T minor(int col, int row);
    T cofactor(int col, int row);

};

#endif //LA_LIBRARY_MATRIX_H
