#include <iostream>
#include "includes/matrix.h"
#include "includes/vector.h"

int main(int argc, char* argv[]) {
    Vector<int> prikol(std::vector<int>{1,2,3,4,5});
    Vector<int> nice(std::vector<int>{1,2,9,4,5});
//    bool ik = (prikol == nice);
    Vector<int> opa = prikol + nice;
//    std::cout << prikol.shape << std::endl;
//    std::cout << prikol << std::endl;
//    std::cout << (prikol + nice);
    std::cout << (prikol - nice);

};
