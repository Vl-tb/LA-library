#ifndef LA_LIBRARY_MATRIX_H
#define LA_LIBRARY_MATRIX_H

#include <iostream>
#include <vector>
#include "vector.h"
#include "errors.h"
#include <typeinfo>
#include <thread>
#include <atomic>
#include <math.h>
#include <pthread.h>
#include "mt.h"
#include "mt_tbb_matrix.h"

template<typename T>
class Vector;

template<typename T>
class Matrix
{
public:
    std::vector<int> shape;
    Vector<Vector<T>> matrix;
    T determin = 0;
    int method = 0;
    int cores = std::thread::hardware_concurrency();
    Matrix() = default;
//    Vector<Vector<int>> Matrix(const Matrix &) = default;
    Matrix &operator=(const Matrix &) = default;
    Matrix (Matrix &&) = default;
    ~Matrix() = default;
    void set_cores(int num_cores) {
        if (num_cores<0) {
            std::cerr << "Cannot be negative amount of working cores!";
            exit(CORES_ERROR);
        }
        cores = num_cores;
    }
    void set_method(int num_method) {
        if (num_method<0 || num_method > 1) {
            std::cerr << "Number of a method may be only 0 or 1";
            exit(CORES_ERROR);
        }
        method = num_method;
    }

    int get_cores() {
        return cores;
    }
    int get_using_method() {
        return method;
    }



    // constr 1
    Matrix(int rows, int cols){
        shape = std::vector<int> {rows, cols};
        Vector<T> vc1(cols);
        vc1.fill(0);
        std::vector<Vector<T>> vec(rows);

        int amount = rows/cores;
        if (cores >0) {

            std::vector<std::thread> threads;

            if (cores < rows) {

                for (int i = 0; i < cores; ++i) {
                    int start = i * amount;
                    int end;
                    if (i != cores-1) {
                        end = (i + 1) * amount;
                    } else {
                        end = rows;
                    }
                    threads.emplace_back(add_to_vector<T>, std::ref(vec), start, end, std::ref(vc1));
                }
            } else {
                for (int i = 0; i < rows; ++i) {
                    threads.emplace_back(add_to_vector<T>, std::ref(vec), i, i + 1, std::ref(vc1));
                }
            }
            for (size_t i = 0; i < threads.size(); ++i) {
                threads[i].join();
            }
        } else {
            for (int i = 0; i < rows; ++i) {
                vec.push_back(vc1);
            }
        }


        Vector mtrx(std::vector<Vector<T>>{vec});
        shape = std::vector<int> {rows, cols};
        matrix = std::ref(mtrx);

    }

    // constr 2
    Matrix(const std::vector<std::vector<T>> &mtrx){
        int rows = mtrx.size();
        int cols = mtrx[0].size();
        shape = std::vector<int> {rows, cols};

        std::vector<Vector<T>> vec(rows);
        int amount = rows/cores;

        if (cores <=1){
            Vector<T> vc1(cols);
            for (int i = 0; i < rows; ++i){

                if (mtrx[i].size()==static_cast<size_t>(cols)){
                    for (int j=0; j<cols; ++j){
                        vc1[j] = mtrx[i][j];
                    }
                    vec.push_back(vc1);
                } else {
                    std::cerr<<"All rows should be the same length!"<<"\n";
                    exit(SHAPES_ERROR);
                }
            }
        } else {

            std::vector<std::thread> threads;

            if (cores < rows) {

                for (int i = 0; i < cores; ++i) {
                    int start = i * amount;
                    int end;
                    if (i != cores-1) {
                        end = (i + 1) * amount;
                    } else {
                        end = rows;
                    }

                    threads.emplace_back(vector_vector<T>, std::ref(mtrx), std::ref(vec), start, end, cols);
                }
            } else {
                for (int i = 0; i < rows; ++i) {
                    threads.emplace_back(vector_vector<T>, std::ref(mtrx), std::ref(vec), i, i+1, cols);
                }
            }
            for (size_t i = 0; i < threads.size(); ++i) {
                threads[i].join();
            }

        }
        Vector mtRx(std::vector<Vector<T>>{vec});
        shape = std::vector<int> {rows, cols};
        matrix = std::ref(mtRx);
    }
    // constr 3
    Matrix(int dim):
        Matrix(dim, dim){}

