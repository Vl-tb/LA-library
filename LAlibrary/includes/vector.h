#ifndef LA_LIBRARY_VECTOR_H
#define LA_LIBRARY_VECTOR_H

#include <vector>
#include "matrix.h"

template<typename T>
class Vector
{
public:
    Vector(int dim);
    Vector(std::vector<T>);

    Vector(const Vector &) = default;
    Vector &operator=(const Vector &) = delete;
    Vector(Vector &&) = default;
    Vector &operator=(Vector &&) = delete;
    ~Vector() = default;

    std::vector<int> shape;
    std::vector<T> vector;

    Vector &operator+(const Vector &);
    Vector &operator-(const Vector &);
    Vector &operator==(const Vector &);
    Vector &operator*(T koef);
    Vector &operator/(T koef);
    Matrix& mul(const Matrix &);
    Matrix& transpose();
    bool add_comp(const Vector &);
    bool mul_comp(const Matrix &);
    bool isnull();

};


#endif //LA_LIBRARY_VECTOR_H
