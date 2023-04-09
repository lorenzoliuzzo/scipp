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
using namespace geometry; 
using namespace tools;


template <typename MEAS_TYPE>
    requires (is_generic_measurement_v<MEAS_TYPE>)
struct andrea : functions::unary_function<MEAS_TYPE, MEAS_TYPE> {

    constexpr MEAS_TYPE operator()(const MEAS_TYPE& x) const noexcept override {

        return 2 * x; 

    } 

};


template <typename VECTOR_TYPE>
    requires (is_vector_v<VECTOR_TYPE>)
struct myFUNC : functions::unary_function<op::measurement_square_t<typename VECTOR_TYPE::measurement_type>, VECTOR_TYPE> {

    constexpr op::measurement_square_t<typename VECTOR_TYPE::measurement_type> operator()(const VECTOR_TYPE& other) const noexcept override {

        return op::square(other.x()) + op::square(other.y());

    } 

};


template <typename VECTOR_TYPE>
    requires (is_vector_v<VECTOR_TYPE>)
struct myFUNC2 : functions::unary_function<op::measurement_inv<typename VECTOR_TYPE::measurement_type>, VECTOR_TYPE> {

    constexpr op::measurement_inv<typename VECTOR_TYPE::measurement_type> operator()(const VECTOR_TYPE& other) const noexcept override {

        return (other.x() - other.y()) / (op::square(other.x()) + op::square(other.y()));

    } 

};


// template <typename VECTOR_TYPE>
//     requires (is_vector_v<VECTOR_TYPE>)
// struct vortex : unary_function<op::measurement_inv<typename VECTOR_TYPE::measurement_type>, VECTOR_TYPE> {

//     constexpr op::measurement_inv<typename VECTOR_TYPE::measurement_type> operator()(const VECTOR_TYPE& other) const noexcept override {

//         return (other.x() - other.y()) / (op::square(other.x()) + op::square(other.y()));

//     } 

// };


