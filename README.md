# scipp
**scipp** is a WIP c++ _header-only_ library for handling physical quantities and units. It allows you to perform arithmetic operations and conversions between units with compile-time type checking.
It is designed to be used in scientific computing and data analysis.

# Table of Contents
* [How to install](#how-to-install)

* [namespace scipp](#namespace-scipp)

    * [namespace physics](#namespace-physics)
        * [base_quantity](#base_quantity)
        * [unit](#unit)
        * [namespace units](#namespace-units)
        * [measurement](#measurement)
        * [umeasurement](#umeasurement)
        
    * [namespace math](#namespace-math)
        * [namespace op](#namespace-op)
        * [namespace constants](#namespace-constants)

    * [namespace geometry](#namespace-geometry)
        * [vector](#vector)
        * [matrix](#matrix)
    


# How to install
To use the scipp library, you need to add the include directory to your include path and add the library to your linker path.
Then, you can use the library by including the header file in your source code.
,,,c++
#include <scipp.hpp>
,,,

# namespace scipp
All the functions and classes are defined in the namespace scipp. 

## namespace physics
The namespace physics contains all the functions and classes related to physics.

### base_quantity
The base_quantity class is a template class that represents a quantity with a dimentional structure. 
A base_quantity takes as template parameters all the powers of the base SI units.