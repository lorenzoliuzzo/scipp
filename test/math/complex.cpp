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



int main() {


    complex<angle_m> mc0(3. * rad, 4. * rad);
    print("real", mc0.real);
    print("imag", mc0.imag);


    // print("abs", op::abs(mc0)); 
    // print("arg", op::arg(mc0)); 
    // print("norm", op::norm(mc0)); 
    // print("conj", op::conj(mc0)); 
    // print("cos", op::cos(mc0)); 

    // print("3^i", op::pow({1.0, 0.5}, math::constants::i));


    // auto integral = integrals::curvilinear(complex_cos(), geometry::circumference(complex<length_m>(), 1.0 * m));
    // print("integrate(cos, (0.0, 0.0) -> (2pi, 0))", integral);


    auto Rmat = make_matrix<vector<scalar_m, 2>, 2>(make_vector(static_cast<scalar_m>(1.0), static_cast<scalar_m>(0.0)), 
                                                    make_vector(static_cast<scalar_m>(0.0), static_cast<scalar_m>(1.0)));

    auto Cmat = make_matrix<vector<scalar_m, 2>, 2>(make_vector(static_cast<scalar_m>(0.0), static_cast<scalar_m>(-1.0)), 
                                                    make_vector(static_cast<scalar_m>(1.0), static_cast<scalar_m>(0.0)));
    
    print("Rmat", Rmat);
    print("Cmat", Cmat);

    complex<scalar_m> r(1.0, 4.0); 
    auto r_mat = Rmat * r.real + Cmat * r.imag;
    print("r", r);
    print("in matrix form", r_mat); 

    complex<scalar_m> c(5.0, -3.0);
    auto c_mat = Rmat * c.real + Cmat * c.imag;
    print("c", c);
    print("in matrix form", c_mat);

    print("r * c", r * c);
    print("in matrix form", r_mat * c_mat);




    return 0; 

}