int main() {


    interval I(0.0m, 1.0m); 
    print(I(0)); 
    print(I(1)); 


    tools::timer t; 
    t.start(); 
    t.stop(); 

    auto func = andrea<length_m>();

    print("testing the rectangle integration");
    auto rectangle100 = integrals::riemann(func, 0.m, 1.m, integrals::method::rectangle, 100); 
    auto rectangle1000 = integrals::riemann(func, 0.m, 1.m, integrals::method::rectangle, 1000); 
    auto rectangle10000 = integrals::riemann(func, 0.m, 1.m, integrals::method::rectangle, 10000); 
    auto rectangle100000 = integrals::riemann(func, 0.m, 1.m, integrals::method::rectangle, 100000); 
    print("int 2x from 0 to 1, 100 steps", rectangle100); 
    print("int 2x from 0 to 1, 1000 steps", rectangle1000); 
    print("int 2x from 0 to 1, 10000 steps", rectangle10000); 
    print("int 2x from 0 to 1, 100000 steps", rectangle100000); 


    print("testing the trapexoid integration");
    auto trapexoid100 = integrals::riemann(func, 0.m, 1.m, integrals::method::trapexoid, 100); 
    auto trapexoid1000 = integrals::riemann(func, 0.m, 1.m, integrals::method::trapexoid, 1000); 
    auto trapexoid10000 = integrals::riemann(func, 0.m, 1.m, integrals::method::trapexoid, 10000); 
    auto trapexoid100000 = integrals::riemann(func, 0.m, 1.m, integrals::method::trapexoid, 100000); 
    print("int 2x from 0 to 1, 100 steps", trapexoid100); 
    print("int 2x from 0 to 1, 1000 steps", trapexoid1000); 
    print("int 2x from 0 to 1, 10000 steps", trapexoid10000); 
    print("int 2x from 0 to 1, 100000 steps", trapexoid100000); 

    print("testing the midpoint integration");
    auto midpoint100 = integrals::riemann(func, 0.m, 1.m, integrals::method::midpoint, 100); 
    auto midpoint1000 = integrals::riemann(func, 0.m, 1.m, integrals::method::midpoint, 1000); 
    auto midpoint10000 = integrals::riemann(func, 0.m, 1.m, integrals::method::midpoint, 10000); 
    auto midpoint100000 = integrals::riemann(func, 0.m, 1.m, integrals::method::midpoint, 100000); 
    print("int 2x from 0 to 1, 100 steps", midpoint100); 
    print("int 2x from 0 to 1, 1000 steps", midpoint1000); 
    print("int 2x from 0 to 1, 10000 steps", midpoint10000); 
    print("int 2x from 0 to 1, 100000 steps", midpoint100000); 

    print("testing the simpson integration");
    auto simpson100 = integrals::riemann(func, I(0), I(1), integrals::method::simpson, 100); 
    auto simpson1000 = integrals::riemann(func, I(0), I(1), integrals::method::simpson, 1000); 
    auto simpson10000 = integrals::riemann(func, I(0), I(1), integrals::method::simpson, 10000); 
    auto simpson100000 = integrals::riemann(func, I(0), I(1), integrals::method::simpson, 100000); 
    auto simpson1000000 = integrals::riemann(func, I(0), I(1), integrals::method::simpson, 1000000); 
    print("int 2x from 0 to 1, 100 steps", simpson100); 
    print("int 2x from 0 to 1, 1000 steps", simpson1000); 
    print("int 2x from 0 to 1, 10000 steps", simpson10000); 
    print("int 2x from 0 to 1, 100000 steps", simpson100000); 
    print("int 2x from 0 to 1, 1000000 steps", simpson1000000); 


    auto func2 = myFUNC<position2>();

    auto cframe = circumference(position2(), 1.m);

    print("testing the lebesque integration");
    auto lebesque100 = integrals::curvilinear(func2, cframe, 100); 
    auto lebesque1000 = integrals::curvilinear(func2, cframe, 1000); 
    auto lebesque10000 = integrals::curvilinear(func2, cframe, 10000); 
    auto lebesque100000 = integrals::curvilinear(func2, cframe, 100000); 
    auto lebesque1000000 = integrals::curvilinear(func2, cframe, 1000000); 
    print("int x * y on a circumference in the origin and radius 1.0m, 100 steps", lebesque100); 
    print("int x * y on a circumference in the origin and radius 1.0m, 1000 steps", lebesque1000); 
    print("int x * y on a circumference in the origin and radius 1.0m, 10000 steps", lebesque10000); 
    print("int x * y on a circumference in the origin and radius 1.0m, 100000 steps", lebesque100000); 
    print("int x * y on a circumference in the origin and radius 1.0m, 1000000 steps", lebesque1000000); 

    auto eframe = ellipse(position2(), 3.m, 1.m);
    auto lebesque_100 = integrals::curvilinear(func2, eframe, 100); 
    auto lebesque_1000 = integrals::curvilinear(func2, eframe, 1000); 
    auto lebesque_10000 = integrals::curvilinear(func2, eframe, 10000); 
    auto lebesque_100000 = integrals::curvilinear(func2, eframe, 100000); 
    auto lebesque_1000000 = integrals::curvilinear(func2, eframe, 1000000); 
    print("int x * y on an ellipse in the origin and a = 3.0m, b = 1.0 with 100 steps", lebesque_100); 
    print("int x * y on an ellipse in the origin and a = 3.0m, b = 1.0 with 1000 steps", lebesque_1000); 
    print("int x * y on an ellipse in the origin and a = 3.0m, b = 1.0 with 10000 steps", lebesque_10000); 
    print("int x * y on an ellipse in the origin and a = 3.0m, b = 1.0 with 100000 steps", lebesque_100000); 
    print("int x * y on an ellipse in the origin and a = 3.0m, b = 1.0 with 1000000 steps", lebesque_1000000); 

    auto sframe = sphere(position3(), 1.m);
    auto func3 = myFUNC<position3>();

    auto SPHERE100 = integrals::curvilinear(func3, sframe, 100); 
    auto SPHERE1000 = integrals::curvilinear(func3, sframe, 1000); 
    auto SPHERE10000 = integrals::curvilinear(func3, sframe, 10000); 
    auto SPHERE100000 = integrals::curvilinear(func3, sframe, 100000); 
    auto SPHERE1000000 = integrals::curvilinear(func3, sframe, 1000000); 
    print("int x * y on an sphere in the origin and r = 1.0m with 100 steps", SPHERE100); 
    print("int x * y on an sphere in the origin and r = 1.0m with 1000 steps", SPHERE1000); 
    print("int x * y on an sphere in the origin and r = 1.0m with 10000 steps", SPHERE10000); 
    print("int x * y on an sphere in the origin and r = 1.0m with 100000 steps", SPHERE100000); 
    print("int x * y on an sphere in the origin and r = 1.0m with 1000000 steps", SPHERE1000000); 


    return 0; 


}