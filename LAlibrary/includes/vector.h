#ifndef LA_LIBRARY_VECTOR_H
#define LA_LIBRARY_VECTOR_H

#include <vector>
#include "matrix.h"

template<typename T>
class Matrix;

template<typename T>
class Vector
{
public:
    Vector(int dim) {
        vector = std::vector<T> (dim);
        shape = std::vector<T> {dim, 1};
    }
    Vector(const std::vector<T>& vc) {
        int dim = vc.size();
        shape = std::vector<T> {dim, 1};
        vector = std::vector<T> (dim);
        for (int i=0; i<dim; ++i) {
            vector[i] = vc[i];
        }
    }

    Vector(const Vector &) = default;
    Vector &operator=(const Vector &) = delete;
    Vector(Vector &&) = default;
    Vector &operator=(Vector &&) = delete;
    ~Vector() = default;

    std::vector<int> shape;
    std::vector<int> vector;

    Vector<T> operator+(Vector<T> &vc) {
        if (shape[0] != vc.shape[0]) {
            return -1; //TODO Error ne shapes
        }
        Vector<T> res(shape[0]);
        for (int i=0; i<shape[0]; ++i) {
            res[i] = vector[i] + vc[i];
        }
        return res;
    }

    Vector<T> operator-(Vector<T> &vc) {
        if (shape[0] != vc.shape[0]) {
            return -1; //TODO Error ne shapes
        }
        Vector<T> res(shape[0]);
        for (int i=0; i<shape[0]; ++i) {
            res[i] = vector[i] - vc[i];
        }
        return res;
    }

    bool operator==(Vector<T> &vc) {
        if (shape[0] != vc.shape[0]) {
            return -1; //TODO Error ne shapes
        }
        for (int i=0; i<shape[0]; ++i) {
            if (vector[i] != vc[i]){
                return false;
            }
        }
        return true;
    }

    Vector<T> &operator*(T koef);
    Vector<T> &operator/(T koef);
    T &operator[](int row) {
        return vector[row];
    }
    std::ostream& print(std::ostream& os);
    Matrix<T> &mul(const Matrix<T> &);
    Matrix<T> &transpose();
    Vector<T> &fill(T num);
    bool add_comp(const Vector<T> &);
    bool mul_comp(const Matrix<T> &);
    bool isnull();
};

template<typename T> std::ostream &operator<<(std::ostream& os, const std::vector<T>& vc) {
    os << "Vector " << std::endl;
    for (int i=0; i<vc.size(); ++i) {
        os << vc[i] << std::endl;
    }
    return os;
}

template<typename T> std::ostream &operator<<(std::ostream& os, const Vector<T>& vc) {
    os << "Vector " << std::endl;
    for (int i=0; i<vc.shape[0]; ++i) {
        os << vc.vector[i] << std::endl;
    }
    return os;
}


#endif //LA_LIBRARY_VECTOR_H
