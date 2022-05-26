//
// Created by ivddorrka on 5/25/22.
//

#include <gtest/gtest.h>
#include "../src/matrix.h"
#include "../src/vector.h"
#include "../src/errors.h"

TEST(MatrixTest, ConstructorShapes) {
    Matrix<int> matrix_ints(5, 5);
    Matrix<double> matrix_doubles(15, 4);
    ASSERT_EQ(matrix_ints.shape[0], 5) << "Matrix constructor via shapes fails!";
    ASSERT_EQ(matrix_ints.shape[1], 5) << "Matrix constructor via shapes fails!";
    ASSERT_EQ(matrix_doubles.shape[0], 15) << "Vector constructor via dimension fails!";
    ASSERT_EQ(matrix_doubles.shape[1], 4) << "Vector constructor via dimension fails!";
}

TEST(MatrixTest, ConstructorVector) {
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}};
    Matrix<int> mt_vec_vec(vector_1);
    std::vector<std::vector<double>> vector_2 {{1.9, 2.0, 3.7}, {3.2, 4.1, 5.3}};
    Matrix<double> mt_vec_vec2(vector_2);

    ASSERT_EQ(mt_vec_vec.shape[0], 2) << "Matrix constructor via std::vector<std::vector<T>> fails!";
    ASSERT_EQ(mt_vec_vec.shape[1], 3) << "Matrix constructor via std::vector<std::vector<T>> fails!";
    ASSERT_EQ(mt_vec_vec2.shape[0], 2) << "Matrix constructor via std::vector<std::vector<T>> fails!";
    ASSERT_EQ(mt_vec_vec2.shape[1], 3) << "Matrix constructor via std::vector<std::vector<T>> fails!";
}


TEST(MatrixTest, ConstructFromClass){
    // for int
    Vector vec_inside(std::vector < int > {1, 2, 5});
    std::vector <Vector<int>> vec_loop{vec_inside, vec_inside, vec_inside};
    Vector gg(vec_loop);
    Vector<Vector<int>> vec{gg};
    Matrix<int> mat_Vec_Vec_T(vec);

    ASSERT_EQ(mat_Vec_Vec_T.shape[0], 3) << "Matrix constructor via std::vector<std::vector<T>> fails!";
    ASSERT_EQ(mat_Vec_Vec_T.shape[1], 3) << "Matrix constructor via std::vector<std::vector<T>> fails!";


    // for double
    Vector vec_inside_double(std::vector < double > {1.7, 2.3, 5.6});
    std::vector <Vector<double>> vec_loop2{vec_inside_double, vec_inside_double, vec_inside_double};
    Vector gg2(vec_loop2);
    Vector<Vector<double>> vec2{gg2};
    Matrix<double> mat_Vec_Vec_T2(vec2);

    EXPECT_DOUBLE_EQ(mat_Vec_Vec_T2[0][2], 5.6) << "Matrix constructor via std::vector<std::vector<T>> fails!";
    EXPECT_DOUBLE_EQ(mat_Vec_Vec_T2[2][1], 2.3) << "Matrix constructor via std::vector<std::vector<T>> fails!";

}



