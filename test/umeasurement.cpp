/**
 * @file    umeasurement.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-19
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp;


int main() {

    std::cout << umeasurement(math::constants::pi * rad, math::constants::pi / 12 * rad) << '\n'; 
    
    std::cout << angle_um(math::constants::pi * rad, math::constants::pi / 12 * rad) << '\n'; 

    



    return 0;

}