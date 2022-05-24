#include <iostream>
#include "../sources/matrix.h"
//#include <gtest/gtest.h>
#include "../sources/vector.h"
#include "../sources/mt.h"
//#include "sources/errors.h"


int main(int argc, char* argv[]) {
//        ::testing::InitGoogleTest(&argc, argv);
//        return RUN_ALL_TESTS();
    std::vector<std::vector<int>> vector_vectors1{{1, 2}, {3, 4}, {5, 6}};
    std::vector<std::vector<int>> vector_vectors2{{1, 2, 3}, {3, 4, 5}};

    Matrix<int> mt_vec_vec(vector_vectors1);
    Matrix<int> mt_vec_vec2(vector_vectors2);

    return 0;
}
//    Vector prikol(std::vector<int>{1,2,5});
//    prikol.set_cores(0);
//    Vector hello(std::vector<int>{6,4,3});
//    Vector nice(std::vector<double>{4.5, 7.5, 5.3});
//    Vector prikol_S(std::vector<int>{1,2,5});
//    Vector nice_S(std::vector<double>{4.5, 7.5, 5.3});
//    Vector<int> vc(5);
//    Vector<int> vcc(5);
//    vcc = vcc.fill(0);
//    std::chrono::high_resolution_clock::time_point find_start;
//    std::chrono::high_resolution_clock::time_point find_end;
//    std::vector<int> yes (10);
//    std::vector<int> yess (10);
//    Vector vyes(yes);
//    Vector vyess(yess);
//    vyess.set_cores(0);
//    vyess.set_method(1);
//    for (int i=0; i<10; ++i) {
//        vyes[i] = 3;
//        vyess[i] = 0;
//    yes[i] = 3;
//    }
//    vyess[5] = 1;
//    Matrix<int> g = vyess.transpose();

//    std::cout << vyess.isnull() << std::endl;
//    Matrix hello = vyess.transpose();
//    find_start = get_current_time_fenced();
//    long long hello = vyess.mult(vyes);
//    vyess.isnull();
//    vyess.mult(vyes);
//    std::cout << vyess-vyes << std::endl;
//    vyess-vyes;
//    Vector kk = vyess*5;
//    Vector<int> gh(yes);
//    bool status = (vyess == vyes);
//    Vector gh = vyess/5;
//    vyess.mul(g);
//    vyess.transpose();
//    vyess.isnull();
//    find_end = get_current_time_fenced();
//    std::cout << to_us(find_end-find_start) << std::endl;
//    std::cout << gh << std::endl;
//    std::cout << status << std::endl;
//    std::cout << hello << std::endl;
//    std::cout << nice << std::endl;
//    std::cout << prikol << std::endl;
//    std::cout << prikol.transpose() << std::endl;
//    Matrix<int> g = prikol.transpose();
//    std::cout << prikol.mul(g) << std::endl;
//    std::cout << (prikol == nice) << std::endl;
//    std::cout << prikol.get_cores() << std::endl;
//    std::cout << (prikol == prikol_S) << std::endl;
//    std::cout << prikol + nice << std::endl;
//    std::cout << prikol - prikol_S << std::endl;
//    std::cout << nice + nice_S << std::endl;
//    std::cout << nice - nice_S << std::endl;
//    std::cout << (prikol / 2) << std::endl;
//    std::cout << (prikol * 3) << std::endl;
//    std::cout << (nice / 4.2) << std::endl;
//    std::cout << (nice * 3) << std::endl;
//    std::cout << prikol[2] << std::endl;
//    vc = vc.fill(5);
//    std::cout << vc << std::endl;
//    std::cout << vcc.isnull() << std::endl;
//    std::cout << prikol.mult(prikol_S) << std::endl;
//    Vector<int> nullvec(5);
//    nullvec.set_cores(0);
//        std::cout << prikol.isnull() << std::endl;
//        std::cout << nullvec.isnull() << std::endl;
//    std::cout << (prikol / 0) << std::endl; ERRORS
//    std::cout << prikol[3] << std::endl;

//    Matrix<int> vec(3,3);
//    Matrix<int> mx(2, 3);
//    std::vector<std::vector<int>> a {{1,2,3}, {4,7,6}, {7,8,9}};
//    std::vector<std::vector<double>> aj {{1.4,2.3,3.9}, {4,5.2,6.1}, {7.9,8.12,9.9}};
//    std::vector<Vector<int>> b {prikol, prikol_S, hello};
//    Vector gg(b);
//    vec = mx.fromVec(gg);
//    Matrix<int> pp(5);
//    Matrix<double> gh(3);
//    gh = gh.fill(3.14);
//    Matrix tm(a);
//    std::vector<std::vector<int>> que {{1,2,3}};
//    Matrix quu(que);
//    std::vector<std::vector<double>> que3 {{1.2,2.2,3.5}};
//    Matrix quu3(que3);
//    std::cout << prikol.mul(quu);
//    std::cout << nice.mul(quu3);
//    Matrix mm(aj);
//    tm = tm.fill(10);
//    std::cout << vec << std::endl;
//    std::cout << pp << std::endl;
//    std::cout << tm << std::endl;
//    std::cout << vec+tm << std::endl;
//    std::cout << vec-tm << std::endl;
//    std::cout << (vec==vec) << std::endl;
//    std::cout << (vec==tm) << std::endl;
//    std::cout << tm*5 << std::endl;
//    std::cout << tm*5.56 << std::endl;
//    std::cout << gh*5 << std::endl;
//    std::cout << gh*2.77 << std::endl;
//    std::cout << tm/5 << std::endl;
//    std::cout << tm/5.56 << std::endl;
//    std::cout << gh/5 << std::endl;
//    std::cout << gh/2.77 << std::endl;
//    std::cout << tm[2] << std::endl;
//    std::cout << vec[2][1] << std::endl;
//    std::cout << tm[3] << std::endl;
//    std::cout << tm.mul(vec) << std::endl;
//    std::cout << vec.mul(tm) << std::endl;
//    std::cout << tm.mul(mm) << std::endl;  diff types
//    std::cout << tm.mul(prikol) << std::endl;
//    std::cout << tm.mul(nice) << std::endl; diff types
//    std::cout << mm.mul(prikol) << std::endl; diff types
//    std::cout << mm.mul(nice) << std::endl;
//    std::cout << vec.determinant(vec) << std::endl;
//    std::cout << tm.inverse() << std::endl;
//    std::cout << prikol.transpose() << std::endl;
//    std::cout << pp << std::endl;
//
//    std::cout << tm << std::endl;
//    std::cout << vec << std::endl;
//    std::cout << tm.shape << std::endl;
//    std::cout << vec.shape << std::endl;
//
//    std::cout << tm+vec << std::endl;
//    std::cout << tm-vec << std::endl;
//    std::cout << tm.mul(vec) << std::endl;
//};
