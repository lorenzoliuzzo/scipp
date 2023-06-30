---
title: Multiply
layout: default
collection: functions
permalink: /math/functions/multiply/
redirect_from: /math/functions/multiply/
parent: Functions namespace
author_profile: true
---

# Multiplication Functions

The `math/functions/multiply.hpp` file contains a collection of multiplication functions implemented in the `scipp::math` namespace. These functions provide various ways to perform multiplication on different types of operands, including numbers, measurements, complex numbers, vectors, and matrices.

## Function Structure

The multiplication functions are defined using a template structure called `multiply`, which takes one or two template arguments representing the types of the operands being multiplied. Each specialization of the `multiply` structure provides a static member function `f` that performs the multiplication operation.

```cpp
template <typename ARG_TYPE1, typename ARG_TYPE2>
struct multiply {
    using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, RESULT_TYPE>;
    inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {
        // Multiplication implementation
    }
};
```

The `multiply` structure uses the `binary_function` template to define the types of the first and second arguments (`first_arg_t` and `second_arg_t`) and the result type (`result_t`). The `RESULT_TYPE` depends on the specialization and represents the result type of the multiplication operation.

## Specializations

### 1. Multiplication of Numbers

The first specialization of `multiply` handles the multiplication of two numbers. It supports any type that satisfies the `is_number_v` concept. The multiplication is performed using the `*` operator.

### 2. Multiplication of Measurements

The second specialization handles the multiplication of two measurements. It supports types that satisfy the `math::is_measurement_v` concept. The multiplication is performed by multiplying the values of the measurements.

### 3. Multiplication of Complex Numbers

The third specialization deals with the multiplication of two complex numbers. It supports types that satisfy the `math::is_cmeasurement_v` concept. The multiplication is performed by multiplying the real and imaginary components separately.

### 4. Multiplication of Generic Measurements and Numbers

This specialization handles the multiplication of a generic measurement and a number. It supports types that satisfy the `is_number_v` and `math::is_generic_measurement_v` concepts and have a scalar base type. The multiplication is performed by multiplying the value of the measurement with the number.

### 5. Multiplication of Vectors

This specialization handles the multiplication of two vectors. It supports types that represent column vectors or row vectors and have the same dimension and base type. The multiplication is performed element-wise by multiplying the corresponding elements of the vectors.

### 6. Multiplication of Matrices

The last specialization deals with the multiplication of two matrices. It supports types that satisfy the `geometry::is_matrix_v` concept. The multiplication is performed according to the matrix multiplication rules.

## Usage

To use the multiplication functions provided by this library, include the `math/functions/multiply.hpp` header file in your code. You can then call the `f` function of the desired specialization of `multiply` to perform the multiplication operation.

Here's an example of using the multiplication function for numbers:

```cpp
#include <iostream>
#include "math/functions/multiply.hpp"

int main() {
    double x = 3.14;
    double y = 2.71;
    auto result = scipp::math::functions::multiply<double>::f(x, y);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```

This example demonstrates the multiplication of two numbers using the `multiply` function specialization for numbers. The result is printed to the console.

You can similarly use the other specializations of the `multiply` function based on your specific requirements.