TEST(MatrixTest, OperatorPlus){
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}};
    Matrix<int> mt_vec_vec(vector_1);
    std::vector<std::vector<double>> vector_2 {{1.9, 2.0, 3.7}, {3.2, 4.1, 5.3}};
    Matrix<double> mt_vec_vec2(vector_2);
    mt_vec_vec.set_method(0);
    mt_vec_vec2.set_method(0);
    mt_vec_vec.set_cores(1);
    mt_vec_vec2.set_cores(1);

    Matrix<double> check_matrix_ints = mt_vec_vec+mt_vec_vec;
    Matrix<double> check_matrix_doubles = mt_vec_vec2+mt_vec_vec2;
    Matrix<double> check_matrix_both = mt_vec_vec2+mt_vec_vec;

    EXPECT_DOUBLE_EQ(check_matrix_ints[0][0], 2.0) << "Matrix addition with ints fails!";
    EXPECT_DOUBLE_EQ(check_matrix_ints[1][2], 10.0) << "Matrix addition with ints fails!";

    EXPECT_DOUBLE_EQ(check_matrix_doubles[0][0], 3.8) << "Matrix addition with doubles fails!";
    EXPECT_DOUBLE_EQ(check_matrix_doubles[1][2], 10.6) << "Matrix addition with doubles fails!";


    EXPECT_DOUBLE_EQ(check_matrix_both[0][0], 2.9) << "Matrix addition with ints-doubles fails!";
    EXPECT_DOUBLE_EQ(check_matrix_both[1][2], 10.3) << "Matrix addition with ints-doubles fails!";


    mt_vec_vec.set_method(0);
    mt_vec_vec2.set_method(0);
    mt_vec_vec.set_cores(2);
    mt_vec_vec2.set_cores(2);

    Matrix<double> check_matrix_ints_2 = mt_vec_vec+mt_vec_vec;
    Matrix<double> check_matrix_doubles_2 = mt_vec_vec2+mt_vec_vec2;
    Matrix<double> check_matrix_both_2 = mt_vec_vec2+mt_vec_vec;

    EXPECT_DOUBLE_EQ(check_matrix_ints_2[0][0], 2.0) << "Matrix addition with ints fails!";
    EXPECT_DOUBLE_EQ(check_matrix_ints_2[1][2], 10.0) << "Matrix addition with ints fails!";

    EXPECT_DOUBLE_EQ(check_matrix_doubles_2[0][0], 3.8) << "Matrix addition with doubles fails!";
    EXPECT_DOUBLE_EQ(check_matrix_doubles_2[1][2], 10.6) << "Matrix addition with doubles fails!";


    EXPECT_DOUBLE_EQ(check_matrix_both_2[0][0], 2.9) << "Matrix addition with ints-doubles fails!";
    EXPECT_DOUBLE_EQ(check_matrix_both_2[1][2], 10.3) << "Matrix addition with ints-doubles fails!";




    mt_vec_vec.set_method(1);
    mt_vec_vec2.set_method(1);

    Matrix<double> check_matrix_ints_3 = mt_vec_vec+mt_vec_vec;
    Matrix<double> check_matrix_doubles_3 = mt_vec_vec2+mt_vec_vec2;
    Matrix<double> check_matrix_both_3 = mt_vec_vec2+mt_vec_vec;

    EXPECT_DOUBLE_EQ(check_matrix_ints_3[0][0], 2.0) << "Matrix addition with ints fails!";
    EXPECT_DOUBLE_EQ(check_matrix_ints_3[1][2], 10.0) << "Matrix addition with ints fails!";

    EXPECT_DOUBLE_EQ(check_matrix_doubles_3[0][0], 3.8) << "Matrix addition with doubles fails!";
    EXPECT_DOUBLE_EQ(check_matrix_doubles_3[1][2], 10.6) << "Matrix addition with doubles fails!";


    EXPECT_DOUBLE_EQ(check_matrix_both_3[0][0], 2.9) << "Matrix addition with ints-doubles fails!";
    EXPECT_DOUBLE_EQ(check_matrix_both_3[1][2], 10.3) << "Matrix addition with ints-doubles fails!";


}



