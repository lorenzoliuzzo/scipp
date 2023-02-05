/**
 * @file    unit_base.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-25
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


    std::cout << "testing the unit_base class\n";
    timer_cpu.start();
    unit_base m_tim1(1, 0, 0, 0, 0, 0, 0, 0);
    timer_cpu.stop();
    std::cout << "cpu elapsed: " << timer_cpu.elapsed() << '\n';

    timer_omp.start();
    unit_base m_tim2(1, 0, 0, 0, 0, 0, 0, 0);
    timer_omp.stop();
    std::cout << "omp elapsed: " << timer_omp.elapsed() << "\n\n";


    std::cout << "testing the unit_base2 class\n";
    timer_cpu.start();
    unit_base2<1, 0, 0, 0, 0, 0, 0, 0> m_timer_cpu;
    timer_cpu.stop();
    std::cout << "cpu elapsed: " << timer_cpu.elapsed() << '\n';

    timer_omp.start();
    unit_base2<1, 0, 0, 0, 0, 0, 0, 0> m_timer_omp;
    timer_omp.stop();
    std::cout << "omp elapsed: " << timer_omp.elapsed() << "\n\n";


    std::cout << "testing the product of unit_base\n"; 
    timer_cpu.start();
    auto result1 = m_tim1 * m_tim2;
    timer_cpu.stop();
    std::cout << "cpu elapsed: " << timer_cpu.elapsed() << '\n';

    timer_omp.start();
    auto result2 = m_timer_cpu * m_timer_omp;
    timer_omp.stop();
    std::cout << "omp elapsed: " << timer_omp.elapsed() << '\n';

    std::cout << "testing the product of unit_base2\n";

    timer_cpu.start();
    auto result3 = m_timer_cpu * m_timer_omp;
    timer_cpu.stop();
    std::cout << "cpu elapsed: " << timer_cpu.elapsed() << '\n';

    timer_omp.start();
    auto result4 = m_timer_cpu * m_timer_omp;
    timer_omp.stop();
    std::cout << "omp elapsed: " << timer_omp.elapsed() << '\n';

    std::cout << "results: " << result1 << " " << " " << result3 << "\n\n";


    std::cout << "testing MTP\n";

    timer_cpu.start();
        unit2<_metre> appo1;
        constexpr measurement2 appo2(3.5, appo1);
        vector2 appo3(std::array<measurement2<_metre>, 3>({appo2, appo2, appo2}));
    timer_cpu.stop();
    std::cout << "cpu elapsed: " << timer_cpu.elapsed() << '\n';

    timer_cpu.start();
        unit<basis::metre> nigga1;
        measurement nigga2(3.5, nigga1);
        geometry::vector nigga3(std::array<measurement<basis::metre>, 3>({nigga2, nigga2, nigga2}));
    timer_cpu.stop();
    std::cout << "cpu elapsed: " << timer_cpu.elapsed() << '\n';
    
    timer_omp.start();
        unit2<_metre> pippo1;
        constexpr measurement2 pippo2(3.5, pippo1);
        vector2 pippo3(std::array<measurement2<_metre>, 3>({pippo2, pippo2, pippo2}));
    timer_omp.stop();
    std::cout << "omp elapsed: " << timer_omp.elapsed() << '\n';

    timer_omp.start();
        unit<basis::metre> pluto1;
        measurement pluto2(3.5, pluto1);
        geometry::vector pluto3(std::array<measurement<basis::metre>, 3>({pluto2, pluto2, pluto2}));
    timer_omp.stop();
    std::cout << "omp elapsed: " << timer_omp.elapsed() << '\n';


    std::cout << decltype(pippo3)::base_type() << '\n'; 
    

    // std::cout << "testing operator*\n";

    // measurement2<_metre> jack0(3.5);
    // measurement<basis::metre> tony0(3.5);

    // timer_cpu.start();
    //     measurement2<_2metre> jack1 = jack0 * jack0;
    // timer_cpu.stop();
    // std::cout << "cpu elapsed: " << timer_cpu.elapsed() << '\n';

    // timer_cpu.start();
    //     measurement<basis::metre * basis::metre> tony1 = tony0 * tony0;
    // timer_cpu.stop();
    // std::cout << "cpu elapsed: " << timer_cpu.elapsed() << '\n';
    
    // timer_omp.start();
    //     measurement2<_2metre> jack2 = jack0 * jack0;
    // timer_omp.stop();
    // std::cout << "omp elapsed: " << timer_omp.elapsed() << '\n';

    // timer_omp.start();
    //     measurement<basis::metre * basis::metre> tony2 = tony0 * tony0;
    // timer_omp.stop();
    // std::cout << "omp elapsed: " << timer_omp.elapsed() << '\n';


    return 0; 


}