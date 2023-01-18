/**
 * @file    bench++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the benchmarks of the measurements library
 * @date    2023-01-14
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

using namespace scipp; 


int main() {
    
    tools::timer stopwatch;
    tools::cpu_timer stopwatch2;
    for (int i{}; i < 10; ++i) {

        stopwatch.start();
        stopwatch.stop();
        stopwatch2.start();
        stopwatch2.stop();

        std::cout << "timer overhead: \t" << stopwatch.elapsed(ns) << "\n";
        std::cout << "CPU timer overhead:\t" << stopwatch2.elapsed(ns) << "\n";

    }


    return 0; 

}