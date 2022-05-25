// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "src/matrix.h"
#include <vector>
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range2d.h>

template<class D>
inline long long to_us(const D &d) {
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced() {
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}


void testing_matrix_creation() {

//    by row//col
    Matrix<int> mt_row_col(10000, 10000);

//    std::vector<std::vector<T>>
    std::vector <std::vector<int>> vector_vectors{{1, 2, 3},
                                                  {4, 5, 6},
                                                  {7, 8, 9}};
    Matrix<int> mt_vec_vec(vector_vectors);


//    Vector<Vector<T>>
    Vector prikol(std::vector < int > {1, 2, 5});
    std::vector <Vector<int>> b{prikol, prikol, prikol};
    Vector gg(b);
    Vector<Vector<int>> vec{gg};
    Matrix<int> mat_Vec_Vec_T(vec);

}

void generate_big_matrix(Matrix<int> &mt, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mt[i][j] = j;
        }
    }
}

//void function_1() {
//    std::vector<std::vector<int>> matrix3d;
//    size_t counter = 0;
//    for ( int i = 0; i < 100; ++i){
//        std::vector<int> a;
//        for (int j =0; j <100 ; ++j){
//            a.push_back(counter++);
//        }
//        matrix3d.push_back(a);
//    }
//
//    tbb::parallel_for(tbb::blocked_range2d<int>(0, 100, 0, 100),
//                      [&](const tbb::blocked_range2d<int> &r) {
//                          for (int i = r.rows().begin(), i_end = r.rows().end(); i < i_end; i++) {
//                              for (int j = r.cols().begin(), j_end = r.cols().end(); j < j_end; j++) {
//                                  matrix3d[i][j] = 0;
//                              }
//                          }
//                      });
//
//    for ( int i = 0; i < 100; ++i){
//        for (int j =0; j <100 ; ++j){
//            std::cout << matrix3d[i][j]<<", ";
//        }
//    }
//
//
//
//}

int main(int argc, char *argv[]) {
////    std::vector<std::vector<int>> vector_vectors{{1, 1, 1, 0}, {0, 3, 1, 2}, {2, 3, 1, 0}, {1, 0, 2, 1}};
    std::vector<std::vector<int>> vector_vectors1{{1, 2}, {3, 4}, {5, 6}};
    std::vector<int> vec{3, 1};
    Vector<int> abcd(vec);
    std::vector<std::vector<int>> vector_vectors2{{1, 1, 2}, {2, 1, 3} , {1,  4, 2 }};

    Matrix<int> mt_vec_vec(vector_vectors2);
//    Matrix<int> mt_vec_vec2(vector_vectors2);
//    mt_vec_vec.set_method(1);
//
    int pet = 5;
    std::cout << mt_vec_vec<<"\n";
    std::cout << "\n" << "\n";


    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(1);
    std::cout << mt_vec_vec / pet<<"\n";


    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(2);
    std::cout << mt_vec_vec / pet<<"\n";


    mt_vec_vec.set_method(1);
    mt_vec_vec.set_cores(1);
    std::cout << mt_vec_vec / pet<<"\n";

////
////    int a = 2;
//    mt_vec_vec.set_method(0);
////
//    mt_vec_vec.set_cores(2);
//    std::cout << "Method 0 = \n"<<mt_vec_vec+mt_vec_vec<<"\n";
////
//
//    mt_vec_vec.set_method(1);
//    std::cout << "Method 1 = \n"<<mt_vec_vec*mt_vec_vec2<<"\n";
//    std::vector<int> a {1, 2, 3};
//    Vector<int> vec_a(a);
//    Matrix<int> vec_b = vec_a.transpose();
//
//    std::cout <<vec_a<<"\n";
//    std::cout <<vec_a.mul(vec_b)<<"\n";
//    function_1();
    return 0;
}
