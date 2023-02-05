/**
 * @file    statistics.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-24
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp; 


int main() {

    std::vector<time_m> time_vector; 
    tools::cpu_timer timer; 

    for (std::size_t i{}; i < 100; ++i)
        time_vector.emplace_back(i * s); 

    timer.start(); 
    time_um result = math::statistics::mean(time_vector); 
    timer.stop(); 

    std::cout << result << " -> ";
    std::cout << result.value() << '\t' << result.uncertainty() << '\n';
    std::cout << "elapsed: " << timer.elapsed() << '\n'; 

    
    // std::cout << "sd: " << math::statistics::sd(time_vector) << '\n'; 

    
    return 0; 

}