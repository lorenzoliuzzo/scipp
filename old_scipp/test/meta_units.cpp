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


void omp_bench() {


    scipp::tools::omp_timer timer;

    timer.start();
    measurement x(3.24, m); 
    timer.stop();
    std::cout << "Time 1: " << timer.elapsed() << '\n';

    timer.start();
    auto y = x * x;
    timer.stop();
    std::cout << "Time 2: " << timer.elapsed() << '\n';

    timer.start();
    std::cout << x << '\n';
    timer.stop();
    std::cout << "Time for a stamp: " << timer.elapsed() << '\n';

    std::cout << y << '\n';

    timer.start();
    meta_measurement<meta_metre> meta_x(3.24, __units::m);
    timer.stop();
    std::cout << "Time 1: " << timer.elapsed() << '\n';

    timer.start();
    auto meta_y = meta_x * meta_x;
    timer.stop();
    std::cout << "Time 2: " << timer.elapsed() << '\n';

    timer.start();
    std::cout << meta_x << '\n'; 
    timer.stop();
    std::cout << "Time for a stamp: " << timer.elapsed() << '\n';

    std::cout << meta_y << '\n'; 

}


void cpu_bench() {


    scipp::tools::cpu_timer timer;

    timer.start();
    measurement x(3.24, m); 
    timer.stop();
    std::cout << "Time 1: " << timer.elapsed() << '\n';

    timer.start();
    auto y = x * x;
    timer.stop();
    std::cout << "Time 2: " << timer.elapsed() << '\n';

    timer.start();
    std::cout << x << '\n';
    timer.stop();
    std::cout << "Time for a stamp: " << timer.elapsed() << '\n';

    std::cout << y << '\n';

    timer.start();
    meta_measurement<meta_metre> meta_x(3.24, __units::m);
    timer.stop();
    std::cout << "Time 1: " << timer.elapsed() << '\n';

    timer.start();
    auto meta_y = meta_x * meta_x;
    timer.stop();
    std::cout << "Time 2: " << timer.elapsed() << '\n';

    timer.start();
    std::cout << meta_x << '\n'; 
    timer.stop();
    std::cout << "Time for a stamp: " << timer.elapsed() << '\n';

    std::cout << meta_y << '\n'; 

}


int main() {

    // omp_bench();

    // std::cout << '\n'; 
    
    // cpu_bench(); 


    meta_measurement x(3.24, (__units::s / __units::m));
    std::cout << x << '\n';

    meta_measurement y(3.24, __units::m);
    std::cout << y << '\n';

    meta_measurement z = x / y;
    std::cout << z << '\n';
    std::cout << y.to_string(__units::km) << '\n';
    // static_assert(std::is_same_v<decltype(z), meta_measurement<metre_per_second>()>);

    std::cout << x * y << '\n';



    std::cout << __units::kg.to_string() << '\n';

    std::cout << sizeof(meta_kilogram) << '\n';
    std::cout << sizeof(decltype(__units::kg)) << '\n';
    std::cout << sizeof(decltype(x)) << '\n'; 


    std::cout << convert(32.3, __units::m, __units::km) * __units::km << '\n';
    // std::cout << __units::km.to_base(345) << '\n';
    


    return 0;

}