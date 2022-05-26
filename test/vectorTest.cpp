#include <gtest/gtest.h>
#include "../src/matrix.h"
#include "../src/vector.h"
#include "../src/errors.h"

TEST(VectorTest, ConstructorDim) {
    Vector<int> vec1(5);
    Vector<double> vec2(5);
    ASSERT_EQ(vec1.size, 5) << "Vector constructor via dimension fails!";
    ASSERT_EQ(vec2.size, 5) << "Vector constructor via dimension fails!";
}

TEST(VectorTest, ConstructorVec) {
    Vector<int> vec1({1, 2, 3});
    std::vector a = {1, 2, 3};
    Vector<double> vec2({1.1, 2.2, 3.3});
    std::vector b = {1.1, 2.2, 3.3};
    ASSERT_EQ(vec1.vector, a) << "Vector constructor via std::vector fails!";
    ASSERT_EQ(vec2.vector, b) << "Vector constructor via std::vector fails!";
}

TEST(VectorTest, GetSize) {
    Vector<int> vec1({1, 2, 3});
    Vector<double> vec2({1.1, 2.2, 3.3});
    ASSERT_EQ(vec1.get_size(), 3) << ".get_size() fails!";
    ASSERT_EQ(vec2.get_size(), 3) << ".get_size() fails!";
}

TEST(VectorTest, SetCores) {
    Vector<int> vec1({1, 2, 3});
    vec1.set_cores(0);
    Vector<double> vec2({1.1, 2.2, 3.3});
    vec2.set_cores(0);
    ASSERT_EQ(vec1.cores, 0) << ".set_cores() fails!";
    ASSERT_EQ(vec2.cores, 0) << ".set_cores() fails!";
}

TEST(VectorTest, GetCores) {
    Vector<int> vec1({1, 2, 3});
    vec1.set_cores(3);
    Vector<double> vec2({1.1, 2.2, 3.3});
    vec2.set_cores(3);
    ASSERT_EQ(vec1.get_cores(), 3) << ".get_cores() fails!";
    ASSERT_EQ(vec2.get_cores(), 3) << ".get_cores() fails!";
}

TEST(VectorTest, GetMethod) {
    Vector<int> vec1({1, 2, 3});
    Vector<double> vec2({1.1, 2.2, 3.3});
    ASSERT_EQ(vec1.get_method(), 0) << ".get_method() fails!";
    ASSERT_EQ(vec2.get_method(), 0) << ".get_method() fails!";
}

TEST(VectorTest, SetMethod) {
    Vector<int> vec1({1, 2, 3});
    Vector<double> vec2({1.1, 2.2, 3.3});
    vec1.set_method(1);
    vec2.set_method(1);
    ASSERT_EQ(vec1.method, 1) << ".set_method() fails!";
    ASSERT_EQ(vec2.method, 1) << ".set_method() fails!";
}

TEST(VectorTest, AddSeq) {
    Vector<int> vec1({1, 2, 3});
    Vector<int> vec2({5, 2, 3});
    Vector<double> vec3({1.1, 2.2, 3.3});
    Vector<double> vec4({5.1, 2.1, 3.8});
    std::vector res = {6, 4, 6};
    std::vector res1 = {6.2, 4.3, 7.1};
    vec1.set_cores(0);
    vec3.set_cores(0);
    ASSERT_EQ((vec1+vec2).vector, res) << "Addition seq fails!";
    ASSERT_DOUBLE_EQ((vec3+vec4).vector[0], res1[0]) << "Addition seq fails!";
    ASSERT_DOUBLE_EQ((vec3+vec4).vector[1], res1[1]) << "Addition seq fails!";
    ASSERT_DOUBLE_EQ((vec3+vec4).vector[2], res1[2]) << "Addition seq fails!";
}

