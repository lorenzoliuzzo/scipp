/**
 * @file    test/autodiff.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06/24
 * 
 * @copyright Copyright (c) 2023
 */



#include "sci++.hpp"


using namespace scipp;

using namespace tools; 
using namespace math; 
using namespace math::op; 
using namespace math::calculus; 
using namespace physics;
using namespace physics::units; 


int main() { 

    variable<measurement<metre>> a = 1.0;      
    variable<measurement<metre>> b = a + a + a; 
    variable<measurement<metre2>> c = a * a; 
    variable<measurement<metre2>> d = c + c; 
    variable<measurement<metre2>> f = c + d; 
    variable<measurement<metre>> e = d / b; 

    print("a", val(a));
    print("b = 3a ", val(b));
    print("c = a^2 ", val(c)); 
    print("d = 2c ", val(d));
    print("f = c + d ", val(d));
    print("e = d / b ", val(e));

    auto dada = derivatives(a, wrt(a)); 
    print("dada", std::get<0>(dada));

    auto dbda = derivatives(b, wrt(a)); 
    print("dbda", std::get<0>(dbda));

    auto dcda = derivatives(c, wrt(a)); 
    print("dcda", std::get<0>(dcda));

    auto [dfdc, dfdd, dfda] = derivatives(f, wrt(c, d, a));
    print("dfdc", dfdc); 
    print("dfdd", dfdd); 
    print("dfda", dfda); 

    auto [dedd, dedb] = derivatives(e, wrt(d, b)); 
    print("dedd", dedd); 
    print("dedb", dedb);    


    return 0; 

}