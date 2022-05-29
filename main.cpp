// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "src/matrix.h"
#include "src/vector.h"
#include <vector>
#include <gtest/gtest.h>
#include "test/eigen_testing.h"
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

    // ::testing::InitGoogleTest(&argc, argv);
    // return RUN_ALL_TESTS();
    std::vector<std::vector<double>> vector_2 {{1.0, 0.7, 5.3},
                                               {2.1,1.6, 6.4},
                                               {3.2, 4.3, 0.5}};
    Matrix<double> mt_vec_vec2(vector_2);
    std::cout << mt_vec_vec2 <<"\n";
    Matrix<double> cut_row_col = mt_vec_vec2.cuT_Col_Row(0, 0);
    std::cout << cut_row_col <<"\n";

}
