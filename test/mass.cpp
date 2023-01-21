/**
 * @file    mamss.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-21
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp;
using namespace scipp::physics;


int main() {


    mass<2> obj(345.3 * kg, position2(1.0 * m, 2.0 * m));

    obj.print();

    





    return 0;

}