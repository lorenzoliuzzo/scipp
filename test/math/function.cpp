/**
 * @file    test/math/function.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-23
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

using namespace scipp; 
using namespace math; 
using namespace physics; 


int main() {


    auto m2 = units::mm * units::mm;

    std::cout << m2.to_string() << '\n'; 


    std::cout << op::sqrt(3.0 * m2) << '\n';  
    std::cout << op::square(-3 * units::mm) << '\n';  


    return 0; 

}