TEST(MatrixTest, OperatorMinus){
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}};
    Matrix<int> mt_vec_vec(vector_1);
    std::vector<std::vector<double>> vector_2 {{1.9, 2.0, 3.7}, {3.2, 4.1, 5.3}};
    Matrix<double> mt_vec_vec2(vector_2);
    mt_vec_vec.set_method(0);
    mt_vec_vec2.set_method(0);
    mt_vec_vec.set_cores(1);
    mt_vec_vec2.set_cores(1);

    Matrix<double> check_matrix_ints = mt_vec_vec-mt_vec_vec;
    Matrix<double> check_matrix_doubles = mt_vec_vec2-mt_vec_vec2;
    Matrix<double> check_matrix_both = mt_vec_vec2-mt_vec_vec;

    mt_vec_vec.set_method(0);
    mt_vec_vec2.set_method(0);
    mt_vec_vec.set_cores(2);
    mt_vec_vec2.set_cores(2);

    Matrix<double> check_matrix_ints_2 = mt_vec_vec-mt_vec_vec;
    Matrix<double> check_matrix_doubles_2 = mt_vec_vec2-mt_vec_vec2;
    Matrix<double> check_matrix_both_2 = mt_vec_vec2-mt_vec_vec;

    mt_vec_vec.set_method(1);
    mt_vec_vec2.set_method(1);
    Matrix<double> check_matrix_ints_3 = mt_vec_vec-mt_vec_vec;
    Matrix<double> check_matrix_doubles_3 = mt_vec_vec2-mt_vec_vec2;
    Matrix<double> check_matrix_both_3 = mt_vec_vec2-mt_vec_vec;



    EXPECT_DOUBLE_EQ(check_matrix_ints[0][0], check_matrix_ints_2[0][0]) << "Matrix substraction with ints fails!";
    EXPECT_DOUBLE_EQ(check_matrix_ints_2[0][0], check_matrix_ints_3[0][0]) << "Matrix substraction with ints fails!";

    EXPECT_DOUBLE_EQ(check_matrix_doubles[0][0], check_matrix_doubles_2[0][0]) << "Matrix substraction with doubles fails!";
    EXPECT_DOUBLE_EQ(check_matrix_doubles_2[1][2], check_matrix_doubles_3[0][0]) << "Matrix substraction with doubles fails!";


    EXPECT_DOUBLE_EQ(check_matrix_both[0][0], check_matrix_both_2[0][0]) << "Matrix substraction with ints-doubles fails!";
    EXPECT_DOUBLE_EQ(check_matrix_both_2[0][0], check_matrix_both_3[0][0]) << "Matrix substraction with ints-doubles fails!";



}

