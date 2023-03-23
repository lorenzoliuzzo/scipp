/**
 * @file    test/statistics.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-23
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

using namespace scipp; 
using namespace physics; 
using namespace units;
using namespace math; 


int main() {

    auto data = tools::read_measurements<length_m, 100000>("data.dat");

    std::cout << "dimension: " << data.dim << '\n'; 
    std::cout << "average: " << statistics::average(data) << '\n';
    std::cout << "median: " << statistics::median(data) << '\n';
    std::cout << "variance: " << statistics::variance(data) << '\n';
    std::cout << "stdev: " << statistics::stdev(data) << '\n';
    std::cout << "stdev_mean: " << statistics::stdev_mean(data) << "\n\n";


    auto data2 = tools::read_measurements<length_um, 3>("measurements.out");
    std::cout << "average: " << statistics::average(data2) << '\n';
    std::cout << "median: " << statistics::median(data2) << '\n'; 
    std::cout << "mean: " << statistics::mean(data2) << '\n';
    std::cout << "variance: "; 
    statistics::variance(data2).print_as(um2); 
    std::cout << "stdev: "; 
    statistics::stdev(data2).print_as(um); 

    return 0; 

}