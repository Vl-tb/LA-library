#ifndef LA_LIBRARY_MATRIX_H
#define LA_LIBRARY_MATRIX_H

#include <vector>
#include "vector.h"
#include "errors.h"
#include <typeinfo>
#include <thread>
#include <atomic>
#include <math.h>
#include <pthread.h>
#include "mt.h"

template<typename T>
class Vector;

template<typename T>
class Matrix
{
public:
    std::vector<int> shape;
    Vector<Vector<T>> matrix;
    T determin = 0;
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

    int get_cores() {
        return cores;
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
        Vector<T> vc1(cols);
        vc1.fill(0);
        std::vector<Vector<T>> vec(rows);
        int amount = rows/cores;

        if (cores <=1){
            for (size_t i = 0; i < rows; ++i){

                if (mtrx[i].size()==cols){
                    for (size_t j=0; j<cols; ++j){
                        vc1[j] = mtrx[i][j];
                    }
                    vec.push_back(vc1);
                } else {
                    std::cerr<<"All rows should be the same length!"<<"\n";
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

                    threads.emplace_back(vector_vector<T>, std::ref(mtrx), std::ref(vec), start, end, std::ref(vc1), cols);
                }
            } else {
                for (int i = 0; i < rows; ++i) {
                    threads.emplace_back(vector_vector<T>, std::ref(mtrx), std::ref(vec), i, i+1, std::ref(vc1), cols);
                }
            }
            for (int i = 0; i < threads.size(); ++i) {
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
        matrix = std::ref(vc);
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

            size_t i, j;
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
                    threads.emplace_back(add_two_matrices<T, S, double>, std::ref(mt), std::ref(matrix), start, end, std::ref(res), cols);
                }
            } else {
                for (int i = 0; i < rows; ++i) {
                    threads.emplace_back(add_two_matrices<T, S, double>, std::ref(mt), std::ref(matrix), i, i+1, std::ref(res), cols);
                }
            }
            for (int i = 0; i < threads.size(); ++i) {
                threads[i].join();
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

            size_t i, j;
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
                    threads.emplace_back(subtract_two_matrices<T, S, double>, std::ref(mt), std::ref(matrix), start, end, std::ref(res), shape[1]);

                }
            } else {
                for (int i = 0; i < rows; ++i) {
                    threads.emplace_back(subtract_two_matrices<T, S, double>, std::ref(mt), std::ref(matrix), i, i+1, std::ref(res), shape[1]);
                }
            }
            for (int i = 0; i < threads.size(); ++i) {
                threads[i].join();
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

        size_t i, j;
        for (i=0; i < shape[0]; ++i){
            for (j=0; j< shape[1]; ++j){
                if (mt[i][j] != matrix[i][j]){
                    return false;
                }
            }
        }
        return true;

    }

    template<typename S>  Matrix<double> operator*(S koef){

        Matrix<double> tm(shape[0], shape[1]);
        std::string s = typeid(T).name();
        std::string s1 = typeid(S).name();
        int rows = shape[0];
        int cols = shape[1];
        int amount = rows/cores;

        if (cores <= 1) {


            for (size_t i = 0; i < shape[0]; ++i) {
                for (size_t j = 0; j < shape[1]; ++j) {
                    if (s1 == "d" || s == "d") {
                        tm[i][j] = static_cast<double>(matrix[i][j]) * static_cast<double>(koef);
                    } else {
                        tm[i][j] = matrix[i][j] * koef;
                    }
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

                    threads.emplace_back(mult_matr_koef<T, S, double>, std::ref(matrix), koef, start, end, std::ref(tm), shape[1]);
                }
            } else {
                for (int i = 0; i < rows; ++i) {
                    threads.emplace_back(mult_matr_koef<T, S, double>, std::ref(matrix), koef, i, i+1, std::ref(tm), shape[1]);
                }
            }
            for (int i = 0; i < threads.size(); ++i) {
                threads[i].join();
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


            for (size_t i = 0; i < shape[0]; ++i) {
                for (size_t j = 0; j < shape[1]; ++j) {
                    tm[i][j] = static_cast<double>(matrix[i][j]) / static_cast<double>(koef);
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

                    threads.emplace_back(divide_matr_koef<T, S, double>, std::ref(matrix), koef, start, end, std::ref(tm), shape[1]);
                }
            } else {
                for (int i = 0; i < rows; ++i) {
                    threads.emplace_back(divide_matr_koef<T, S, double>, std::ref(matrix), koef, i, i+1, std::ref(tm), shape[1]);
                }
            }
            for (int i = 0; i < threads.size(); ++i) {
                threads[i].join();
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

            size_t i, j;
            for (i=0; i< shape[0]; ++i) {
                for (j=0; j<trns.rowNum(); ++j){
                    resMatr[i][j] = matrix[i].mult(trns[j]);
                }
            }
        } else {
//matrix_by_matrix(Vector<Vector<T>>& matrix, Matrix<S> &mt, int start, int end, Matrix<F> &result_matrix, int shape_1) {
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
//matrix_by_matrix(Vector<Vector<T>>& matrix, Matrix<S> &mt, int start, int end, Matrix<F> &result_matrix, int shape_1) {
                    threads.emplace_back(matrix_by_matrix<T, S, double>, std::ref(matrix), std::ref(trns), start, end, std::ref(resMatr));
                }
            } else {
                for (int i = 0; i < rows; ++i) {
                    threads.emplace_back(matrix_by_matrix<T, S, double>, std::ref(matrix), std::ref(trns), i, i+1, std::ref(resMatr));
                }
            }
            for (int i = 0; i < threads.size(); ++i) {
                threads[i].join();
            }

        }

        return resMatr;
    }

