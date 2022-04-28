#ifndef LA_LIBRARY_VECTOR_H
#define LA_LIBRARY_VECTOR_H

#include <vector>
#include "matrix.h"
#include "errors.h"
#include <typeinfo>
#include <thread>
#include <atomic>
#include <math.h>
#include "mt.h"

template<typename T>
class Matrix;

template<typename T>
class Vector
{
public:
    std::vector<int> shape;
    std::vector<T> vector;
    int size;
    int cores = std::thread::hardware_concurrency();


    Vector &operator=(const Vector &) = default;
    Vector(Vector&& ) = default;
    Vector(const Vector&)= default;
    Vector() = default;
    ~Vector() = default;


    explicit Vector(int dim) {
        vector = std::vector<T> (dim);
        shape = std::vector<int> {dim, 1};
        size = dim;
    }

    explicit Vector(const std::vector<T>& vc) {
        int dim = vc.size();
        size = dim;
        shape = std::vector<int> {dim, 1};
        vector = std::vector<T> (dim);
        if (cores == 0) {
            for (int i=0; i<dim; ++i) {
                vector[i] = vc[i];
            }
        }
        else {
            std::vector<std::thread> threads;
            for (int i=0; i<cores; ++i) {
                threads.emplace_back(mt_assign<T>, i, cores, dim, std::ref(vc), std::ref(vector));
            }
            for (std::thread &th: threads) {
                th.join();
            }
        }
    }


    int get_size(){
        return shape[0];
    }

    template<typename S> Vector<T> operator+(Vector<S> &vc) {
        if (!add_comp(vc)) {
            std::cerr << "Incorrect shapes of vectors!" << std::endl;
            exit(SHAPES_ERROR); //TODO Error ne shapes
        }
        Vector<T> res(shape[0]);
        if (get_cores() == 0) {
            for (int i=0; i<shape[0]; ++i) {
                res[i] = vector[i] + vc[i];
            }
        }
        else {
            std::vector<std::thread> threads;
            for (int i=0; i<cores; ++i) {
                threads.emplace_back(mt_add<T, S>, i, cores, shape[0], std::cref(vc.vector), std::cref(vector),
                                     std::ref(res.vector));
            }
            for (std::thread &th: threads) {
                th.join();
            }
        }
        return res;
    }

    template<typename S> Vector<T> operator-(Vector<S> &vc) {
        if (!add_comp(vc)) {
            std::cerr << "Incorrect shapes of vectors!" << std::endl;
            exit(SHAPES_ERROR); //TODO Error ne shapes
        }
        Vector<T> res(shape[0]);
        if (get_cores() == 0) {
            for (int i=0; i<shape[0]; ++i) {
                res[i] = vector[i] - vc[i];
            }
        }
        else {
            std::vector<std::thread> threads;
            for (int i=0; i<cores; ++i) {
                threads.emplace_back(mt_sub<T, S>, i, cores, shape[0], std::cref(vc.vector), std::cref(vector),
                                     std::ref(res.vector));
            }
            for (std::thread &th: threads) {
                th.join();
            }
        }
        return res;
    }

    template<typename S> bool operator==(Vector<S> &vc) {
        if (shape[0] != vc.shape[0]) {
            return false;
        }
        if (get_cores() == 0) {
            for (int i=0; i<shape[0]; ++i) {
                if (vector[i] != vc[i]){
                    return false;
                }
            }
        }
        else {
            std::atomic<int> flag (1);
            std::vector<std::thread> threads;
            for (int i=0; i<cores; ++i) {
                threads.emplace_back(mt_com<T, S>, i, cores, shape[0], std::cref(vc.vector), std::cref(vector),
                                     std::ref(flag));
            }
            while (flag != pow(2, cores)) {
                if (flag == 0) {
                    for (std::thread &th: threads) {
//                        th.terminate();
                    }
                }
            }
            for (std::thread &th: threads) {
                th.join();
            }
        }
        return true;
    }

