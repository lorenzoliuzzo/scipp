/**
 * @file    measurements.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-17
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

using namespace scipp; 
using namespace physics; 
using namespace units;


int main() {


    static_assert(are_same_measurements_v<length_m, length_m>);
    static_assert(are_same_measurements_v<length_m, length_m, length_m>);
    // static_assert(are_same_measurements_v<length_m, length_m, length_m, time_m>);
    // static_assert(are_same_measurements_v<length_m, length_m, time_m, time_m>);


    constexpr measurement x = 3.54 * m; 
    constexpr measurement y = 0.5 * mm;

    std::cout << x << '\n';
    std::cout << y << '\n';


    // std::cout << measurements_prod_t<length_m, length_m>() << '\n';
    // std::cout << measurements_prod_t<length_m, length_m, length_m>() << '\n';
    // std::cout << measurements_prod_t<length_m, length_m, time_m, length_m>() << '\n';
    // // xy.print(); 

    umeasurement k(x, y);   
    std::cout << k << '\n'; 

    std::ofstream of("measurements.out"); 
    of << measurements_prod_t<length_m, length_m>() << '\n';
    of << measurements_prod_t<length_m, length_m, length_m>() << '\n';
    of << measurements_prod_t<length_m, length_m, time_m, length_m>() << '\n';
    of << k; 
    of.close(); 

    


    return 0; 

}