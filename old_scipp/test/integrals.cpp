/**
 * @file    integrals.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-24
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp; 


int main() {
    
    tools::cpu_timer timer1;
    tools::omp_timer timer2;

    timer1.start();
    auto result = math::integral2::midpoint<lenght_m>([](length_m x) -> measurement<basis::metre2> { return x * x; }, 0 * m, 2 * m, 10000); 
    timer1.stop();
    std::cout << "fucked cpu elapsed: " << timer1.elapsed() << "\n\n";


    // timer2.start();
    // result = math::integral2::midpoint<basis::metre, basis::metre2>([](measurement<basis::metre> x) { return x * x; }, 0 * m, 2 * m, 10000); 
    // timer2.stop();
    // std::cout << "fucked omp elapsed: " << timer2.elapsed() << "\n\n";


    // timer1.start();
    // auto result_d = math::integral2::midpoint([](double x) { return x * x; }, 0, 2, 100); 
    // timer1.stop();
    // std::cout << "cpu elapsed: " << timer1.elapsed() << '\n';
    // std::cout << "double: " << result_d << "\n\n";


    // timer1.start();
    // auto result_m = math::integral2::midpoint<basis::metre, basis::metre2>([](measurement<basis::metre> x) { return x * x; }, 0 * m, 2 * m, 100); 
    // timer1.stop();
    // std::cout << "cpu elapsed: " << timer1.elapsed() << '\n';
    // std::cout << "measurements: " << result_m << "\n\n";



    // timer2.start();
    // auto result_d2 = math::integral2::midpoint([](double x) { return x * x; }, 0, 2, 10000000); 
    // timer2.stop();
    // std::cout << "omp elapsed: " << timer2.elapsed() << '\n';
    // std::cout << "double: " << result_d2 << "\n\n";

    // timer2.start();
    // auto result_m2 = math::integral2::midpoint<basis::metre, basis::metre2>([](measurement<basis::metre> x) { return x * x; }, 0 * m, 2 * m, 10000000); 
    // timer2.stop();
    // std::cout << "omp elapsed: " << timer2.elapsed() << '\n';
    // std::cout << "measurement: " << result_m2 << "\n\n";



    // timer2.start();
    // auto fixed_m = math::integral2::midpoint_fixed<basis::metre, basis::metre2>([](measurement<basis::metre> x) { return x * x; }, 0 * m, 2 * m, 1.e-12); 
    // timer2.stop();
    // std::cout << "omp elapsed: " << timer2.elapsed() << '\n';
    // std::cout << "fixed measurement: " << fixed_m << '\n';

    // timer1.start();
    // fixed_m = math::integral2::midpoint_fixed<basis::metre, basis::metre2>([](measurement<basis::metre> x) { return x * x; }, 0 * m, 2 * m, 1.e-12); 
    // timer1.stop();
    // std::cout << "cpu elapsed: " << timer1.elapsed() << '\n';
    // std::cout << "fixed measurement: " << fixed_m << "\n\n";



    // timer1.start();
    // auto result_pm2 = math::integral2::midpoint([](double x) { return 4 / (1 + x * x); }, 0, 1, 10000000); 
    // timer1.stop();
    // std::cout << "elapsed: " << timer1.elapsed() << '\n';
    // std::cout << result_pm2 << '\n';




    return 0; 

}