TEST(VectorTest, AddPar) {
    Vector<int> vec1({1, 2, 3});
    Vector<int> vec2({5, 2, 3});
    Vector<double> vec3({1.1, 2.2, 3.3});
    Vector<double> vec4({5.1, 2.1, 3.8});
    std::vector res = {6, 4, 6};
    std::vector res1 = {6.2, 4.3, 7.1};
    //    by default counts in parallel
    ASSERT_EQ((vec1+vec2).vector, res) << "Addition par fails!";
    ASSERT_DOUBLE_EQ((vec3+vec4).vector[0], res1[0]) << "Addition par fails!";
    ASSERT_DOUBLE_EQ((vec3+vec4).vector[1], res1[1]) << "Addition par fails!";
    ASSERT_DOUBLE_EQ((vec3+vec4).vector[2], res1[2]) << "Addition par fails!";
}

TEST(VectorTest, AddTbb) {
    Vector<int> vec1({1, 2, 3});
    Vector<int> vec2({5, 2, 3});
    Vector<double> vec3({1.1, 2.2, 3.3});
    Vector<double> vec4({5.1, 2.1, 3.8});
    std::vector res = {6, 4, 6};
    std::vector res1 = {6.2, 4.3, 7.1};
    vec1.set_method(1);
    vec3.set_method(1);
    ASSERT_EQ((vec1+vec2).vector, res) << "Addition tbb fails!";
    ASSERT_DOUBLE_EQ((vec3+vec4).vector[0], res1[0]) << "Addition tbb fails!";
    ASSERT_DOUBLE_EQ((vec3+vec4).vector[1], res1[1]) << "Addition tbb fails!";
    ASSERT_DOUBLE_EQ((vec3+vec4).vector[2], res1[2]) << "Addition tbb fails!";
}

TEST(VectorTest, SubSeq) {
    Vector<int> vec1({1, 2, 3});
    Vector<int> vec2({5, 2, 3});
    Vector<double> vec3({1.1, 2.2, 3.3});
    Vector<double> vec4({5.1, 2.2, 3.8});
    std::vector res = {-4, 0, 0};
    std::vector res1 = {-4.0, 0.0, -0.5};
    vec1.set_cores(0);
    vec3.set_cores(0);
    ASSERT_EQ((vec1-vec2).vector, res) << "Subtraction seq fails!";
    ASSERT_DOUBLE_EQ((vec3-vec4).vector[0], res1[0]) << "Subtraction seq fails!";
    ASSERT_DOUBLE_EQ((vec3-vec4).vector[1], res1[1]) << "Subtraction seq fails!";
    ASSERT_DOUBLE_EQ((vec3-vec4).vector[2], res1[2]) << "Subtraction seq fails!";
}

TEST(VectorTest, SubPar) {
    Vector<int> vec1({1, 2, 3});
    Vector<int> vec2({5, 2, 3});
    Vector<double> vec3({1.1, 2.2, 3.3});
    Vector<double> vec4({5.1, 2.2, 3.8});
    std::vector res = {-4, 0, 0};
    std::vector res1 = {-4.0, 0.0, -0.5};
    //    by default counts in parallel
    ASSERT_EQ((vec1-vec2).vector, res) << "Subtraction par fails!";
    ASSERT_DOUBLE_EQ((vec3-vec4).vector[0], res1[0]) << "Subtraction par fails!";
    ASSERT_DOUBLE_EQ((vec3-vec4).vector[1], res1[1]) << "Subtraction par fails!";
    ASSERT_DOUBLE_EQ((vec3-vec4).vector[2], res1[2]) << "Subtraction par fails!";
}

TEST(VectorTest, SubTbb) {
    Vector<int> vec1({1, 2, 3});
    Vector<int> vec2({5, 2, 3});
    Vector<double> vec3({1.1, 2.2, 3.3});
    Vector<double> vec4({5.1, 2.2, 3.8});
    std::vector res = {-4, 0, 0};
    std::vector res1 = {-4.0, 0.0, -0.5};
    vec1.set_method(1);
    vec3.set_method(1);
    ASSERT_EQ((vec1-vec2).vector, res) << "Subtraction tbb fails!";
    ASSERT_DOUBLE_EQ((vec3-vec4).vector[0], res1[0]) << "Subtraction tbb fails!";
    ASSERT_DOUBLE_EQ((vec3-vec4).vector[1], res1[1]) << "Subtraction tbb fails!";
    ASSERT_DOUBLE_EQ((vec3-vec4).vector[2], res1[2]) << "Subtraction tbb fails!";
}

