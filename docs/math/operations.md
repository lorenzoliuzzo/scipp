---
title: Operations namespace
layout: default
permalink: /math/operations/
parent: Math namespace
author_profile: true
---

# Operations namespace
Brief description of the scipp::math operations among the different types declared on the library, i.e. numbers, measurements, vectors, matrices, etc.
All the operations are defined in the `scipp::math::op` namespace and are implemented as functions calling the corresponding methods of the types involved in the operation. For example, the addition operation for numbers is implemented as a function calling the `add` method of the `Number` class. 
In this way, the operations are defined in a single place and the implementation of the methods is hidden from the user. As a consequence, the user can use the operations without knowing the implementation details of the types involved in the operation.
Another thing that adds value to this approach is that with a single operator overload we can define the operation for different types. 
For example, the addition operation for numbers is defined in a single function that can be used to add two numbers, two measurements, two complex numbers, etc.
But it is not only this: when we are working with real phenomena, we often need to perform operations on different types of quantities. For example, we may need to add a measurement to a number or multiply a vector by a number. In this way, the library garanties that all the operations performed on the different types are consistent dimensionally and physically.


## Usage

Let's see how to use the operations provided by the library. We will use the addition operation as an example.

Here's an example of using the addition function for numbers:

```cpp
#include "sci++.hpp"

using namespace scipp;
using namespace scipp::math;

using scipp::tools::print;

int main() {

    double x = 3.14;
    double y = 2.71;
    auto result = op::add(x, y);
    print("result = ", result); 

    return 0;

}
```