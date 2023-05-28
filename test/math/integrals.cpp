/**
 * @file    test/math/integrals.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-24
 * 
 * @copyright Copyright (c) 2023
 */



#include "sci++.hpp"

using namespace scipp;

using namespace tools; 
using namespace math; 
using namespace math::functions; 
using namespace math::integrals; 
using namespace physics;
using namespace physics::units;


constexpr void test_rectangle_method(const auto I); 
constexpr void test_rectangle_fixed_method(const auto I); 
constexpr void test_midpoint_method(const auto I); 
constexpr void test_midpoint_fixed_method(const auto I);
constexpr void test_simpson_method(const auto I); 
constexpr void test_simpson_fixed_method(const auto I);
constexpr void test_trapezoid_method(const auto I);
constexpr void test_trapezoid_fixed_method(const auto I);


struct gaussian : unary_function<double, double> {


    using result_t = double; 

    using arg_t = double;


    inline static constexpr result_t f(const arg_t& x) noexcept { 

        return std::exp(-op::square(x)); 
    
    }


};


int main() { 

    constexpr interval I(0.0m, 1.0m);
    print("\nTesting the rectangle method...");
    test_rectangle_method(I);

    print("\nTesting the rectangle fixed method...");
    test_rectangle_fixed_method(I);

    print("\nTesting the midpoint method...");
    test_midpoint_method(I);

    print("\nTesting the midpoint fixed method...");
    test_midpoint_fixed_method(I);


    print("\nTesting the simpson method...");
    test_simpson_method(I);

    print("\nTesting the simpson fixed method...");
    test_simpson_fixed_method(I);

    print("\nTesting the trapexoid method...");
    test_trapezoid_method(I);

    print("\nTesting the trapezoid fixed method...");
    test_trapezoid_fixed_method(I);
    
    return 0; 

}


constexpr void test_rectangle_method(const auto I) {

    timer t; 
    t.start();

    auto result = rectangle<power<2, length_m>>(I, 100);
    print<std::femto>("int x^2, x in (0, 1), steps 100", result);

    result = rectangle<power<2, length_m>>(I, 1000);
    print<std::femto>("int x^2, x in (0, 1), steps 1000", result);

    result = rectangle<power<2, length_m>>(I, 10000);
    print<std::femto>("int x^2, x in (0, 1), steps 10000", result);

    result = rectangle<power<2, length_m>>(I, 100000);
    print<std::femto>("int x^2, x in (0, 1), steps 100000", result);

    result = rectangle<power<2, length_m>>(I, 1000000);
    print<std::femto>("int x^2, x in (0, 1), steps 1000000", result);

    t.stop(); 

    print("elapsed_time", t.elapsed());

}

constexpr void test_rectangle_fixed_method(const auto I) {

    timer t; 
    t.start();

    auto result = rectangle<power<2, length_m>, std::ratio<1, 100>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 100", result);

    result = rectangle<power<2, length_m>, std::ratio<1, 1000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 1000", result);

    result = rectangle<power<2, length_m>, std::ratio<1, 10000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 10000", result);

    result = rectangle<power<2, length_m>, std::ratio<1, 100000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 100000", result);

    result = rectangle<power<2, length_m>, std::ratio<1, 1000000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 1000000", result);

    result = rectangle<power<2, length_m>, std::nano>(I);
    print<std::femto>("int x^2, x in (0, 1), precision nano", result);


    t.stop(); 
    print("elapsed_time", t.elapsed());
    
    
}



constexpr void test_midpoint_method(const auto I) {

    timer t; 
    t.start();

    auto result = midpoint<power<2, length_m>>(I, 100);
    print<std::femto>("int x^2, x in (0, 1), steps 100", result);

    result = midpoint<power<2, length_m>>(I, 1000);
    print<std::femto>("int x^2, x in (0, 1), steps 1000", result);

    result = midpoint<power<2, length_m>>(I, 10000);
    print<std::femto>("int x^2, x in (0, 1), steps 10000", result);

    result = midpoint<power<2, length_m>>(I, 100000);
    print<std::femto>("int x^2, x in (0, 1), steps 100000", result);

    result = midpoint<power<2, length_m>>(I, 1000000);
    print<std::femto>("int x^2, x in (0, 1), steps 1000000", result);

    t.stop(); 
    print("elapsed_time", t.elapsed());

}

