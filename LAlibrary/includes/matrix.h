#ifndef LA_LIBRARY_MATRIX_H
#define LA_LIBRARY_MATRIX_H

#include <vector>
#include "vector.h"
#include "errors.h"
#include <typeinfo>
#include <thread>
#include <atomic>
#include <math.h>
#include "mt.h"
#include "thr_queue.h"

template<typename T, typename S> void mult_matr_by_koef(Vector<Vector<T>> &matrix, Vector<Vector<double>> &res_matr, S koef, int j_max, int i_from, int i_to, int i_max){
    std::string s = typeid(T).name();
    std::string s1 = typeid(S).name();


    if (i_to > i_max){
        i_to = i_max;
    }
    for (int i = i_from; i< i_to; ++i) {
        for (int j = 0; j < j_max; ++j) {
            if (s == "d" || s1 == "d") {
                res_matr[i][j] = static_cast<double>(matrix[i][j]) * static_cast<double>(koef);
            } else {
                res_matr[i][j] = matrix[i][j] * koef;
            }
        }
    }
}
//
//threads.emplace_back(matr_rows_minus<T, S>, std::ref(matrix), std::ref(result.matrix), std::ref(mt.matrix),
//        std::ref(shape[1]), i * (delta), (i + 1) * (delta), std::ref(shape[0]));
//template<typename T, typename S> void matr_rows_minus(Vector<Vector<T>> &matrix, Vector<Vector<double>> &res_matr, Vector<Vector<S>> &matrix_minus, int j_max, int i_from, int i_to, int i_max){
//    std::string s = typeid(T).name();
//    std::string s1 = typeid(S).name();
//
//
//    if (i_to > i_max){
//        i_to = i_max;
//    }
//    for (int i = i_from; i< i_to; ++i) {
//        for (int j = 0; j < j_max; ++j) {
//            if (s == "d" || s1 == "d") {
//                res_matr[i][j] = static_cast<double>(matrix[i][j]) - static_cast<double>(res_matr[i][j]);
//            } else {
//                res_matr[i][j] = matrix[i][j] - res_matr[i][j];
//            }
//        }
//    }
//}
//

template<typename T, typename S> void matr_rows_minus(Vector<Vector<T>> &matrix){

    std::cout<<8<<"\n";
}

template<typename T>
class mt_que;

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
    Matrix(const Matrix &) = default;
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

    // constr 2
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
            }
        }
        Vector mtRx(std::vector<Vector<T>>{vec});
        shape = std::vector<int> {rows, cols};
        matrix = mtRx;
    }
    // constr 3
    Matrix(int dim):
            Matrix(dim, dim){}

    // get obj for future methods
//    Matrix<T> fromVec(Vector<Vector<T>> &vc){
//        std::vector<std::vector<T>> aa;
//        size_t i, j;
//        for (i=0; i < vc.get_size(); ++i){
//            std::vector<T> a;
//            for (j=0; j< vc[0].get_size(); ++j){
//                a.push_back(vc[i][j]);
//            }
//            aa.push_back(a);
//            a.clear();
//        }
//        Matrix<T> tm(std::vector<std::vector<T>>{aa});
//        return tm;
//    }









    // constr 1
