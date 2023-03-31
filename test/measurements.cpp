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
using namespace units;
using namespace math; 


int main() {


    static_assert(are_same_measurements_v<length_m, length_m>);
    static_assert(are_same_measurements_v<length_m, length_m, length_m>);
    // static_assert(are_same_measurements_v<length_m, length_m, length_m, time_m>);
    // static_assert(are_same_measurements_v<length_m, length_m, time_m, time_m>);


    constexpr measurement x = 3.54 * m; 
    constexpr measurement y = 1.5 * mm;
    umeasurement k(x, y);   

    std::cout << x << '\n';
    std::cout << y << '\n';
    std::cout << k << '\n'; 

    y.print_as(mm); 

    tools::read_measurements<length_um, 3>("data/measurements.out").print();
    auto data = tools::read_measurements<length_um>("data/measurements.out");

    tools::print("vector or std::vector", data);


    // std::ofstream of("measurements.out"); 
    // of << x << '\n'; 
    // of << y << '\n'; 
    // of << k << '\n';
    // of.close(); 



    return 0; 

}