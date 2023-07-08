/**
 * @file    test/math/variables.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-12
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"

using namespace scipp;

using tools::print; 
using namespace math; 
using namespace math::calculus;    


int main() {


    variable<double> x = 9.0;
    variable<double> y = 1.0;
    variable<double> z = 3.0 * y + op::square(x); 

    print("x = ", x);
    print("y = ", y);
    print("z = x^2 + 3 * y -> ", z);

    std::tuple<variable<double>, variable<double>> der = derivatives(z, wrt(x, y));
    auto dx = std::get<0>(der);
    auto dy = std::get<1>(der);
    print("dz/dx = ", dx);
    print("dz/dy = ", dy);

    auto [ddx] = derivatives(dx, wrt(x));
    print("d^2z/dx^2 = ", ddx); // Error here: this gives zero because dx does not depend on x -> @todo derivativesx

    return 0;
}