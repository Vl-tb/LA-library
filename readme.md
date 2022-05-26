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
`Vector` is an 1xn object, which represents obviously a vector in linear algebra. There are several methods of creating it:  
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
  * `size` is size (dimension) of vector;
