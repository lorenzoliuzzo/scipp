/**
 * @file    meta_units.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-28
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp; 


int main() {


    tools::cpu_timer timer_cpu;
    tools::omp_timer timer_omp;


    std::cout << "evaluating the overhead\n";
    timer_cpu.start();
    timer_cpu.stop();
    std::cout << "fucked cpu elapsed: " << timer_cpu.elapsed() << '\n';

    timer_omp.start();
    timer_omp.stop();
    std::cout << "fucked omp elapsed: " << timer_omp.elapsed() << "\n\n";

    timer_omp.start(); 
    meta_unit_base<1, 0, 0, 0, 0, 0, 0, 0> meta_metre2;
    timer_omp.stop();
    std::cout << "meta_metre2 elapsed: " << timer_omp.elapsed() << '\n';
    std::cout << meta_metre2 << '\n';

    timer_omp.start(); 
    auto meta_metre3 = meta_metre();
    timer_omp.stop();
    std::cout << "meta_metre3 elapsed: " << timer_omp.elapsed() << '\n';
    std::cout << meta_metre3 << '\n';

    timer_omp.start();
    meta_unit<decltype(meta_metre3), std::milli> meta_millimetre_u1;
    timer_omp.stop();
    std::cout << "meta_millimetre_u1 elapsed: " << timer_omp.elapsed() << '\n'; 

    std::cout << meta_millimetre_u1.convertion_factor() << '\n';
    std::cout << decltype(meta_millimetre_u1)::convertion_factor() << '\n';
    std::cout << meta_millimetre_u1 << '\n';

    timer_omp.start();
    meta_unit<meta_metre, std::centi> meta_centimetre_u1;
    timer_omp.stop();
    std::cout << "meta_centimetre_u1 elapsed: " << timer_omp.elapsed() << '\n'; 


    std::cout << "meta_centimetre_u1: " << decltype(meta_centimetre_u1)::convertion_factor() << meta_centimetre_u1 << '\n';

    std::cout << "meta_kilometre_u1: " << _kilo_metre::convertion_factor() << _kilo_metre::to_string() << '\n';


    timer_omp.start();
    measurement m1(1.0, km);
    timer_omp.stop();
    std::cout << "m1 elapsed: " << timer_omp.elapsed() << '\n';

    timer_omp.start();
    meta_measurement m3(1.0, _km);
    timer_omp.stop();
    std::cout << "m2 elapsed: " << timer_omp.elapsed() << '\n';


    return 0; 


}