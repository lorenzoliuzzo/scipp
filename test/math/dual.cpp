/**
 * @file    test/math/dual.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-17
 * 
 * @copyright Copyright (c) 2023
 */



#include "sci++.hpp"

using namespace scipp;

using namespace tools; 
using namespace math; 
using namespace math::functions; 
using namespace physics;
using namespace physics::units; 


int main() { 

    constexpr auto func = compose<square<dual<double>>, invert<dual<double>>>(); 
    constexpr auto I = curves::interval(-10.0, 10.0);
    constexpr auto steps = 100;
    constexpr auto incr = I.step(steps);

    std::vector<double> x_(steps), y_(steps), y_der(steps);
    for (size_t i = 0; i < steps; ++i) {

        x_[i] = I.start + i * incr; 
        auto f_x = func.f(dual(x_[i]));
        y_[i] = f_x.real; 
        y_der[i] = f_x.imag; 

    }

    plt::title("Autodifferentiation with dual numbers");    
    plt::named_plot("f(x)", x_, y_);
    plt::named_plot("f'(x)", x_, y_der);
    plt::legend(); 
    plt::show(); 
    
    return 0; 

}