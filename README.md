# scipp 
**scipp** is a c++ _header-only_ library for scientific programming. 
The library provides a set of tools for scientific computing, including dimensional analysis, automatic differentiation, integration and more in general it could be used for performing accurate and reliable scientific computations. 
Whether it's simulating physical systems, optimizing designs, or solving differential equations, the library equips users with the tools they need to drive scientific discoveries and technological advancements. 

The library is written in modern c++ and it is designed to be easy to use and to integrate with existing code.

Here is a pair of features that the library provides:
## Dimensional analysis
Dimensional analysis plays a crucial role in scientific computations by ensuring that mathematical expressions and equations are consistent in terms of units and dimensions. The library incorporates a compile-time structure for dimensional analysis, allowing users to define and manipulate physical quantities with their associated units. This feature provides compile-time checks to catch unit mismatches and enforce dimensional consistency, reducing errors and improving code reliability.

## Automatic differentiation
The library also provides a simple and efficient implementation of automatic differentiation, which is a powerful tool for calculus and physics. Automatic differentiation is a technique for evaluating derivatives of functions specified by a computer program. It is implemented by applying the chain rule repeatedly to obtain derivatives of higher order. This implementation is based on the [Reverse mode autodiff](https://autodiff.github.io/#reverse-mode) implementation, with the major advantage of being dimensionally consistent.

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

If you want to use the library in your project, you can add the following line to your `CMakeLists.txt` file:
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

# Documentation
The library documentation is available [here](https://lorenzoliuzzo.github.io/scipp/) and it is written using GPT-4 under the supervision of the author.
The documentation is also available in the `docs` folder of the repository.

The site is still WIP and it will be updated in the next days with more and more examples and code snippets. 

# Contributing
If you want to contribute to the project, you can open a [pull requests](https://github.com/lorenzoliuzzo/scipp/pulls) or use the [issue tracker](https://github.com/lorenzoliuzzo/scipp/issues/) to suggest any code implementations or report bugs. 
Any contributions are welcome! 

## License
The code is released under the terms of the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.html). 
See the file [LICENSE.md](https://github.com/lorenzoliuzzo/scipp/blob/master/LICENSE).