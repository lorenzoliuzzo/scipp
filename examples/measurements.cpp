/**
 * @file    examples/physics/measurements.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Demonstrating the usage of the measurement struct and the units namespace.
 * @date    2023-07-12
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"


using namespace scipp;

using namespace physics;
using tools::print; 


void error_in_converting() {
  // This code will not compile because it contains incorrect physical operations.
  measurement<base::acceleration, double> acc{1.0};
  measurement<base::mass, double> mass{1.0};
  measurement<base::force, double> force = acc * mass;
}


int main() {

    error_in_converting();

    // Creating measurements with explicit value_type and base_quantity
    measurement<base::length, int> l0(1, units::m);     

    print(sizeof(l0));                                  ///< '4' (bytes)

    // Creating measurements by multiplying a number by a unit 
    measurement<base::length> l1 = 2.0 * units::m;      
    // @note the value_type is deduced from the number
    // @note the unit base_quantity must be compatible with the base_quantity of the measurement

    print(sizeof(l1));                                  ///< '8' (bytes)

    // Creating measurements with implicit deduction of base quantity and value type
    measurement l2 = 3.0 * units::m;    
    print(l2);                                          ///< '3.0 m'

    // Creating measurements with a prefixed unit
    auto l3 = 4.0 * units::cm;                          
    
    print(l3);                                          ///< '0.04 m'
    // @note The prefix is automatically applied to the value by multiplying it by the prefix factor

    // Printing a measurement with a specific unit type
    print<units::centimetre>(l3);                       ///< '4.0 [c]m'
    print(l3, units::cm);                               ///< '4.0 [c]m'
    // @note the unit base_quantity must be compatible with the base_quantity of the measurement


    // Using literal operators for units
    using namespace units::literals;
    auto l4 = 5.0m;                                     
    auto l5 = 6.0mm;                                    

    print(l4);                                          ///< '5.0 m'
    print(l5);                                          ///< '0.006 m'


    // Creating measurements by combining other measurements
    auto l6 = l1 + l2;                                  
    
    print(l6);                                          ///< '5.0 m'
    print(l1 * l2);                                     ///< '6 m^2'
    print("l1 / l2 = ", l1 / l2);                       ///< 'l1 / l2 = 0.666667'
    print<std::centi>("l1 / l2 = ", l1 / l2);           ///< 'l1 / l2 = 0.67'
    print<std::milli>("l1 / l2 = ", l1 / l2);           ///< 'l1 / l2 = 0.667'


    return 0; 

}