TEST(MatrixTest, OperatorMultDivKoef){

    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}};
    Matrix<int> mt_vec_vec(vector_1);
    std::vector<std::vector<double>> vector_2 {{1.9, 2.0, 3.7}, {3.2, 4.1, 5.3}};
    Matrix<double> mt_vec_vec2(vector_2);

    int int_a = 9;
    int int_b = 2;

    double double_a = 3.1;
    double double_b = 1.5;


    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(1);

    mt_vec_vec2.set_method(0);
    mt_vec_vec2.set_cores(1);

    Matrix<double> result_matr_1 = mt_vec_vec*int_a;
    Matrix<double> result_matr_2 = mt_vec_vec/int_a;
    Matrix<double> result_matr_3 = mt_vec_vec*double_a;
    Matrix<double> result_matr_4 = mt_vec_vec/double_b;
    Matrix<double> result_matr_5 = mt_vec_vec2*int_a;
    Matrix<double> result_matr_6 = mt_vec_vec2/int_a;
    Matrix<double> result_matr_7 = mt_vec_vec2*double_a;
    Matrix<double> result_matr_8 = mt_vec_vec2/double_b;


    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(2);

    mt_vec_vec2.set_method(0);
    mt_vec_vec2.set_cores(2);

    Matrix<double> result_matr_1_2 = mt_vec_vec*int_a;
    Matrix<double> result_matr_2_2 = mt_vec_vec/int_a;
    Matrix<double> result_matr_3_2 = mt_vec_vec*double_a;
    Matrix<double> result_matr_4_2 = mt_vec_vec/double_b;
    Matrix<double> result_matr_5_2 = mt_vec_vec2*int_a;
    Matrix<double> result_matr_6_2 = mt_vec_vec2/int_a;
    Matrix<double> result_matr_7_2 = mt_vec_vec2*double_a;
    Matrix<double> result_matr_8_2 = mt_vec_vec2/double_b;


    mt_vec_vec.set_method(1);
    mt_vec_vec2.set_method(1);

    Matrix<double> result_matr_1_3 = mt_vec_vec*int_a;
    Matrix<double> result_matr_2_3 = mt_vec_vec/int_a;
    Matrix<double> result_matr_3_3 = mt_vec_vec*double_a;
    Matrix<double> result_matr_4_3 = mt_vec_vec/double_b;
    Matrix<double> result_matr_5_3 = mt_vec_vec2*int_a;
    Matrix<double> result_matr_6_3 = mt_vec_vec2/int_a;
    Matrix<double> result_matr_7_3 = mt_vec_vec2*double_a;
    Matrix<double> result_matr_8_3 = mt_vec_vec2/double_b;

    EXPECT_DOUBLE_EQ(result_matr_1[0][0], result_matr_1_2[0][0]) << "Multiplication of a matrix by a koef failed";
    EXPECT_DOUBLE_EQ(result_matr_1[0][0], result_matr_1_3[0][0]) << "Multiplication of a matrix by a koef failed";

    EXPECT_DOUBLE_EQ(result_matr_2[0][0], result_matr_2_2[0][0]) << "Division of a matrix by a koef failed";
    EXPECT_DOUBLE_EQ(result_matr_2[0][0], result_matr_2_3[0][0]) << "Division of a matrix by a koef failed";

    EXPECT_DOUBLE_EQ(result_matr_3[0][0], result_matr_3_2[0][0]) << "Multiplication of a matrix by a koef failed";
    EXPECT_DOUBLE_EQ(result_matr_3[0][0], result_matr_3_3[0][0]) << "Multiplication of a matrix by a koef failed";

    EXPECT_DOUBLE_EQ(result_matr_4[0][0], result_matr_4_2[0][0]) << "Division of a matrix by a koef failed";
    EXPECT_DOUBLE_EQ(result_matr_4[0][0], result_matr_4_3[0][0]) << "Division of a matrix by a koef failed";

    EXPECT_DOUBLE_EQ(result_matr_5[0][0], result_matr_5_2[0][0]) << "Multiplication of a matrix by a koef failed";
    EXPECT_DOUBLE_EQ(result_matr_5[0][0], result_matr_5_3[0][0]) << "Multiplication of a matrix by a koef failed";

    EXPECT_DOUBLE_EQ(result_matr_6[0][0], result_matr_6_2[0][0]) << "Division of a matrix by a koef failed";
    EXPECT_DOUBLE_EQ(result_matr_6[0][0], result_matr_6_3[0][0]) << "Division of a matrix by a koef failed";

    EXPECT_DOUBLE_EQ(result_matr_7[0][0], result_matr_7_2[0][0]) << "Multiplication of a matrix by a koef failed";
    EXPECT_DOUBLE_EQ(result_matr_7[0][0], result_matr_7_3[0][0]) << "Multiplication of a matrix by a koef failed";

    EXPECT_DOUBLE_EQ(result_matr_8[0][0], result_matr_8_2[0][0]) << "Division of a matrix by a koef failed";
    EXPECT_DOUBLE_EQ(result_matr_8[0][0], result_matr_8_3[0][0]) << "Division of a matrix by a koef failed";

}

TEST(MatrixTest, OperatorEquals) {
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}};
    Matrix<int> mt_vec_vec(vector_1);
    std::vector<std::vector<double>> vector_2 {{1.9, 2.0, 3.7}, {3.2, 4.1, 5.3}};
    Matrix<double> mt_vec_vec2(vector_2);


    ASSERT_EQ((mt_vec_vec==mt_vec_vec), true) << "Equality of two matrices fails!";
    ASSERT_EQ((mt_vec_vec2==mt_vec_vec2), true) << "Equality of two matrices fails!";
}


TEST(MatrixTest, OperatorMultMatr){
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}, {4, 5, 6}};
    Matrix<int> mt_vec_vec(vector_1);
    std::vector<std::vector<double>> vector_2 {{1.9, 2.0, 3.7}, {3.2, 4.1, 5.3}, {4.5, 7.1, 2.3}};
    Matrix<double> mt_vec_vec2(vector_2);

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(1);
    Matrix<double> one_thread = mt_vec_vec*mt_vec_vec2;

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(2);
    Matrix<double> two_threads = mt_vec_vec*mt_vec_vec2;

    mt_vec_vec.set_method(1);
    Matrix<double> tbb_threads = mt_vec_vec*mt_vec_vec2;



    EXPECT_DOUBLE_EQ(one_thread[0][0], two_threads[0][0]) << "Matrix x Matrix multiplication failed";
    EXPECT_DOUBLE_EQ(one_thread[0][0], tbb_threads[0][0]) << "Matrix x Matrix multiplication failed";
    EXPECT_DOUBLE_EQ(tbb_threads[1][0], one_thread[1][0]) << "Matrix x Matrix multiplication failed";


}


