/**
 * @file    measurements.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-22
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

using namespace scipp; 
using namespace physics; 
using namespace physics::units; 
using namespace tools; 


int main() {


    static_assert(are_same_measurements_v<length_m, length_m>);
    static_assert(are_same_measurements_v<length_m, length_m, length_m>);

    constexpr measurement x = 3.54 * m; 
    constexpr measurement y = 1.5 * mm;
    umeasurement k(x, y);   

    std::cout << x << '\n';
    std::cout << y << '\n';
    std::cout << k << '\n'; 

    print(y, um); 

    return 0; 

}