    // create matrix from Vector<Vector<T>>
    Matrix<T>(Vector<Vector<T>> &vc){
        int init_size = vc[0].size;
        for (int i =0; i < vc.size; ++ i) {
            if (vc[i].size != init_size) {
                std::cerr<<"All rows should be the same length!"<<"\n";
                exit(SHAPES_ERROR);
            }
        }
        matrix = std::ref(vc);
        shape = std::vector<int> {vc.size, vc[0].size};
    }

    template<typename S> Matrix<double> operator+(Matrix<S> &mt){
        if (!add_comp(mt)){
            std::cerr << "Incorrect shapes of one of matrices!" << std::endl;
            exit(SHAPES_ERROR);
        }
        std::string s = typeid(T).name();
        std::string s1 = typeid(S).name();
        int rows = shape[0];
        int cols = shape[1];
        int amount = (rows/cores);

        Matrix<double> res(rows, cols);
        if ( cores <=1) {

            int i, j;
            for (i = 0; i < shape[0]; ++i) {
                for (j = 0; j < shape[1]; ++j) {
                    if (s1 == "d" || s == "d") {
                        res[i][j] = static_cast<double>(matrix[i][j]) + static_cast<double>(mt[i][j]);
                    } else {
                        res[i][j] = matrix[i][j] + mt[i][j];
                    }
                }
            }
        } else {
            if (method == 0) {
                std::vector<std::thread> threads;

                if (cores < rows) {

                    for (int i = 0; i < cores; ++i) {
                        int start = i * amount;
                        int end;
                        if (i != cores - 1) {
                            end = (i + 1) * amount;
                        } else {
                            end = rows;
                        }
                        threads.emplace_back(add_two_matrices<T, S, double>, std::ref(mt), std::ref(matrix), start, end,
                                             std::ref(res), cols);
                    }
                } else {
                    for (int i = 0; i < rows; ++i) {
                        threads.emplace_back(add_two_matrices<T, S, double>, std::ref(mt), std::ref(matrix), i, i + 1,
                                             std::ref(res), cols);
                    }
                }
                for (size_t i = 0; i < threads.size(); ++i) {
                    threads[i].join();
                }

            }
            else if (method==1){
                mt_mt_add_tbb<T, S, double>(std::ref(matrix), std::ref(mt), std::ref(res), shape[0], shape[1]);
            }
        }
        return res;
    }

    template<typename S> Matrix<double> operator-(Matrix<S> &mt){
        if (!add_comp(mt)){
            exit(SHAPES_ERROR);
        }
        std::string s = typeid(T).name();
        std::string s1 = typeid(S).name();
        int rows = shape[0];
        int cols = shape[1];
        int amount = rows/cores;

        Matrix<double> res(shape[0], shape[1]);

        if ( cores <=1) {

            int i, j;
            for (i = 0; i < shape[0]; ++i) {
                for (j = 0; j < shape[1]; ++j) {
                    if (s1 == "d" || s == "d") {
                        res[i][j] = static_cast<double>(matrix[i][j]) - static_cast<double>(mt[i][j]);
                    } else {
                        res[i][j] = matrix[i][j] - mt[i][j];
                    }
                }
            }
        } else {
            if (method == 0) {
                std::vector<std::thread> threads;

                if (cores < rows) {

                    for (int i = 0; i < cores; ++i) {
                        int start = i * amount;
                        int end;
                        if (i != cores - 1) {
                            end = (i + 1) * amount;
                        } else {
                            end = rows;
                        }
                        threads.emplace_back(subtract_two_matrices<T, S, double>, std::ref(mt), std::ref(matrix), start,
                                             end, std::ref(res), shape[1]);

                    }
                } else {
                    for (int i = 0; i < rows; ++i) {
                        threads.emplace_back(subtract_two_matrices<T, S, double>, std::ref(mt), std::ref(matrix), i,
                                             i + 1, std::ref(res), shape[1]);
                    }
                }
                for (size_t i = 0; i < threads.size(); ++i) {
                    threads[i].join();
                }
            } else if (method ==1 ) {
                mt_mt_sub_tbb<T, S, double>(std::ref(matrix), std::ref(mt), std::ref(res), shape[0], shape[1]);
            }
        }
        return res;
    }