//    Matrix(int rows, int cols){
//        shape = std::vector<int> {rows, cols};
//        Vector<T> vc1(cols);
//        vc1.fill(0);
//        std::vector<Vector<T>> vec;
//        for (size_t i = 0; i < rows; ++i){
//            vec.push_back(vc1);
//        }
//        Vector mtrx(std::vector<Vector<T>>{vec}); // here the prll process is
//        shape = std::vector<int> {rows, cols};
//        matrix = mtrx;
//
//    }
//
//    // constr 2
//    Matrix(const std::vector<std::vector<T>> &mtrx){
//        int rows = mtrx.size();
//        int cols = mtrx[0].size();
//        shape = std::vector<int> {rows, cols};
//
//        std::vector<Vector<T>> vec;
//
//        mt_que<int> n_i_s;
//        n_i_s.set_maxsize(10000);
//
//
//        for (size_t i = 0; i < rows; ++i){
//
//            if (mtrx[i].size()==cols){
//                if (cores ==0){
//                    Vector<T> vc1(cols);
//                    vc1.fill(0);
//
//                    for (size_t j=0; j<cols; ++j){
//                        vc1[j] = mtrx[i][j];
//                    }
//                    vec.push_back(vc1);
//                }
//                else{
//                    Vector<T> vc1(cols);
//                    vc1.fill(0);
//
////                    std::cout<<"Enqued"<<"\n";
//                    if (i != rows-1){
//                        n_i_s.enque(i);
//                    } else {
//                        n_i_s.enque(i);
//                        n_i_s.enque(-1);
//                    }
//                }
//
//            } else {
//                std::cerr<<"All rows should be the same length!"<<"\n";
//            }
//        }
//
//        if (cores==0){
//            Vector mtRx(std::vector<Vector<T>>{vec});
//            shape = std::vector<int> {rows, cols};
//            matrix = mtRx;
//        } else{
//            std::vector<std::thread> threads;
//            for (int i =0; i < cores; ++i){
////                threads.emplace_back(mt_constr_vec_assign<T>, std::ref(mtrx));
//                threads.emplace_back(mt_constr_vec_assign<T>, std::ref(n_i_s), std::ref(mtrx), std::ref(vec), std::ref(cols));
//            }
//            for (std::thread &th: threads) {
//                th.join();
//            }
//            Vector mtRx(std::vector<Vector<T>>{vec});
//            shape = std::vector<int> {rows, cols};
//            matrix = mtRx;
//        }
//
//    }
//    // constr 3
//    Matrix(int dim):
//        Matrix(dim, dim){}









    // get obj for future methods
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
        Matrix<T> tm(std::vector<std::vector<T>>{aa}); // here goes the prll-ion
        return tm;
    }

    template<typename S> Matrix<double> operator+(Matrix<S> &mt){
        if (!add_comp(mt)){
            std::cerr << "Incorrect shapes of one of matrices!" << std::endl;
            exit(SHAPES_ERROR);
        }

        if (cores == 0){
            std::string s = typeid(T).name();
            std::string s1 = typeid(S).name();


            std::vector<std::vector<double>> res;
            size_t i, j;
            for (i=0; i < shape[0]; ++i){
                std::vector<double> proms;
                for (j=0; j< shape[1]; ++j){
                    double prom_res;
                    if(s1=="d" ||s=="d"){
                        prom_res = static_cast<double>(matrix[i][j])+static_cast<double>(mt[i][j]);
                    }
                    else{
                        prom_res = matrix[i][j]+mt[i][j];
                    }
                    proms.push_back(prom_res);

                }
                res.push_back(proms);
                proms.clear();

            }
            Matrix<double> result(std::vector<std::vector<double>>{res});
            return result;
        } else {
            mt_que<std::pair<Vector<T>, Vector<S>>> rows_of_matr;
            rows_of_matr.set_maxsize(10000);
            for (int i = 0; i < shape[0]; ++i){
                rows_of_matr.enque({matrix[i], mt[i]});
                if (i==shape[0]-1){
                    Vector<T> PP1(shape[1]-1);
                    Vector<S> PP2(shape[1]-1);
                    rows_of_matr.enque({PP1, PP2});
                }

            }

            std::vector<std::thread> threads;
            std::vector<std::vector<double>> res_vec_out;
            for ( int i =0; i< cores; ++i) {
                threads.emplace_back(matr_rows_addition<T, S>, std::ref(rows_of_matr), std::ref(res_vec_out), std::ref(shape[1]));
            }
            for (std::thread &th: threads) {
                th.join();
            }
            Matrix<double> res(std::vector<std::vector<double>>{res_vec_out});

            return res;
        }

    }
    template<typename S> Matrix<double> operator-(Matrix<S> &mt){
        if (!add_comp(mt)){
            std::cerr << "Incorrect shapes of one of matrices!" << std::endl;
            exit(SHAPES_ERROR);
        }

        if (cores == 0){
            std::string s = typeid(T).name();
            std::string s1 = typeid(S).name();


            std::vector<std::vector<double>> res;
            size_t i, j;
            for (i=0; i < shape[0]; ++i){
                std::vector<double> proms;
                for (j=0; j< shape[1]; ++j){
                    double prom_res;
                    if(s1=="d" ||s=="d"){
                        prom_res = static_cast<double>(matrix[i][j])-static_cast<double>(mt[i][j]);
                    }
                    else{
                        prom_res = matrix[i][j]-mt[i][j];
                    }
                    proms.push_back(prom_res);

                }
                res.push_back(proms);
                proms.clear();

            }
            Matrix<double> result(std::vector<std::vector<double>>{res});
            return result;
        } else {
            mt_que<std::pair<Vector<T>, Vector<S>>> rows_of_matr;
            rows_of_matr.set_maxsize(10000);
            for (int i = 0; i < shape[0]; ++i){
                rows_of_matr.enque({matrix[i], mt[i]});
                if (i==shape[0]-1){
                    Vector<T> PP1(shape[1]-1);
                    Vector<S> PP2(shape[1]-1);
                    rows_of_matr.enque({PP1, PP2});
                }

            }

            std::vector<std::thread> threads;
            std::vector<std::vector<double>> res_vec_out;
            for ( int i =0; i< cores; ++i) {
                threads.emplace_back(matr_rows_substraction<T, S>, std::ref(rows_of_matr), std::ref(res_vec_out), std::ref(shape[1]));
            }
            for (std::thread &th: threads) {
                th.join();
            }
            Matrix<double> res(std::vector<std::vector<double>>{res_vec_out});

            return res;
        }

    }


    template<typename S>  Matrix<double> operator*(S koef){

        if (cores ==0) {
//            Matrix<double> tm(shape[0], shape[1]);
            std::string s = typeid(T).name();
            std::string s1 = typeid(S).name();
            std::vector<std::vector<double>> tm;
            for( size_t i = 0; i < shape[0]; ++i ) {
                std::vector<double> proms;
                double res_prom;
                for ( size_t j = 0; j<shape[1]; ++j){
                    if(s1=="d"||s=="d"){
                        res_prom = static_cast<double>(matrix[i][j])*static_cast<double>(koef);
                    }
                    else
                    {
                        res_prom = matrix[i][j]*koef;
                    }
                    proms.push_back(res_prom);
                }
                tm.push_back(proms);
                proms.clear();
            }
            Matrix<double> result(std::vector<std::vector<double>>{tm});
            return result;
        } else {
            mt_que<std::pair<Vector<T>, S>> rows_of_matr;
            rows_of_matr.set_maxsize(10000);
            for (int i = 0; i < shape[0]; ++i){
                rows_of_matr.enque({matrix[i], koef});
                if (i==shape[0]-1){
                    Vector<T> PP1(shape[1]-1);
                    rows_of_matr.enque({PP1, koef});
                }

            }

            std::vector<std::thread> threads;
            std::vector<std::vector<double>> res_vec_out;
            for ( int i =0; i< cores; ++i) {
                threads.emplace_back(matr_koef_multiplication<T, S>, std::ref(rows_of_matr), std::ref(res_vec_out), std::ref(shape[1]));
            }
            for (std::thread &th: threads) {
                th.join();
            }
            Matrix<double> res(std::vector<std::vector<double>>{res_vec_out});

            return res;
        }
    }
