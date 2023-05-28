/**
 * @file    test/physics/measurements.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-06
 * 
 * @copyright Copyright (c) 2023
 */



#include "sci++.hpp"


using namespace scipp;
using namespace tools; 
using namespace physics;
using namespace physics::units; 
using namespace math; 


int main() {


    scalar_m z = 0.5; 
    print(z); 
    print(z += 0.5);
    print(z);

    z += 0.5;
    print(z);

    auto x = 3.14m; 
    print(x); 

    auto y = 1.0m;
    print(y); 

    y += x; 
    print(y); 

    y += 0.5m;
    print(y);


    print(x + y); 
    print(x * y); 
    print(x * -1.5m); 
    print(op::sq(x)); 
    print(op::cb(x)); 
    
    // print(x / y); 


    return 0; 

}