TEST(VectorTest, EqSeq) {
    Vector<int> vec1({1, 2, 3});
    Vector<int> vec2({1, 2, 3});
    Vector<int> vec3({1, -2, 3});
    Vector<double> vec4({1.1, 2.1, 3.1});
    Vector<double> vec5({1.1, 2.1, 3.1});
    Vector<double> vec6({1.1, -2.1, 3.1});
    vec1.set_cores(0);
    vec4.set_cores(0);
    ASSERT_EQ((vec1==vec2), true) << "Equality seq fails!";
    ASSERT_EQ((vec1==vec3), false) << "Equality seq fails!";
    ASSERT_EQ((vec4==vec5), true) << "Equality seq fails!";
    ASSERT_EQ((vec4==vec6), false) << "Equality seq fails!";
}

TEST(VectorTest, EqPar) {
    Vector<int> vec1({1, 2, 3});
    Vector<int> vec2({1, 2, 3});
    Vector<int> vec3({1, -2, 3});
    Vector<double> vec4({1.1, 2.1, 3.1});
    Vector<double> vec5({1.1, 2.1, 3.1});
    Vector<double> vec6({1.1, -2.1, 3.1});
    ASSERT_EQ((vec1==vec2), true) << "Equality par fails!";
    ASSERT_EQ((vec1==vec3), false) << "Equality par fails!";
    ASSERT_EQ((vec4==vec5), true) << "Equality par fails!";
    ASSERT_EQ((vec4==vec6), false) << "Equality par fails!";
}

TEST(VectorTest, EqTbb) {
    Vector<int> vec1({1, 2, 3});
    Vector<int> vec2({1, 2, 3});
    Vector<int> vec3({1, -2, 3});
    Vector<double> vec4({1.1, 2.1, 3.1});
    Vector<double> vec5({1.1, 2.1, 3.1});
    Vector<double> vec6({1.1, -2.1, 3.1});
    vec1.set_method(1);
    vec4.set_method(1);
    ASSERT_EQ((vec1==vec2), true) << "Equality tbb fails!";
    ASSERT_EQ((vec1==vec3), false) << "Equality tbb fails!";
    ASSERT_EQ((vec4==vec5), true) << "Equality tbb fails!";
    ASSERT_EQ((vec4==vec6), false) << "Equality tbb fails!";
}

TEST(VectorTest, MulOpSeq) {
    Vector<int> vec1({1, 2, 3});
    Vector<double> vec2({1.1, 2.1, 3.1});
    int koef = 3;
    double dkoef = 3;
    vec1.set_cores(0);
    vec2.set_cores(0);
    std::vector res = {3.0, 6.0, 9.0};
    std::vector res1 = {3.3, 6.3, 9.3};
    ASSERT_EQ((vec1*koef).vector, res) << "Multiplication seq fails!";
    ASSERT_DOUBLE_EQ((vec2*dkoef).vector[0], res1[0]) << "Multiplication seq fails!";
    ASSERT_DOUBLE_EQ((vec2*dkoef).vector[1], res1[1]) << "Multiplication seq fails!";
    ASSERT_DOUBLE_EQ((vec2*dkoef).vector[2], res1[2]) << "Multiplication seq fails!";
}

TEST(VectorTest, MulOpPar) {
    Vector<int> vec1({1, 2, 3});
    Vector<double> vec2({1.1, 2.1, 3.1});
    int koef = 3;
    double dkoef = 3;
    std::vector res = {3.0, 6.0, 9.0};
    std::vector res1 = {3.3, 6.3, 9.3};
    ASSERT_EQ((vec1*koef).vector, res) << "Multiplication par fails!";
    ASSERT_DOUBLE_EQ((vec2*dkoef).vector[0], res1[0]) << "Multiplication par fails!";
    ASSERT_DOUBLE_EQ((vec2*dkoef).vector[1], res1[1]) << "Multiplication par fails!";
    ASSERT_DOUBLE_EQ((vec2*dkoef).vector[2], res1[2]) << "Multiplication par fails!";
}

