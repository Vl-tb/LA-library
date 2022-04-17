#include <iostream>
#include "includes/matrix.h"
#include "includes/vector.h"

int main(int argc, char* argv[]) {
    Vector prikol(std::vector<int>{1,2,5});
    Vector nice(std::vector<double>{4.5, 7.5, 5.3});
    Vector prikol_S(std::vector<int>{1,2,5});
    Vector nice_S(std::vector<double>{4.5, 7.5, 5.3});
    Vector<int> vc(5);
    Vector<int> vcc(5);
    vcc = vcc.fill(0);

    std::cout << nice << std::endl;
    std::cout << (prikol == nice) << std::endl;
    std::cout << prikol + prikol_S << std::endl;
    std::cout << prikol - prikol_S << std::endl;
    std::cout << nice + nice_S << std::endl;
    std::cout << nice - nice_S << std::endl;
    std::cout << (prikol / 4) << std::endl;
    std::cout << (prikol * 3.5) << std::endl;
    std::cout << (nice / 4) << std::endl;
    std::cout << (nice * 3.5) << std::endl;
    std::cout << prikol[2] << std::endl;
    std::cout << vc.fill(5) << std::endl;
    std::cout << vcc.isnull() << std::endl;

//    std::cout << (prikol / 0) << std::endl; ERRORS
//    std::cout << prikol[3] << std::endl;

};
