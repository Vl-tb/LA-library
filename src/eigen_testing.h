//
// Created by ivddorrka on 5/25/22.
//

#ifndef TEMPLATE_EIGEN_TESTING_H
#define TEMPLATE_EIGEN_TESTING_H
#include <Eigen/Dense>

using vec3d = Eigen::Vector3d;
using Eigen::MatrixXd;
using Eigen::VectorXd;


MatrixXd create_matrix(int rows, int cols);

MatrixXd create_matrix_filled_with_k(int rows, int cols, int k) ;

vec3d create_vector(int num_elements) ;

void sum_matr_eigens(MatrixXd &matr1, MatrixXd &matr2, MatrixXd &res_matr);

void minus_matr_eigens(MatrixXd &matr1, MatrixXd &matr2, MatrixXd &res_matr);

void mult_matr_eigens(MatrixXd &matr1, MatrixXd &matr2, MatrixXd &res_matr);

void matrix_transpose(MatrixXd &matr1, MatrixXd &res_matr);

void matrix_adjoint(MatrixXd &matr1, MatrixXd &res_matr);

void inverse_matrix(MatrixXd &matr1, MatrixXd &res_matr);

template <typename T> void matrix_determinant(MatrixXd &matr1, T determinant_found){
    determinant_found = matr1.determinant();
}
void matr_mult_vector_eigen(MatrixXd &matr1, VectorXd &vec, VectorXd &result_vector);

template <typename T> void vector_mult_vector_eigen(VectorXd &vc1, VectorXd &vc2, T result){
    result = vc1 * vc2 ;
}

template <typename T> void fill_vector_with_number(VectorXd &vc, T koef){
    for (int i =0; i < vc.size(); ++i){
        vc[i] = koef;
    }
}


template <typename T> void mult_matrix_by_k(MatrixXd &matrix, MatrixXd &result, T koef){
    result = matrix*koef;

}


template <typename T> void divide_matrix_by_k(MatrixXd &matrix, MatrixXd &result, T koef){
    result = matrix/koef;
}


#endif //TEMPLATE_EIGEN_TESTING_H
