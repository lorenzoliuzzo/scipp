/**
 * @file    test/complex.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-03
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


#include <external/matplotlibcpp.h>
namespace plt = matplotlibcpp;


// struct complex_cosh : meta::unary_function<cmeasurement<scalar_m>, cmeasurement<scalar_m>> {

    
//     constexpr cmeasurement<scalar_m> f(const cmeasurement<scalar_m>& x) const noexcept override {

//         return op::cosh(x);

//     }


// };


int main() {


    scalar_m radius = 1.0;
    auto circ = circumference(cmeasurement<scalar_m>(), radius);
    print("circumference", circ(0));
    print("circumference", circ(0.50));
    print("circumference", circ(1));

    print(std::numeric_limits<double>::epsilon());
    print(std::numeric_limits<long double>::epsilon());
    print(std::numeric_limits<float>::epsilon());
    print(sizeof(long double)); 
    // vector<scalar_m, 100> x_vec;
    // vector<scalar_m, 100> y_vec;

    // for (std::size_t i = 0; i < 100; ++i) {

    //     auto p = circ(static_cast<double>(i) / 100.0);
    //     x_vec[i] = p.real;
    //     y_vec[i] = p.imag;

    // }

    // plt::title("Circumference in C");
    // plt::plot(static_cast<std::vector<double>>(x_vec), static_cast<std::vector<double>>(y_vec), "r");
    // plt::show(); 
    

    // vector<scalar_m, 2> p0;
    // auto circ2 = circumference(p0, radius);

    // for (std::size_t i = 0; i < 100; ++i) {

    //     auto p = circ2(static_cast<double>(i) / 100.0);
    //     x_vec[i] = p[0];
    //     y_vec[i] = p[1];

    // }

    // plt::title("Circumference in R2");
    // plt::plot(static_cast<std::vector<double>>(x_vec), static_cast<std::vector<double>>(y_vec), "r");
    // plt::show(); 


    // auto result = integrals::curvilinear(complex_cosh(), circ);
    // print("log(r)", result);


    return 0; 

}



    // cmeasurement<angle_m> mc0(3. * rad, 4. * rad);
    // print("real", mc0.real);
    // print("imag", mc0.imag);


    // print("abs", op::abs(mc0)); 
    // print("arg", op::arg(mc0)); 
    // print("norm", op::norm(mc0)); 
    // print("conj", op::conj(mc0)); 
    // print("cos", op::cos(mc0)); 

    // print("3^i", op::pow({1.0, 0.5}, math::constants::i));


    // auto integral = integrals::curvilinear(cmeasurement_cos(), geometry::circumference(cmeasurement<length_m>(), 1.0 * m));
    // print("integrate(cos, (0.0, 0.0) -> (2pi, 0))", integral);


    // auto Rmat = make_matrix<vector<scalar_m, 2>, 2>(make_vector(static_cast<scalar_m>(1.0), static_cast<scalar_m>(0.0)), 
    //                                                 make_vector(static_cast<scalar_m>(0.0), static_cast<scalar_m>(1.0)));

    // auto Cmat = make_matrix<vector<scalar_m, 2>, 2>(make_vector(static_cast<scalar_m>(0.0), static_cast<scalar_m>(-1.0)), 
    //                                                 make_vector(static_cast<scalar_m>(1.0), static_cast<scalar_m>(0.0)));
    
    // print("Rmat", Rmat);
    // print("Cmat", Cmat);

    // cmeasurement<scalar_m> r(1.0, 4.0); 
    // auto r_mat = Rmat * r.real + Cmat * r.imag;
    // print("r", r);
    // print("in matrix form", r_mat); 

    // cmeasurement<scalar_m> c(5.0, -3.0);
    // auto c_mat = Rmat * c.real + Cmat * c.imag;
    // print("c", c);
    // print("in matrix form", c_mat);

    // print("r * c", r * c);
    // print("in matrix form", r_mat * c_mat);
