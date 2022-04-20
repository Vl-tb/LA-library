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
            for (size_t j=0; j<cols; ++j){
                vc1[j] = mtrx[i][j];
            }
            vec.push_back(vc1);
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
    Vector<T> &operator[](int row);
    std::ostream& print(std::ostream& os);
    Matrix<T> &mul(const Matrix<T> &);
    Matrix<T> &mul(const Vector<T> &);
    Matrix<T> &inverse();
    Matrix<T> &transpose();
    Matrix<T> &det();
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

    
    T minor(int col, int row);
    T cofactor(int col, int row);

};

template<typename T> std::ostream &operator<<(std::ostream& os, const Matrix<T>& mx);
#endif //LA_LIBRARY_MATRIX_H