TEST(MatrixTest, OperatorMultVector){
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}, {4, 5, 6}};
    Matrix<int> mt_vec_vec(vector_1);
    Vector<double> vec4({1.1, 2.1, 3.1});

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(1);
    Matrix<double> one_thread = mt_vec_vec*vec4;

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(2);
    Matrix<double> two_threads = mt_vec_vec*vec4;

    mt_vec_vec.set_method(1);
    Matrix<double> tbb_threads = mt_vec_vec*vec4;



    EXPECT_DOUBLE_EQ(one_thread[0][0], two_threads[0][0]) << "Matrix x Matrix multiplication failed";
    EXPECT_DOUBLE_EQ(one_thread[0][0], tbb_threads[0][0]) << "Matrix x Matrix multiplication failed";
    EXPECT_DOUBLE_EQ(tbb_threads[1][0], one_thread[1][0]) << "Matrix x Matrix multiplication failed";


}

TEST(MatrixTest, MinorMatrices){
//    minor_matrix
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}, {4, 5, 6}};
    Matrix<int> mt_vec_vec(vector_1);

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(1);
    Matrix<int> minors_1 = mt_vec_vec.minor_matrix();

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(2);
    Matrix<int> minors_2 = mt_vec_vec.minor_matrix();

    mt_vec_vec.set_method(1);
    Matrix<int> minors_3 = mt_vec_vec.minor_matrix();


    EXPECT_DOUBLE_EQ(minors_1[0][0], minors_2[0][0]) << "Matrix minor failed";
    EXPECT_DOUBLE_EQ(minors_1[0][0], minors_3[0][0]) << "Matrix minor failed";
    EXPECT_DOUBLE_EQ(minors_3[1][0], minors_1[1][0]) << "Matrix minor failed";


}


TEST(MatrixTest, CofactorMatrices){
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}, {4, 5, 6}};
    Matrix<int> mt_vec_vec(vector_1);

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(1);
    Matrix<int> cofactors_1 = mt_vec_vec.get_cofactors_matrix();

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(2);
    Matrix<int> cofactors_2 = mt_vec_vec.get_cofactors_matrix();

    mt_vec_vec.set_method(1);
    Matrix<int> cofactors_3 = mt_vec_vec.get_cofactors_matrix();


    EXPECT_DOUBLE_EQ(cofactors_1[0][0], cofactors_2[0][0]) << "Matrix cofactor failed";
    EXPECT_DOUBLE_EQ(cofactors_2[0][0], cofactors_3[0][0]) << "Matrix cofactor failed";
    EXPECT_DOUBLE_EQ(cofactors_3[1][0], cofactors_1[1][0]) << "Matrix cofactor failed";


}



TEST(MatrixTest, MatrixInverse) {
    std::vector<std::vector<int>> vector_1 {{1, 0, 5}, {2,1, 6}, {3, 4, 0}};
    Matrix<int> mt_vec_vec(vector_1);

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(1);
    Matrix<double> inversion_1 = mt_vec_vec.inverse();

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(2);
    Matrix<double> inversion_2 = mt_vec_vec.inverse();

    mt_vec_vec.set_method(1);
    Matrix<double> inversion_3 = mt_vec_vec.inverse();


    EXPECT_DOUBLE_EQ(inversion_1[0][0], inversion_2[0][0]) << "Matrix inversion failed";
    EXPECT_DOUBLE_EQ(inversion_2[0][0], inversion_3[0][0]) << "Matrix inversion failed";
    EXPECT_DOUBLE_EQ(inversion_3[1][0], inversion_1[1][0]) << "Matrix inversion failed";

}


