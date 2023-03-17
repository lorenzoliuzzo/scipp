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


    measurement x = 3.54 * m; 
    measurement y = 2.34 * m;
    measurement z = 1.23 * m;

    std::cout << x << '\n';
    std::cout << y << '\n';


    std::cout << measurements_prod_t<length_m, length_m>() << '\n';
    std::cout << measurements_prod_t<length_m, length_m, length_m>() << '\n';
    std::cout << measurements_prod_t<length_m, length_m, time_m, length_m>() << '\n';
    // xy.print(); 



    return 0; 

}