//if (koef == 0) {
//            std::cerr << "Cannot divide by zero!" << std::endl;
//            exit(ZERO_DIVISION_ERROR);
//        }


    template<typename S>  Matrix<double> operator/(S koef){
        if (koef == 0) {
            std::cerr << "Cannot divide by zero!" << std::endl;
            exit(ZERO_DIVISION_ERROR);
        }
        if (cores ==0) {
//            Matrix<double> tm(shape[0], shape[1]);
            std::string s = typeid(T).name();
            std::string s1 = typeid(S).name();
            std::vector<std::vector<double>> tm;
            for( size_t i = 0; i < shape[0]; ++i ) {
                std::vector<double> proms;
                double res_prom;
                for ( size_t j = 0; j<shape[1]; ++j){
                    if(s1=="d"||s=="d"){
                        res_prom = static_cast<double>(matrix[i][j])/static_cast<double>(koef);
                    }
                    else
                    {
                        res_prom = matrix[i][j]/koef;
                    }
                    proms.push_back(res_prom);
                }
                tm.push_back(proms);
                proms.clear();
            }
            Matrix<double> result(std::vector<std::vector<double>>{tm});
            return result;
        } else {
            mt_que<std::pair<Vector<T>, S>> rows_of_matr;
            rows_of_matr.set_maxsize(10000);
            for (int i = 0; i < shape[0]; ++i){
                rows_of_matr.enque({matrix[i], koef});
                if (i==shape[0]-1){
                    Vector<T> PP1(shape[1]-1);
                    rows_of_matr.enque({PP1, koef});
                }

            }

            std::vector<std::thread> threads;
            std::vector<std::vector<double>> res_vec_out;
            for ( int i =0; i< cores; ++i) {
                threads.emplace_back(matr_koef_division<T, S>, std::ref(rows_of_matr), std::ref(res_vec_out), std::ref(shape[1]));
            }
            for (std::thread &th: threads) {
                th.join();
            }
            Matrix<double> res(std::vector<std::vector<double>>{res_vec_out});
            return res;
        }
    }

    Vector<T> &operator[](int row){
        if (row >= shape[0]){
            std::cerr << "Incorrect index!" << std::endl;
            exit(INDEX_ERROR);
        }
        return matrix[row];
    }

