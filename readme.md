# LA-Library
This is a c++ library of linear algebra, which uses paralelism for better efficiency.  
This library supports 3 variants of executing for main la methods: sequential execution, parallel execution and execution with usage of tbb parallel algorithms.  
## Structure
All library is located on `main` branch, in headers in `src/` directory and consists of several `.h` files.  
There is also `test/` directory, which has our custom tests as well as google tests.  
`data/` directory has some info files (some graphs) and `.py` file.
## How to
All library consists of 2 big parts: `Vector`, with all it's methods, and `Matrix` with it's methods.  
Let's start with `Vector`.  
## Vector
`Vector` is an nx1 object, which represents obviously a vector in linear algebra. There are several methods of creating it:  
  * using dimension of vector:  
  ```
  Vector<int> vc(3); #creating 3-dimensional empty vector of ints (undetermined values)
  ``` 
  * using `std::vector`:  
  ```
  std::vector list{1, 2, 3};  
  Vector<int> vc(list);
  ```
  or:
  ```
  Vector<int> vc({1, 2, 3});
  ```
It's recommended to use `.fill()` right after creating vector by dimension to avoid unexpected results:
```
Vector<int> vc(3);
vc = vc.fill(3) #[3, 3, 3]
```
Vector object has some important attributes: `cores`, `method` and `size`.  
  * `cores` is equal by default to the number of logical cores of mashine;
  * `method` is by default 0;
  * `size` is size (dimension) of vector.    
 
We can operate with these attributes via:  
 * `set_cores(number_of_cores)` and `get_cores()`;
 * `set_method(number_of_method)` and `get_method()` (to use tbb parallel algorithms use `set_method(1)`);
 * `get_size()`;

