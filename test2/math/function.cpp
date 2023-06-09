/**
 * @file    test/math/function.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-23
 * 
 * @copyright Copyright (c) 2023
 */



#include "sci++.hpp"


using namespace scipp; 
using namespace math; 
using namespace physics; 
using namespace geometry; 
using namespace tools; 


struct func : unary_function<complex<scalar_m>, complex<scalar_m>> {

    constexpr complex<scalar_m> operator()(const complex<scalar_m>& x) const override {

        return x * op::exp(x); 

    }

};


int main() {


    auto m2 = units::mm * units::mm;

    std::cout << m2.to_string() << '\n'; 


    std::cout << op::sqrt(3.0 * m2) << '\n';  
    std::cout << op::square(-3 * units::mm) << '\n';  


    std::cout << multiply_t<length_m>() << '\n';
    std::cout << multiply_t<length_m, length_m, time_m>() << '\n';
    std::cout << meta::divide_t<length_m, time_m>() << '\n';
    std::cout << meta::cube_t<length_m>() << '\n';
    std::cout << meta::invert_t<length_m>() << '\n';


    std::cout << multiply_t<complex<length_m>, complex<time_m>, time_m>() << '\n';

    auto f = func(); 
    complex<scalar_m> x(1.0, 1.0);

    auto circ = circumference(x, x.real); 

    print(f(x)); 

    // auto integral = integrals::curvilinear(f, circ); 
    // print(integral);

    return 0; 

}