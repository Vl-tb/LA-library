#ifndef LA_LIBRARY_MT_H
#define LA_LIBRARY_MT_H

#include "vector.h"

template<typename T>
class Vector;

template<typename T>
class Matrix;

template<typename T> void mt_assign(int thread_num, int delta, int size, const std::vector<T>& from,
                                    std::vector<T>& to) {
    for (int i=thread_num; i<size; i+= delta) {
        to[i] = from[i];
    }
}

template<typename T, typename S> void mt_add(int thread_num, int delta, int size, const std::vector<S>& vc,
        const std::vector<T>& vector, std::vector<S>& res) {
    for (int i=thread_num; i<size; i+= delta) {
        res[i] = vc[i] + vector[i];
    }
}

template<typename T, typename S> void mt_sub(int thread_num, int delta, int size, const std::vector<S>& vc,
                                             const std::vector<T>& vector, std::vector<S>& res) {
    for (int i=thread_num; i<size; i+= delta) {
        res[i] = vector[i] - vc[i];
    }
}

template<typename T, typename S> void mt_com(int thread_num, int delta, int size, const std::vector<S>& vc,
                                             const std::vector<T>& vector, std::atomic<int>& flag) {
    for (int i=thread_num; i<size; i+= delta) {
        if (vector[i] != vc[i]) {
            flag = -delta;
            return;
        }
    }
    flag += 1;
}

template<typename T, typename S> void mt_mul(int thread_num, int delta, int size, S koef,
                                             const std::vector<T>& vector, std::vector<double>& res) {
    for (int i=thread_num; i<size; i+= delta) {
        res[i] = static_cast<double>(vector[i]) * static_cast<double>(koef);
    }
}

template<typename T, typename S> void mt_div(int thread_num, int delta, int size, S koef,
                                             const std::vector<T>& vector, std::vector<double>& res) {
    for (int i=thread_num; i<size; i+= delta) {
        res[i] = static_cast<double>(vector[i])/static_cast<double>(koef);
    }
}

template<typename T, typename S> void mt_mul_mx(int thread_num, int delta,
        const std::vector<T>& vector, Matrix<S>& mx, Matrix<T>& res) {
    for (int i=0; i<vector.size(); ++i) {
        for (int j=thread_num; j<mx.shape[1]; j+=delta) {
            res[i][j] = vector[i]*mx.matrix[0][j];
        }
    }
}

template<typename T> void mt_trans(int thread_num, int delta, const std::vector<T>& vector, Matrix<T>& mx) {
    for (int i=thread_num; i<vector.size(); i+=delta) {
        mx[0][i] = vector[i];
    }
}

template<typename T> void mt_prod(int thread_num, int delta, const std::vector<T>& vector,
        const std::vector<T>& vc1, std::vector<T>& res) {
    for (int i=thread_num; i< vector.size(); i+=delta){
        res[i] = vector[i]*vc1[i];
    }
}

template<typename T> void mt_fill(int thread_num, int delta, T value, std::vector<T>& vector) {
    for (int i=thread_num; i< vector.size(); i+=delta){
        vector[i] = value;
    }
}

template<typename T> void mt_null(int thread_num, int delta, const std::vector<T>& vector, std::atomic<int>& flag) {
    for (int i=thread_num; i<vector.size(); i+= delta) {
        if (vector[i] != 0) {
            flag = -delta;
            return;
        }
    }
    flag += 1;
}

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template <class D>
long long to_us(const D &d)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
}

#endif //LA_LIBRARY_MT_H