This library provides the next possible methods for `Vector` object (all methods don't modify object, they create a new one instead):  
 * addition, `vector1 + vector2`;  
 * subtraction, `vector1 - vector2`;
 * multiplication by number, `vector * num`;  
 * division by number, `vector / num`;
 * equality of vectors, `vector1 == vector2`;  
 * accessing elements by undex, `int num = vector1[2]`;  
 * multiplication by matrix, `vector.mul(matrix)`;
 * transposition (converting to matrix), `matrix = vector.transpose()`;  
 * dot product between vectors, `vector1.mult(vector2)`;  
 * check whether vector is null, `vector.isnull()`.
 
All these methods (except index accessing) can be performed in parallel.  
## Examples for Vector  
#1 Counting sum of vectors in parallel:  
```
#include "matrix.h"
#include "vector.h"

int main(int argc, char *argv[]) {
    Vector<int> vc1({1, 2, 3});
    Vector<int> vc2({4, 5, 6});
    vc1.set_cores(8);
    std::cout << vc1 + vc2 << std::endl;
    return 0;
}
```
Output:  
```
[5, 7, 9]
```

#2 Counting dot product using tbb:  
```
#include "matrix.h"
#include "vector.h"

int main(int argc, char *argv[]) {
    Vector<int> vc1({1, 2, 3});
    Vector<int> vc2({4, 5, 6});
    vc1.set_method(1);
    std::cout << vc1.mult(vc2) << std::endl;
    return 0;
}
```
Output:  
```
32
```

#3 Counting multiplication of vector by it's trasposition in parallel:  
```
int main(int argc, char *argv[]) {
    Vector<int> hello({1,2,3});
    hello.set_cores(4);
    Matrix<int> helloT = hello.transpose();
    std::cout << hello.mul(helloT) << std::endl;
    return 0;
}
```
Output:  
```
[[1, 2, 3]
 [2, 4, 6]
 [3, 6, 9]]
```

## Matrix
`Matrix` is an nxm object, which represents a matrix  in linear algebra. There are several methods of creating it: 

* By sizes: 

<sub>creating a rows X cols matrix, which has each element by default equal to zero</sub>

```
  int rows = 5;
  int cols = 7;
  Matrix<int> matrix_from_sizes_int(rows, cols); 
  Matrix<double> matrix_from_sizes_double(rows, cols;
  ``` 
* From ```std::vector<std::vector<T>>```:

<sub>create a matrix with the number of rows is equal to the number of the inner vectors, and number of cols is the number of elements of each inner vector - if they all have different length - an error message would appear</sub>

```
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}};
    Matrix<int> mt_vector_1(vector_1);
    std::vector<std::vector<double>> vector_2 {{1.9, 2.0, 3.7}, {3.2, 4.1, 5.3}};
    Matrix<double> mt_vector_2(vector_2);
  ``` 

* From ``` Vector<Vector<T>>```


<sub> For the final shapes of the matrix this method works the same as the previous one; </sub>

<sub> Below is an example for int-Matrix, for double everything works pretty much the same
</sub>
```
    Vector vec_inside(std::vector < int > {1, 2, 5});
    std::vector <Vector<int>> vec_loop{vec_inside, vec_inside, vec_inside};
    Vector from_vector_to_be(vec_loop);
    Vector<Vector<int>> vec{from_vector_to_be};
    Matrix<int> mat_Vec_Vec_T(vec); 
```
### Matrix setting 

There are two instructions for this class, which can be changed by user

* Number of threads to run on 

```
int num_threads = 1; // number should be set from 1 - to any number user needs - it doesn't affect any further calculations 

Matrix<int> matrix_int(5, 5); // 5x5 matrix of integers
matrix_int.set_cores(num_threads);
```


All further calculations will be performed in parallel on **num_threads** number of threads, if number of threads is == 1, then the linear versions of calculations are used

* Choice of method of parallelization

Here user may choose either 0 or 1. <b>0</b> stands for parallelization which dependds on the set number of threads to run on, <b> 1 </b> stands for tbb realisation, where number of threads user sets doesn't matter, therefore after setting method of parallelization to 1, it doesn't make sense to set any number of threads. 


```
int method = 1; // number should be set either 0 or 1

Matrix<int> matrix_int(5, 5); // 5x5 matrix of integers
matrix_int.set_method(method);
```

Although these two methods are not the same, they give the same result for all matrix's calculations. 
<br> </br>

### Possible operations with Matrix

* **Adding matrices**

<u><i> Matrices should be the same size to work with in this case, otherwise a shapes's error would appear with the corresponding error</i></u>

This library supports linear version, parallel version (with the set number of threads), parallel version 2 based on tbb realisation, therefore user is able to choose between these 3 options: 

```
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}};
    Matrix<int> mt_vec_vec(vector_1);
    mt_vec_vec.set_method(0); // parallel method from the given number of threads to run on
    mt_vec_vec.set_cores(1); // set number of threads , otherwise the default number is equal to 4

    Matrix<double> matrix_result = mt_vec_vec + mt_vec_vec;

```

The result matrix is: 
```
[[2, 4, 6]
 [6, 8, 10]]
```

Running with two threads (or more - doesn't affect the result of calculations)
```
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}};
    Matrix<int> mt_vec_vec(vector_1);
    mt_vec_vec.set_method(0); // parallel method from the given number of threads to run on
    mt_vec_vec.set_cores(3); // set number of threads , otherwise the default number is equal to 4

    Matrix<double> matrix_result = mt_vec_vec + mt_vec_vec;

```

The result matrix is: 
```
[[2, 4, 6]
 [6, 8, 10]]
```

Running with tbb realisation
```
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}};
    Matrix<int> mt_vec_vec(vector_1);
    mt_vec_vec.set_method(1); // tbb 
    Matrix<double> matrix_result = mt_vec_vec + mt_vec_vec;

```

The result matrix is: 
```
[[2, 4, 6]
 [6, 8, 10]]
```

* **Substracting matrices**

<u><i> Matrices should be the same size to work with in this case, otherwise a shapes's error would appear with the corresponding error</i></u>


This library supports linear version, parallel version (with the set number of threads), parallel version 2 based on tbb realisation, therefore user is able to choose between these 3 options: 

```
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}};
    Matrix<int> mt_vec_vec(vector_1);
    std::vector<std::vector<double>> vector_2 {{1.5, 1.3, 1.2}, {5.3, 6.4, 0.5}};
    Matrix<double> mt_vec_vec2(vector_2);
    mt_vec_vec.set_method(0); // parallel method from the given number of threads to run on
    mt_vec_vec.set_cores(1); // set number of threads , otherwise the default number is equal to 4

    Matrix<double> matrix_result = mt_vec_vec - mt_vec_vec2;

```

The result matrix is: 
```
[[0.5, 0.7, 1.8]
 [-2.3, -2.4, 4.5]]
```

Running with two threads (or more - doesn't affect the result of calculations)
```
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}};
    Matrix<int> mt_vec_vec(vector_1);
    std::vector<std::vector<double>> vector_2 {{1.5, 1.3, 1.2}, {5.3, 6.4, 0.5}};
    Matrix<double> mt_vec_vec2(vector_2);
    mt_vec_vec.set_method(0); // parallel method from the given number of threads to run on
    mt_vec_vec.set_cores(8); // set number of threads , otherwise the default number is equal to 4

    Matrix<double> matrix_result = mt_vec_vec - mt_vec_vec2;

```
The result matrix is: 
```
[[0.5, 0.7, 1.8]
 [-2.3, -2.4, 4.5]]
```

Running with tbb realisation
```
    std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}};
    Matrix<int> mt_vec_vec(vector_1);
    std::vector<std::vector<double>> vector_2 {{1.5, 1.3, 1.2}, {5.3, 6.4, 0.5}};
    Matrix<double> mt_vec_vec2(vector_2);
    mt_vec_vec.set_method(1); // tbb

    Matrix<double> matrix_result = mt_vec_vec - mt_vec_vec2;

```

The result matrix is: 
```
[[0.5, 0.7, 1.8]
 [-2.3, -2.4, 4.5]]
```


* Multiplication of a matrix by a number

This method simply multiplies the given matrix by a given number


```
std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5};
Matrix<int> mt_vec_vec(vector_1);
int number_1 = 4;
double number_2 = 1.5;

Matrix<double> res_matr_1 = mt_vec_vec * number_1;
std::cout << res_matr_1 << "\n;
Matrix<double> res_matr_2 = mt_vec_vec * number_2;
std::cout << res_matr_2 << "\n;
```
The output of the given code would be (doesn't depend on method or number of threads):

```
[[4, 8, 12]
 [12, 16, 20]]

[[1.5, 3, 4.5]
 [4.5, 6, 7.5]]
```

* Division of a matrix by a number

This method simply divides each matrix's element by a given number (if the number is zero - obviously zeroError would appear)


```
std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5};
Matrix<int> mt_vec_vec(vector_1);
int number_1 = 2;
double number_2 = 0.5;

Matrix<double> res_matr_1 = mt_vec_vec / number_1;
std::cout << res_matr_1 << "\n;
Matrix<double> res_matr_2 = mt_vec_vec / number_2;
std::cout << res_matr_2 << "\n;
```
The output of the given code would be (doesn't depend on method or number of threads):

```
[[0.5, 1, 1.5]
 [1.5, 2, 2.5]]

[[2, 4, 6]
 [6, 8, 10]]
```

* Check if two matrices are equal 

User may run this either linear, in parallel with the set amount of threads or via tbb. 
```
std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}};
Matrix<int> mt_vec_vec(vector_1);
std::vector<std::vector<double>> vector_2 {{1.9, 2.0, 3.7}, {3.2, 4.1, 5.3}};
Matrix<double> mt_vec_vec2(vector_2);
// here you may use: 
//mt_vec_vec.set_method(0); - to use the set amount of threads, therefore:
//mt_vec_vec.set_cores(1); - to run in linear 
//mt_vec_vec.set_cores(2); - to run in two threads (you may put any number of threads here)

// or 
//  mt_vec_vec.set_method(1); - then tbb variant will be chosen 
std::cout << mt_vec_vec==mt_vec_vec2<<"\n;
std::cout << mt_vec_vec==mt_vec_vec<<"\n;
```
The output of the given code would be:

```
false
true
```

* Matrices multiplication 

As it is only possible to multiply matrices with the corresponding sizes: 


Matrix A -> ```KxN```
Matrix B -> ```NxM```
Hence, the result matrix would have ```KxM``` size. Therefore, before the multiplication the shapes of the matrices are checked, and if they do not correspond as they have to the Shapes Error would appear. 

Example of usages: 

```
std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}, {4, 5, 6}};
Matrix<int> mt_vec_vec(vector_1);
std::vector<std::vector<double>> vector_2 {{1.9, 2.0, 3.7}, {3.2, 4.1, 5.3}, {4.5, 7.1, 2.3}};
Matrix<double> mt_vec_vec2(vector_2);

mt_vec_vec.set_method(0);
mt_vec_vec.set_cores(1);
Matrix<double> one_thread = mt_vec_vec*mt_vec_vec2;

mt_vec_vec.set_method(0);
mt_vec_vec.set_cores(2);
Matrix<double> two_threads = mt_vec_vec*mt_vec_vec2;

mt_vec_vec.set_method(1);
Matrix<double> tbb_threads = mt_vec_vec*mt_vec_vec2;
```

All three matrices (one_thread, two_threads, tbb_threads) would be as follows: 

```
[[21.8, 31.5, 21.2]
 [41, 57.9, 43.8]
 [50.6, 71.1, 55.1]]
```


* Obtain matrix of minors from the given one 

<u> <i> Works only for the square matrices for which determinant exists </i> </u> 

Here as well number of threads and method doesn't affect the result.

```
  std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}, {4, 5, 6}};
    Matrix<int> mt_vec_vec(vector_1);

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(1);
    Matrix<int> minors_1 = mt_vec_vec.minor_matrix();

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(2);
    Matrix<int> minors_2 = mt_vec_vec.minor_matrix();

    mt_vec_vec.set_method(1);
    Matrix<int> minors_3 = mt_vec_vec.minor_matrix();


```

All minors_1, minors_2, minors_3 would produce the same result: 

```
[[-1, -2, -1]
 [-3, -6, -3]
 [-2, -4, -2]]
```



* Obtain matrix of cofactors from the given one 

<u> <i> Works only for the square matrices for which determinant exists </i> </u> 

Here as well number of threads and method doesn't affect the result.

```
  std::vector<std::vector<int>> vector_1 {{1, 2, 3}, {3, 4, 5}, {4, 5, 6}};
    Matrix<int> mt_vec_vec(vector_1);

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(1);
    Matrix<int> cofactors_1 = mt_vec_vec.get_cofactors_matrix();

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(2);
    Matrix<int> cofactors_2 = mt_vec_vec.get_cofactors_matrix();

    mt_vec_vec.set_method(1);
    Matrix<int> cofactors_3 = mt_vec_vec.get_cofactors_matrix();
```

All cofactors_1, cofactors_2, cofactors_3 would produce the same result: 

```
[[-1, 2, -1]
 [3, -6, 3]
 [-2, 4, -2]]
```


* Matrix transpose of the given one


Number of threads and the method which is being used doesn't affect the result, therefore for this example: 

```
    std::vector<std::vector<int>> vector_1 {{1, 0, 5}, {2,1, 6}, {3, 4, 0}};
    Matrix<int> mt_vec_vec(vector_1);

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(1);
    Matrix<int> itran_1 = mt_vec_vec.transpose();

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(2);
    Matrix<int> itran_2 = mt_vec_vec.transpose();

    mt_vec_vec.set_method(1);
    Matrix<int> itran_3 = mt_vec_vec.transpose();

```
The resulting transpose matrix would be same for all (itran_1, itran_2, itran_3):

```
[[1, 2, 3]
 [0, 1, 4]
 [5, 6, 0]]
```


* Determinant of a given matrix
<u> <i> Works only for the square matrices for which determinant exists and so far only linearly</i> </u> 

This method works recursively, therefore the matrix itself should be also passed as an argument:

```
std::vector<std::vector<int>> vector_1 {{1, 0, 5}, {2,1, 6}, {3, 4, 0}};
Matrix<int> mt_vec_vec(vector_1);

int determinannt = mt_vec_vec.determinant.(mt_vec_vec);
```

Here determinant is equal to 1. 


* The inverse matrix to the given one 

<u> <i> Works only for the square matrices for which determinant exists </i> </u> 

```
std::vector<std::vector<int>> vector_1 {{1, 0, 5}, {2,1, 6}, {3, 4, 0}};
    Matrix<int> mt_vec_vec(vector_1);

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(1);
    Matrix<double> inversion_1 = mt_vec_vec.inverse();

    mt_vec_vec.set_method(0);
    mt_vec_vec.set_cores(2);
    Matrix<double> inversion_2 = mt_vec_vec.inverse();

    mt_vec_vec.set_method(1);
    Matrix<double> inversion_3 = mt_vec_vec.inverse();
```

All of the inversion results would be same: 

```
[[-24, 20, -5]
 [18, -15, 4]
 [5, -4, 1]]
```

* Cut matrix's row and col accordingly 
Works only linearly so far.  
Only existing row or column can be cut, otherwise Shapes Error appears. 
If user only needs a part of a matrix which can be obtained by taking way one row and one column, then this would work: 

```

    std::vector<std::vector<double>> vector_2 {{1.0, 0.7, 5.3},
                                               {2.1,1.6, 6.4},
                                               {3.2, 4.3, 0.5}};
    Matrix<double> mt_vec_vec2(vector_2);
    std::cout << mt_vec_vec2 <<"\n";
    Matrix<double> cut_row_col = mt_vec_vec2.cuT_Col_Row(0, 0);
    std::cout << cut_row_col <<"\n";
```

The output of the given code sample would be: 
```
[[1, 0.7, 5.3]
 [2.1, 1.6, 6.4]
 [3.2, 4.3, 0.5]]

[[1.6, 6.4]
 [4.3, 0.5]]
```

* Check matrix for being identent 

bool function to check whether the given matrix is identent or not. User may run this either linear, in parallel with the set amount of threads or via tbb.


```
std::vector<std::vector<int>> vector_1 {{1, 0, 5}, {2,1, 6}, {3, 4, 0}};
    Matrix<int> mt_vec_vec(vector_1);

    std::vector<std::vector<int>> vector_2 {{1, 0, 0}, {0,1, 0}, {0, 0, 1}};
    Matrix<int> mt_vec_vec2(vector_2);

    // here you may use: 
    //mt_vec_vec.set_method(0); - to use the set amount of threads, therefore:
    //mt_vec_vec.set_cores(1); - to run in linear 
    //mt_vec_vec.set_cores(2); - to run in two threads (you may put any number of threads here)
    
    // or 
    //  mt_vec_vec.set_method(1); - then tbb variant will be chosen 
    bool first_matrix = mt_vec_vec.isident(); // false
    bool second_matrix = mt_vec_vec2.isident(); // true
```

