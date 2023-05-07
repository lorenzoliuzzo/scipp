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


std::vector<double> bench_double_sum(const size_t& n) {

    double a = std::rand() % 10000 + 1;
    double b = std::rand() % 10000 + 1;

    std::vector<double> times; 
    for (double i{2 * 64}; i < n; i *= 2)
        times.emplace_back(tools::cpu_bench(i, [&]() { auto x = a + b; }).value_as(ns));
    
    return times;

}

std::vector<double> bench_double_prod(const size_t& n) {

    double a = std::rand() % 10000 + 1;
    double b = std::rand() % 10000 + 1;

    std::vector<double> times; 
    for (double i{2 * 64}; i < n; i *= 2)
        times.emplace_back(tools::cpu_bench(i, [&]() { auto x = a * b; }).value_as(ns));
    
    return times;

}

std::vector<double> bench_double_div(const size_t& n) {

    double a = std::rand() % 10000 + 1;
    double b = std::rand() % 10000 + 1;

    std::vector<double> times; 
    for (double i{2 * 64}; i < n; i *= 2)
        times.emplace_back(tools::cpu_bench(i, [&]() { auto x = a / b; }).value_as(ns));
    
    return times;

}


std::vector<double> bench_measurement_sum(const size_t& n) {

    measurement a = (std::rand() % 10000 + 1) * N;
    measurement b = (std::rand() % 10000 + 1) * N;

    tools::cpu_timer sw;
    std::vector<double> times; 
    for (double i{2 * 64}; i < n; i *= 2) {
        sw.start();
        sw.stop();
        times.emplace_back(tools::cpu_bench(i, [&]() { auto x = a + b; }).value_as(ns));
    }
    
    return times;

}

std::vector<double> bench_measurement_prod(const size_t& n) {

    measurement a = (std::rand() % 10000 + 1) * N;
    measurement b = (std::rand() % 10000 + 1) * N;

    std::vector<double> times; 
    for (double i{2 * 64}; i < n; i *= 2)
        times.emplace_back(tools::cpu_bench(i, [&]() { auto x = a * b; }).value_as(ns));
    
    return times;

}

std::vector<double> bench_measurement_div(const size_t& n) {

    measurement a = (std::rand() % 10000 + 1) * N;
    measurement b = (std::rand() % 10000 + 1) * N;

    std::vector<double> times; 
    for (double i{2 * 64}; i < n; i *= 2)
        times.emplace_back(tools::cpu_bench(i, [&]() { auto x = a / b; }).value_as(ns));
    
    return times;

}


std::vector<double> bench_umeasurement_sum(const size_t& n) {

    umeasurement a = ((std::rand() % 10000 + 1) * N, (std::rand() % 100 + 1) * N);
    umeasurement b = ((std::rand() % 10000 + 1) * N, (std::rand() % 100 + 1) * N);

    std::vector<double> times; 
    for (double i{2 * 64}; i < n; i *= 2)
        times.emplace_back(tools::cpu_bench(i, [&]() { auto x = a + b; }).value_as(ns));
    
    return times;

}

std::vector<double> bench_umeasurement_prod(const size_t& n) {

    umeasurement a = ((std::rand() % 10000 + 1) * N, (std::rand() % 100 + 1) * N);
    umeasurement b = ((std::rand() % 10000 + 1) * N, (std::rand() % 100 + 1) * N);

    std::vector<double> times; 
    for (double i{2 * 64}; i < n; i *= 2)
        times.emplace_back(tools::cpu_bench(i, [&]() { auto x = a * b; }).value_as(ns));
    
    return times;

}

std::vector<double> bench_umeasurement_div(const size_t& n) {

    umeasurement a = ((std::rand() % 10000 + 1) * N, (std::rand() % 100 + 1) * N);
    umeasurement b = ((std::rand() % 10000 + 1) * N, (std::rand() % 100 + 1) * N);

    std::vector<double> times; 
    for (double i{2 * 64}; i < n; i *= 2)
        times.emplace_back(tools::cpu_bench(i, [&]() { auto x = a / b; }).value_as(ns));
    
    return times;

}


