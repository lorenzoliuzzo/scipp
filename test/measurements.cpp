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

    length_um z; 
    
    std::ifstream file_in("measurements.out");
    file_in >> z; 
    
    if (file_in.fail()) 
        throw std::runtime_error("Cannot read properly from file."); 

    file_in.close(); 

    std::cout << z << '\n'; 


    // std::ofstream of("measurements.out"); 
    // of << x << '\n'; 
    // of << y << '\n'; 
    // of << k << '\n';
    // of.close(); 



    std::cout << op::measurements_prod_t<length_m, length_m>() << '\n';
    std::cout << op::measurements_prod_t<length_m, length_m, length_m>() << '\n';
    std::cout << op::measurements_prod_t<length_m, length_m, time_m, length_m>() << '\n';

    // std::cout << op::sin(3.54 * rad) << '\n'; 


    return 0; 

}