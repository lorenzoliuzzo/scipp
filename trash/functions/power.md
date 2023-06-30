---
title: Power
layout: default
collection: functions
permalink: /math/functions/power/
redirect_from: /math/functions/power/
parent: Functions namespace
author_profile: true
---

# Power Functions

The `math/functions/power.hpp` file contains a collection of power functions implemented in the `scipp::math` namespace. These functions provide various ways to calculate the power of different types of operands, including numbers, measurements, complex numbers, vectors, and matrices.

## Function Structure

The power functions are defined using a template structure called `power`, which takes two template arguments representing the power exponent and the base type. Each specialization of the `power` structure provides a static member function `f` that calculates the power operation.

```cpp
template <size_t POWER, typename BASE_TYPE>
struct power {
    using function_t = unary_function<BASE_TYPE, RESULT_TYPE>;
    inline static constexpr function_t::result_t f(const function_t::arg_t&) noexcept {
        // Power calculation implementation
    }
};
```

The `power` structure uses the `unary_function` template to define the types of the argument (`arg_t`) and the result type (`result_t`). The `RESULT_TYPE` depends on the specialization and represents the result type of the power operation.

## Specializations

### 1. Power of Numbers

The first specialization of `power` handles the calculation of the power of a number. It supports any type that satisfies the `is_number_v` concept. The power calculation is performed using the `std::pow` function.

### 2. Power of Measurements

The second specialization handles the calculation of the power of a measurement. It supports types that satisfy the `physics::is_measurement_v` concept. The power calculation is performed by raising the value of the measurement to the specified power while preserving the uncertainty.

### 3. Power of Umeasurements

This specialization handles the calculation of the power of a Umeasurement (measurement with uncertainty). It supports types that satisfy the `physics::is_umeasurement_v` concept. The power calculation is performed by raising the value of the Umeasurement to the specified power while scaling the uncertainty by the power.

### 4. Power of Complex Numbers

The fourth specialization deals with the calculation of the power of a complex number. It supports types that satisfy the `physics::is_cmeasurement_v` concept. The power calculation is performed using the complex logarithm and exponential functions.

### 5. Power of Vectors

This specialization handles the calculation of the power of a vector. It supports types that represent column vectors or row vectors. The power calculation is performed element-wise by raising each element of the vector to the specified power.

## Usage

To use the power functions provided by this library, include the `math/functions/power.hpp` header file in your code. You can then call the `f` function of the desired specialization of `power` to calculate the power operation.

Here's an example of using the power function for numbers:

```cpp
#include <iostream>
#include "math/functions/power.hpp"

int main() {
    double x = 2.0;
    auto result = scipp::math::functions::power<3, double>::f(x);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```

This example demonstrates the calculation of the cube of a number using the `power` function specialization for numbers. The result is printed to the console.

You can similarly use the other specializations of the `power` function based on your specific requirements.

Please note that the code provided is a template for the `power` structure and may require additional modifications based on your specific implementation and requirements.