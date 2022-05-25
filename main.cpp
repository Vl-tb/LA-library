// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "src/matrix.h"
#include "src/vector.h"
#include <vector>
#include <gtest/gtest.h>
#include "src/eigen_testing.h"
#include <Eigen/Dense>

using vec3d = Eigen::Vector3d;
using Eigen::MatrixXd;

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


void generate_big_matrix(Matrix<int> &mt, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mt[i][j] = j;
        }
    }
}



int main(int argc, char *argv[]) {

//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
    MatrixXd m (3, 3);
    MatrixXd m2 (3, 3);
    int counter = 0;
    for ( int i = 0 ; i < 3; ++i) {
        for (int j =0; j < 3; ++j ){
            m(i, j) = counter++;
            m2(i, j) = counter++;
        }
    }
    std::cout <<m<< "\n";
    std::cout <<"Something" <<"\n";
    mult_matrix_by_k(std::ref(m), std::ref(m2), 9);

    std::cout <<m2<< "\n";
    std::cout <<"Something" <<"\n";

    divide_matrix_by_k(std::ref(m), std::ref(m2), 9);

    std::cout <<m2<< "\n";

//    mult_matr_eigens(std::ref(m), std::ref(m2));
    return 0;


}
