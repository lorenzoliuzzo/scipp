/**
 * @file    hermite.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-31
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

using namespace scipp; 
using namespace math; 


int main() {


    tools::timer t; 

    t.start(); 
    t.stop(); 
    tools::print("trash time", t.elapsed());


    t.start();
    auto y = hermite<50>(-2.4); 
    t.stop();
    tools::print("hermite fast", t.elapsed());
    tools::print("H_50(-2.4)", y);


    t.start();
    auto x = hermite<100>(-2.4); 
    t.stop();
    tools::print("hermite fast", t.elapsed());
    tools::print("H_100(-2.4)", x);


    t.start();
    auto z = hermite<200>(-2.4); 
    t.stop();
    tools::print("hermite fast", t.elapsed());
    tools::print("H_200(-2.4)", z);

    return 0; 

}