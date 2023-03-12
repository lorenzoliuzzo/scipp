/**
 * @file    matrix.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Example of matrix constructions
 * @date    2023-02-12
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp; 
using namespace physics; 
using namespace physics::units; 
using namespace geometry;


int main() {
    
    
    // matrix m1 = make_matrix<position3, position3, lin_velocity3>(position3(1.0m, 0.0m, 0.0m),
    //                       position3(0.0m, 1.0m, 0.0m),
    //                       lin_velocity3(0.0 * units::m_s, 0.0 * units::m_s, 1.0 * units::m_s)); 
    // m1.print(); 


    matrix m1(position3(1.0m, 0.0m, 0.0m),
              position3(0.0m, 1.0m, 0.0m),
              position3(0.0m, 0.0m, 1.0m));
    m1.print();

    // matrix<3, position3> m2(position3(1.0m, 0.0m, 0.0m),
    //                         position3(0.0m, 1.0m, 0.0m),
    //                         position3(0.0m, 0.0m, 1.0m));
    // m2.print();

    matrix<3, position3, position3, lin_velocity3> m3(position3(1.0m, 0.0m, 0.0m),
                                                      position3(0.0m, 1.0m, 0.0m),
                                                      lin_velocity3(0.0 * units::m_s, 0.0 * units::m_s, 1.0 * units::m_s));
    m3.print();

    matrix m4 = make_matrix<position3>(position3(-1.0m, 0.0m, 0.0m),
                                       position3(0.0m, -1.0m, 0.0m),
                                       position3(0.0m, 0.0m, -1.0m));

    m4.print();


    return 0; 

}