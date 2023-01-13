/**
 * @file    sci++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Test file for sci++ library
 * @date    2023-01-01
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

using namespace scipp; 


int main(int argc, char** argv) {


    uint64_t n = std::atoi(argv[1]);
    tools::timer stopwatch;

    time_umeasurement mean_time;

    double d1{3.1};    
    double d2{4.5};

    stopwatch.start();
    mean_time = tools::bench(n, [&]() { auto x = d1 + d2; }, ns);
    stopwatch.stop();
    std::cout << "Mean time of double sum: " << mean_time << '\n';
    std::cout << "Elapsed time: " << stopwatch.elapsed(s) << '\n';

    stopwatch.start();
    mean_time = tools::bench(n, [&]() { auto x = d1 * d2; }, ns);
    stopwatch.stop();
    std::cout << "Mean time of double multiplication: " << mean_time << '\n';
    std::cout << "Elapsed time: " << stopwatch.elapsed(s) << '\n';


    measurement m1(3.1 * m);    
    measurement m2(4.5 * m);

    stopwatch.start();
    mean_time = tools::bench(n, [&]() { auto x = m1 + m2; }, ns);
    stopwatch.stop();
    std::cout << "Mean time of measurement sum: " << mean_time << '\n';
    std::cout << "Elapsed time: " << stopwatch.elapsed(s) << '\n';

    stopwatch.start();
    mean_time = tools::bench(n, [&]() { auto x = m1 * m2; }, ns);
    stopwatch.stop();
    std::cout << "Mean time of measurement multiplication: " << mean_time << '\n';
    std::cout << "Elapsed time: " << stopwatch.elapsed(s) << '\n';


    umeasurement um1(3.1 * m, 0.8 * m);    
    umeasurement um2(4.5 * m, 0.6 * m);

    stopwatch.start();
    mean_time = tools::bench(n, [&]() { auto x = um1 + um2; }, ns);
    stopwatch.stop();
    std::cout << "Mean time of umeasurement sum: " << mean_time << '\n';
    std::cout << "Elapsed time: " << stopwatch.elapsed(s) << '\n';

    stopwatch.start();
    mean_time = tools::bench(n, [&]() { auto x = um1 * um2; }, ns);
    stopwatch.stop();
    std::cout << "Mean time of umeasurement multiplication: " << mean_time << '\n';
    std::cout << "Elapsed time: " << stopwatch.elapsed(s) << '\n';


    return 0; 

}