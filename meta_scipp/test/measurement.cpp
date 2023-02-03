/**
 * @file    measurement.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"
#include <cassert>

using namespace scipp; 
using namespace physics; 


int main() {


    static_assert(units::is_unit_v<decltype(units::Km)>); 

    measurement x = 3.43 * units::Km; 
    std::cout << x.value << '\n'; 

    measurement y = 4.33 * units::m; 

    measurement z = x - y; 

    x.print(); 
    y.print(units::mm); 
    z.print(units::Km); 


    math::op::abs(z).print(units::Km); 

    std::cout << sizeof(double) << '\n'; 
    std::cout << sizeof(decltype(x)) << '\n'; 




    return 0; 

}