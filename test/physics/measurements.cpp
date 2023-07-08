/**
 * @file    test/physics/measurements.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-06
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"


using namespace scipp;
using tools::print; 
using namespace physics;
using namespace physics::units; 
using namespace math; 
using namespace calculus;


int main() {

    // variable<measurement<metre>> x = 1.0;
    // variable<measurement<metre>> y = 2.0;

    // variable<measurement<metre>> z = x + 2.0 * y;
    // auto [d_dx, d_dy] = derivativesx(z, wrt(x, y));

    // print("d_dx = ", d_dx);
    // print("d_dy = ", d_dy);

    // variable<measurement<metre2>> z2 = x * x + y * y;
    // auto [d2_dx2, d2_dy2] = derivatives(z2, wrt(x, y));

    // print("d2_dx2 = ", d2_dx2);
    // print("d2_dy2 = ", d2_dy2);

    

    return 0; 

}