//    void set_cores(int crs){
//        cores = cores;
//    }

    template<typename S>  Matrix<double> mul(Matrix<S> &mt){
        if(!mul_comp(mt)) {
            std::cerr << "Cannot multiply such matrices" << std::endl;
            exit(SHAPES_ERROR);
        }
        Matrix<double> resMatr(shape[0], mt.colNum());
        Matrix<S> trns = mt.transpose();

        size_t i, j;
        for (i=0; i< shape[0]; ++i) {
            for (j=0; j<trns.rowNum(); ++j){
                resMatr[i][j] = matrix[i].mult(trns[j]);
            }
        }
        return resMatr;
    }

    template<typename S>  Matrix<double> mul(Vector<S> &vc){
        if (shape[0] != vc.get_size()){
            std::cerr << "Can not be mutliplied1" << std::endl;
            exit(SHAPES_ERROR);
        }
        Matrix<S> mt(vc.get_size(), 1);
        Matrix<T> orig_matr(shape[0], shape[1]);
        size_t i, j;
        for (i=0; i < shape[0]; ++i){
            for (j=0; j< shape[1]; ++j){
                orig_matr[i][j]=matrix[i][j];
            }
            mt[i][0] = vc[i];
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

        T deter_original = orig_matr.determinant(orig_matr);
        if (deter_original==0){
            std::cerr << "Cannot inverse singular matrix!";
            exit(DETERMINANT_ERROR);
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
        Matrix<T> ptrm = mt.cuT_Col_Row(col, row, mt);
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
                    Matrix<T> ptrm = mt.cuT_Col_Row(0, i, mt);
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
    Matrix<T> cuT_Col_Row(int col, int row, Matrix<T> &mt){
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
