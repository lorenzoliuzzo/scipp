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
using namespace geometry;


int main() {
    
    
    auto m1 = make_matrix(position3(1.0m, 0.0m, 0.0m),
                          position3(0.0m, 1.0m, 0.0m),
                          lin_velocity3(0.0 * units::m_s, 0.0 * units::m_s, 1.0 * units::m_s)); 
    m1.print(); 

    matrix m2 = make_matrix<position3>(position3(-1.0m, 0.0m, 0.0m),
                                       position3(0.0m, -1.0m, 0.0m),
                                       position3(0.0m, 0.0m, -1.0m));

    m2.print();

    matrix m3 = make_matrix<position3, lin_velocity3, lin_acceleration3>(position3(1.0m, 0.0m, 0.0m),
                                                               lin_velocity3(0.0 * units::m_s, 0.0 * units::m_s, 3.0 * units::m_s),
                                                               lin_acceleration3(0.0 * units::m_ss, 0.0 * units::m_ss, 3.0 * units::m_ss));

    m3.print();


    matrix<3, position3, position3, lin_velocity3> m4(position3(1.0m, 0.0m, 0.0m),
                                                      position3(0.0m, 1.0m, 0.0m),
                                                      lin_velocity3(0.0 * units::m_s, 0.0 * units::m_s, 3.0 * units::m_s));

    m4.print();


    matrix m5(position3(1.0m, 0.0m, 0.0m),
              position3(0.0m, 1.0m, 0.0m),
              lin_velocity3(13.0 * units::m_s, 0.0 * units::m_s, 3.0 * units::m_s));

    m5.print();


    auto m6 = m5; 

    std::cout << '\n';
    m6.print();


    // auto m7 = m6.augment(position3()); 

    // std::cout << '\n';
    // m7.print();

    return 0; 

}