#ifndef LA_LIBRARY_VECTOR_H
#define LA_LIBRARY_VECTOR_H

#include <vector>
#include "matrix.h"
#include "errors.h"
#include <typeinfo>
#include <thread>
#include <atomic>
#include <math.h>
#include <pthread.h>
#include "mt.h"
#include "mt_tbb_vlad.h"

template<typename T>
class Matrix;

template<typename T>
class Vector
{
public:
    std::vector<int> shape;
    std::vector<T> vector;
    int size;
    int method=0;
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
        if (method == 0) {
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
        else {
            mt_tbb_assign<T>(std::cref(vc), std::ref(vector));
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
        if (method == 0) {
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
        }
        else {
            mt_tbb_add<T, S>(std::cref(vc.vector), std::cref(vector), std::ref(res.vector));
        }
        return res;
    }

    template<typename S> Vector<T> operator-(Vector<S> &vc) {
        if (!add_comp(vc)) {
            std::cerr << "Incorrect shapes of vectors!" << std::endl;
            exit(SHAPES_ERROR); //TODO Error ne shapes
        }
        Vector<T> res(shape[0]);
        if (method == 0) {
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
        }
        else {
            mt_tbb_sub<T, S>(std::cref(vc.vector), std::cref(vector), std::ref(res.vector));
        }
        return res;
    }

    template<typename S> bool operator==(Vector<S> &vc) {
        if (shape[0] != vc.shape[0]) {
            return false;
        }
        if (method == 0) {
            if (get_cores() == 0) {
                for (int i=0; i<shape[0]; ++i) {
                    if (vector[i] != vc[i]){
                        return false;
                    }
                }
            }
            else {
                std::atomic<int> flag (0);
                std::vector<std::thread> threads;
                for (int i=0; i<cores; ++i) {
                    threads.emplace_back(mt_com<T, S>, i, cores, shape[0], std::cref(vc.vector), std::cref(vector),
                                         std::ref(flag));
                }
                while (flag != get_cores()) {
                    if (flag < 0) {
                        for (std::thread &th: threads) {
                            pthread_cancel(th.native_handle());
                        }
                        break;
                    }
                }
                for (std::thread &th: threads) {
                    th.join();
                }
                if (flag != get_cores()) {
                    return false;
                }
            }
        }
        else {
            int flag=1;
            mt_tbb_com<T, S>(std::ref(flag), std::cref(vc.vector), std::cref(vector));
            if (!flag) {
                return false;
            }
        }
        return true;
    }

    template<typename S> Vector<double> operator*(S koef) {
        Vector<double> res(shape[0]);
        if (method == 0) {
            if (get_cores() == 0) {
                for (int i=0; i<shape[0]; ++i) {
                    res[i] = static_cast<double>(vector[i]) * static_cast<double>(koef);
                }
            }
            else {
                std::vector<std::thread> threads;
                for (int i=0; i<cores; ++i) {
                    threads.emplace_back(mt_mul<T, S>, i, cores, shape[0], koef, std::cref(vector),
                                         std::ref(res.vector));
                }
                for (std::thread &th: threads) {
                    th.join();
                }
            }
        }
        else {
            mt_tbb_mul<T, S>(koef, std::cref(vector), std::ref(res.vector));
        }
        return res;
    }

    template<typename S> Vector<double> operator/(S koef) {
        if (koef == 0) {
            std::cerr << "Cannot divide by zero!" << std::endl;
            exit(ZERO_DIVISION_ERROR);
        }
        Vector<double> res(shape[0]);
        if (method == 0) {
            if (get_cores() == 0) {
                for (int i=0; i<shape[0]; ++i) {
                    res[i] = static_cast<double>(vector[i])/static_cast<double>(koef);
                }
            }
            else {
                std::vector<std::thread> threads;
                for (int i=0; i<cores; ++i) {
                    threads.emplace_back(mt_div<T, S>, i, cores, shape[0], koef, std::cref(vector),
                                         std::ref(res.vector));
                }
                for (std::thread &th: threads) {
                    th.join();
                }
            }
        }
        else {
            mt_tbb_div<T, S>(koef, std::cref(vector), std::ref(res.vector));
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
        if (method == 0) {
            if (get_cores() == 0) {
                for (int i=0; i<shape[0]; ++i) {
                    for (int j=0; j<mx.shape[1]; ++j) {
                        res[i][j] = vector[i]*mx.matrix[0][j];
                    }
                }
            }
            else {
                std::vector<std::thread> threads;
                for (int i=0; i<cores; ++i) {
                    threads.emplace_back(mt_mul_mx<T, S>, i, cores, std::cref(vector), std::ref(mx),
                                         std::ref(res));
                }
                for (std::thread &th: threads) {
                    th.join();
                }
            }
        }
        else {
            mt_tbb_mul_mx<T, S>(std::cref(vector), std::ref(mx), std::ref(res));
        }
        return res;
    }

    Matrix<T> transpose() {
        Matrix<T> res(1, shape[0]);
        if (method == 0) {
            if (get_cores() == 0) {
                for (int i=0; i<shape[0]; ++i) {
                    res[0][i] = vector[i];
                }
            }
            else {
                std::vector<std::thread> threads;
                for (int i=0; i<cores; ++i) {
                    threads.emplace_back(mt_trans<T>, i, cores, std::cref(vector), std::ref(res));
                }
                for (std::thread &th: threads) {
                    th.join();
                }
            }
        }
        else {
            mt_tbb_trans<T>(std::cref(vector), std::ref(res));
        }
        return res;
    }

    template<typename S> double mult(Vector<S> &vc1){
        if (shape[0] != vc1.get_size()){
            std::cerr << "Incorrect shapes of vectors!" << std::endl;
            exit(SHAPES_ERROR);
        }
        if (method == 0) {
            if (get_cores() == 0) {
                double res = 0;
                for (int i=0; i< shape[0]; ++i){
                    res += static_cast<double>(vector[i])*static_cast<double>(vc1[i]);
                }
                return res;
            }
            else {
                std::vector<double> resv (vc1.get_size());
                std::vector<std::thread> threads;
                for (int i=0; i<cores; ++i) {
                    threads.emplace_back(mt_prod<T, S, double>, i, cores, std::cref(vector), std::cref(vc1.vector), std::ref(resv));
                }
                for (std::thread &th: threads) {
                    th.join();
                }
                double out = 0;
                for (size_t i=0; i<resv.size(); ++i) {
                    out += resv[i];
                }
                return out;
            }
        }
        else {
            double out = 0;
            mt_tbb_prod<T, S, double>(std::cref(vector), std::cref(vc1.vector), std::ref(out));

            return out;
        }
    }

    Vector<T> fill(T num) {
        Vector<T> res(shape[0]);
        if (method == 0) {
            if (get_cores() == 0) {
                for (int i=0; i<shape[0]; ++i) {
                    res[i] = num;
                }
            }
            else {
                std::vector<std::thread> threads;
                for (int i=0; i<cores; ++i) {
                    threads.emplace_back(mt_fill<T>, i, cores, num, std::ref(res.vector));
                }
                for (std::thread &th: threads) {
                    th.join();
                }
            }
        }
        else {
            mt_tbb_fill<T>(num, std::ref(res.vector));
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
        if (method == 0) {
            if (get_cores() == 0) {
                for (int i=0; i<shape[0]; ++i) {
                    if (vector[i] != 0) {
                        return false;
                    }
                }
            }
            else {
                std::atomic<int> flag (0);
                std::vector<std::thread> threads;
                for (int i=0; i<cores; ++i) {
                    threads.emplace_back(mt_null<T>, i, cores, std::cref(vector),
                                         std::ref(flag));
                }
                while (flag != get_cores()) {
                    if (flag < 0) {
                        for (std::thread &th: threads) {
                            pthread_cancel(th.native_handle());
                        }
                        break;
                    }
                }
                for (std::thread &th: threads) {
                    th.join();
                }
                if (flag != get_cores()) {
                    return false;
                }
            }
        }
        else {
            int flag = 1;
            mt_tbb_null<T>(std::ref(flag), std::cref(vector));
            if (!flag) {
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

    void set_method(int num) {
        method = num;
    }

    int get_method() {
        return method;
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
