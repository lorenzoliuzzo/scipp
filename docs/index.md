---
title: Home
layout: home
permalink: /
nav_order: 0
---


# Scipp Library Documentation

## Hello World! 
This site contains the documentation of the **scipp** library, which is a c++ _header-only_ library for scientific programming.
The site is still WIP and it will be updated in the next days with more and more examples and code snippets. 
The documentation is also available in the `docs` folder of the repository.

The library provides a set of tools for scientific computing, including dimensional analysis, automatic differentiation, integration and more in general it could be used to perform accurate and reliable scientific computations. 
Whether it's simulating physical systems, optimizing designs, or solving differential equations, the library equips users with the tools they need to drive scientific discoveries and technological advancements. 

The library is written in modern c++ and it is designed to be easy to use and to integrate with existing code.

# Key features
## Dimensional analysis
Dimensional analysis plays a crucial role in scientific computations by ensuring that mathematical expressions and equations are consistent in terms of units and dimensions. The library incorporates a compile-time structure for dimensional analysis, allowing users to define and manipulate physical quantities with their associated units. 

This feature is better illustrated in the documentation of the [units and measurements](https://lorenzoliuzzo.github.io/scipp/physics/units-and-measurements/) defined inside the scipp::physics namespace.

## Automatic differentiation
The library also provides a simple and efficient implementation of automatic differentiation, which is a powerful tool for calculus and physics. Automatic differentiation is a technique for evaluating derivatives of functions specified by a computer program. It is implemented by applying the chain rule repeatedly to obtain derivatives of higher order. This implementation is based on the [reverse mode autodiff](https://autodiff.github.io/#reverse-mode) library, with the major advantage of being dimensionally consistent.

Using the `scipp::math::calculus` namespace and its functions, it is possible to compute the derivatives of variables with respect to other variables in a simple and efficient way:
```cpp
#include "scipp"

using namespace scipp;
using namespace scipp::physics; 
using namespace scipp::math;
using namespace scipp::math::calculus;
using tools::print; 

int main() {

    variable<measurement<base::length>> x = 2.0 * units::m;

    variable<measurement<base::length>> y = -3.0 * x; 

    variable<measurement<base::area>> z = x * x; 
    
    auto dy_dx = derivatives(y, wrt(x)); 
    auto [dz_dx, dz_dy, dz_dz] = derivatives(z, wrt(x, y, z));

    print("x = ", x);
    print("y = -3x = ", y);
    print("z = x^2 = ", z);
    print("dy_dx = ", dy_dx);
    print("dz_dx = ", dz_dx);
    print("dz_dy = ", dz_dy);
    print("dz_dz = ", dz_dz);

    return 0; 
}
```

output: 
```bash
x = 2 m
y = -3x = -6 m
z = x^2 = 4 m^2
dy_dx = -3
dz_dx = 4 m
dz_dy = 0 m
dz_dz = 1
```

# How to install
The library is a header-only library, so there is no need to install it once cloned the repository using this command:
```bash
git clone https://github.com/lorenzoliuzzo/scipp.git 
```

You can easily use the library by including the header file in your code: 
```cpp
#include "scipp"

using namespace scipp;
```

If you want to use the library in your project, you can add the following line to your `CMakeLists.txt`:
```cmake
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/path/to/scipp)
```
If you would want to run the tests and the examples, you can use the following commands from the root directory of the repository:
```bash
bash build.sh
```

After that, you can run the tests and the examples using the following commands:
```bash
./build/tests/some_test
./build/examples/some_example
```

# Contributing
If you want to contribute to the project, you can open a [pull requests](https://github.com/lorenzoliuzzo/scipp/pulls) or use the [issue tracker](https://github.com/lorenzoliuzzo/scipp/issues/) to suggest any code implementations or report bugs. 
Any contributions are welcome! 