TEST(VectorTest, MulOpTbb) {
    Vector<int> vec1({1, 2, 3});
    Vector<double> vec2({1.1, 2.1, 3.1});
    int koef = 3;
    double dkoef = 3;
    vec1.set_method(1);
    vec2.set_method(1);
    std::vector res = {3.0, 6.0, 9.0};
    std::vector res1 = {3.3, 6.3, 9.3};
    ASSERT_EQ((vec1*koef).vector, res) << "Multiplication tbb fails!";
    ASSERT_DOUBLE_EQ((vec2*dkoef).vector[0], res1[0]) << "Multiplication tbb fails!";
    ASSERT_DOUBLE_EQ((vec2*dkoef).vector[1], res1[1]) << "Multiplication tbb fails!";
    ASSERT_DOUBLE_EQ((vec2*dkoef).vector[2], res1[2]) << "Multiplication tbb fails!";
}

TEST(VectorTest, DivSeq) {
    Vector<int> vec1({1, 2, 3});
    Vector<double> vec2({1.1, 2.2, 3.3});
    int koef = 2;
    double dkoef = 1.1;
    vec1.set_cores(0);
    vec2.set_cores(0);
    std::vector res = {0.5, 1.0, 1.5};
    std::vector res1 = {1.0, 2.0, 3.0};
    ASSERT_EQ((vec1/koef).vector, res) << "Division seq fails!";
    ASSERT_DOUBLE_EQ((vec2/dkoef).vector[0], res1[0]) << "Division seq fails!";
    ASSERT_DOUBLE_EQ((vec2/dkoef).vector[1], res1[1]) << "Division seq fails!";
    ASSERT_DOUBLE_EQ((vec2/dkoef).vector[2], res1[2]) << "Division seq fails!";
}

TEST(VectorTest, DivPar) {
    Vector<int> vec1({1, 2, 3});
    Vector<double> vec2({1.1, 2.2, 3.3});
    int koef = 2;
    double dkoef = 1.1;
    std::vector res = {0.5, 1.0, 1.5};
    std::vector res1 = {1.0, 2.0, 3.0};
    ASSERT_EQ((vec1/koef).vector, res) << "Division par fails!";
    ASSERT_DOUBLE_EQ((vec2/dkoef).vector[0], res1[0]) << "Division par fails!";
    ASSERT_DOUBLE_EQ((vec2/dkoef).vector[1], res1[1]) << "Division par fails!";
    ASSERT_DOUBLE_EQ((vec2/dkoef).vector[2], res1[2]) << "Division par fails!";
}

TEST(VectorTest, DivTbb) {
    Vector<int> vec1({1, 2, 3});
    Vector<double> vec2({1.1, 2.2, 3.3});
    int koef = 2;
    double dkoef = 1.1;
    vec1.set_method(1);
    std::vector res = {0.5, 1.0, 1.5};
    std::vector res1 = {1.0, 2.0, 3.0};
    ASSERT_EQ((vec1/koef).vector, res) << "Division tbb fails!";
    ASSERT_DOUBLE_EQ((vec2/dkoef).vector[0], res1[0]) << "Division tbb fails!";
    ASSERT_DOUBLE_EQ((vec2/dkoef).vector[1], res1[1]) << "Division tbb fails!";
    ASSERT_DOUBLE_EQ((vec2/dkoef).vector[2], res1[2]) << "Division tbb fails!";
}

TEST(VectorTest, Index) {
    Vector<int> vec1({1, 2, 3});
    Vector<double> vec2({1.1, 2.1, 3.1});
    ASSERT_EQ(vec1[0], 1) << "Index operator fails!";
    ASSERT_EQ(vec1[1], 2) << "Index operator fails!";
    ASSERT_EQ(vec1[2], 3) << "Index operator fails!";
    ASSERT_EQ(vec2[0], 1.1) << "Index operator fails!";
    ASSERT_EQ(vec2[1], 2.1) << "Index operator fails!";
    ASSERT_EQ(vec2[2], 3.1) << "Index operator fails!";
}

