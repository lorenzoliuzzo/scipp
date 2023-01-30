/**
 * @file    meta_units.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-28
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp::measurements::meta_units;
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
    meta_base<1, 0, 0, 0, 0, 0, 0, 0> meta_metre2;
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

    std::cout << meta_millimetre_u1.mult << '\n';
    std::cout << decltype(meta_millimetre_u1)::mult << '\n';
    std::cout << meta_millimetre_u1 << '\n';

    timer_omp.start();
    meta_unit<meta_metre, std::centi> meta_centimetre_u1;
    timer_omp.stop();
    std::cout << "meta_centimetre_u1 elapsed: " << timer_omp.elapsed() << '\n'; 


    std::cout << "meta_centimetre_u1: " << decltype(meta_centimetre_u1)::mult << meta_centimetre_u1 << '\n';

    // std::cout << "meta_kilometre_u1: " << _kilo_metre::factor() << _kilo_metre::to_string() << '\n';


    timer_omp.start();
    measurement m1(1.0, km);
    timer_omp.stop();
    std::cout << "m1 elapsed: " << timer_omp.elapsed() << '\n';
    timer_omp.start();
    // meta_measurement m3(1.0, _km);
    timer_omp.stop();
    std::cout << "m2 elapsed: " << timer_omp.elapsed() << '\n';


    std::cout << ratio_product_t<std::milli, std::milli>::den << '\n'; 

    timer_omp.start();
    auto x = base_product<meta_metre, meta_second>(); 
    timer_omp.stop();
    std::cout << "1 elapsed: " << timer_omp.elapsed() << '\n'; 

    timer_omp.start();

    timer_omp.stop();
    std::cout << "2 elapsed: " << timer_omp.elapsed() << '\n'; 


    std::cout << __units::km << '\n';
    std::cout << __units::km.mult << '\n';

    std::cout << __units::km * __units::km << '\n';
    
    // std::cout << decltype(km2)::mult << '\n'; 
    // std::cout << km2 << '\n'; 
    std::cout << base::metre * base::second << '\n'; 


    return 0; 


}