    template<typename S> bool operator==(Matrix<S> &mt){
        if (shape[0]!=mt.rowNum() || shape[1]!=mt.colNum()){
            return false;
        }
        std::string s = typeid(T).name();
        std::string s1 = typeid(S).name();
        if (s!=s1) {
            std::cerr << "Matrices should be the same type to compare" << "\n";
            exit(TYPE_ERROR);
        }

        if (cores == 1){
            size_t i, j;
            for (i=0; i < shape[0]; ++i) {
                for (j = 0; j < shape[1]; ++j) {
                    if (mt[i][j] != matrix[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        } else {
            std::atomic<bool> current_true = true;
            if (method == 0) {
                int rows = shape[0];
                int amount = rows / cores;

                std::vector<std::thread> threads;

                if (cores < rows) {
                    for (int i = 0; i < cores; ++i) {
                        int start = i * amount;
                        int end;
                        if (i != cores - 1) {
                            end = (i + 1) * amount;
                        } else {
                            end = rows;
                        }
// void matrix__check__equal(Vector<Vector<T>>& matrix, Matrix<S> &matr_2, std::atomic<bool> &check, int start, int end, int shape_1) {

                            threads.emplace_back(matrix__check__equal<T, S>, std::ref(matrix), std::ref(mt), std::ref(current_true), start,
                                             end, shape[1]);
                    }
                } else {
                    for (int i = 0; i < rows; ++i) {
                        threads.emplace_back(matrix__check__equal<T, S>, std::ref(matrix), std::ref(mt), std::ref(current_true), i,
                                             i+1, shape[1]);
                    }
                }
                for (auto &thread: threads) {
                    thread.join();
                }
            } else {
//   matrix__check_equal_tbb(Vector<Vector<T>>& matrix, Matrix<S> &matr_2, std::atomic<bool> &check, int shape_0, int shape_1) {
                matrix__check_equal_tbb<T, S>(std::ref(matrix), std::ref(mt), std::ref(current_true), shape[0], shape[1]);
            }
            return current_true;

        }
    }

    template<typename S>  Matrix<double> operator*(S koef){

        Matrix<double> tm(shape[0], shape[1]);
        std::string s = typeid(T).name();
        std::string s1 = typeid(S).name();
        int rows = shape[0];
        int cols = shape[1];
        int amount = rows/cores;

        if (cores <= 1) {


            for (int i = 0; i < shape[0]; ++i) {
                for (int j = 0; j < shape[1]; ++j) {
                    if (s1 == "d" || s == "d") {
                        tm[i][j] = static_cast<double>(matrix[i][j]) * static_cast<double>(koef);
                    } else {
                        tm[i][j] = matrix[i][j] * koef;
                    }
                }
            }
        } else {
            if (method == 0) {
                std::vector<std::thread> threads;

                if (cores < rows) {
                    for (int i = 0; i < cores; ++i) {
                        int start = i * amount;
                        int end;
                        if (i != cores - 1) {
                            end = (i + 1) * amount;
                        } else {
                            end = rows;
                        }

                        threads.emplace_back(mult_matr_koef<T, S, double>, std::ref(matrix), koef, start, end,
                                             std::ref(tm), shape[1]);
                    }
                } else {
                    for (int i = 0; i < rows; ++i) {
                        threads.emplace_back(mult_matr_koef<T, S, double>, std::ref(matrix), koef, i, i + 1,
                                             std::ref(tm), shape[1]);
                    }
                }
                for (size_t i = 0; i < threads.size(); ++i) {
                    threads[i].join();
                }
            }else if (method == 1) {
                mt_koef_mult_tbb<T, S, double>(std::ref(matrix), koef, std::ref(tm), shape[0], shape[1]);
            }
        }
        return tm;

    }

    template<typename S>  Matrix<double> operator/(S koef){
        if (koef == 0) {
            std::cerr << "Cannot divide by zero!" << std::endl;
            exit(ZERO_DIVISION_ERROR);
        }

        Matrix<double> tm(shape[0], shape[1]);
        int rows = shape[0];
        int cols = shape[1];
        int amount = rows/cores;

        if (cores <= 1) {


            for (int i = 0; i < shape[0]; ++i) {
                for (int j = 0; j < shape[1]; ++j) {
                    tm[i][j] = static_cast<double>(matrix[i][j]) / static_cast<double>(koef);
                }
            }
        } else {
            if (method == 0){
                std::vector<std::thread> threads;

                if (cores < rows) {
                    for (int i = 0; i < cores; ++i) {
                        int start = i * amount;
                        int end;
                        if (i != cores - 1) {
                            end = (i + 1) * amount;
                        } else {
                            end = rows;
                        }

                        threads.emplace_back(divide_matr_koef<T, S, double>, std::ref(matrix), koef, start, end,
                                             std::ref(tm), shape[1]);
                    }
                } else {
                    for (int i = 0; i < rows; ++i) {
                        threads.emplace_back(divide_matr_koef<T, S, double>, std::ref(matrix), koef, i, i + 1, std::ref(tm),
                                             shape[1]);
                    }
                }
                for (size_t i = 0; i < threads.size(); ++i) {
                    threads[i].join();
                }
            } else if (method == 1) {
                mt_koef_div_tbb<T, S, double>(std::ref(matrix), koef, std::ref(tm), shape[0], shape[1]);
            }
        }
        return tm;
    }

    Vector<T> &operator[](int row){
        if (row >= shape[0]){
            std::cerr << "Incorrect index!" << std::endl;
            exit(INDEX_ERROR);
        }
        return matrix[row];
    }

    template<typename S>  Matrix<double> operator*(Matrix<S> &mt){
        if(!mul_comp(mt)) {
            std::cerr << "Cannot multiply such matrices" << std::endl;
            exit(SHAPES_ERROR);
        }
        Matrix<double> resMatr(shape[0], mt.colNum());
        Matrix<S> trns = mt.transpose();
        int rows = shape[0];
        int cols = shape[1];
        int amount = rows/cores;

        if (cores <= 1){

            int i, j;
            for (i=0; i< shape[0]; ++i) {
                for (j=0; j<trns.rowNum(); ++j){
                    resMatr[i][j] = matrix[i].mult(trns[j]);
                }
            }
        } else {

            if ( method == 0) {
                std::vector<std::thread> threads;

                if (cores < rows) {
                    for (int i = 0; i < cores; ++i) {
                        int start = i * amount;
                        int end;
                        if (i != cores - 1) {
                            end = (i + 1) * amount;
                        } else {
                            end = rows;
                        }
                        threads.emplace_back(matrix_by_matrix<T, S, double>, std::ref(matrix), std::ref(trns), start,
                                             end, std::ref(resMatr));
                    }
                } else {
                    for (int i = 0; i < rows; ++i) {
                        threads.emplace_back(matrix_by_matrix<T, S, double>, std::ref(matrix), std::ref(trns), i, i + 1,
                                             std::ref(resMatr));
                    }
                }
                for (size_t i = 0; i < threads.size(); ++i) {
                    threads[i].join();
                }
            } else {
                mt_mt_mult_tbb<T, S, double>(std::ref(matrix), std::ref(trns), std::ref(resMatr), shape[0]);
            }
        }

        return resMatr;
    }

    template<typename S>  Matrix<double> operator*(Vector<S> &vc){
        if (shape[1] != vc.get_size()){
            std::cerr << "Can not be mutliplied1" << std::endl;
            exit(SHAPES_ERROR);
        }
        Matrix<double> result_matrix(shape[0], 1);
        Matrix<S> mt(vc.get_size(), 1);
        Matrix<T> orig_matr(shape[0], shape[1]);
        int rows = shape[0];
        int amount = rows/cores;

        if (cores <=1) {

            int i, j;
            for (i = 0; i < shape[0]; ++i) {
                result_matrix[i][0] = matrix[i].mult(vc);
            }
        } else {
            if (method == 0) {
                std::vector <std::thread> threads;

                if (cores < rows) {
                    for (int i = 0; i < cores; ++i) {
                        int start = i * amount;
                        int end;
                        if (i != cores - 1) {
                            end = (i + 1) * amount;
                        } else {
                            end = rows;
                        }

                        threads.emplace_back(matrix_by_vector<T, S, double>, std::ref(matrix), std::ref(vc),
                                             std::ref(result_matrix), start, end);
                    }
                } else {
                    for (int i = 0; i < rows; ++i) {
                        threads.emplace_back(matrix_by_vector<T, S, double>, std::ref(matrix), std::ref(vc),
                                             std::ref(result_matrix), i, i+1);
                    }
                }
                for (size_t i = 0; i < threads.size(); ++i) {
                    threads[i].join();
                }
            } else {
                matrix_by_vector_tbb<T, S, double>(std::ref(matrix), std::ref(vc), std::ref(result_matrix), shape[0]);
            }
        }
        return result_matrix;
    }

    Matrix<T> minor_matrix(){
        if (shape[0] != shape[1]){
            std::cerr << "Minor Matrix doesn't exist for a non-square matrix" <<"\n";
            exit(SHAPES_ERROR);
        }

        Matrix<T> or_matrix = some_matrix();
        Matrix<T> minors(shape[0], shape[1]);
        if (cores <=1) {
            int i, j;
            for (i = 0; i < shape[0]; ++i) {
                for (j = 0; j < shape[1]; ++j) {

                    minors[i][j] = or_matrix.minor(i, j);
                }
            }
        } else {
            if (method == 1) {


                int rows = shape[0];
                int amount = rows / cores;

                std::vector <std::thread> threads;

                if (cores < rows) {
                    for (int i = 0; i < cores; ++i) {
                        int start = i * amount;
                        int end;
                        if (i != cores - 1) {
                            end = (i + 1) * amount;
                        } else {
                            end = rows;
                        }
                        threads.emplace_back(put_minors_to_matrix<T>, std::ref(or_matrix), std::ref(minors), start, end,
                                             shape[1]);
                    }
                } else {
                    for (int i = 0; i < rows; ++i) {
                        threads.emplace_back(put_minors_to_matrix<T>, std::ref(or_matrix), std::ref(minors), i, i + 1,
                                             shape[1]);
                    }
                }
                for (size_t i = 0; i < threads.size(); ++i) {
                    threads[i].join();
                }
            } else {
                minor_matrix_tbb<T>(std::ref(or_matrix), std::ref(minors), shape[0], shape[1]);
            }
        }
        return minors;
    }
    Matrix<T> some_matrix(){
        Matrix<T> orig_matr(shape[0], shape[1]);
        int i, j;
        for (i=0; i < shape[0]; ++i){
            for (j=0; j< shape[1]; ++j){
                orig_matr[i][j]=matrix[i][j];
            }
        }
        return orig_matr;
    }

    Matrix<T> get_cofactors_matrix(){
        Matrix<T> or_matrix = some_matrix();
        Matrix<T> cofactors(shape[0], shape[1]);
        if (cores <=1) {
            int i, j;
            for (i = 0; i < shape[0]; ++i) {
                for (j = 0; j < shape[1]; ++j) {
                    T calculated = or_matrix.minor(i, j);
                    int sum = i + j;
                    if (sum%2==1){
                        cofactors[i][j] = -calculated;
                    }else {
                        cofactors[i][j] = calculated;
                    }

                }
            }
        } else {
            if (method == 0) {
                int rows = shape[0];
                int amount = rows / cores;

                std::vector <std::thread> threads;

                if (cores < rows) {
                    for (int i = 0; i < cores; ++i) {
                        int start = i * amount;
                        int end;
                        if (i != cores - 1) {
                            end = (i + 1) * amount;
                        } else {
                            end = rows;
                        }
                        threads.emplace_back(put_cofactors_to_matrix<T>, std::ref(or_matrix), std::ref(cofactors),
                                             start, end, shape[1]);
                    }
                } else {
                    for (int i = 0; i < rows; ++i) {
                        threads.emplace_back(put_cofactors_to_matrix<T>, std::ref(or_matrix), std::ref(cofactors), i,
                                             i + 1, shape[1]);
                    }
                }
                for (size_t i = 0; i < threads.size(); ++i) {
                    threads[i].join();
                }
            } else {
                cofactor_matrix_tbb<T>(std::ref(or_matrix), std::ref(cofactors), shape[0], shape[1]);
            }
        }
        return cofactors;
    }

    Matrix<double> inverse(){
        Matrix<T> orig_matr = some_matrix();
        T deter_original = orig_matr.determinant(orig_matr);
        if (deter_original==0){
            std::cerr << "Cannot inverse singular matrix!";
            exit(DETERMINANT_ERROR);
        }
        Matrix<T> cofactors  = get_cofactors_matrix();

        Matrix<T> adj = cofactors.transpose();

        double one_by_deter = 1.0 / static_cast<double>(deter_original);

        return adj * one_by_deter;
    }


    Matrix<T> transpose() {
        Matrix<T> mt(shape[1], shape[0]);
        if (cores <= 1) {

            for (int j = 0; j < shape[0]; ++j) {
                for (int i = 0; i < shape[1]; ++i) {
                    mt[i][j] = matrix[j][i];
                }
            }
        } else {
            if (method == 0) {
                int rows = shape[0];
                int amount = rows / cores;

                std::vector <std::thread> threads;

                if (cores < rows) {
                    for (int i = 0; i < cores; ++i) {
                        int start = i * amount;
                        int end;
                        if (i != cores - 1) {
                            end = (i + 1) * amount;
                        } else {
                            end = rows;
                        }
                        threads.emplace_back(transpose_matrix_fill<T>, std::ref(matrix), std::ref(mt), start, end,
                                             shape[1]);
                    }
                } else {

                    for (int i = 0; i < rows; ++i) {
                        threads.emplace_back(transpose_matrix_fill<T>, std::ref(matrix), std::ref(mt), i, i + 1,
                                             shape[1]);
                    }
                }
                for (size_t i = 0; i < threads.size(); ++i) {
                    threads[i].join();
                }
            } else {
                matrix_transpose_tbb<T>(std::ref(matrix), std::ref(mt), shape[0], shape[1]);
            }
        }
        return mt;

    }

    Matrix<T> fill(T num){
        Matrix<T> res(shape[0], shape[1]);
        if (cores <= 1){
            int i, j;

            for (i=0; i< shape[0]; ++i){
                for (j=0; j<shape[1]; ++j){
                    res[i][j] = num;
                }
            }
        } else {
            if (method == 0) {
                int rows = shape[0];
                int amount = rows / cores;

                std::vector <std::thread> threads;

                if (cores < rows) {
                    for (int i = 0; i < cores; ++i) {
                        int start = i * amount;
                        int end;
                        if (i != cores - 1) {
                            end = (i + 1) * amount;
                        } else {
                            end = rows;
                        }
                        threads.emplace_back(fill_with_k<T>, num, std::ref(res), start, end, shape[1]);
                    }
                } else {
                    for (int i = 0; i < rows; ++i) {
                        threads.emplace_back(fill_with_k<T>, num, std::ref(res), i, i + 1, shape[1]);
                    }
                }
                for (size_t i = 0; i < threads.size(); ++i) {
                    threads[i].join();
                }
            } else {
                matrix_fill_with<T>(std::ref(res), num, shape[0], shape[1]);
            }
        }
        return res;
    }


    template<typename S> bool add_comp(const Matrix<S> &mt){
        if(shape[0]==mt.shape[0] && shape[1]==mt.shape[1]){
            return true;
        }
        return false;
    }
    template<typename S> bool mul_comp(const Matrix<S> &mt){
        if(shape[1]==mt.shape[0]){
            return true;
        }
        return false;
    }
    bool isnull(){
        for (size_t i =0; i < shape[0]; ++i){
            if (!matrix[i].isnull()){
                return false;
            }
        }
        return true;
    }
    bool isident(){
        if (shape[0]!=shape[1]){
            return false;
        }

        if (cores ==1){
            int i, j;
            for ( i =0; i < shape[0]; ++i ){
                for (j=0; j < shape[1]; ++j){

                    if(i==j){
                        if (matrix[i][j]!=1){
                            return false;
                        }
                    } else if (matrix[i][j]!=0){
                        return false;
                    }
                }
            }
            return true;
        } else {
            std::atomic<bool> current_true = true;
            if (method == 0) {
                int rows = shape[0];
                int amount = rows / cores;

                std::vector <std::thread> threads;

                if (cores < rows) {
                    for (int i = 0; i < cores; ++i) {
                        int start = i * amount;
                        int end;
                        if (i != cores - 1) {
                            end = (i + 1) * amount;
                        } else {
                            end = rows;
                        }
                            threads.emplace_back(matrix__check_ident<T>, std::ref(matrix), std::ref(current_true), start, end, shape[1]);
                    }
                } else {
                    for (int i = 0; i < rows; ++i) {
                        threads.emplace_back(matrix__check_ident<T>, std::ref(matrix), std::ref(current_true), i, i+1, shape[1]);
                    }
                }
                for (auto & thread : threads) {
                    thread.join();
                }
            } else {
                matrix__check_ident_tbb<T>(std::ref(matrix), std::ref(current_true), shape[0], shape[1]);
            }
            return current_true;
        }
    }

    int rowNum(){
        return shape[0];
    }

    int colNum(){
        return shape[1];
    }

    T minor(int row, int col){
        Matrix<T> mt = some_matrix();
        Matrix<T> ptrm = mt.cuT_Col_Row(row, col);
        return ptrm.determinant(ptrm);
    }

    T determinant(Matrix<T> & mt){
        if (mt.colNum() == mt.rowNum()) {
            if (mt.colNum()==1){
                return mt[0][0];
            }
            if (mt.colNum() == 2){
                return mt.determinant2x2();
            } else {
                int i, j;
                for (i=0; i< mt.rowNum(); ++i){
                    Matrix<T> ptrm = mt.cuT_Col_Row(i, 0);
                    if (i%2==0){
                        determin += mt[i][0] * ptrm.determinant(ptrm);
                    } else {
                        determin -= mt[i][0] * ptrm.determinant(ptrm);
                    }
                }
                return determin;
            }
        } else {
            std::cerr<<"Both matrices should be a square matrices!";
            exit(SHAPES_ERROR);
        }
    }

    T determinant2x2(){
        if (shape[0] == shape[1]) {
            T first = matrix[0][0] * matrix[1][1];
            T second = matrix[0][1] * matrix[1][0];
            return first-second;
        } else {
            std::cerr << "Should be a 2x2 matrix" << std::endl;
            exit(SHAPES_ERROR);
        }
    }


    // this method cuts the given column and row from the matrix
    // and returns the result afterwards
    Matrix<T> cuT_Col_Row(int row, int col){
        if ( row >= shape[0] || col >= shape[1]) {
            std::cerr << "Cannot cat an unexisting row or column!" << "\n";
            exit(SHAPES_ERROR);
        }
        int i, j;
        Matrix<T> res_matrix(shape[0]-1, shape[1]-1);
        int r = 0;
        int c = 0;
        for(i =0; i<shape[0]; ++i) {
            for (j=0; j<shape[1]; ++j) {
                if(j!=col && i!=row) {
                    res_matrix[r][c] = matrix[i][j];
                    c +=1;
                }
            }
            c = 0;
            if(i != row){
                r += 1;
            }
        }
        return res_matrix;
    }

    T cofactor(int row, int col){
        T min = minor(row, col);
        int sum = row+col;
        if (sum%2==1){
            return -min;
        }else {
            return min;
        }
    }

};

template<typename T> std::ostream &operator<<(std::ostream& os, const Matrix<T>& mx){
    os << mx.matrix << "\n";
    return os;
}


#endif //LA_LIBRARY_MATRIX_H