    template<typename S> Vector<double> operator*(S koef) {
        Vector<double> res(shape[0]);
        for (int i=0; i<shape[0]; ++i) {
            res[i] = static_cast<double>(vector[i]) * static_cast<double>(koef);
        }
        return res;
    }

    template<typename S> Vector<double> operator/(S koef) {
        if (koef == 0) {
            std::cerr << "Cannot divide by zero!" << std::endl;
            exit(ZERO_DIVISION_ERROR);
        }
        Vector<double> res(shape[0]);
        for (int i=0; i<shape[0]; ++i) {
            res[i] = static_cast<double>(vector[i])/static_cast<double>(koef);
        }
        return res;
    }

    T &operator[](int row) {
        if (row >= shape[0]) {
            std::cerr << "Incorrect index!" << std::endl;
            exit(INDEX_ERROR);
        }
        return vector[row];
    }

    template<typename S> Matrix<T> mul(Matrix<S> &mx) {
        if (!this->mul_comp(mx)) {
            std::cerr << "Incorrect shapes of vector and matrix!" << std::endl;
            exit(SHAPES_ERROR);
        }
        Matrix<T> res(shape[0], mx.shape[1]);
        for (int i=0; i<shape[0]; ++i) {
            for (int j=0; j<mx.shape[1]; ++j) {
                res[i][j] = vector[i]*mx.matrix[0][j];
            }
        }
        return res;
    }

    Matrix<T> transpose() {
        Matrix<T> res(1, shape[0]);
        for (int i=0; i<shape[0]; ++i) {
            res[0][i] = vector[i];
        }
        return res;
    }

    T mult(Vector<T> &vc1){
        if (shape[0] != vc1.get_size()){
            std::cerr << "Incorrect shapes of vectors!" << std::endl;
            exit(SHAPES_ERROR);
        }
        size_t i, j;
        T result = 0;
        for (i=0; i< shape[0]; ++i){
            result += vector[i]*vc1[i];
        }
        return result;
    }

    Vector<T> fill(T num) {
        Vector<T> res(shape[0]);
        for (int i=0; i<shape[0]; ++i) {
            res[i] = num;
        }
        return res;
    }

    bool add_comp(const Vector<T> &vc) {
        if (shape[0] == vc.shape[0]) {
            return true;
        }
        return false;
    }

    bool mul_comp(const Matrix<T> &mx) {
        if (shape[1] == mx.shape[0]) {
            return true;
        }
        return false;
    }

    bool isnull() {
        for (int i=0; i<shape[0]; ++i) {
            if (vector[i] != 0) {
                return false;
            }
        }
        return true;
    }

    void set_cores(int num_cores) {
        if (num_cores<0) {
            std::cerr << "Cannot be negative amount of working cores!";
            exit(CORES_ERROR);
        }
        cores = num_cores;
    }

    int get_cores() {
        return cores;
    }
};

template<typename T> std::ostream &operator<<(std::ostream& os, const std::vector<T>& vc) {
    os << "[";
    for (int i=0; i<vc.size(); ++i) {
        if (i != vc.size()-1) {
            os << vc[i]<< ", ";
        } else {
            os << vc[i];
        }
    }
    os << "]";
    return os;
}

template<typename T> std::ostream &operator<<(std::ostream& os, const Vector<T>& vc) {
    os << "[";
    std::string type = typeid(T).name();
    for (int i = 0; i < vc.shape[0]; ++i) {
        if ( i!=vc.shape[0]-1 && (type.substr(1, 6) != "Vector")){
            os << vc.vector[i] << ", ";
        }
        else if (i!=vc.shape[0]-1) {
            os << vc.vector[i] << '\n' << " ";
        }
        else {
            os << vc.vector[i];
        }
    }
    os << "]";
    return os;
}


#endif //LA_LIBRARY_VECTOR_H
