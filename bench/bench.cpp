/**
 * @file    sci++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Test file for sci++ library
 * @date    2023-01-01
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"
#include "../plot/gplot++.hpp"


using namespace scipp; 


int main() {

    Gnuplot plt{};

    tools::timer stopwatch;
    time_umeasurement mean_time;

    tools::cpu_timer stopwatch2;
    stopwatch2.start();
    stopwatch2.stop();
    std::cout << "CPU timer overhead: " << stopwatch2.elapsed(ns) << "\n";
    

    double d1{3.1};    
    double d2{4.5};
    measurement m1(3.1 * m);    
    measurement m2(4.5 * m);
    umeasurement um1(3.1 * m, 0.8 * m);    
    umeasurement um2(4.5 * m, 0.6 * m);

    std::vector<double> iterations;
    std::vector<double> double_sum_times;
    std::vector<double> measurement_sum_times;
    std::vector<double> umeasurement_sum_times;
    std::vector<double> double_prod_times;
    std::vector<double> measurement_prod_times;
    std::vector<double> umeasurement_prod_times;
    std::vector<double> double_div_times;
    std::vector<double> measurement_div_times;
    std::vector<double> umeasurement_div_times;

    std::vector<double> double_sum_times_uncertainty;
    std::vector<double> measurement_sum_times_uncertainty;
    std::vector<double> umeasurement_sum_times_uncertainty;
    std::vector<double> double_prod_times_uncertainty;
    std::vector<double> measurement_prod_times_uncertainty;
    std::vector<double> umeasurement_prod_times_uncertainty;
    std::vector<double> double_div_times_uncertainty;
    std::vector<double> measurement_div_times_uncertainty;
    std::vector<double> umeasurement_div_times_uncertainty;
 
    std::cout << "Testing the performance of the measurements library\n"; 

    for (double n{1e1}; n < 1e9; n *= 10) {

        iterations.emplace_back(n);
    
        // SUM
        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = d1 + d2; }, ns);
        stopwatch.stop();
        double_sum_times.emplace_back(mean_time.value());
        double_sum_times_uncertainty.emplace_back(mean_time.uncertainty());

        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = m1 + m2; }, ns);
        stopwatch.stop();
        measurement_sum_times.emplace_back(mean_time.value());
        measurement_sum_times_uncertainty.emplace_back(mean_time.uncertainty());

        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = um1 + um2; }, ns);
        stopwatch.stop();
        umeasurement_sum_times.emplace_back(mean_time.value());
        umeasurement_sum_times_uncertainty.emplace_back(mean_time.uncertainty());

        // PRODUCT
        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = d1 * d2; }, ns);
        stopwatch.stop();
        double_prod_times.emplace_back(mean_time.value());
        double_prod_times_uncertainty.emplace_back(mean_time.uncertainty());

        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = m1 * m2; }, ns);
        stopwatch.stop();
        measurement_prod_times.emplace_back(mean_time.value());
        measurement_prod_times_uncertainty.emplace_back(mean_time.uncertainty());

        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = um1 * um2; }, ns);
        stopwatch.stop();
        umeasurement_prod_times.emplace_back(mean_time.value());
        umeasurement_prod_times_uncertainty.emplace_back(mean_time.uncertainty());


        // DIVISION
        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = d1 / d2; }, ns);
        stopwatch.stop();
        double_div_times.emplace_back(mean_time.value());
        double_div_times_uncertainty.emplace_back(mean_time.uncertainty());

        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = m1 / m2; }, ns);
        stopwatch.stop();
        measurement_div_times.emplace_back(mean_time.value());
        measurement_div_times_uncertainty.emplace_back(mean_time.uncertainty());

        stopwatch.start();
            mean_time = tools::cpu_bench(n, [&]() { auto x = um1 / um2; }, ns);
        stopwatch.stop();
        umeasurement_div_times.emplace_back(mean_time.value());
        umeasurement_div_times_uncertainty.emplace_back(mean_time.uncertainty());


    }

    // plt.redirect_to_png("sum.png", "800,600");
    // plt.set_logscale(Gnuplot::AxisScale::LOGX);
    // // plt.title("Sum");
    // plt.set_xlabel("Number of iterations");
    // plt.set_ylabel("Mean time of execution [ns]");
    // plt.plot_yerr(iterations, double_sum_times, double_sum_times_uncertainty, "double");
    // plt.plot_yerr(iterations, measurement_sum_times, measurement_sum_times_uncertainty, "measurement");
    // plt.plot_yerr(iterations, umeasurement_sum_times, umeasurement_sum_times_uncertainty, "umeasurement");
    // plt.show();

    // plt.redirect_to_png("product.png", "800,600");
    // plt.set_logscale(Gnuplot::AxisScale::LOGX);
    // // plt.title("Product");
    // plt.set_xlabel("Number of iterations");
    // plt.set_ylabel("Mean time of execution [ns]");
    // plt.plot_yerr(iterations, double_prod_times, double_prod_times_uncertainty, "double");
    // plt.plot_yerr(iterations, measurement_prod_times, measurement_prod_times_uncertainty, "measurement");
    // plt.plot_yerr(iterations, umeasurement_prod_times, umeasurement_prod_times_uncertainty, "umeasurement");
    // plt.show(); 

    plt.redirect_to_png("bench/sum.png", "800,600");
    plt.set_logscale(Gnuplot::AxisScale::LOGX);
    plt.set_xlabel("Number of iterations");
    plt.set_ylabel("Mean time of execution [ns]");
    plt.plot(iterations, double_sum_times, "double", Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(iterations, measurement_sum_times, "measurement", Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(iterations, umeasurement_sum_times, "umeasurement", Gnuplot::LineStyle::LINESPOINTS);
    plt.show();

    plt.redirect_to_png("bench/product.png", "800,600");
    plt.set_logscale(Gnuplot::AxisScale::LOGX);
    plt.set_xlabel("Number of iterations");
    plt.set_ylabel("Mean time of execution [ns]");
    plt.plot(iterations, double_prod_times, "double", Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(iterations, measurement_prod_times, "measurement", Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(iterations, umeasurement_prod_times, "umeasurement", Gnuplot::LineStyle::LINESPOINTS);
    plt.show();

    plt.redirect_to_png("bench/div.png", "800,600");
    plt.set_logscale(Gnuplot::AxisScale::LOGX);
    plt.set_xlabel("Number of iterations");
    plt.set_ylabel("Mean time of execution [ns]");
    plt.plot(iterations, double_div_times, "double", Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(iterations, measurement_div_times, "measurement", Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(iterations, umeasurement_div_times, "umeasurement", Gnuplot::LineStyle::LINESPOINTS);
    plt.show();


    return 0; 

}