/**
 * @file    test/math/functions.cpp
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
using namespace physics;
using namespace physics::units; 


int main() { 


    print("size int", sizeof(int));
    print("size double", sizeof(double));
    print("size long double", sizeof(long double));
    print("size measurement with int", sizeof(measurement<metre, int>));
    print("size measurement with double", sizeof(measurement<metre, double>));
    print("size measurement with long double", sizeof(measurement<metre, long double>));


    // auto a = measurement<metre, int>(3);
    // auto b = measurement<metre>(4.6);
    // auto c = a + b; 
    // auto d = a + a; 

    // print(sizeof(a));
    // print(sizeof(b));
    // print(sizeof(c));
    // print(sizeof(d));

    // print(a);
    // print(b);
    // print(a + b);
    // print(a + c);

    // print(op::inv(3.0m)); 

    // auto x = 3.0m;
    // print(x);
    // op::add(x, 3.0m);
    // print(x);

    // x -= 6.0m;
    // print(x);

    // x += x; 
    // print(x);

    // x *= 300.0; 
    // print<std::micro>(x);
    // x /= 3000.0;
    // print<std::micro>(x);


    // print(x + 3.0m);
    // print(x - 3.0m);
    // print(x * 3.0m);

    // print(op::abs(x));
    // print(op::sq(x) * 2.0);
    // print(op::abs(cmeasurement(x, x)));
    // print(op::exp(-4.0));
    // print(op::sin(0.0));
    // print(op::sin(math::constants::pi * 0.5));


    double oi = 5.0; 
    double oa = -5.0; 

    auto r = op::add(oi, oa);
    print(r);


    return 0; 

}