/**
 * @file    examples/curves.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Example of applied automatic differentiation in calculus: curvilinear integral
 * @date    2023-07-16
 * 
 * @copyright Copyright (c) 2023
 */

#include "scipp"


using namespace scipp;
using namespace math;
using namespace math::op;
using namespace math::calculus;
using namespace math::calculus::integrals;

using tools::print;


int main() {

    auto gamma = curve([](variable<double>& x) -> variable<double> { return op::sin(x); }, interval(0.0, 30.0)); 

    variable<double> x = 0.0;
    auto y = gamma(x);

    print("x = ", x);
    print("y = ", y);

    auto length = curvilinear<1000>(gamma);
    print("length = ", length);
    
    return 0; 

}