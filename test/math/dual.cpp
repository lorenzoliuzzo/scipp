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
<<<<<<< Updated upstream
using namespace physics::units; 
=======
using namespace physics::units;


inline variable<measurement<metre>> f(const variable<measurement<metre>>& x, const variable<measurement<metre>>& y, const variable<measurement<metre>>& z) {

    return 3 * x * y + z;

}
>>>>>>> Stashed changes


int main() { 

<<<<<<< Updated upstream
    constexpr auto func = compose<square<dual<double>>, invert<dual<double>>>(); 
    constexpr auto I = curves::interval(-10.0, 10.0);
    constexpr auto steps = 100;
    constexpr auto incr = I.step(steps);

    std::vector<double> x_(steps), y_(steps), y_der(steps);
    for (size_t i = 0; i < steps; ++i) {
=======
    variable<measurement<metre>> x = 1.0;
    variable<measurement<metre>> y = 2.0;
    variable<measurement<metre>> z = 0.01;

    variable<measurement<metre>> f_xyz = f(x, y, z);
    auto [dx, dy, dz] = derivatives(f_xyz, wrt(x, y, z)); 
   

    // print("x", val(x));
    // print("y", val(y));
    // print("z", val(z));
    // print("f(x, y, z)", val(f_xyz));
    print("df/dx", dx.value);
    print("df/dy", dy.value);   
    print("df/dz", dz.value);   


    // constexpr size_t N = 200; 
    // std::vector<double> x_(N), y_(N), f_xy_(N), dfdx(N), dfdy(N); 
    // meta::_for<N>([&](auto i) constexpr {

    //     x += d;
    //     y -= d; 

    //     x_[i] = val(x); 
    //     y_[i] = val(y); 

    //     var f_xy = f(x, y);
    //     f_xy_[i] = val(f_xy); 

    //     auto [dx, dy] = derivatives(f_xy, wrt(x, y)); 
    //     dfdx[i] = dx; 
    //     dfdy[i] = dy;
        
    // });


    // plt::scatter(x_, y_, f_xy_);
    // plt::show(); 

    // plt::grid(true);
    // plt::title("Partials derivatives");
    // plt::named_plot("dfdx", x_, dfdx); 
    // plt::named_plot("dfdy", y_, dfdy); 
    // plt::legend(); 
    // plt::tight_layout(); 
    // plt::show();



    // constexpr auto func = compose<square<dual<double, double>>, invert<dual<double, double>>>(); 




    // constexpr auto I = curves::interval(-10.0, 10.0);
    // constexpr auto steps = 100;
    // constexpr auto incr = I.step(steps);

    // std::vector<double> x_(steps), y_(steps), y_der(steps);
    // for (size_t i = 0; i < steps; ++i) {
>>>>>>> Stashed changes

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