    template<typename S>  Matrix<double> operator*(Vector<S> &vc){
        if (shape[1] != vc.get_size()){
            std::cerr << "Can not be mutliplied1" << std::endl;
            exit(SHAPES_ERROR);
        }
        Matrix<S> mt(vc.get_size(), 1);
        Matrix<T> orig_matr(shape[0], shape[1]);
        int rows = shape[0];
        int amount = rows/cores;

        if (cores <=1) {


            size_t i, j;
            for (i = 0; i < shape[0]; ++i) {
                for (j = 0; j < shape[1]; ++j) {
                    orig_matr[i][j] = matrix[i][j];
                }
                mt[i][0] = vc[i];
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

                    threads.emplace_back(matrix_by_vector<T, S>, std::ref(matrix), std::ref(vc), std::ref(mt), std::ref(orig_matr), start, end, shape[1]);
                }
            } else {
                for (int i = 0; i < rows; ++i) {
                    threads.emplace_back(matrix_by_vector<T, S>, std::ref(matrix), std::ref(vc), std::ref(mt), std::ref(orig_matr), i, i+1, shape[1]);
                }
            }
            for (int i = 0; i < threads.size(); ++i) {
                threads[i].join();
            }

        }
        return orig_matr*(mt);
    }

    Matrix<T> minor_matrix(){
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
            int rows = shape[0];
            int amount = rows/cores;

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
                    threads.emplace_back(put_minors_to_matrix<T>, std::ref(or_matrix), std::ref(minors), start, end, shape[1]);
                }
            } else {
                for (int i = 0; i < rows; ++i) {
                    threads.emplace_back(put_minors_to_matrix<T>, std::ref(or_matrix), std::ref(minors), i, i+1, shape[1]);
                }
            }
            for (int i = 0; i < threads.size(); ++i) {
                threads[i].join();
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
            int rows = shape[0];
            int amount = rows/cores;

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
                    threads.emplace_back(put_cofactors_to_matrix<T>, std::ref(or_matrix), std::ref(cofactors), start, end, shape[1]);
                }
            } else {
                for (int i = 0; i < rows; ++i) {
                    threads.emplace_back(put_cofactors_to_matrix<T>, std::ref(or_matrix), std::ref(cofactors), i, i+1, shape[1]);
                }
            }
            for (int i = 0; i < threads.size(); ++i) {
                threads[i].join();
            }

        }
        return cofactors;
    }

    Matrix<double> inverse(){
//        Matrix<T> minors = minor_matrix();
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
            int rows = shape[0];
            int amount = rows/cores;

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
                    threads.emplace_back(transpose_matrix_fill<T>, std::ref(matrix), std::ref(mt), start, end, shape[1]);
                }
            } else {
                for (int i = 0; i < rows; ++i) {
                    threads.emplace_back(transpose_matrix_fill<T>, std::ref(matrix), std::ref(mt), i, i+1, shape[1]);
                }
            }
            for (int i = 0; i < threads.size(); ++i) {
                threads[i].join();
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
            int rows = shape[0];
            int amount = rows/cores;

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
                    threads.emplace_back(fill_with_k<T>, num, std::ref(res), start, end, shape[1]);
                }
            } else {
                for (int i = 0; i < rows; ++i) {
                    threads.emplace_back(fill_with_k<T>, num, std::ref(res), i, i+1, shape[1]);
                }
            }
            for (int i = 0; i < threads.size(); ++i) {
                threads[i].join();
            }
        }
        return res;
    }


    bool add_comp(const Matrix<T> &mt){
        if(shape[0]==mt.shape[0] && shape[1]==mt.shape[1]){
            return true;
        }
        return false;
    }
    bool mul_comp(const Matrix<T> &mt){
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
                size_t i, j;
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
        size_t i, j;
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