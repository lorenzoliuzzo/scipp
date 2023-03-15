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
    
    
    std::cout << sizeof(2.34m) << '\n'; 
    
    matrix<2, position3, position3> m1(position3(1.0m, 0.0m, 0.0m),
                                       position3(0.0m, 1.0m, 0.0m)); 
    m1.print();

    matrix m2(position3(1.0m, 0.0m, 0.0m),
              position3(0.0m, 1.0m, 0.0m),
              position3(0.0m, 0.0m, 1.0m));
    m2.print();

    matrix m3 = make_matrix(position3(1.0m, 0.0m, 0.0m),
                            position3(0.0m, 1.0m, 0.0m),
                            lin_velocity3(0.0 * m_s, 0.0 * m_s, 1.0 * m_s));
    m3.print();

    matrix m4 = make_matrix<position3>(position3(-1.0m, 0.0m, 0.0m),
                                       position3(0.0m, -1.0m, 0.0m),
                                       position3(0.0m, 0.0m, -1.0m));

    m4.print();

    matrix m5 = make_matrix<3, position3>(position3(-1.0m, 0.0m, 0.0m),
                                          position3(0.0m, -1.0m, 0.0m),
                                          position3(0.0m, 0.0m, -1.0m));

    m5.print();


    m4.column<0>() = position3(1.0m, 0.0m, 0.0m);
    std::cout << m4.column<0>() << '\n' << '\n';


    m1.augment(m4.column<0>()).print();
    std::cout << '\n'; 

    m1.print(); 


    // matrix<2, position3>().column<1>().print();
    make_matrix<2, position3, position3>().column<1>().print();
    m4.element<0, 0>() = 0.0m;
    m4.print();

    std::cout << "zero matrix: " << '\n';
    // make_matrix<2, position3, position3>()zero.print();


    return 0; 

}