/**
 * @file    examples/physics/autodiff.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Example of automatic differentiation that preserve dimensional analysis
 * @date    2023-07-15
 * 
 * @copyright Copyright (c) 2023
 */

#include "scipp"


using namespace scipp;
using namespace scipp::physics; 
using namespace scipp::math;
using namespace scipp::math::calculus;
using tools::print; 


int main() {

    variable<measurement<base::length>> x = 2.0 * units::m;

    variable<measurement<base::length>> y = -3.0 * x; 

    variable<measurement<base::area>> z = x * x; 
    

    auto dy_dx = derivatives(y, wrt(x)); 
    auto [dz_dx, dz_dy, dz_dz] = derivatives(z, wrt(x, y, z));

    print("x = ", x);
    print("y = ", y);
    print("z = ", z);
    print("dy_dx = ", dy_dx);
    print("dz_dx = ", dz_dx);
    print("dz_dy = ", dz_dy);
    print("dz_dz = ", dz_dz);

    return 0; 

}