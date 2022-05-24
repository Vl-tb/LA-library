// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "src/matrix.h"
#include <vector>

template<class D>
inline long long to_us(const D& d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}


void testing_matrix_creation(){

//    by row//col
    Matrix<int> mt_row_col(10000, 10000);

//    std::vector<std::vector<T>>
    std::vector<std::vector<int>> vector_vectors{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> mt_vec_vec(vector_vectors);


//    Vector<Vector<T>>
    Vector prikol(std::vector<int>{1,2,5});
    std::vector<Vector<int>> b {prikol, prikol, prikol};
    Vector gg(b);
    Vector<Vector<int>> vec {gg};
    Matrix<int> mat_Vec_Vec_T(vec);

}

void generate_big_matrix(Matrix<int> &mt, int rows, int cols){
    for (int i =0; i< rows; ++i ){
        for (int j =0; j < cols; ++j){
            mt[i][j] = j;
        }
    }
}



int main(int argc, char* argv[]) {
//    Matrix<int> mt(1000, 1000);
//    generate_big_matrix(mt, 1000, 1000);
//
//    std::vector<size_t> time;
//    int a = 9;
//    for (int i =1; i <= 16; ++i ){
//        mt.set_cores(i);
//        auto start_total = get_current_time_fenced();
//
//        mt.inverse();
//
//        auto final_total = get_current_time_fenced();
//        auto final = final_total -start_total;
//        time.push_back(to_us(final));
//        std::cout <<"Total time of multiplication with "<< i << " cores = "<< to_us(final)<<"\n";
//    }
//
//    for ( int i =0; i < 16; ++ i){
//        std::cout << time[i]<< ", ";
//    }

    std::vector<std::vector<int>> vector_vectors{{1, 1, 1, 0}, {0, 3, 1, 2}, {2, 3, 1, 0}, {1, 0, 2, 1}};
    
    Matrix<int> mt_vec_vec(vector_vectors);
    std::cout << mt_vec_vec<<"\n";
    std::cout << mt_vec_vec.inverse()<<"\n";

    return 0;
}
