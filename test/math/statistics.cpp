/**
 * @file    test/statistics.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-02
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

using namespace scipp; 
using namespace physics; 
using namespace math; 
using namespace tools; 


int main() {

    auto data = tools::read_measurements<length_m, 100000>("data/data.dat");

    std::cout << "dimension: " << data.dim << '\n'; 
    std::cout << "average: " << statistics::average(data) << '\n';
    std::cout << "median: " << statistics::median(data) << '\n';
    std::cout << "variance: " << statistics::variance(data) << '\n';
    std::cout << "stdev: " << statistics::stdev(data) << '\n';
    std::cout << "stdev_mean: " << statistics::stdev_mean(data) << "\n\n";


    auto data2 = tools::read_measurements<length_um, 3>("data/measurements.out");
    print("average", statistics::average(data2));
    print("median", statistics::median(data2)); 
    print("mean", statistics::mean(data2));
    print("variance", statistics::variance(data2), units::um2); 
    print("stdev", statistics::stdev(data2), units::um); 

    return 0; 

}