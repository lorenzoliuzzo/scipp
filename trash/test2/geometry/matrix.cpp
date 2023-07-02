/**
 * @file    matrix.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Example of matrix constructions
 * @date    2023-03-19
 * 
 * @copyright Copyright (c) 2023
 */


#include "scipp"
#include <cassert>
#include <thread>

using namespace scipp; 
using namespace physics; 
using namespace physics::units; 
using namespace math; 
using namespace geometry;
using namespace tools;


int main() {

    auto mat1 = make_matrix(position2(3.m, 1.m), position2(-1.m, -3.m));
                                          
    auto mat2 = make_matrix(position2(0.0m, 1.0m), position2(1.0m, -2.m));

    auto mat3 = mat1 * mat2;

    print("mat1", mat1);
    print("mat2", mat2);
    print("mat3", mat3);


    return 0; 

}