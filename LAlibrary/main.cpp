#include <iostream>
#include "includes/matrix.h"
#include "includes/vector.h"
//#include "includes/errors.h"

int main(int argc, char* argv[]) {
    Vector prikol(std::vector<int>{1,2,5});
    Vector hello(std::vector<int>{6,4,3});
    Vector nice(std::vector<double>{4.5, 7.5, 5.3});
    Vector prikol_S(std::vector<int>{1,2,5});
    Vector nice_S(std::vector<double>{4.5, 7.5, 5.3});
    Vector<int> vc(5);
    Vector<int> vcc(5);
    vcc = vcc.fill(0);

//    std::cout << nice << std::endl;
//    std::cout << prikol << std::endl;
//    std::cout << prikol.transpose() << std::endl;
//    Matrix<int> g = prikol.transpose();
//    std::cout << prikol.mul(g) << std::endl;
//    std::cout << (prikol == nice) << std::endl;
//    std::cout << (prikol == prikol_S) << std::endl;
//    std::cout << prikol + prikol_S << std::endl;
//    std::cout << prikol - prikol_S << std::endl;
//    std::cout << nice + nice_S << std::endl;
//    std::cout << nice - nice_S << std::endl;
//    std::cout << (prikol / 4) << std::endl;
//    std::cout << (prikol * 3.5) << std::endl;
//    std::cout << (nice / 4) << std::endl;
//    std::cout << (nice * 3.5) << std::endl;
//    std::cout << prikol[2] << std::endl;
//    std::cout << vc.fill(5) << std::endl;
//    std::cout << vcc.isnull() << std::endl;
//    std::cout << prikol.mult(prikol_S) << std::endl;

//    std::cout << (prikol / 0) << std::endl; ERRORS
//    std::cout << prikol[3] << std::endl;

    Matrix<int> vec(3,3);
    Matrix<int> mx(2, 3);
    std::vector<std::vector<int>> a {{1,2,3}, {4,7,6}, {7,8,9}};
    std::vector<std::vector<double>> aj {{1.4,2.3,3.9}, {4,5.2,6.1}, {7.9,8.12,9.9}};
    std::vector<Vector<int>> b {prikol, prikol_S, hello};
    Vector gg(b);
    vec = mx.fromVec(gg);
    Matrix<int> pp(5);
    Matrix<double> gh(3);
    gh = gh.fill(3.14);
    Matrix tm(a);
    Matrix mm(aj);
//    tm = tm.fill(10);
    std::cout << vec << std::endl;
//    std::cout << pp << std::endl;
    std::cout << tm << std::endl;
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
    std::cout << tm.transpose() << std::endl;
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
};
