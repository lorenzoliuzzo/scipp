/**
 * @file    test/autodiff.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06/21
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"

using namespace scipp;

using namespace tools; 
using namespace math; 
using namespace math::op; 
using namespace math::calculus; 
using namespace physics;
using namespace physics::units; 


int main() { 

    auto x = 3.0 * m; 
    print(x); 

    auto y = x; 
    print(y); 

    auto z = x + y; 
    print(z);

    auto w = x * y; 
    print(w);

    auto e = op::power<2>(x);
    print(e);

    auto f = op::invert(x); 
    print(f); 

    auto g = x / w; 
    print(g); 

    auto h = op::divide_t<decltype(x), decltype(y)>(4.0); 
    print(h);

    return 0; 


}