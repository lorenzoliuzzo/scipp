/**
 * @file    examples/physics/derivative.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Example of function derivative
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

    std::vector<double> x_values(500), f_values(500), df_values(500);

    variable<measurement<base::scalar>> x = 0.0;

    auto f = [&](const auto& x) { return op::sinh(x); };


    meta::for_<500>([&](auto i) {

        x = 0.01 * i.index;
        variable y = f(x);

        x_values[i] = val(x);
        f_values[i] = val(y);
        df_values[i] = derivatives(y, wrt(x));

    });

    plt::figure();
    plt::title("Derivative of sinh(x)");
    plt::named_plot("sinh", x_values, f_values);
    plt::named_plot("d(sinh(x))/dx", x_values, df_values);
    plt::xlabel("x");
    plt::ylabel("y");
    plt::legend();
    plt::grid(true);
    plt::save("images/derivative.png");
    plt::show();


    return 0; 

}