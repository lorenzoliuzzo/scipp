/**
 * @file    test/math/gauss.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-29
 * 
 * @copyright Copyright (c) 2023
 */



#include "sci++.hpp"
#include <cassert>


using namespace scipp; 
using namespace math; 
using namespace integrals;
using namespace tools;


struct func : meta::unary_function<double, double> {

    constexpr double f(const double& x) const override {

        return op::pow<4>(x);

    }

};


void chebyshev() {

    auto f = func();
    auto chebyshev1_result = gauss<polynomials::chebyshev<1, 50>>(f);
    auto chebyshev2_result = gauss<polynomials::chebyshev<2, 50>>(f);
    auto chebyshev3_result = gauss<polynomials::chebyshev<3, 50>>(f);
    auto chebyshev4_result = gauss<polynomials::chebyshev<4, 50>>(f);
    print<std::femto>(chebyshev1_result); 
    print<std::femto>(chebyshev2_result); 
    print<std::femto>(chebyshev3_result); 
    print<std::femto>(chebyshev4_result); 
    print<std::femto>(3.0 * math::constants::pi / 8.0);
    print<std::femto>(math::constants::pi / 16.0);


    auto result1 = gauss<polynomials::chebyshev<1, 50>>(f);
    auto result2 = gauss<polynomials::chebyshev<2, 50>>(f);
    auto result3 = gauss<polynomials::chebyshev<3, 50>>(f);
    auto result4 = gauss<polynomials::chebyshev<4, 50>>(f);

    print<std::femto>(result1);
    print<std::femto>(result2);
    print<std::femto>(result3);
    print<std::femto>(result4);

    auto result = gauss_legendre(f); 
    print<std::femto>(result);

    auto I = curves::interval(-1., 6.);
    auto oooresult1 = gauss<polynomials::chebyshev<1, 50>>(f, I);
    auto oooresult2 = gauss<polynomials::chebyshev<2, 50>>(f, I);
    auto oooresult3 = gauss<polynomials::chebyshev<3, 50>>(f, I);
    auto oooresult4 = gauss<polynomials::chebyshev<4, 50>>(f, I);
    auto legendre = gauss_legendre(f, I);
    print<std::femto>(oooresult1);
    print<std::femto>(oooresult2);
    print<std::femto>(oooresult3);
    print<std::femto>(oooresult4);
    print<std::femto>(legendre);

}


int main() {


    chebyshev();

    auto f = func();
    auto I = curves::interval(-1., 1.);
    auto riemann_result = riemann<integration_method::simpson>(f, I, 0.000000001); 
    print("riemann_result"); 
    print<std::femto>(riemann_result);

    auto I2 = curves::interval(-1., 6.);
    auto riemann_result2 = riemann<integration_method::simpson>(f, I2, 0.000000001); 
    print("riemann_result2"); 
    print<std::femto>(riemann_result2);

    auto x = std::complex<physics::length_m>(1.0, 1.0);
    std::cout << x << std::endl;

    auto y = std::complex<physics::length_m>(-1.0, 1.0);
    std::cout << y << std::endl;

    std::cout << x + y << std::endl;
    std::cout << x - y << std::endl;
    // std::cout << x * y << std::endl;
    // std::cout << x / y << std::endl;


    return 0; 

}


// int main() {

//     timer sw;

//     auto f = func(); 
//     auto I = curves::interval(-1., 1.);

//     sw.start();
//     sw.stop();
//     print("time", sw.elapsed());

//     auto chebyshev1_result = gauss<weight_function_type::chebyshev1, 5>(f, I);
//     print("chebyshev1", chebyshev1_result); 

//     auto chebyshev2_result = gauss<weight_function_type::chebyshev2, 5>(f, I);
//     print("chebyshev2", chebyshev2_result); 

//     sw.start();
//     auto legendre_result = gauss<weight_function_type::legendre, 5>(f, I);
//     sw.stop();
//     print("legendre", sw.elapsed());
//     print<std::femto>(legendre_result);

//     sw.start();
//     auto riemann_result = riemann<integration_method::simpson>(f, I, 0.000000001); 
//     sw.stop();
//     print("riemann_result", sw.elapsed());
//     print<std::femto>(riemann_result);

//     auto riemann_result2 = riemann<integration_method::midpoint, 1000>(f, I); 
//     print("midpoint", riemann_result2);

//     print("diff", op::abs(riemann_result - legendre_result));
//     return 0; 

// }