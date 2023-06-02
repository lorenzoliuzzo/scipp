---
title: Add
layout: default
permalink: /math/functions/add/
# redirect_from: /math/functions/add/
parent: Functions namespace
author_profile: true
---

# Adding functions 

The `math/functions/add.hpp` file contains a collection of addition functions implemented in the `scipp::math::functions` namespace. These functions provide various ways to perform addition on different types of operands, including numbers, measurements, complex numbers, vectors, and matrices.

## Function Structure

The addition functions are defined using a template structure called `add`, which takes one or two template arguments representing the types of the operands being added. Each specialization of the `add` structure provides a static member function `f` that performs the addition operation.

```cpp
template <typename ARG_TYPE1, typename ARG_TYPE2>
struct add {
    using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, RESULT_TYPE>;
    inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {
        // Addition implementation
    }
};
```

The `add` structure uses the `binary_function` template to define the types of the first and second arguments (`first_arg_t` and `second_arg_t`) and the result type (`result_t`). The `RESULT_TYPE` depends on the specialization and represents the result type of the addition operation.

## Specializations

### 1. Addition of Numbers

The first specialization of `add` handles the addition of two numbers. It supports any type that satisfies the `is_number_v` concept. The addition is performed using the `+` operator.

### 2. Addition of Measurements

The second specialization handles the addition of two measurements. It supports types that satisfy the `physics::is_measurement_v` concept. The addition is performed by adding the values of the measurements while preserving the uncertainty.

### 3. Addition of Complex Numbers

The third specialization deals with the addition of two complex numbers. It supports types that satisfy the `physics::is_cmeasurement_v` concept. The addition is performed by adding the real and imaginary components separately.

### 4. Addition of Generic Measurements and Numbers

This specialization handles the addition of a generic measurement and a number. It supports types that satisfy the `physics::is_generic_measurement_v` concept and have a scalar base type. The addition is performed by casting the number to the measurement's type and then adding them.

### 5. Addition of Vectors

This specialization handles the addition of two vectors. It supports types that represent column vectors or row vectors and have the same dimension and base type. The addition is performed element-wise by adding the corresponding elements of the vectors.

### 6. Addition of Matrices

The last specialization deals with the addition of two matrices. It supports types that satisfy the `geometry::is_matrix_v` concept. The addition is performed element-wise by adding the corresponding elements of the matrices.

## Usage

To use the addition functions provided by this library, include the `math/functions/add.hpp` header file in your code. You can then call the `f` function of the desired specialization of `add` to perform the addition operation.

Here's an example of using the addition function for numbers:

```cpp
#include "sci++.hpp"

using namespace scipp::math;

int main() {
    double x = 3.14;
    double y = 2.71;
    auto result = functions::add<double>::f(x, y);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```

This example demonstrates the addition of two numbers using the `add` function specialization for numbers. The result is printed to the console.

You can similarly use the other specializations of the `add` function based on your specific requirements.