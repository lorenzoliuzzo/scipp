/**
 * @file    sci++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Test file for sci++ library
 * @date    2023-01-01
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"
#include "../plot/matplotlibcpp.h"


using namespace scipp; 
namespace plt = matplotlibcpp;


int main(int argc, char** argv) {


    tools::timer stopwatch;
    tools::cpu_timer stopwatch2;
    time_umeasurement mean_time;

    double d1{3.1};    
    double d2{4.5};
    measurement m1(3.1 * m);    
    measurement m2(4.5 * m);
    umeasurement um1(3.1 * m, 0.8 * m);    
    umeasurement um2(4.5 * m, 0.6 * m);

    std::vector<std::size_t> iterations;
    std::vector<double> double_sum_times;
    std::vector<double> measurement_sum_times;
    std::vector<double> umeasurement_sum_times;
    std::vector<double> double_prod_times;
    std::vector<double> measurement_prod_times;
    std::vector<double> umeasurement_prod_times;

 
    std::cout << "Testing the performarce of the measurements library\n"; 

    for (std::size_t n{1}; n <= 1e9; n *= 10) {

        iterations.emplace_back(n);
    
        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = d1 + d2; }, ns);
        stopwatch.stop();
        double_sum_times.emplace_back(mean_time.value());
        // std::cout << "Mean time for a single double sum:\t\t\t" << mean_time << '\n';
        // std::cout << "Elapsed time: " << stopwatch.elapsed(s) << '\n';

        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = m1 + m2; }, ns);
        stopwatch.stop();
        measurement_sum_times.emplace_back(mean_time.value());
        // std::cout << "Mean time for a single measurement sum:\t\t\t" << mean_time << '\n';
        // std::cout << "Elapsed time: " << stopwatch.elapsed(s) << '\n';

        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = um1 + um2; }, ns);
        stopwatch.stop();
        umeasurement_sum_times.emplace_back(mean_time.value());
        // std::cout << "Mean time for a single umeasurement sum:\t\t" << mean_time << '\n';
        // std::cout << "Elapsed time: " << stopwatch.elapsed(s) << '\n';


        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = d1 * d2; }, ns);
        stopwatch.stop();
        double_prod_times.emplace_back(mean_time.value());
        // std::cout << "Mean time for a single double multiplication:\t\t" << mean_time << '\n';
        // std::cout << "Elapsed time: " << stopwatch.elapsed(s) << '\n';

        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = m1 * m2; }, ns);
        stopwatch.stop();
        measurement_prod_times.emplace_back(mean_time.value());
        // std::cout << "Mean time for a single measurement multiplication:\t" << mean_time << '\n';
        // std::cout << "Elapsed time: " << stopwatch.elapsed(s) << '\n';

        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = um1 * um2; }, ns);
        stopwatch.stop();
        umeasurement_prod_times.emplace_back(mean_time.value());
        // std::cout << "Mean time for a single umeasurement multiplication:\t" << mean_time << '\n';
        // std::cout << "Elapsed time: " << stopwatch.elapsed(s) << '\n';

    }

    plt::figure();
    plt::title("Sum");
    plt::named_plot("double", iterations, double_sum_times);
    plt::named_plot("measurement", iterations, measurement_sum_times);
    plt::named_plot("umeasurement", iterations, umeasurement_sum_times);
    plt::legend();
    plt::show();

    plt::figure();
    plt::title("Product");
    plt::named_plot("double", iterations, double_prod_times);
    plt::named_plot("measurement", iterations, measurement_prod_times);
    plt::named_plot("umeasurement", iterations, umeasurement_prod_times);
    plt::legend();
    plt::show();
    

    return 0; 

}