#ifndef LA_LIBRARY_MT_H
#define LA_LIBRARY_MT_H

#include "vector.h"
#include "matrix.h"

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
    for (size_t i=0; i<vector.size(); ++i) {
        for (int j=thread_num; j<mx.shape[1]; j+=delta) {
            res[i][j] = vector[i]*mx.matrix[0][j];
        }
    }
}

template<typename T> void mt_trans(int thread_num, int delta, const std::vector<T>& vector, Matrix<T>& mx) {
    for (size_t i=thread_num; i<vector.size(); i+=delta) {
        mx[0][i] = vector[i];
    }
}

template<typename T, typename S, typename F> void mt_prod(int thread_num, int delta, const std::vector<T>& vector,
                                  const std::vector<S>& vc1, std::vector<F>& res) {
    for (size_t i=thread_num; i< vector.size(); i+=delta){
        res[i] = static_cast<double>(vector[i])*static_cast<double>(vc1[i]);
    }
}

template<typename T> void mt_fill(int thread_num, int delta, T value, std::vector<T>& vector) {
    for (size_t i=thread_num; i< vector.size(); i+=delta){
        vector[i] = value;
    }
}

template<typename T> void mt_null(int thread_num, int delta, const std::vector<T>& vector, std::atomic<int>& flag) {
    for (size_t i=thread_num; i<vector.size(); i+= delta) {
        if (vector[i] != 0) {
            flag = -delta;
            return;
        }
    }
    flag += 1;
}

template<typename T> void add_to_vector(std::vector<Vector<T>>& vec, int start, int end, Vector<T>& nul_col) {
    for ( int i = start; i < end; ++i){
        vec[i] = nul_col;
    }
}

template<typename T> void vector_vector(const std::vector<std::vector<T>> &mtrx, std::vector<Vector<T>>& vec, int start, int end, int cols) {
    Vector<T> vc1(cols);

    for (int i = start; i < end; ++i){
        if (mtrx[i].size()==static_cast<size_t>(cols)){
            for (int j=0; j<cols; ++j){
                vc1[j] = mtrx[i][j];
            }
            vec[i] = vc1;
        } else {
            std::cerr<<"All rows should be the same length!"<<"\n";
            exit(SHAPES_ERROR);
        }
    }
}


template<typename T, typename S, typename F> void add_two_matrices(Matrix<S> &mtx1, Vector<Vector<T>>& vec, int start, int end, Matrix<F> &result_matrix, int shape_1) {
    int i, j;
    for (i = start; i < end; ++i) {
        for (j = 0; j < shape_1; ++j) {
            result_matrix[i][j] = static_cast<double>(mtx1[i][j]) + static_cast<double>(vec[i][j]);
        }
    }

}



template<typename T, typename S, typename F> void subtract_two_matrices(Matrix<S> &mtx1, Vector<Vector<T>>& vec, int start, int end, Matrix<F> &result_matrix, int shape_1) {
    int i, j;
    for (i = start; i < end; ++i) {
        for (j = 0; j < shape_1; ++j) {
            result_matrix[i][j] = static_cast<double>(vec[i][j]) - static_cast<double>(mtx1[i][j]);
        }
    }
}


template<typename T, typename S, typename F> void mult_matr_koef(Vector<Vector<T>>& vec, S koef, int start, int end, Matrix<F> &result_matrix, int shape_1) {
    int i, j;
    for (i = start; i < end; ++i) {
        for (j = 0; j < shape_1; ++j) {
            result_matrix[i][j] = static_cast<double>(koef) * static_cast<double>(vec[i][j]);
        }
    }
}


template<typename T, typename S, typename F> void divide_matr_koef(Vector<Vector<T>>& vec, S koef, int start, int end, Matrix<F> &result_matrix, int shape_1) {
    int i, j;
    for (i = start; i < end; ++i) {
        for (j = 0; j < shape_1; ++j) {
            result_matrix[i][j] = static_cast<double>(vec[i][j]) / static_cast<double>(koef);
        }
    }
}



template<typename T, typename S, typename F> void matrix_by_matrix(Vector<Vector<T>>& matrix, Matrix<S> &mt, int start, int end, Matrix<F> &result_matrix) {
    int i, j;
    for (i = start; i < end; ++i) {
        for (j = 0; j < mt.rowNum(); ++j) {
            result_matrix[i][j] = matrix[i].mult(mt[j]);
        }
    }
}

template<typename T> void matrix__check_ident(Vector<Vector<T>>& matrix, std::atomic<bool> &check, int start, int end, int shape_1) {
    int i, j;

    for ( i =start; i < end; ++i ){
        if (check){
            for (j=0; j < shape_1; ++j){

                if(i==j){
                    if (matrix[i][j]!=1){
                        check = false;
                    }
                } else if (matrix[i][j]!=0){
                    check = false;
                }
            }
        } else {
            break;
        }
    }
}

template<typename T, typename S> void matrix__check__equal(Vector<Vector<T>>& matrix, Matrix<S> &matr_2, std::atomic<bool> &check, int start, int end, int shape_1) {
    int i, j;

    for ( i =start; i < end; ++i ){
        if (check){
            for (j=0; j < shape_1; ++j){
                if (matrix[i][j]!=matr_2[i][j]){
                    check = false;
                }
            }
        } else {
            break;
        }
    }
}

template<typename T, typename S, typename F> void matrix_by_vector(Vector<Vector<T>> &matrix, Vector<S> &vc, Matrix<F> &result_matrix, int start, int end) {
    int i;
    for (i = start; i < end; ++i) {
        result_matrix[i][0] = matrix[i].mult(vc);
    }
}


template<typename T> void cofactors_threading(Matrix<T> &minors, Matrix<T> &cofactors, int start, int end, int shape_1) {
    int i, j;
    for (i = start; i < end; ++i) {
        for (j = 0; j < shape_1; ++j) {
            if (i % 2 == 0) {
                if (j % 2 == 1) {
                    cofactors[i][j] = -minors[i][j];
                } else {
                    cofactors[i][j] = minors[i][j];
                }
            } else {
                if (j % 2 == 1) {
                    cofactors[i][j] = minors[i][j];
                } else {
                    cofactors[i][j] = -minors[i][j];
                }
            }
        }

    }
}

template<typename T> void put_minors_to_matrix(Matrix<T> &matrix, Matrix<T> &mt, int start, int end, int shape_1) {
    int i, j;
    for (i=start; i < end; ++i){
        for (j=0; j< shape_1; ++j){

            mt[i][j] = matrix.minor(i, j);
        }
    }
}

template<typename T> void put_cofactors_to_matrix(Matrix<T> &matrix, Matrix<T> &mt, int start, int end, int shape_1) {
    int i, j;
    for (i=start; i < end; ++i){
        for (j=0; j< shape_1; ++j){
            T calculated=  matrix.minor(i, j);
            int sum = i + j;
            if (sum%2==1){
                mt[i][j] = -calculated;
            }else {
                mt[i][j] = calculated;
            }

        }
    }
}


template<typename T> void transpose_matrix_fill(Vector<Vector<T>> &matrix, Matrix<T> &mt, int start, int end, int shape_1) {
    int i, j;
    for (i=start; i < end; ++i){
        for (j=0; j< shape_1; ++j){
            mt[j][i] = matrix[i][j];
        }
    }
}


template<typename T> void fill_with_k(T koef, Matrix<T> &mt, int start, int end, int shape_1) {
    int i, j;
    for (i = start; i < end; ++i) {
        for (j = 0; j < shape_1; ++j) {
            mt[i][j] = koef;
        }
    }
}


#endif //LA_LIBRARY_MT_H
