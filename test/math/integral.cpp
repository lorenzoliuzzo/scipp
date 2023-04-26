/**
 * @file    test/integral.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-05
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

using namespace scipp; 
using namespace physics; 
using namespace physics::units; 
using namespace math; 
using namespace math::integrals; 
using namespace geometry; 
using namespace tools;


template <typename MEAS_TYPE>
    requires (is_generic_measurement_v<MEAS_TYPE>)
struct andrea : meta::unary_function<MEAS_TYPE, MEAS_TYPE> {

    constexpr MEAS_TYPE f(const MEAS_TYPE& x) const noexcept override {

        return 2 * x + op::log(x) * op::square(x); 

    } 

};


template <typename VECTOR_TYPE>
    requires (is_vector_v<VECTOR_TYPE>)
struct myFUNC : meta::unary_function<meta::square_t<typename VECTOR_TYPE::measurement_t>, VECTOR_TYPE> {

    constexpr meta::square_t<typename VECTOR_TYPE::measurement_t> f(const VECTOR_TYPE& other) const noexcept override {

        return op::square(other.x()) + op::square(other.y());

    } 

};


template <typename VECTOR_TYPE>
    requires (is_vector_v<VECTOR_TYPE>)
struct myFUNC2 : meta::unary_function<meta::invert_t<typename VECTOR_TYPE::measurement_t>, VECTOR_TYPE> {

    constexpr meta::invert_t<typename VECTOR_TYPE::measurement_t> f(const VECTOR_TYPE& other) const noexcept override {

        return (other.x() - other.y()) / (op::square(other.x()) + op::square(other.y()));

    } 

};


// template <typename VECTOR_TYPE>
//     requires (is_vector_v<VECTOR_TYPE>)
// struct vortex : unary_function<op::inv<typename VECTOR_TYPE::measurement_t>, VECTOR_TYPE> {

//     constexpr op::inv<typename VECTOR_TYPE::measurement_t> operator()(const VECTOR_TYPE& other) const noexcept override {

//         return (other.x() - other.y()) / (op::square(other.x()) + op::square(other.y()));

//     } 

// };


int main() {


    interval I(1.0m, 10.0m); 
    print(I(0)); 
    print(I(1)); 


    tools::timer t; 
    t.start(); 
    t.stop(); 

    auto func = andrea<length_m>();

        print("testing the rectangle integration");
        auto rectangle100 = riemann<integration_method::rectangle, 100>(func, I); 
        auto rectangle1000 = riemann<integration_method::rectangle, 1000>(func, I); 
        auto rectangle10000 = riemann<integration_method::rectangle, 10000>(func, I); 
        auto rectangle100000 = riemann<integration_method::rectangle, 100000>(func, I); 
        print("int 2x from 0 to 1, 100 steps", rectangle100); 
        print("int 2x from 0 to 1, 1000 steps", rectangle1000); 
        print("int 2x from 0 to 1, 10000 steps", rectangle10000); 
        print("int 2x from 0 to 1, 100000 steps", rectangle100000); 


    print("testing the trapexoid integration");
    auto trapexoid100 = riemann<integration_method::trapexoid, 100>(func, I(0), I(1)); 
    auto trapexoid1000 = riemann<integration_method::trapexoid, 1000>(func, I(0), I(1)); 
    auto trapexoid10000 = riemann<integration_method::trapexoid, 10000>(func, I(0), I(1)); 
    auto trapexoid100000 = riemann<integration_method::trapexoid, 100000>(func, I(0), I(1)); 
    print("int 2x from 0 to 1, 100 steps", trapexoid100); 
    print("int 2x from 0 to 1, 1000 steps", trapexoid1000); 
    print("int 2x from 0 to 1, 10000 steps", trapexoid10000); 
    print("int 2x from 0 to 1, 100000 steps", trapexoid100000); 

    print("testing the midpoint integration");
    auto midpoint100 = riemann<integration_method::midpoint, 100>(func, I); 
    auto midpoint1000 = riemann<integration_method::midpoint, 1000>(func, I); 
    auto midpoint10000 = riemann<integration_method::midpoint, 10000>(func, I); 
    auto midpoint100000 = riemann<integration_method::midpoint, 100000>(func, I); 
    print("int 2x from 0 to 1, 100 steps", midpoint100); 
    print("int 2x from 0 to 1, 1000 steps", midpoint1000); 
    print("int 2x from 0 to 1, 10000 steps", midpoint10000); 
    print("int 2x from 0 to 1, 100000 steps", midpoint100000); 

    print("testing the simpson integration");
    auto simpson100 = riemann<integration_method::simpson, 100>(func, I); 
    auto simpson1000 = riemann<integration_method::simpson, 1000>(func, I); 
    auto simpson10000 = riemann<integration_method::simpson, 10000>(func, I); 
    auto simpson100000 = riemann<integration_method::simpson, 100000>(func, I); 
    auto simpson1000000 = riemann<integration_method::simpson, 1000000>(func, I); 
    print("int 2x from 0 to 1, 100 steps", simpson100); 
    print("int 2x from 0 to 1, 1000 steps", simpson1000); 
    print("int 2x from 0 to 1, 10000 steps", simpson10000); 
    print("int 2x from 0 to 1, 100000 steps", simpson100000); 
    print("int 2x from 0 to 1, 1000000 steps", simpson1000000); 

    print("testing the simpson integration");
    auto simpson001 = riemann<integration_method::simpson>(func, I, 0.001); 
    auto simpson0001 = riemann<integration_method::simpson>(func, I, 0.0001); 
    auto simpson00001 = riemann<integration_method::simpson>(func, I, 0.00001); 
    auto simpson000001 = riemann<integration_method::simpson>(func, I, 0.000001); 
    auto simpson0000001 = riemann<integration_method::simpson>(func, I, 0.0000001); 
    print("int 2x from 0 to 1, 0.001 precision", simpson001); 
    print("int 2x from 0 to 1, 0.0001 precision", simpson0001); 
    print("int 2x from 0 to 1, 0.00001 precision", simpson00001); 
    print("int 2x from 0 to 1, 0.000001 precision", simpson000001); 
    print("int 2x from 0 to 1, 0.0000001 precision", simpson0000001); 

    auto func2 = myFUNC<position2>();

    // auto cframe = circumference(position2(), 1.m);

    // print("testing the lebesque integration");
    // auto lebesque100 = curvilinear(func2, cframe, 100); 
    // auto lebesque1000 = curvilinear(func2, cframe, 1000); 
    // auto lebesque10000 = curvilinear(func2, cframe, 10000); 
    // auto lebesque100000 = curvilinear(func2, cframe, 100000); 
    // auto lebesque1000000 = curvilinear(func2, cframe, 1000000); 
    // print("int x * y on a circumference in the origin and radius 1.0m, 100 steps", lebesque100); 
    // print("int x * y on a circumference in the origin and radius 1.0m, 1000 steps", lebesque1000); 
    // print("int x * y on a circumference in the origin and radius 1.0m, 10000 steps", lebesque10000); 
    // print("int x * y on a circumference in the origin and radius 1.0m, 100000 steps", lebesque100000); 
    // print("int x * y on a circumference in the origin and radius 1.0m, 1000000 steps", lebesque1000000); 

    // auto eframe = ellipse(position2(), 3.m, 1.m);
    // auto lebesque_100 = curvilinear(func2, eframe, 100); 
    // auto lebesque_1000 = curvilinear(func2, eframe, 1000); 
    // auto lebesque_10000 = curvilinear(func2, eframe, 10000); 
    // auto lebesque_100000 = curvilinear(func2, eframe, 100000); 
    // auto lebesque_1000000 = curvilinear(func2, eframe, 1000000); 
    // print("int x * y on an ellipse in the origin and a = 3.0m, b = 1.0 with 100 steps", lebesque_100); 
    // print("int x * y on an ellipse in the origin and a = 3.0m, b = 1.0 with 1000 steps", lebesque_1000); 
    // print("int x * y on an ellipse in the origin and a = 3.0m, b = 1.0 with 10000 steps", lebesque_10000); 
    // print("int x * y on an ellipse in the origin and a = 3.0m, b = 1.0 with 100000 steps", lebesque_100000); 
    // print("int x * y on an ellipse in the origin and a = 3.0m, b = 1.0 with 1000000 steps", lebesque_1000000); 

    // auto sframe = sphere(position3(), 1.m);
    // auto func3 = myFUNC<position3>();

    // auto SPHERE100 = curvilinear(func3, sframe, 100); 
    // auto SPHERE1000 = curvilinear(func3, sframe, 1000); 
    // auto SPHERE10000 = curvilinear(func3, sframe, 10000); 
    // auto SPHERE100000 = curvilinear(func3, sframe, 100000); 
    // auto SPHERE1000000 = curvilinear(func3, sframe, 1000000); 
    // print("int x * y on an sphere in the origin and r = 1.0m with 100 steps", SPHERE100); 
    // print("int x * y on an sphere in the origin and r = 1.0m with 1000 steps", SPHERE1000); 
    // print("int x * y on an sphere in the origin and r = 1.0m with 10000 steps", SPHERE10000); 
    // print("int x * y on an sphere in the origin and r = 1.0m with 100000 steps", SPHERE100000); 
    // print("int x * y on an sphere in the origin and r = 1.0m with 1000000 steps", SPHERE1000000); 


    return 0; 


}