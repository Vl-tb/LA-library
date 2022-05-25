//
// Created by ivddorrka on 5/24/22.
//

#ifndef TEMPLATE_MT_TBB_H
#define TEMPLATE_MT_TBB_H



#include "vector.h"
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range2d.h>
template<typename T>
class Vector;

template<typename T>
class Matrix;

template <typename T, typename S, typename F> void mt_mt_add_tbb(Vector<Vector<T>> &matrix, Matrix<S> &mt, Matrix<F> &res_matrix, int shape_0, int shape_1){

    tbb::parallel_for(tbb::blocked_range2d<int>(0, shape_0, 0, shape_1),
                      [&](const tbb::blocked_range2d<int> &r) {
          for (int i = r.rows().begin(), i_end = r.rows().end(); i < i_end; i++) {
              for (int j = r.cols().begin(), j_end = r.cols().end(); j < j_end; j++) {
                  res_matrix[i][j] = static_cast<double>(matrix[i][j]) + static_cast<double>(mt[i][j]);
              }
          }
      });
}

template <typename T, typename S, typename F> void mt_mt_sub_tbb(Vector<Vector<T>> &matrix, Matrix<S> &mt, Matrix<F> &res_matrix, int shape_0, int shape_1){

    tbb::parallel_for(tbb::blocked_range2d<int>(0, shape_0, 0, shape_1),
                      [&](const tbb::blocked_range2d<int> &r) {
                          for (int i = r.rows().begin(), i_end = r.rows().end(); i < i_end; i++) {
                              for (int j = r.cols().begin(), j_end = r.cols().end(); j < j_end; j++) {
                                  res_matrix[i][j] = static_cast<double>(matrix[i][j]) - static_cast<double>(mt[i][j]);
                              }
                          }
                      });
}

template <typename T, typename S, typename F> void mt_koef_mult_tbb(Vector<Vector<T>> &matrix, S koef, Matrix<F> &res_matrix, int shape_0, int shape_1){

    tbb::parallel_for(tbb::blocked_range2d<int>(0, shape_0, 0, shape_1),
                      [&](const tbb::blocked_range2d<int> &r) {
                          for (int i = r.rows().begin(), i_end = r.rows().end(); i < i_end; i++) {
                              for (int j = r.cols().begin(), j_end = r.cols().end(); j < j_end; j++) {
                                  res_matrix[i][j] = static_cast<double>(matrix[i][j]) * static_cast<double>(koef);
                              }
                          }
                      });


}


template <typename T, typename S, typename F> void mt_koef_div_tbb(Vector<Vector<T>> &matrix, S koef, Matrix<F> &res_matrix, int shape_0, int shape_1){

    tbb::parallel_for(tbb::blocked_range2d<int>(0, shape_0, 0, shape_1),
                      [&](const tbb::blocked_range2d<int> &r) {
                          for (int i = r.rows().begin(), i_end = r.rows().end(); i < i_end; i++) {
                              for (int j = r.cols().begin(), j_end = r.cols().end(); j < j_end; j++) {
                                  res_matrix[i][j] = static_cast<double>(matrix[i][j]) / static_cast<double>(koef);
                              }
                          }
                      });


}

template<typename T, typename S, typename F> void mt_mt_mult_tbb(Vector<Vector<T>>& matrix, Matrix<S> &mt, Matrix<F> &result_matrix, int shape_0) {
    tbb::parallel_for(tbb::blocked_range2d<int>(0, shape_0, 0, mt.rowNum()),
                      [&](const tbb::blocked_range2d<int> &r) {
                          for (int i = r.rows().begin(), i_end = r.rows().end(); i < i_end; i++) {
                              for (int j = r.cols().begin(), j_end = r.cols().end(); j < j_end; j++) {
                                  result_matrix[i][j] = matrix[i].mult(mt[j]);
                              }
                          }
                      });
}



template<typename T, typename S, typename F> void matrix_by_vector_tbb(Vector<Vector<T>> &matrix, Vector<S> &vc, Matrix<F> &result_matrix, int shape_0) {
    tbb::parallel_for(tbb::blocked_range<int>(0, shape_0), [&](tbb::blocked_range<int> r){
        for(int i = r.begin(); i < r.end(); ++i){
            result_matrix[i][0] = matrix[i].mult(vc);
        }
    });
}

template<typename T> void minor_matrix_tbb(Matrix<T> &or_matrix, Matrix<T> &minors, int shape_0, int shape_1) {

    tbb::parallel_for(tbb::blocked_range2d<int>(0, shape_0, 0, shape_1),
                      [&](const tbb::blocked_range2d<int> &r) {
                          for (int i = r.rows().begin(), i_end = r.rows().end(); i < i_end; i++) {
                              for (int j = r.cols().begin(), j_end = r.cols().end(); j < j_end; j++) {
                                  minors[i][j] = or_matrix.minor(i, j);
                              }
                          }
                      });
}

template<typename T> void cofactor_matrix_tbb(Matrix<T> &or_matrix, Matrix<T> &cofactors, int shape_0, int shape_1) {

    tbb::parallel_for(tbb::blocked_range2d<int>(0, shape_0, 0, shape_1),
                      [&](const tbb::blocked_range2d<int> &r) {
                          for (int i = r.rows().begin(), i_end = r.rows().end(); i < i_end; i++) {
                              for (int j = r.cols().begin(), j_end = r.cols().end(); j < j_end; j++) {
                                  int check_sign = i + j;
                                  if (check_sign%2 == 1){
                                      cofactors[i][j] = -(or_matrix.minor(i, j));
                                  }else {
                                      cofactors[i][j] = or_matrix.minor(i, j);
                                  }
                              }
                          }
                      });
}




template<typename T> void matrix_transpose_tbb(Vector<Vector<T>> &or_matrix, Matrix<T> &transposed_matr, int shape_0, int shape_1) {

    tbb::parallel_for(tbb::blocked_range2d<int>(0, shape_0, 0, shape_1),
                      [&](const tbb::blocked_range2d<int> &r) {
                          for (int i = r.rows().begin(), i_end = r.rows().end(); i < i_end; i++) {
                              for (int j = r.cols().begin(), j_end = r.cols().end(); j < j_end; j++) {
                                  transposed_matr[i][j] = or_matrix[j][i];
                              }
                          }
                      });
}

template<typename T> void matrix_fill_with(Matrix<T> &or_matrix, T koef, int shape_0, int shape_1) {

    tbb::parallel_for(tbb::blocked_range2d<int>(0, shape_0, 0, shape_1),
                      [&](const tbb::blocked_range2d<int> &r) {
                          for (int i = r.rows().begin(), i_end = r.rows().end(); i < i_end; i++) {
                              for (int j = r.cols().begin(), j_end = r.cols().end(); j < j_end; j++) {
                                  or_matrix[i][j] = koef;
                              }
                          }
                      });
}

#endif //TEMPLATE_MT_TBB_H
