#ifndef LA_LIBRARY_MATRIX_H
#define LA_LIBRARY_MATRIX_H

#include <vector>
#include "vector.h"

template<typename T>
class Vector;

template<typename T>
class Matrix
{
public:
    std::vector<int> shape;
    Vector<Vector<T>> matrix;
    T determin = 0;

    Matrix(int rows, int cols){
        shape = std::vector<int> {rows, cols};
        Vector<T> vc1(cols);
        vc1.fill(0);
        std::vector<Vector<T>> vec;
        for (size_t i = 0; i < rows; ++i){
            vec.push_back(vc1);
        }
        Vector mtrx(std::vector<Vector<T>>{vec});
        shape = std::vector<int> {rows, cols};
        matrix = mtrx;

    }


    Matrix(const std::vector<std::vector<T>> &mtrx){
        int rows = mtrx.size();
        int cols = mtrx[0].size();
        shape = std::vector<int> {rows, cols};
        Vector<T> vc1(cols);
        vc1.fill(0);
        std::vector<Vector<T>> vec;
        for (size_t i = 0; i < rows; ++i){

            if (mtrx[i].size()==cols){
                for (size_t j=0; j<cols; ++j){
                    vc1[j] = mtrx[i][j];
                }
                vec.push_back(vc1);
            } else {
                std::cerr<<"All rows should be the same length!"<<"\n";
//                break;
            }
        }
        Vector mtRx(std::vector<Vector<T>>{vec});
        shape = std::vector<int> {rows, cols};
        matrix = mtRx;

    }

    Matrix(const Matrix &) = default;
    Matrix &operator=(const Matrix &) = delete;
    Matrix(Matrix &&) = default;
    Matrix &operator=(Matrix &&) = delete;
    ~Matrix() = default;

    Matrix<T> &operator+(const Matrix<T> &);

    Matrix<T> &operator-(const Matrix<T> &);
    Matrix<T> &operator==(const Matrix<T> &);
    Matrix<T> &operator*(T koef);
    Matrix<T> &operator/(T koef);
    Vector<T> &operator[](int row){
        if (row >= shape[0]){
            std::cerr << "Incorrect index!" << std::endl;
            exit(INDEX_ERROR);
        }
        return matrix[row];
    }
//    std::ostream& print(std::ostream& os);
    Matrix<T> &mul(const Matrix<T> &);
    Matrix<T> &mul(const Vector<T> &);
    Matrix<T> &inverse();
    Matrix<T> &transpose();
//    Matrix<T> &det(){
//        if(shape[0] == shape[1]){
//
//        }
//    }
    Matrix<T> &fill(T num);


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
        for ( size_t i =0; i < shape[0]; ++i ){
            for (size_t j=0; j < shape[1]; ++j){

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

    Matrix<T> fromVec(Vector<Vector<T>> &vc){
        std::vector<std::vector<T>> aa;
        size_t i, j;
        for (i=0; i < vc.get_size(); ++i){
            std::vector<T> a;
            for (j=0; j< vc[0].get_size(); ++j){
                a.push_back(vc[i][j]);
            }
            aa.push_back(a);
            a.clear();

        }
        Matrix<T> tm(std::vector<std::vector<T>>{aa});
        return tm;

    }
    int rowNum(){
        return shape[0];
    }
    int colNum(){
        return shape[1];
    }
    T minor(int col, int row){
        Matrix<T> mt = fromVec(matrix);
        Matrix<T> ptrm = mt.curColRow(col, row, mt);
        return ptrm.determinant(ptrm);
    }


    int determinant(Matrix<T> &mt){

        if (mt.colNum() == mt.rowNum()) {
            if (mt.colNum() == 2){
                return mt.determinant2x2();
            } else {
                size_t i, j;
                for (i=0; i< mt.rowNum(); ++i){
                    Matrix<T> ptrm = mt.curColRow(0, i, mt);
                    if (i%2==0){
                        determin += mt[i][0] * ptrm.determinant(ptrm);
                    } else {
                        determin -= mt[i][0] * ptrm.determinant(ptrm);
                    }
                }
                return determin;
            }
        } else {
            std::cerr<<"Should a square matrix!"<<"\n";
        }

    }

    T determinant2x2(){
        if (shape[0] == shape[1]) {
            T first = matrix[0][0] * matrix[1][1];
            T second = matrix[0][1] * matrix[1][0];
            return first-second;
        } else {
            std::cerr<<"Matrix has to be 2x2 square matrix" <<"\n";
            return 0;
        }
    }

    Matrix<T> curColRow(int col, int row, Matrix<T> &mt){
        std::vector<std::vector<T>> mtrx;
        size_t i, j;

        for(i =0; i<mt.shape[0]; ++i){
            std::vector<T> prom;
            for (j=0; j<mt.shape[1];++j){
                if(i!=row && j!=col){
                    prom.push_back(mt[i][j]);
                }
            }
            if (prom.size() > 0){
                mtrx.push_back(prom);
            }
            prom.clear();
        }
        Matrix tm(std::vector<std::vector<T>>{mtrx});
        return tm;
    }

    T cofactor(int col, int row){
        T min = minor(col, row);
        int min_one = -1;
        for (size_t i = 0; i < row+col+2; ++i){
            min_one = min_one*min_one;
        }
        return min_one*min;
    }

};

template<typename T> std::ostream &operator<<(std::ostream& os, const Matrix<T>& mx){
    os << mx.matrix << "\n";
    return os;
}


#endif //LA_LIBRARY_MATRIX_H
