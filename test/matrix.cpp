/**
 * @file    matrix.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Example of matrix constructions
 * @date    2023-03-17
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp; 
using namespace physics; 
using namespace physics::units; 
using namespace geometry;


int main() {
    
    
    std::cout << "sizeof matrix 2x2: " << sizeof(matrix<2, position2, position2>) << " bytes\n"; 
    std::cout << "sizeof matrix 3x3: " << sizeof(matrix<3, position3, position3, position3>) << " bytes\n";


    std::cout << "number of rows: " << matrix<2, position3, position3>::rows << '\n';
    std::cout << "number of columns: " << matrix<2, position3, position3>::columns << '\n';

    
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


    matrix m6 = m4 + m5; 
    m6.print();

    m6 -= m4;
    m6.print();

    (-m6).print();

    (m6 * 23.0).print();





    // m4.column<0>() = position3(1.0m, 0.0m, 0.0m);
    // std::cout << m4.column<0>() << '\n' << '\n';


    // m1.augment(m4.column<0>()).print();
    // std::cout << '\n'; 

    // m1.print(); 


    // // matrix<2, position3>().column<1>().print();
    // make_matrix<2, position3, position3>().column<1>().print();
    // m4.element<0, 0>() = 0.0m;
    // m4.print();

    // std::cout << "zero matrix: " << '\n';
    // // make_matrix<2, position3, position3>()zero.print();


    return 0; 

}