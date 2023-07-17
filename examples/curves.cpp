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
using tools::plot;


int main() {
   
    auto circle = curve<std::array<variable<double>, 2>, variable<double>>(
        [](variable<double>& theta) -> std::array<variable<double>, 2> { 
            return { op::cos(theta), op::sin(theta) }; 
        }, interval(0.0, 2.0 * std::numbers::pi)
    );

    constexpr size_t n = 1000;
    variable<double> theta = circle.domain.start;
    const auto dtheta = circle.domain.step(n);

    std::vector<double> x_values(n), y_values(n); 
    meta::for_<n>([&](auto i) constexpr {
        const auto [x, y] = circle(theta); 
        x_values[i.index] = val(x);
        y_values[i.index] = val(y);
        theta += dtheta;
    });

    print<std::nano>("initial x = ", x_values.front());
    print<std::nano>("final x = ", x_values.back());
    print<std::nano>("initial y = ", y_values.front());
    print<std::nano>("final y = ", y_values.back());

    print<std::nano>("final theta = ", val(theta));
    print<std::nano>("end of the domain = ", circle.domain.end);

    print<std::nano>("length of the curve = ", integrals::curvilinear<n>(circle)); 


    plt::title("Circle");
    plt::xlabel("x");
    plt::ylabel("y");

    plt::plot(x_values, y_values);

    plt::tight_layout();
    plt::grid(true);

    plt::save("images/circle.png");
    plt::show();    

    return 0; 

}