TEST(VectorTest, MulSeq) {
    Vector<int> vec1({1, 2, 3});
    Matrix<int> vec2({{1, 2, 2}});
    Vector<double> vec3({1.1, 2.1, 3.1});
    Matrix<double> vec4({{1.0, 2.0, 2.0}});
    vec1.set_cores(0);
    vec3.set_cores(0);
    std::vector res1 = {1, 2, 2};
    std::vector res2 = {2, 4, 4};
    std::vector res3 = {3, 6, 6};
    std::vector res4 = {1.1, 2.2, 2.2};
    std::vector res5 = {2.1, 4.2, 4.2};
    std::vector res6 = {3.1, 6.2, 6.2};

    ASSERT_EQ(vec1.mul(vec2)[0].vector, res1) << "Mul seq fails!";
    ASSERT_EQ(vec1.mul(vec2)[1].vector, res2) << "Mul seq fails!";
    ASSERT_EQ(vec1.mul(vec2)[2].vector, res3) << "Mul seq fails!";
    ASSERT_EQ(vec3.mul(vec4)[0].vector, res4) << "Mul seq fails!";
    ASSERT_EQ(vec3.mul(vec4)[1].vector, res5) << "Mul seq fails!";
    ASSERT_EQ(vec3.mul(vec4)[2].vector, res6) << "Mul seq fails!";
}

TEST(VectorTest, MulPar) {
    Vector<int> vec1({1, 2, 3});
    Matrix<int> vec2({{1, 2, 2}});
    Vector<double> vec3({1.1, 2.1, 3.1});
    Matrix<double> vec4({{1.0, 2.0, 2.0}});

    std::vector res1 = {1, 2, 2};
    std::vector res2 = {2, 4, 4};
    std::vector res3 = {3, 6, 6};
    std::vector res4 = {1.1, 2.2, 2.2};
    std::vector res5 = {2.1, 4.2, 4.2};
    std::vector res6 = {3.1, 6.2, 6.2};

    ASSERT_EQ(vec1.mul(vec2)[0].vector, res1) << "Mul par fails!";
    ASSERT_EQ(vec1.mul(vec2)[1].vector, res2) << "Mul par fails!";
    ASSERT_EQ(vec1.mul(vec2)[2].vector, res3) << "Mul par fails!";
    ASSERT_EQ(vec3.mul(vec4)[0].vector, res4) << "Mul par fails!";
    ASSERT_EQ(vec3.mul(vec4)[1].vector, res5) << "Mul par fails!";
    ASSERT_EQ(vec3.mul(vec4)[2].vector, res6) << "Mul par fails!";
}

TEST(VectorTest, MulTbb) {
    Vector<int> vec1({1, 2, 3});
    Matrix<int> vec2({{1, 2, 2}});
    Vector<double> vec3({1.1, 2.1, 3.1});
    Matrix<double> vec4({{1.0, 2.0, 2.0}});
    vec1.set_method(1);
    vec3.set_method(1);
    std::vector res1 = {1, 2, 2};
    std::vector res2 = {2, 4, 4};
    std::vector res3 = {3, 6, 6};
    std::vector res4 = {1.1, 2.2, 2.2};
    std::vector res5 = {2.1, 4.2, 4.2};
    std::vector res6 = {3.1, 6.2, 6.2};

    ASSERT_EQ(vec1.mul(vec2)[0].vector, res1) << "Mul tbb fails!";
    ASSERT_EQ(vec1.mul(vec2)[1].vector, res2) << "Mul tbb fails!";
    ASSERT_EQ(vec1.mul(vec2)[2].vector, res3) << "Mul tbb fails!";
    ASSERT_EQ(vec3.mul(vec4)[0].vector, res4) << "Mul tbb fails!";
    ASSERT_EQ(vec3.mul(vec4)[1].vector, res5) << "Mul tbb fails!";
    ASSERT_EQ(vec3.mul(vec4)[2].vector, res6) << "Mul tbb fails!";
}

TEST(VectorTest, TransSeq) {
    Vector<int> vec1({1, 2, 3});
    Matrix<int> vec2({{1, 2, 3}});
    Vector<double> vec3({1.1, 2.1, 3.1});
    Matrix<double> vec4({{1.1, 2.1, 3.1}});

    vec1.set_cores(0);
    vec3.set_cores(0);
    Matrix<int> res = vec1.transpose();
    Matrix<double> res1 = vec3.transpose();

    ASSERT_EQ(res.matrix[0].vector, vec2.matrix[0].vector) << "Transpose seq fails!";
    ASSERT_EQ(res1.matrix[0].vector, vec4.matrix[0].vector) << "Transpose seq fails!";
}

