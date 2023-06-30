---
title: Measurements
layout: default
permalink: /physics/measurements/
parent: Physics namespace
author_profile: true
---

{:toc}

# Measurements and units of measure
Brief description of the scipp::physics measurement structures.

## Base quantity
Brief description of the scipp::physics::base_quantity type representing a physical quantity.
```cpp
template <int LENGTH, int TIME, int MASS, int TEMPERATURE, 
          int ELETTRIC_CURRENT, int SUBSTANCE_AMOUNT, int LUMINOUS_INTENSITY>
struct base_quantity {
    // Implementation details...
};
```
This struct contains template parameters for the powers of the seven base quantities of the International System of Units (SI) - length, time, mass, temperature, electric current, substance amount, and luminous intensity. 

## Unit of measure
Brief description of the scipp::physics::unit type representing a unit of measure.
```cpp
template <typename BASE_TYPE, typename PREFIX_TYPE = std::ratio<1>>
struct unit {
    // Implementation details...
};
```
This struct represents a unit of measurement and combines a base quantity with an std::ratio prefix. It contains type aliases for the base quantity and prefix types and static members for storing conversion factors between units. It also defines operators for outputting the unit to a stream and methods for converting the unit to a string representation.

## Measurement
```cpp
template <typename BASE_TYPE, typename VALUE_TYPE = double>
struct measurement {
    // Implementation details...
};
```
This struct represents a physical measurement as a value of type VALUE_TYPE (defaulted to double) and a base quantity. 
It contains member variables, static members for zero and one measurements, constructors for creating measurements from values and units, and operators for comparing and printing measurements.


## Operations with measurements
