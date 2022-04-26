#ifndef LA_LIBRARY_MATRIX_H
#define LA_LIBRARY_MATRIX_H

#include <vector>
#include "vector.h"
#include "errors.h"

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

//    Matrix(const Vector<Vector<T>> &vec):
//            Matrix<T> m1(shape[0], shape[1]) {
//        size_t i,j;
//        for (i = 0; i<shape[0]; ++i){
//            for (j=0; j<shape[1]; ++j){
//                m1[i][j] = matrix[i][j];
//            }
//        }
//    }


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

    Matrix(int dim):
        Matrix(dim, dim){}

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

    Matrix() = default;
    Matrix(const Matrix &) = default;
    Matrix &operator=(const Matrix &) = default;
    Matrix (Matrix &&) = default;
    ~Matrix() = default;

    Matrix<T> operator+(Matrix<T> &mt){
        if (shape[0]!=mt.rowNum() && shape[1]!=mt.colNum()){
            std::cerr << "Incorrect shapes of one of matrices!" << std::endl;
            exit(SHAPES_ERROR);
        }
        Matrix<T> res(shape[0], shape[1]);

        size_t i, j;
        for (i=0; i < shape[0]; ++i){
            for (j=0; j< shape[1]; ++j){
                res[i][j] = mt[i][j] + matrix[i][j];
            }
        }
        return res;
    }

    Matrix<T> operator-(Matrix<T> &mt){
        if (shape[0]!=mt.rowNum() && shape[1]!=mt.colNum()){
            std::cerr << "Incorrect shapes of one of matrices!" << std::endl;
            exit(SHAPES_ERROR);
        }
        Matrix<T> res(shape[0], shape[1]);

        size_t i, j;
        for (i=0; i < shape[0]; ++i){
            for (j=0; j< shape[1]; ++j){
                res[i][j] = matrix[i][j] - mt[i][j];
            }
        }
        return res;
    }

    bool operator==(Matrix<T> &mt){
        if (shape[0]!=mt.rowNum() || shape[1]!=mt.colNum()){
            return false;
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
        for( size_t i = 0; i < shape[0]; ++i ) {
            for ( size_t j = 0; j<shape[1]; ++j){
                tm[i][j] = static_cast<double>(matrix[i][j])*static_cast<double>(koef);
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
        for( size_t i = 0; i < shape[0]; ++i ) {
            for ( size_t j = 0; j<shape[1]; ++j){
                tm[i][j] = static_cast<double>(matrix[i][j])/static_cast<double>(koef);
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

    Matrix<T> mul(Matrix<T> &mt){
        if(shape[1] != mt.rowNum()) {
            std::cerr << "Cannot multiply such matrices" << std::endl;
            exit(SHAPES_ERROR);
        }
        Matrix<T> resMatr(shape[0], mt.colNum());
        Matrix<T> trns = mt.transpose();
        size_t i, j;
        for (i=0; i< shape[0]; ++i) {
            for (j=0; j<trns.rowNum(); ++j){
                resMatr[i][j] = matrix[i].mult(trns[j]);
            }
        }
        return resMatr;
    }

    Matrix<T> mul(Vector<T> &vc){
        Matrix<T> mt = vc.transpose();
        Matrix<T> orig_matr(shape[0], shape[1]);

        size_t i, j;
        for (i=0; i < shape[0]; ++i){
            for (j=0; j< shape[1]; ++j){
                orig_matr[i][j]=matrix[i][j];
            }
        }
        return orig_matr.mul(mt);
    }

    Matrix<double> inverse(){
//        if (перевірка на 0 дет) {
//            std::cerr << "Cannot inverse singular matrix!";
//            exit(DETERMINANT_ERROR);
//        }
        Matrix<T> minors(shape[0], shape[1]);
        Matrix<T> orig_matr(shape[0], shape[1]);
        size_t i, j;
        for (i=0; i < shape[0]; ++i){
            for (j=0; j< shape[1]; ++j){
                minors[i][j] = minor(j, i);
                orig_matr[i][j]=matrix[i][j];
            }
        }
        Matrix<T> cofactors(shape[0], shape[1]);
        for (i=0; i < shape[0]; ++i){
            for (j=0; j< shape[1]; ++j){
                if (i%2==0) {
                    if(j%2==1){
                        cofactors[i][j] = -minors[i][j];
                    } else{
                        cofactors[i][j] = minors[i][j];
                    }
                } else {
                    if(j%2==1){
                        cofactors[i][j] = minors[i][j];
                    } else{
                        cofactors[i][j] = -minors[i][j];
                    }
                }
            }
        }
        Matrix<T> adj = cofactors.transpose();
        T deter_original = orig_matr.determinant(orig_matr);
        double one_by_deter = 1.0 / static_cast<double>(deter_original);

        return adj * one_by_deter;
    }


    Matrix<T> transpose() {
        Matrix<T> mt(shape[1], shape[0]);
        size_t i=0;
        size_t j=0;
        while(j!=shape[0]){
            for( i = 0; i < shape[1]; ++i){
                mt[i][j] = matrix[j][i];
            }

            j = j+1;

        }
        return mt;

    }

    Matrix<T> fill(T num){
        size_t i, j;
        Matrix<T> res(shape[0], shape[1]);
        for (i=0; i< shape[0]; ++i){
            for (j=0; j<shape[1]; ++j){
                res[i][j] = num;
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

    T determinant(Matrix<T> &mt){
        if (mt.colNum() == mt.rowNum()) {
            if (mt.colNum()==1){
                return mt[0][0];
            }
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
