/**
 * @file    test/math/functions.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-07-07
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"

using namespace scipp;
using tools::print; 

using namespace math; 
using namespace math::calculus; 
using namespace physics;
using namespace physics::base;
using namespace physics::units; 
using namespace physics::units::literals;
using namespace geometry;



int main() { 

    // variable<double> x = 1.0; 
    // variable<double> y = 2.0;
    // auto f = function<double, double, double>([](auto x, auto y) { return 2.0 * op::square(x) + y; }, x, y);

    // auto z = f();
    // print(z);

    // auto [dx, dy] = f.gradient();
    // print(dx);
    // print(dy);

    // auto vars = f.variables;
    // print(std::get<0>(vars));
    // print(std::get<1>(vars));

    // std::get<0>(vars) = 3.0;
    // print(x); 
    // print(f());


    // auto line = curves::line<measurement<length>, measurement<time>>(0.5 * op::div(units::m, units::s), 0.0m);
    // print(line());
    // // print(line.at(1.0 * s));
    // // print(line.at(2.0 * s));
    // print(line.slope);

    // auto par = curves::parabola<double, double>(1.0, 0.0, 0.0);
    // print(par());
    // // print(par.at(1.0));
    // // print(par.at(2.0));


    print(1.0s);    
    measurement t = 1.0min;
    print(t);
    // variable<measurement<time>> t = 0.0s;
    // auto x_t_line = curves::line<measurement<length>, measurement<time>>(1.0 * op::div(units::m, units::s), -10.0 * m, t);
    // print(x_t_line());

    // t = 10.0s;
    // print(x_t_line());
    // t = 20.0s;
    // print(x_t_line());  
    // print(x_t_line.at(50.0s));

    // auto param = x_t_line.parametrization;
    // auto grad = param.gradient();
    // print(std::get<0>(grad)); // 1.0 * m/s

    // auto grad2 = param.gradient(50.0 * s);
    // print(std::get<0>(grad2)); // 0.0 * m/s because i am not passing a reference and so it cannot operate the differentiation

    // vector<double, 2> v1 = {1.0, 2.0};
    // auto cir = curves::circle<vector<double, 2>, double>(v1, 1.0);
    // print(cir()); 

    
    return 0; 

}