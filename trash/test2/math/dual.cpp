/**
 * @file    test/math/dual.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-11
 * 
 * @copyright Copyright (c) 2023
 */


#include "scipp"

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
        z_vec[i] = z.val;
        dzdx_vec[i] = z.eps;
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
        z_vec[i] = f({x_vec[i], 1.0}, {y_vec[i], 1.0}).val;
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


void autodiff() {

    enum {x1,x2,x3,N}; // labels: 0,1,2,3
    std::array<var<scalar_m, 3>, 3> input;
    correlation_model<scalar_m, 3> ex;
    input[ x1 ] = ex.variable(x1, 4.9990, 0.0032);
    input[ x2 ] = ex.variable(x2, 19.661E-3, 0.0095E-3);
    input[ x3 ] = ex.variable(x3, 1.04446, 0.00075);

    print("r", ex.r);
    ex.setCorrelation(x1, x2, -0.36);
    ex.setCorrelation(x1, x3, 0.86);
    ex.setCorrelation(x2, x3, -0.65);
    print("r", ex.r);

    // Model equation: R = V * cos(phi) / I
    var<scalar_m, 3> res = input[ x1 ] * cosine( input[ x3 ]) / input[ x2 ];

    // Prints:
    // Value = 127.732, uc = 0.0699787,
    // u = [0.0817649,-0.0617189,-0.164885]
    print("value", res.val); 
    print("uncertainty", ex.combinedUncertainty(res));
    print("u", res.unc); 


    dual<scalar_m> x(4.9990, 0.0032);
    dual<scalar_m> y(19.661E-3, 0.0095E-3);
    dual<scalar_m> z(1.04446, 0.00075);

    auto R = x * op::cos(z) / y;

    print("value", R.val);
    print("uncertainty", R.eps);

}


template <size_t N>
struct dual_n_func : unary_function<dual_n<physics::scalar_m, N>, dual_n<physics::scalar_m, N>> {
    
    constexpr dual_n<physics::scalar_m, N> operator()(const dual_n<physics::scalar_m, N>& x) const noexcept override {

        return x * x; 
    
    }

};

int main() {

    // ONED(); 
    // TWOD();

    // autodiff();


    dual_n<scalar_m, 3> x(3.0, {1.0, 0.0, 0.0}); 
    
    print("value", x.val);
    for (size_t i{}; i < 3; ++i) 
        print("order " + std::to_string(i), x.der[i]);
    

    auto f = dual_n_func<3>();
    auto y = f(x);

    print("value", y.val);
    for (size_t i{}; i < 3; ++i) 
        print("order " + std::to_string(i), y.der[i]);
    

    return 0; 

}