/**
 * @file    bench++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the benchmarks of the measurements library
 * @date    2023-01-01
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"
#include "../plot/gplot++.hpp"
#include <thread>


using namespace scipp; 


std::pair<std::vector<double>, std::vector<double>> bench_double_sum(const std::size_t& n) {

    double a = std::rand() % 10000 + 1;
    double b = std::rand() % 10000 + 1;

    std::vector<double> times_value, times_uncertainty; 
    for (double i{64}; i < n; i *= 2) {
        umeasurement mean_time = tools::cpu_bench(i, [&]() { auto x = a + b; });
        times_value.emplace_back(mean_time.value_as(ns)); 
        times_uncertainty.emplace_back(mean_time.uncertainty_as(ns));
    } 
    
    return { times_value, times_uncertainty };

}

std::pair<std::vector<double>, std::vector<double>> bench_double_prod(const std::size_t& n) {

    double a = std::rand() % 10000 + 1;
    double b = std::rand() % 10000 + 1;

    std::vector<double> times_value, times_uncertainty; 
    for (double i{64}; i < n; i *= 2) {
        umeasurement mean_time = tools::cpu_bench(i, [&]() { auto x = a * b; });
        times_value.emplace_back(mean_time.value_as(ns)); 
        times_uncertainty.emplace_back(mean_time.uncertainty_as(ns));
    } 
    
    return { times_value, times_uncertainty };

}

std::pair<std::vector<double>, std::vector<double>> bench_double_div(const std::size_t& n) {

    double a = std::rand() % 10000 + 1;
    double b = std::rand() % 10000 + 1;

    std::vector<double> times_value, times_uncertainty; 
    for (double i{64}; i < n; i *= 2) {
        umeasurement mean_time = tools::cpu_bench(i, [&]() { auto x = a / b; });
        times_value.emplace_back(mean_time.value_as(ns)); 
        times_uncertainty.emplace_back(mean_time.uncertainty_as(ns));
    } 
    
    return { times_value, times_uncertainty };

}


std::pair<std::vector<double>, std::vector<double>> bench_measurement_sum(const std::size_t& n) {

    measurement a = (std::rand() % 10000 + 1) * N;
    measurement b = (std::rand() % 10000 + 1) * N;

    std::vector<double> times_value, times_uncertainty; 
    for (double i{64}; i < n; i *= 2) {
        umeasurement mean_time = tools::cpu_bench(i, [&]() { auto x = a + b; });
        times_value.emplace_back(mean_time.value_as(ns)); 
        times_uncertainty.emplace_back(mean_time.uncertainty_as(ns));
    } 
    
    return { times_value, times_uncertainty };

}

std::pair<std::vector<double>, std::vector<double>> bench_measurement_prod(const std::size_t& n) {

    measurement a = (std::rand() % 10000 + 1) * N;
    measurement b = (std::rand() % 10000 + 1) * N;

    std::vector<double> times_value, times_uncertainty; 
    for (double i{64}; i < n; i *= 2) {
        umeasurement mean_time = tools::cpu_bench(i, [&]() { auto x = a * b; });
        times_value.emplace_back(mean_time.value_as(ns)); 
        times_uncertainty.emplace_back(mean_time.uncertainty_as(ns));
    } 
    
    return { times_value, times_uncertainty };

}

std::pair<std::vector<double>, std::vector<double>> bench_measurement_div(const std::size_t& n) {

    measurement a = (std::rand() % 10000 + 1) * N;
    measurement b = (std::rand() % 10000 + 1) * N;

    std::vector<double> times_value, times_uncertainty; 
    for (double i{64}; i < n; i *= 2) {
        umeasurement mean_time = tools::cpu_bench(i, [&]() { auto x = a / b; });
        times_value.emplace_back(mean_time.value_as(ns)); 
        times_uncertainty.emplace_back(mean_time.uncertainty_as(ns));
    } 
    
    return { times_value, times_uncertainty };

}


std::pair<std::vector<double>, std::vector<double>> bench_umeasurement_sum(const std::size_t& n) {

    umeasurement a = ((std::rand() % 10000 + 1) * N, (std::rand() % 100 + 1) * N);
    umeasurement b = ((std::rand() % 10000 + 1) * N, (std::rand() % 100 + 1) * N);

    std::vector<double> times_value, times_uncertainty; 
    for (double i{64}; i < n; i *= 2) {
        umeasurement mean_time = tools::cpu_bench(i, [&]() { auto x = a + b; });
        times_value.emplace_back(mean_time.value_as(ns)); 
        times_uncertainty.emplace_back(mean_time.uncertainty_as(ns));
    } 
    
    return { times_value, times_uncertainty };

}

std::pair<std::vector<double>, std::vector<double>> bench_umeasurement_prod(const std::size_t& n) {

    umeasurement a = ((std::rand() % 10000 + 1) * N, (std::rand() % 100 + 1) * N);
    umeasurement b = ((std::rand() % 10000 + 1) * N, (std::rand() % 100 + 1) * N);

    std::vector<double> times_value, times_uncertainty; 
    for (double i{64}; i < n; i *= 2) {
        umeasurement mean_time = tools::cpu_bench(i, [&]() { auto x = a * b; });
        times_value.emplace_back(mean_time.value_as(ns)); 
        times_uncertainty.emplace_back(mean_time.uncertainty_as(ns));
    } 
    
    return { times_value, times_uncertainty };

}

std::pair<std::vector<double>, std::vector<double>> bench_umeasurement_div(const std::size_t& n) {

    umeasurement a = ((std::rand() % 10000 + 1) * N, (std::rand() % 100 + 1) * N);
    umeasurement b = ((std::rand() % 10000 + 1) * N, (std::rand() % 100 + 1) * N);

    std::vector<double> times_value, times_uncertainty; 
    for (double i{64}; i < n; i *= 2) {
        umeasurement mean_time = tools::cpu_bench(i, [&]() { auto x = a / b; });
        times_value.emplace_back(mean_time.value_as(ns)); 
        times_uncertainty.emplace_back(mean_time.uncertainty_as(ns));
    } 
    
    return { times_value, times_uncertainty };

}


void bench_sum() {

    std::vector<double> iterations; 
    for (double i{64}; i < 5e8; i *= 2)
        iterations.emplace_back(i); 

    auto bench_double = bench_double_sum(5e8);
    auto bench_measurement = bench_measurement_sum(5e8);
    auto bench_umeasurement = bench_umeasurement_sum(5e8);

    Gnuplot plt{};
    plt.redirect_to_png("images/sum_err.png", "800,600");
    plt.set_logscale(Gnuplot::AxisScale::LOGX);
    plt.set_xlabel("Number of iterations");
    plt.set_ylabel("Mean time of execution [ns]");
    plt.plot_yerr(iterations, bench_double.first, bench_double.second, "double");
    plt.plot_yerr(iterations, bench_measurement.first, bench_measurement.second, "measurement");
    plt.plot_yerr(iterations, bench_umeasurement.first, bench_umeasurement.second, "umeasurement");
    plt.show();

}


void bench_prod() {

    std::vector<double> iterations; 
    for (double i{64}; i < 5e8; i *= 2)
        iterations.emplace_back(i); 

    auto bench_double = bench_double_prod(5e8); 
    auto bench_measurement = bench_measurement_prod(5e8); 
    auto bench_umeasurement = bench_umeasurement_prod(5e8); 

    Gnuplot plt{};
    plt.redirect_to_png("images/prod_err.png", "800,600");
    plt.set_logscale(Gnuplot::AxisScale::LOGX);
    plt.set_xlabel("Number of iterations");
    plt.set_ylabel("Mean time of execution [ns]");
    plt.plot_yerr(iterations, bench_double.first, bench_double.second, "double");
    plt.plot_yerr(iterations, bench_measurement.first, bench_measurement.second, "measurement");
    plt.plot_yerr(iterations, bench_umeasurement.first, bench_umeasurement.second, "umeasurement");
    plt.show();

}


void bench_div() {

    std::vector<double> iterations; 
    for (double i{64}; i < 5e8; i *= 2)
        iterations.emplace_back(i); 

    auto bench_double = bench_double_div(5e8); 
    auto bench_measurement = bench_measurement_div(5e8); 
    auto bench_umeasurement = bench_umeasurement_div(5e8); 

    Gnuplot plt{};
    plt.redirect_to_png("images/div_err.png", "800,600");
    plt.set_logscale(Gnuplot::AxisScale::LOGX);
    plt.set_xlabel("Number of iterations");
    plt.set_ylabel("Mean time of execution [ns]");
    plt.plot_yerr(iterations, bench_double.first, bench_double.second, "double");
    plt.plot_yerr(iterations, bench_measurement.first, bench_measurement.second, "measurement");
    plt.plot_yerr(iterations, bench_umeasurement.first, bench_umeasurement.second, "umeasurement");
    plt.show();

}



int main() {

    std::srand(std::time(NULL));

    std::thread sum(bench_sum); 
    std::thread prod(bench_prod); 
    std::thread div(bench_div); 

    sum.join(); 
    prod.join(); 
    div.join(); 

    return 0; 

}