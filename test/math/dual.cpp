/**
 * @file    test/math/dual.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-11
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

using namespace scipp; 
using namespace math; 
using namespace functions;
using namespace physics;
using namespace geometry;
using namespace tools;


#include <external/matplotlibcpp.h>
namespace plt = matplotlibcpp;


struct myFunc1D : unary_function<dual<physics::scalar_m>, dual<physics::scalar_m>> {


    constexpr dual<physics::scalar_m> operator()(const dual<physics::scalar_m>& x) const noexcept override {

        return op::log(x);

    }


};


int ONED() {

    auto f = myFunc1D();
    auto df = derivative<myFunc1D>();

    vector<scalar_m, 100> x_vec;
    vector<scalar_m, 100> z_vec;
    vector<scalar_m, 100> dzdx_vec;
    vector<scalar_m, 100> dzdx_vec2;

    for (auto i = 0; i < 100; ++i) {
        x_vec[i] = (3.60 + i * 0.1);
        auto z = f(x_vec[i]);
        z_vec[i] = z.real;
        dzdx_vec[i] = z.imag;
        dzdx_vec2[i] = df(x_vec[i]);
    }


    plt::figure(); 
    plt::title("Logarithmic function");
    plt::named_plot("z", static_cast<std::vector<double>>(x_vec), static_cast<std::vector<double>>(z_vec));
    plt::named_plot("dz/dx", static_cast<std::vector<double>>(x_vec), static_cast<std::vector<double>>(dzdx_vec));
    plt::named_plot("dz/dx 2", static_cast<std::vector<double>>(x_vec), static_cast<std::vector<double>>(dzdx_vec2));
    plt::legend();
    plt::grid(true);
    plt::save("images/log_func.png");
    plt::show();

    return 0; 

}


struct myFunc2D : binary_function<dual<physics::scalar_m>, dual<physics::scalar_m>, dual<physics::scalar_m>> {

    constexpr dual<physics::scalar_m> operator()(const dual<physics::scalar_m>& x, const dual<physics::scalar_m>& y) const noexcept {

        return op::exp(2.0 * op::cbrt(x) + op::cos(y)) + op::log(y) / op::square(x + 1.0);

    } 

};

int TWOD() {

    auto f = myFunc2D();
    auto df = gradient<myFunc2D>();

    vector<scalar_m, 500> x_vec;
    vector<scalar_m, 500> y_vec;
    vector<scalar_m, 500> z_vec;
    vector<scalar_m, 500> dzdx_vec;
    vector<scalar_m, 500> kn_dzdx_vec;
    vector<scalar_m, 500> dzdy_vec;

    for (auto i = 1; i < 500; ++i) {
        x_vec[i] = (i * 0.1);
        y_vec[i] = (i * 0.1);
        z_vec[i] = f({x_vec[i], 1.0}, {y_vec[i], 1.0}).real;
        dzdx_vec[i] = df({x_vec[i], 1.0}, {y_vec[i], 0.0});
        dzdy_vec[i] = df({x_vec[i], 0.0}, {y_vec[i], 1.0});
    }

    plt::scatter(static_cast<std::vector<double>>(x_vec), static_cast<std::vector<double>>(y_vec), static_cast<std::vector<double>>(z_vec));
    plt::title("f(x, y) = exp(2.0 * cbrt(x) + cos(y)) + log(y) / square(x + 1.0)");
    plt::save("images/binary_func.png");

    plt::figure();
    plt::title("partial derivatives of exp(2.0 * cbrt(x) + cos(y)) + log(y) / square(x + 1.0)");
    plt::named_plot("dz/dx", static_cast<std::vector<double>>(x_vec), static_cast<std::vector<double>>(dzdx_vec));
    plt::named_plot("dz/dy", static_cast<std::vector<double>>(y_vec), static_cast<std::vector<double>>(dzdy_vec));
    plt::legend();
    plt::grid(true);
    plt::save("images/binary_part_der.png");
    plt::show();


    return 0;

}


int main() {

    // ONED(); 
    TWOD();

    return 0; 

}