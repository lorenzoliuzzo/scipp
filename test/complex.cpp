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

    return 0; 

}