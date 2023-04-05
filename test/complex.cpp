/**
 * @file    test/complex.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-03
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

#include <complex>

using namespace scipp; 
using namespace physics; 
using namespace physics::units; 
using namespace math; 
using namespace tools;


struct complex_cos : unary_function<complex<angle_m>, complex<angle_m>> {

    constexpr complex<angle_m> operator()(const complex<angle_m>& other) const noexcept override { 

        return op::cos(other); 

    }

};


int main() {


    complex<angle_m> mc0(3. * rad, 4. * rad);
    print("real", mc0.real);
    print("imag", mc0.imag);
    
    std::complex<double> c0(3., 4.);

    std::cout << "abs: " << std::abs(c0) << '\n';
    std::cout << "arg: " << std::arg(c0) << '\n';
    std::cout << "norm: " << std::norm(c0) << '\n';
    std::cout << "conj: " << std::conj(c0) << '\n';
    std::cout << "cos: " << std::cos(c0) << '\n';

    print("abs", op::abs(mc0)); 
    print("arg", op::arg(mc0)); 
    print("norm", op::norm(mc0)); 
    print("conj", op::conj(mc0)); 
    print("cos", op::cos(mc0)); 

    print("3^i", op::pow({1.0, 0.5}, math::constants::i));


    auto result = complex_cos()(mc0); 

    print("mc0", mc0);
    print("cos(mc0)", result);
    // print("integrate(cos, (0.0, 0.0) -> (2pi, 0))", integral::midpoint(complex_cos(), complex<angle_m>(), complex<angle_m>(2. * math::constants::pi * rad)));


    return 0; 

}