TEST(VectorTest, TransPar) {
    Vector<int> vec1({1, 2, 3});
    Matrix<int> vec2({{1, 2, 3}});
    Vector<double> vec3({1.1, 2.1, 3.1});
    Matrix<double> vec4({{1.1, 2.1, 3.1}});

    Matrix<int> res = vec1.transpose();
    Matrix<double> res1 = vec3.transpose();

    ASSERT_EQ(res.matrix[0].vector, vec2.matrix[0].vector) << "Transpose par fails!";
    ASSERT_EQ(res1.matrix[0].vector, vec4.matrix[0].vector) << "Transpose par fails!";
}

TEST(VectorTest, TransTbb) {
    Vector<int> vec1({1, 2, 3});
    Matrix<int> vec2({{1, 2, 3}});
    Vector<double> vec3({1.1, 2.1, 3.1});
    Matrix<double> vec4({{1.1, 2.1, 3.1}});

    vec1.set_method(1);
    vec3.set_method(1);
    Matrix<int> res = vec1.transpose();
    Matrix<double> res1 = vec3.transpose();

    ASSERT_EQ(res.matrix[0].vector, vec2.matrix[0].vector) << "Transpose tbb fails!";
    ASSERT_EQ(res1.matrix[0].vector, vec4.matrix[0].vector) << "Transpose tbb fails!";
}

TEST(VectorTest, MultSeq) {
    Vector<int> vec1({1, 2, 3});
    Vector<int> vec2({7, 1, -6});
    Vector<double> vec3({1.1, 2.1, 3.1});
    Vector<double> vec4({7, 1, -6});
    vec1.set_cores(0);
    vec3.set_cores(0);
    double res = -9;
    double res1 = -8.8;
    ASSERT_EQ(vec1.mult(vec2), res) << "Mult seq fails!";
    ASSERT_DOUBLE_EQ(vec3.mult(vec4), res1) << "Mult seq fails!";
}

TEST(VectorTest, MultPar) {
    Vector<int> vec1({1, 2, 3});
    Vector<int> vec2({7, 1, -6});
    Vector<double> vec3({1.1, 2.1, 3.1});
    Vector<double> vec4({7, 1, -6});
    double res = -9;
    double res1 = -8.8;
    ASSERT_EQ(vec1.mult(vec2), res) << "Mult par fails!";
    ASSERT_DOUBLE_EQ(vec3.mult(vec4), res1) << "Mult par fails!";
}

TEST(VectorTest, MultTbb) {
    Vector<int> vec1({1, 2, 3});
    Vector<int> vec2({7, 1, -6});
    Vector<double> vec3({1.1, 2.1, 3.1});
    Vector<double> vec4({7, 1, -6});
    vec1.set_method(1);
    vec3.set_method(1);
    double res = -9;
    double res1 = -9;
    ASSERT_EQ(vec1.mult(vec2), res) << "Mult tbb fails!";
    ASSERT_DOUBLE_EQ(vec3.mult(vec4), res1) << "Mult tbb fails!";
}

TEST(VectorTest, FillSeq) {
    Vector<int> vec1(5);
    Vector<double> vec2(5);
    vec1.set_cores(0);
    vec2.set_cores(0);
    vec1 = vec1.fill(-1);
    vec2 = vec2.fill(1.1);
    std::vector res = {-1, -1, -1, -1, -1};
    std::vector res1 = {1.1, 1.1, 1.1, 1.1, 1.1};
    ASSERT_EQ(vec1.vector, res) << "Fill seq fails!";
    ASSERT_EQ(vec2.vector, res1) << "Fill seq fails!";
}

TEST(VectorTest, FillPar) {
    Vector<int> vec1(5);
    Vector<double> vec2(5);
    vec1 = vec1.fill(-1);
    vec2 = vec2.fill(1.1);
    std::vector res = {-1, -1, -1, -1, -1};
    std::vector res1 = {1.1, 1.1, 1.1, 1.1, 1.1};
    ASSERT_EQ(vec1.vector, res) << "Fill par fails!";
    ASSERT_EQ(vec2.vector, res1) << "Fill par fails!";
}

