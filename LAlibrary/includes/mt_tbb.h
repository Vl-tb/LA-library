#ifndef LA_LIBRARY_MT_TBB_H
#define LA_LIBRARY_MT_TBB_H

#include "vector.h"
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>

template<typename T>
class Vector;

template<typename T>
class Matrix;

template <typename T, typename S> void mt_tbb_add(const std::vector<S>& vc,
                                                  const std::vector<T>& vector, std::vector<S>& res){
    tbb::parallel_for(tbb::blocked_range<int>(0, res.size()),
                       [&](tbb::blocked_range<int> r) {
       for (int i=r.begin(); i<r.end(); ++i) {
           res[i] = vector[i] + vc[i];
       }
   });
}

template <typename T, typename S> void mt_tbb_sub(const std::vector<S>& vc,
                                                  const std::vector<T>& vector, std::vector<S>& res){
    tbb::parallel_for(tbb::blocked_range<int>(0, res.size()),
                       [&](tbb::blocked_range<int> r) {
       for (int i=r.begin(); i<r.end(); ++i) {
           res[i] = vector[i] - vc[i];
       }
   });
}

template<typename T> void mt_tbb_assign(const std::vector<T>& from, std::vector<T>& to) {
    tbb::parallel_for(tbb::blocked_range<int>(0, to.size()),
                      [&](tbb::blocked_range<int> r) {
      for (int i=r.begin(); i<r.end(); ++i) {
          to[i] = from[i];
      }
  });
}

template<typename T, typename S> void mt_tbb_com(int& flag, const std::vector<S>& vc, const std::vector<T>& vector) {
    flag = tbb::parallel_reduce( tbb::blocked_range<int>(0, vc.size()), 1,
            [&](tbb::blocked_range<int> r, int running_flag){
                for (int i=r.begin(); i<r.end(); ++i) {
                    if (vc[i] != vector[i])
                    running_flag = 0;
                }

                return running_flag;
            }, std::multiplies<int>() );
}

template <typename T, typename S> void mt_tbb_mul(S koef, const std::vector<T>& vector,
                                                                    std::vector<double>& res){
    tbb::parallel_for(tbb::blocked_range<int>(0, res.size()),
                      [&](tbb::blocked_range<int> r) {
      for (int i=r.begin(); i<r.end(); ++i) {
          res[i] = static_cast<double>(vector[i]*static_cast<double>(koef));
      }
  });
}

template <typename T, typename S> void mt_tbb_div(S koef, const std::vector<T>& vector,
                                                  std::vector<double>& res){
    tbb::parallel_for(tbb::blocked_range<int>(0, res.size()),
                      [&](tbb::blocked_range<int> r) {
      for (int i=r.begin(); i<r.end(); ++i) {
          res[i] = static_cast<double>(vector[i])/static_cast<double>(koef);
      }
  });
}

template<typename T, typename S> void mt_tbb_mul_mx(const std::vector<T>& vector, Matrix<S>& mx,
                                                        Matrix<T>& res) {
    tbb::parallel_for(tbb::blocked_range<int>(0, vector.size()),
                      [&](tbb::blocked_range<int> r) {
      for (int i=r.begin(); i<r.end(); ++i) {
          for (int j=0; j<mx.shape[1]; ++j) {
              res[i][j] = vector[i]*mx.matrix[0][j];
          }
      }
  });
}

template<typename T> void mt_tbb_trans(const std::vector<T>& vector, Matrix<T>& mx) {
    tbb::parallel_for(tbb::blocked_range<int>(0, vector.size()),
                      [&](tbb::blocked_range<int> r) {
      for (int i=r.begin(); i<r.end(); ++i) {
          mx[0][i] = vector[i];
      }
  });
}

template<typename T> void mt_tbb_prod(const std::vector<T>& vector, const std::vector<T>& vc1,
                                      T& res) {
    res = tbb::parallel_reduce( tbb::blocked_range<int>(0, vector.size()), 0,
                                 [&](tbb::blocked_range<int> r, T running_res){
         for (int i=r.begin(); i<r.end(); ++i) {
             running_res += vector[i]*vc1[i];
         }
         return running_res;
     }, std::plus<T>());
}

template<typename T> void mt_tbb_fill(T value, std::vector<T>& vector) {
    tbb::parallel_for(tbb::blocked_range<int>(0, vector.size()),
                      [&](tbb::blocked_range<int> r) {
      for (int i=r.begin(); i<r.end(); ++i) {
          vector[i] = value;
      }
  });
}

template<typename T> void mt_tbb_null(int& flag, const std::vector<T>& vector) {
    flag = tbb::parallel_reduce( tbb::blocked_range<int>(0, vector.size()), 1,
                                 [&](tbb::blocked_range<int> r, int running_flag){
         for (int i=r.begin(); i<r.end(); ++i) {
             if (vector[i] != 0)
                 running_flag = 0;
         }

         return running_flag;
     }, std::multiplies<int>());
}

#endif //LA_LIBRARY_MT_TBB_H