TEST(MatrixTest, MatrixTranspose) {
    std::vector<std::vector<int>> vector_1 {{1, 0, 5}, {2,1, 6}, {3, 4, 0}};
    Matrix<int> mt_vec_vec(vector_1);

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(1);
    Matrix<int> itran_1 = mt_vec_vec.transpose();

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(2);
    Matrix<int> itran_2 = mt_vec_vec.transpose();

    mt_vec_vec.set_method(1);
    Matrix<int> itran_3 = mt_vec_vec.transpose();


    EXPECT_DOUBLE_EQ(itran_1[0][0], itran_2[0][0]) << "Matrix transpose failed";
    EXPECT_DOUBLE_EQ(itran_2[0][0], itran_3[0][0]) << "Matrix transpose failed";
    EXPECT_DOUBLE_EQ(itran_3[1][0], itran_1[1][0]) << "Matrix transpose failed";

}


TEST(MatrixTest, MatrixFill) {
    std::vector<std::vector<int>> vector_1 {{1, 0, 5}, {2,1, 6}, {3, 4, 0}};
    Matrix<int> mt_vec_vec(vector_1);
    int number = 9;

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(1);
    Matrix<int> fill_1 = mt_vec_vec.fill(number);

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(2);
    Matrix<int> fill_2 = mt_vec_vec.fill(number);

    mt_vec_vec.set_method(1);
    Matrix<int> fill_3 = mt_vec_vec.fill(number);


    EXPECT_DOUBLE_EQ(fill_1[0][0], fill_2[0][0]) << "Matrix filling with a number failed";
    EXPECT_DOUBLE_EQ(fill_2[0][0], fill_3[0][0]) << "Matrix filling with a number failed";
    EXPECT_DOUBLE_EQ(fill_3[1][0], fill_1[1][0]) << "Matrix filling with a number failed";

}

TEST(MatrixTest, MatrixDeterminant) {
    std::vector<std::vector<int>> vector_1 {{1, 0, 5}, {2,1, 6}, {3, 4, 0}};
    Matrix<int> mt_vec_vec(vector_1);

    int determinannt = mt_vec_vec.determinant(mt_vec_vec);

    ASSERT_EQ(determinannt, 1) << "Determinant error";


    std::vector<std::vector<double>> vector_2 {{1.0, 0.7, 5.3}, {2.1,1.6, 6.4}, {3.2, 4.3, 0.5}};
    Matrix<double> mt_vec_vec2(vector_2);

    double determinannt_double = mt_vec_vec2.determinant(mt_vec_vec2);
    EXPECT_NEAR(determinannt_double, 7.604, 10e3) << "Determinant error";

    std::vector<std::vector<int>> vector_small {{1, 5}, {1, 9}};
    Matrix<int> mt_vec_vec_small(vector_small);

    int determinannt_small = mt_vec_vec_small.determinant(mt_vec_vec_small);

    ASSERT_EQ(determinannt_small, 4) << "Determinant error";

}

TEST(MatrixTest, MatrixCutting) {
    std::vector<std::vector<double>> vector_2 {{1.0, 0.7, 5.3},
                                               {2.1,1.6, 6.4},
                                               {3.2, 4.3, 0.5}};
    Matrix<double> mt_vec_vec2(vector_2);

    Matrix<double> cut_row_col = mt_vec_vec2.cuT_Col_Row(0, 0);
    EXPECT_DOUBLE_EQ(cut_row_col[0][0], mt_vec_vec2[1][1]) << "Cutting row and col error";
}



TEST(MatrixTest, MatrixIfIdent) {
    std::vector<std::vector<int>> vector_1 {{1, 0, 5}, {2,1, 6}, {3, 4, 0}};
    Matrix<int> mt_vec_vec(vector_1);

    std::vector<std::vector<int>> vector_2 {{1, 0, 0}, {0,1, 0}, {0, 0, 1}};
    Matrix<int> mt_vec_vec2(vector_2);


    bool first_matrix = mt_vec_vec.isident();
    bool second_matrix = mt_vec_vec2.isident();


    ASSERT_EQ(first_matrix, false) << "Is ident check error";
    ASSERT_EQ(second_matrix, true) << "Is ident check error";
}