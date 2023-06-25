/**
 * @file    test/math/polynomials.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-28
 * 
 * @copyright Copyright (c) 2023
 */



#include "sci++.hpp"


using namespace scipp; 
using namespace math; 
using namespace polynomials;
using namespace geometry;
using namespace tools;


void hermite_polynomials() {

    auto hermite0 = hermite<0>(); 
    auto hermite1 = hermite<1>(); 
    auto hermite2 = hermite<2>(); 
    auto hermite3 = hermite<3>(); 
    auto hermite4 = hermite<4>(); 
    auto hermite5 = hermite<5>(); 
    // auto hermite6 = hermite<6>(); 

    plot(hermite0, curves::interval(-5., 5.), 1000, "hermite0");
    plot(hermite1, curves::interval(-5., 5.), 1000, "hermite1");
    plot(hermite2, curves::interval(-5., 5.), 1000, "hermite2");
    plot(hermite3, curves::interval(-5., 5.), 1000, "hermite3");
    plot(hermite4, curves::interval(-5., 5.), 1000, "hermite4");
    plot(hermite5, curves::interval(-5., 5.), 1000, "hermite5");
    // plot(hermite6, curves::interval(-5., 5.), 1000, "hermite6");
    plt::legend();
    plt::title("Hermite polynomials"); 
    plt::show(); 

}


void legendre_polynomials() {

    auto legendre0 = legendre<0>(); 
    auto legendre1 = legendre<1>(); 
    auto legendre2 = legendre<2>(); 
    auto legendre3 = legendre<3>(); 
    auto legendre4 = legendre<4>(); 
    auto legendre5 = legendre<5>(); 
    auto legendre6 = legendre<6>(); 


    plot(legendre0, curves::interval(-1., 1.), 1000, "legendre0");
    plot(legendre1, curves::interval(-1., 1.), 1000, "legendre1");
    plot(legendre2, curves::interval(-1., 1.), 1000, "legendre2");
    plot(legendre3, curves::interval(-1., 1.), 1000, "legendre3");
    plot(legendre4, curves::interval(-1., 1.), 1000, "legendre4");
    plot(legendre5, curves::interval(-1., 1.), 1000, "legendre5");
    plot(legendre6, curves::interval(-1., 1.), 1000, "legendre6");
    plt::legend();
    plt::title("Legendre polynomials"); 
    plt::show(); 

}


void chebyshev_polynomials() {

    auto chebyshev0 = chebyshev<1, 0>(); 
    auto chebyshev1 = chebyshev<1, 1>(); 
    auto chebyshev2 = chebyshev<1, 2>(); 
    auto chebyshev3 = chebyshev<1, 3>(); 
    auto chebyshev4 = chebyshev<1, 4>(); 
    auto chebyshev5 = chebyshev<1, 5>(); 
    auto chebyshev6 = chebyshev<1, 6>(); 


    plot(chebyshev0, curves::interval(-1., 1.), 1000, "chebyshev0");
    plot(chebyshev1, curves::interval(-1., 1.), 1000, "chebyshev1");
    plot(chebyshev2, curves::interval(-1., 1.), 1000, "chebyshev2");
    plot(chebyshev3, curves::interval(-1., 1.), 1000, "chebyshev3");
    plot(chebyshev4, curves::interval(-1., 1.), 1000, "chebyshev4");
    plot(chebyshev5, curves::interval(-1., 1.), 1000, "chebyshev5");
    // plot(chebyshev6, curves::interval(-1., 1.), 1000, "chebyshev6");
    plt::legend();
    plt::title("chebyshev polynomials of 1st type"); 
    plt::show(); 

    auto chebyshev20 = chebyshev<2, 0>(); 
    auto chebyshev21 = chebyshev<2, 1>(); 
    auto chebyshev22 = chebyshev<2, 2>(); 
    auto chebyshev23 = chebyshev<2, 3>(); 
    auto chebyshev24 = chebyshev<2, 4>(); 
    auto chebyshev25 = chebyshev<2, 5>(); 
    auto chebyshev26 = chebyshev<2, 6>(); 


    plot(chebyshev20, curves::interval(-1., 1.), 1000, "chebyshev0");
    plot(chebyshev21, curves::interval(-1., 1.), 1000, "chebyshev1");
    plot(chebyshev22, curves::interval(-1., 1.), 1000, "chebyshev2");
    plot(chebyshev23, curves::interval(-1., 1.), 1000, "chebyshev3");
    plot(chebyshev24, curves::interval(-1., 1.), 1000, "chebyshev4");
    // plot(chebyshev25, curves::interval(-1., 1.), 1000, "chebyshev25");
    // plot(chebyshev26, curves::interval(-1., 1.), 1000, "chebyshev26");
    plt::legend();
    plt::title("chebyshev polynomials of 2nd type"); 
    plt::show(); 

}


int main() {
    
    // hermite_polynomials();
    // legendre_polynomials();
    // chebyshev_polynomials();


    // test the find_roots function
    auto coeff = make_vector<double>(-9.0, 0.0, 1.0); // increasing power

    // std::complex<double> x = 1.0; 
    // auto eval = eval_polynomial(coeff, x); 
    // print("eval", eval);

    auto roots = roots_newton(coeff);

    for (auto root : roots.data) 
        std::cout << "root: " << root << std::endl; 

    return 0; 

}