#ifndef LA_LIBRARY_MT_H
#define LA_LIBRARY_MT_H
#include "vector.h"
#include "matrix.h"
#include "thr_queue.h"


template<typename T>
class mt_que;

template<typename T>
class Vector;


template<typename T>
class Matrix;


template<typename T> void mt_assign(int thread_num, int delta, int size, const std::vector<T>& from,
                                    std::vector<T>& to) {
    for (int i=thread_num; i<size; i+= delta) {
        to[i] = from[i];
    }
}



template<typename T> void mt_constr_vec_assign( mt_que<int> &n_i_s , const std::vector<std::vector<T>> &mtrx, std::vector<Vector<T>> &vec, int &cols) {
    int deqd = 2; // can be any number
    Vector<T> vc1(cols);

    while (deqd != -1){
        deqd = n_i_s.deque();
        if (deqd==-1){
            n_i_s.enque(deqd);
            break;
        } else{
            for ( int i = 0; i < cols; ++i) {
                vc1[i] = mtrx[deqd][i];
            }
            vec.push_back(vc1);
        }

    }
}



template<typename T, typename S>  void matr_rows_addition(mt_que<std::pair<Vector<T>, Vector<S>>> &rows_of_matr, std::vector<std::vector<double>> &res_vec_out, int init_shape){
    int check_size = init_shape;

    while(check_size == init_shape){
        std::pair<Vector<T>, Vector<S>> deqd = rows_of_matr.deque();
        if (deqd.first.get_size() != init_shape){
            rows_of_matr.enque(deqd);
            break;
        } else{
            check_size = deqd.first.get_size();
            std::string s = typeid(T).name();
            std::string s1 = typeid(S).name();
            std::vector<double> res_vec;
            double res;
            if(s1=="d" || s=="d"){
                for (int i = 0; i < deqd.first.get_size(); ++i){
                    res = static_cast<double>(deqd.first[i]) + static_cast<double>(deqd.second[i]);
                    res_vec.push_back(res);
                }
            } else {
                for (int i = 0; i < deqd.first.get_size(); ++i){
                    res = deqd.first[i] + deqd.second[i];
                    res_vec.push_back(res);
                }
            }
            res_vec_out.push_back(res_vec);
        }

    }

}



template<typename T, typename S>  void matr_rows_substraction(mt_que<std::pair<Vector<T>, Vector<S>>> &rows_of_matr, std::vector<std::vector<double>> &res_vec_out, int init_shape){
    int check_size = init_shape;

    while(check_size == init_shape){
        std::pair<Vector<T>, Vector<S>> deqd = rows_of_matr.deque();
        if (deqd.first.get_size() != init_shape){
            rows_of_matr.enque(deqd);
            break;
        } else{
            check_size = deqd.first.get_size();
            std::string s = typeid(T).name();
            std::string s1 = typeid(S).name();
            std::vector<double> res_vec;
            double res;
            if(s1=="d" || s=="d"){
                for (int i = 0; i < deqd.first.get_size(); ++i){
                    res = static_cast<double>(deqd.first[i]) - static_cast<double>(deqd.second[i]);
                    res_vec.push_back(res);
                }
            } else {
                for (int i = 0; i < deqd.first.get_size(); ++i){
                    res = deqd.first[i] - deqd.second[i];
                    res_vec.push_back(res);
                }
            }
            res_vec_out.push_back(res_vec);
        }

    }

}



template<typename T, typename S>  void matr_by_mat_mult(mt_que<std::pair<Vector<T>, Vector<S>>> &rows_of_matr, std::vector<std::vector<double>> &res_vec_out, int init_shape){
    int check_size = init_shape;

    while(check_size == init_shape){
        std::pair<Vector<T>, Vector<S>> deqd = rows_of_matr.deque();
        if (deqd.first.get_size() != init_shape){
            rows_of_matr.enque(deqd);
            break;
        } else{
            check_size = deqd.first.get_size();
            std::string s = typeid(T).name();
            std::string s1 = typeid(S).name();
            std::vector<double> res_vec;
            double res;
            if(s1=="d" || s=="d"){
                for (int i = 0; i < deqd.first.get_size(); ++i){
                    res = static_cast<double>(deqd.first[i]) * static_cast<double>(deqd.second[i]);
                    res_vec.push_back(res);
                }
            } else {
                for (int i = 0; i < deqd.first.get_size(); ++i){
                    res = deqd.first[i] * deqd.second[i];
                    res_vec.push_back(res);
                }
            }
            res_vec_out.push_back(res_vec);
        }

    }

}



