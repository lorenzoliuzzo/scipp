/**
 * @file    matrix.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Example of matrix constructions
 * @date    2023-03-19
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

using namespace scipp; 
using namespace physics; 
using namespace physics::units; 
using namespace math; 
using namespace geometry;


int main() {
    
    
    std::cout << "sizeof matrix 2x2: " << sizeof(matrix<position2, 2>) << " bytes\n"; 
    std::cout << "sizeof matrix 3x3: " << sizeof(matrix<position3, 3>) << " bytes\n\n";

    auto mat1 = make_matrix<position2, 2>(position2(3.0m, 0.4m), 
                                          position2(-1.02m, -3.54m));

    auto mat2 = make_matrix<position2>(position2(3.0m, 0.4m), 
                                       position2(-1.02m, -3.54m), 
                                       position2(-1.0m, 0.5m)); 


    mat1.print(); 
    mat2.print(); 

    (-mat2).print(); 
    (mat2 * 2.0).print(); 
    (mat2 * 2.0m).print(); 
    mat2.transpose().print(); 

    auto id2 = make_matrix<position2, 2>(position2(1.0m, 0.0m), position2(0.0m, 1.0m)); 
    (id2 * position2(3.0m, -3.0m)).print(); 

    auto id3 = matrix<position3, 3>::identity(); 
    id3.print(); 
    id3.determinant().print();


    matrix<vector<length_m, 4>, 4> mat4;

    mat4.print();
    mat4.determinant().print();

    decltype(mat4)::identity().determinant().print(); 
    decltype(mat4)::identity().trace().print(); 

    mat1.inverse().print();
    mat1.cofactors().print();


    return 0; 

}