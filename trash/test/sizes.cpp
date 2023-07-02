/**
 * @file    sizes.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-20
 * 
 * @copyright Copyright (c) 2023
 */


#include "scipp"


using namespace scipp; 


int main() {


    std::cout << "Printing the size of scipp::measurements types...\n";

    std::cout << "measurement: " << sizeof(length_m) << " bytes\n";
    std::cout << "umeasurement: " << sizeof(mass_um) << " bytes\n";
    std::cout << "vector<2>: " << sizeof(physics::position2) << " bytes\n";
    std::cout << "vector<3>: " << sizeof(physics::position3) << " bytes\n";
    std::cout << "vector<100>: " << sizeof(geometry::vector<basis::kilogram, 100>) << " bytes\n";


    return 0;

}