template<typename T, typename S>  void matr_koef_multiplication(mt_que<std::pair<Vector<T>, S>> &rows_of_matr, std::vector<std::vector<double>> &res_vec_out, int init_shape){
    int check_size = init_shape;

    while(check_size == init_shape){
        std::pair<Vector<T>, S> deqd = rows_of_matr.deque();
        if (deqd.first.get_size() != init_shape){
            rows_of_matr.enque(deqd);
            break;
        } else{
            check_size = deqd.first.get_size();
            std::string s = typeid(T).name();
            std::string s1 = typeid(S).name();
            std::vector<double> res_vec;
            double res;
            if(s1=="d" || s=="d"){
                for (int i = 0; i < deqd.first.get_size(); ++i){
                    res = static_cast<double>(deqd.first[i]) * static_cast<double>(deqd.second);
                    res_vec.push_back(res);
                }
            } else {
                for (int i = 0; i < deqd.first.get_size(); ++i){
                    res = deqd.first[i] * deqd.second;
                    res_vec.push_back(res);
                }
            }
            res_vec_out.push_back(res_vec);
        }

    }

}




template<typename T, typename S>  void matr_koef_division(mt_que<std::pair<Vector<T>, S>> &rows_of_matr, std::vector<std::vector<double>> &res_vec_out, int init_shape){
    int check_size = init_shape;

    while(check_size == init_shape){
        std::pair<Vector<T>, S> deqd = rows_of_matr.deque();
        if (deqd.first.get_size() != init_shape){
            rows_of_matr.enque(deqd);
            break;
        } else{
            check_size = deqd.first.get_size();

            std::vector<double> res_vec;
            double res;

            for (int i = 0; i < deqd.first.get_size(); ++i){
                res = static_cast<double>(deqd.first[i]) / static_cast<double>(deqd.second);
                res_vec.push_back(res);
            }

//

            res_vec_out.push_back(res_vec);
        }

    }

}

//template<typename T, typename S> void mult_matr_by_koef(Vector<Vector<T>> &matrix, Vector<Vector<double>> &res_matr, S koef, int j_max, int i_from, int i_to, int i_max){
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
//                res_matr.get_row()[j] = static_cast<double>(matrix[i][j]) * static_cast<double>(koef);
//            }
//        }
//    }
//}

//template<typename T> void mult_matr_by_koef(Vector<Vector<double>> &vec){
//
//    std::cout<<8<<"\n";
//}

template<typename T, typename S> void mt_add(int thread_num, int delta, int size, const std::vector<S>& vc,
                                             const std::vector<T>& vector, std::vector<S>& res) {
    for (int i=thread_num; i<size; i+= delta) {
        res[i] = vc[i] + vector[i];
    }
}

template<typename T, typename S> void mt_sub(int thread_num, int delta, int size, const std::vector<S>& vc,
                                             const std::vector<T>& vector, std::vector<S>& res) {
    for (int i=thread_num; i<size; i+= delta) {
        res[i] = vector[i] - vc[i];
    }
}

template<typename T, typename S> void mt_com(int thread_num, int delta, int size, const std::vector<S>& vc,
                                             const std::vector<T>& vector, std::atomic<int>& flag) {
    for (int i=thread_num; i<size; i+= delta) {
        if (vector[i] != vc[i]) {
            flag = 0;
            return;
        }
        flag = flag * 2;
    }
}

#endif //LA_LIBRARY_MT_H
