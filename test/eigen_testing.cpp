//
// Created by ivddorrka on 5/25/22.
//
#include <iostream>
#include <Eigen/Dense>

using vec3d = Eigen::Vector3d;
using Eigen::MatrixXd;
using Eigen::VectorXd;


MatrixXd create_matrix(int rows, int cols){
    MatrixXd m(rows,cols);
    std::cout << m << "\n";

}

MatrixXd create_matrix_filled_with_k(int rows, int cols, int k) {
    return MatrixXd::Constant( rows, cols,k);
}

void create_vector(int num_elements) {
    Eigen::VectorXd v(num_elements);
}

void sum_matr_eigens(MatrixXd &matr1, MatrixXd &matr2, MatrixXd &res_matr){
    res_matr = matr1+matr2;
}

void minus_matr_eigens(MatrixXd &matr1, MatrixXd &matr2, MatrixXd &res_matr){
    res_matr = matr1-matr2;
}


void mult_matr_eigens(MatrixXd &matr1, MatrixXd &matr2, MatrixXd &res_matr){
    res_matr = matr1*matr2;
}

void matrix_transpose(MatrixXd &matr1, MatrixXd &res_matr){
    res_matr = matr1.transpose();
}

void matrix_adjoint(MatrixXd &matr1, MatrixXd &res_matr) {
    res_matr = matr1.adjoint();
}

void inverse_matrix(MatrixXd &matr1, MatrixXd &res_matr){
    res_matr = matr1.inverse();
}

void matr_mult_vector_eigen(MatrixXd &matr1, VectorXd &vec, VectorXd &result_vector){
    result_vector = matr1*vec;
}

void find_vector_transpose(VectorXd &vc1, MatrixXd &result){
    result = vc1.transpose();
}