std::vector<double> bench_double_sin(const size_t& n) {

    double a = (std::rand() % 10000 + 1); 

    std::vector<double> times; 
    for (double i{2 * 64}; i < n; i *= 2)
        times.emplace_back(tools::cpu_bench(i, [&]() { auto x = std::sin(a); }).value_as(ns));
    
    return times;

}

std::vector<double> bench_measurement_sin(const size_t& n) {

    measurement a = (std::rand() % 10000 + 1) * rad;

    std::vector<double> times; 
    for (double i{2 * 64}; i < n; i *= 2)
        times.emplace_back(tools::cpu_bench(i, [&]() { auto x = math::op::sin(a); }).value_as(ns));
    
    return times;

}

std::vector<double> bench_umeasurement_sin(const size_t& n) {

    umeasurement a = ((std::rand() % 10000 + 1) * rad, (std::rand() % 100 + 1) * rad);

    std::vector<double> times; 
    for (double i{2 * 64}; i < n; i *= 2)
        times.emplace_back(tools::cpu_bench(i, [&]() { auto x = math::op::sin(a); }).value_as(ns));
    
    return times;

}




void bench_sum() {

    std::vector<double> iterations; 
    for (double i{2 * 64}; i < 5e8; i *= 2)
        iterations.emplace_back(i); 

    Gnuplot plt{};
    plt.redirect_to_png("images/sum.png", "800,600");
    plt.set_logscale(Gnuplot::AxisScale::LOGX);
    plt.set_xlabel("Number of iterations");
    plt.set_ylabel("Mean time of execution [ns]");
    plt.plot(iterations, bench_double_sum(5e8), "double", Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(iterations, bench_measurement_sum(5e8), "measurement", Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(iterations, bench_umeasurement_sum(5e8), "umeasurement", Gnuplot::LineStyle::LINESPOINTS);
    plt.show();

}


void bench_prod() {

    std::vector<double> iterations; 
    for (double i{2 * 64}; i < 5e8; i *= 2)
        iterations.emplace_back(i); 

    Gnuplot plt{};
    plt.redirect_to_png("images/prod.png", "800,600");
    plt.set_logscale(Gnuplot::AxisScale::LOGX);
    plt.set_xlabel("Number of iterations");
    plt.set_ylabel("Mean time of execution [ns]");
    plt.plot(iterations, bench_double_prod(5e8), "double", Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(iterations, bench_measurement_prod(5e8), "measurement", Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(iterations, bench_umeasurement_prod(5e8), "umeasurement", Gnuplot::LineStyle::LINESPOINTS);
    plt.show();

}


void bench_div() {

    std::vector<double> iterations; 
    for (double i{2 * 64}; i < 5e8; i *= 2)
        iterations.emplace_back(i); 

    Gnuplot plt{};
    plt.redirect_to_png("images/div.png", "800,600");
    plt.set_logscale(Gnuplot::AxisScale::LOGX);
    plt.set_xlabel("Number of iterations");
    plt.set_ylabel("Mean time of execution [ns]");
    plt.plot(iterations, bench_double_div(5e8), "double", Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(iterations, bench_measurement_div(5e8), "measurement", Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(iterations, bench_umeasurement_div(5e8), "umeasurement", Gnuplot::LineStyle::LINESPOINTS);
    plt.show();

}


void bench_sin() {

    std::vector<double> iterations; 
    for (double i{2 * 64}; i < 5e8; i *= 2)
        iterations.emplace_back(i); 

    Gnuplot plt{};
    plt.redirect_to_png("images/sin.png", "800,600");
    plt.set_logscale(Gnuplot::AxisScale::LOGX);
    plt.set_xlabel("Number of iterations");
    plt.set_ylabel("Mean time of execution [ns]");
    plt.plot(iterations, bench_double_sin(5e8), "double", Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(iterations, bench_measurement_sin(5e8), "measurement", Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(iterations, bench_umeasurement_sin(5e8), "umeasurement", Gnuplot::LineStyle::LINESPOINTS);
    plt.show();

}


int main() {

    std::cout << "Benchmarking...\n";

    std::srand(std::time(NULL));

    std::thread sum(bench_sum); 
    std::thread prod(bench_prod); 
    std::thread div(bench_div); 
    // std::thread sin(bench_sin);

    std::cout << "Ready!\n"; 

    sum.join(); 
    prod.join(); 
    div.join(); 
    // sin.join();

    std::cout << "Done!\n";

    return 0; 

}