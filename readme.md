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