constexpr void test_midpoint_fixed_method(const auto I) {

    timer t; 
    t.start();

    auto result = midpoint<power<2, length_m>, std::ratio<1, 100>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 100", result);

    result = midpoint<power<2, length_m>, std::ratio<1, 1000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 1000", result);

    result = midpoint<power<2, length_m>, std::ratio<1, 10000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 10000", result);

    result = midpoint<power<2, length_m>, std::ratio<1, 100000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 100000", result);

    result = midpoint<power<2, length_m>, std::ratio<1, 1000000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 1000000", result);

    result = midpoint<power<2, length_m>, std::nano>(I);
    print<std::femto>("int x^2, x in (0, 1), precision nano", result);


    t.stop(); 
    print("elapsed_time", t.elapsed());
    
    
}



constexpr void test_simpson_method(const auto I) {

    timer t; 
    t.start();

    auto result = simpson<power<2, length_m>>(I, 100);
    print<std::femto>("int x^2, x in (0, 1), steps 100", result);

    result = simpson<power<2, length_m>>(I, 1000);
    print<std::femto>("int x^2, x in (0, 1), steps 1000", result);

    result = simpson<power<2, length_m>>(I, 10000);
    print<std::femto>("int x^2, x in (0, 1), steps 10000", result);

    result = simpson<power<2, length_m>>(I, 100000);
    print<std::femto>("int x^2, x in (0, 1), steps 100000", result);

    result = simpson<power<2, length_m>>(I, 1000000);
    print<std::femto>("int x^2, x in (0, 1), steps 1000000", result);

    t.stop(); 
    print("elapsed_time", t.elapsed());

}

constexpr void test_simpson_fixed_method(const auto I) {

    timer t; 
    t.start();

    auto result = simpson<power<2, length_m>, std::ratio<1, 100>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 100", result);

    result = simpson<power<2, length_m>, std::ratio<1, 1000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 1000", result);

    result = simpson<power<2, length_m>, std::ratio<1, 10000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 10000", result);

    result = simpson<power<2, length_m>, std::ratio<1, 100000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 100000", result);

    result = simpson<power<2, length_m>, std::ratio<1, 1000000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 1000000", result);

    result = simpson<power<2, length_m>, std::nano>(I);
    print<std::femto>("int x^2, x in (0, 1), precision nano", result);


    t.stop(); 
    print("elapsed_time", t.elapsed());
    
    
}




constexpr void test_trapezoid_method(const auto I) {

    timer t; 
    t.start();

    auto result = trapezoid<power<2, length_m>>(I, 100);
    print<std::femto>("int x^2, x in (0, 1), steps 100", result);

    result = trapezoid<power<2, length_m>>(I, 1000);
    print<std::femto>("int x^2, x in (0, 1), steps 1000", result);

    result = trapezoid<power<2, length_m>>(I, 10000);
    print<std::femto>("int x^2, x in (0, 1), steps 10000", result);

    result = trapezoid<power<2, length_m>>(I, 100000);
    print<std::femto>("int x^2, x in (0, 1), steps 100000", result);

    result = trapezoid<power<2, length_m>>(I, 1000000);
    print<std::femto>("int x^2, x in (0, 1), steps 1000000", result);

    t.stop(); 
    print("elapsed_time", t.elapsed());

}


constexpr void test_trapezoid_fixed_method(const auto I) {

    timer t; 
    t.start();

    auto result = trapezoid<power<2, length_m>, std::ratio<1, 100>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 100", result);

    result = trapezoid<power<2, length_m>, std::ratio<1, 1000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 1000", result);

    result = trapezoid<power<2, length_m>, std::ratio<1, 10000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 10000", result);

    result = trapezoid<power<2, length_m>, std::ratio<1, 100000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 100000", result);

    result = trapezoid<power<2, length_m>, std::ratio<1, 1000000>>(I);
    print<std::femto>("int x^2, x in (0, 1), precision 1 / 1000000", result);

    result = trapezoid<power<2, length_m>, std::nano>(I);
    print<std::femto>("int x^2, x in (0, 1), precision nano", result);


    t.stop(); 
    print("elapsed_time", t.elapsed());
    
    
}




// constexpr void gauss(const auto I) {

//     // auto I2 = interval(0.0, 1.0);
//     // auto result = gauss<power<2, length_m>, weight_function<laguerre>>(I2, 100000);
//     // print("laguerre", result); 
//     // result = gauss<power<2, length_m>, weight_function<legendre>>(I2, 100000);
//     // print("legendre", result); 
//     // result = gauss<power<2, length_m>, weight_function<hermite>>(I2, 100000);
//     // print("hermite", result); 
//     // result = gauss<power<2, length_m>, weight_function<chebyshev1>>(I2, 100000);
//     // print("chebyshev1", result); 
//     // result = gauss<power<2, length_m>, weight_function<chebyshev2>>(I2, 100000);
//     // print("chebyshev2", result); 

//     // result = trapezoid<power<2, length_m>>(I2, 100000);
//     // print("simpson", result);

// }