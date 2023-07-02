/**
 * @file    test/autodiff.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06/24
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"


using namespace scipp;

using namespace tools; 
using namespace math; 
using namespace math::op; 
using namespace math::calculus; 


variable<double> sin_function(const variable<double>& x) {

    return op::sin(2.0 * x * x); 

}


int main() { 

    constexpr size_t N = 200; 
    constexpr auto h = std::numbers::pi / N;

    variable<double> x{}; 
    std::vector<double> x_i(N), y_i(N), dy_i(N);

    meta::for_<N>([&](auto i) constexpr {

        x += h; 
        variable<double> y = sin_function(x);
        x_i[i] = val(x); 
        y_i[i] = val(y); 
        auto dydx_i = derivatives(y, wrt(x)); 
        dy_i[i] = std::get<0>(dydx_i);

    }); 

    plt::title("Automatic differentiation");
    plt::named_plot("sin(2x^2)", x_i, y_i); 
    plt::named_plot("4xcos(2x^2)", x_i, dy_i);
    plt::grid(true);
    plt::tight_layout(); 
    plt::legend();
    plt::show(); 

    return 0; 

}