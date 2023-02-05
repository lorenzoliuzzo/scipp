/**
 * @file    measurement.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-19
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp;


int main() {

    std::cout << math::constants::pi * rad << '\n'; 

    measurement l1 = 1 * m;

    std::cout << l1 << '\n'; 

    length_m l2 = 2 * m;
    std::cout << l2 << '\n'; 

    auto f = [](length_m x) { return x * x; };
    std::cout << f(l2) << '\n';

    auto g = [](auto x) { return x * x; };
    std::cout << g(l2) << '\n';





    return 0;

}