TEST(VectorTest, FillTbb) {
    Vector<int> vec1(5);
    Vector<double> vec2(5);
    vec1.set_method(1);
    vec2.set_method(1);
    vec1 = vec1.fill(-1);
    vec2 = vec2.fill(1.1);
    std::vector res = {-1, -1, -1, -1, -1};
    std::vector res1 = {1.1, 1.1, 1.1, 1.1, 1.1};
    ASSERT_EQ(vec1.vector, res) << "Fill tbb fails!";
    ASSERT_EQ(vec2.vector, res1) << "Fill tbb fails!";
}

TEST(VectorTest, AddComp) {
    Vector<int> vec1(5);
    Vector<int> vec2(5);
    Vector<int> vec3(2);
    Vector<double> vec4(5);
    Vector<double> vec5(5);
    Vector<double> vec6(2);
    ASSERT_EQ(vec1.add_comp(vec2), true) << "AddComp fails!";
    ASSERT_EQ(vec1.add_comp(vec3), false) << "AddComp fails!";
    ASSERT_EQ(vec4.add_comp(vec5), true) << "AddComp fails!";
    ASSERT_EQ(vec4.add_comp(vec6), false) << "AddComp fails!";
}

TEST(VectorTest, MulComp) {
    Vector<int> vec1(5);
    Matrix<int> vec2({{1, 2, 3}});
    Matrix<int> vec3(2);
    Vector<int> vec4(5);
    Matrix<int> vec5({{1, 2, 3}});
    Matrix<int> vec6(2);
    ASSERT_EQ(vec1.mul_comp(vec2), true) << "MulComp fails!";
    ASSERT_EQ(vec1.mul_comp(vec3), false) << "MulComp fails!";
    ASSERT_EQ(vec4.mul_comp(vec5), true) << "MulComp fails!";
    ASSERT_EQ(vec4.mul_comp(vec6), false) << "MulComp fails!";
}

TEST(VectorTest, IsnullSeq) {
    Vector<int> vec1({0, 0, 0});
    Vector<int> vec2({0, 1, 0});
    Vector<double> vec3({0.0, 0.0, 0.0});
    Vector<double> vec4({0.0, 1.0, 0.0});
    vec1.set_cores(0);
    vec3.set_cores(0);
    ASSERT_EQ(vec1.isnull(), true) << "Isnull seq fails!";
    ASSERT_EQ(vec2.isnull(), false) << "Isnull seq fails!";
    ASSERT_EQ(vec3.isnull(), true) << "Isnull seq fails!";
    ASSERT_EQ(vec4.isnull(), false) << "Isnull seq fails!";
}

TEST(VectorTest, IsnullPar) {
    Vector<int> vec1({0, 0, 0});
    Vector<int> vec2({0, 1, 0});
    Vector<double> vec3({0.0, 0.0, 0.0});
    Vector<double> vec4({0.0, 1.0, 0.0});
    ASSERT_EQ(vec1.isnull(), true) << "Isnull par fails!";
    ASSERT_EQ(vec2.isnull(), false) << "Isnull par fails!";
    ASSERT_EQ(vec3.isnull(), true) << "Isnull par fails!";
    ASSERT_EQ(vec4.isnull(), false) << "Isnull par fails!";
}

TEST(VectorTest, IsnullTbb) {
    Vector<int> vec1({0, 0, 0});
    Vector<int> vec2({0, 1, 0});
    Vector<double> vec3({0.0, 0.0, 0.0});
    Vector<double> vec4({0.0, 1.0, 0.0});
    vec1.set_method(1);
    vec3.set_method(1);
    ASSERT_EQ(vec1.isnull(), true) << "Isnull tbb fails!";
    ASSERT_EQ(vec2.isnull(), false) << "Isnull tbb fails!";
    ASSERT_EQ(vec3.isnull(), true) << "Isnull tbb fails!";
    ASSERT_EQ(vec4.isnull(), false) << "Isnull tbb fails!";
}