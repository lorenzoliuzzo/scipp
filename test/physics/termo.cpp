/**
 * @file    test/physics/potentials.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-28
 * 
 * @copyright Copyright (c) 2023
 */



#include "sci++.hpp"


using namespace scipp;

using namespace tools; 
using namespace math; 
using namespace math::op; 
using namespace physics;
using namespace physics::units; 


int main() { 

    auto V_acqua = 0.1 * L; 
    auto n_gas = 1.0 * mol;
    auto T_amb = (40 + 273.13) * K;  
    auto p_amb = 1.0 * atm;
    auto m_gh = 0.01 * kg;     
    auto c_gh = 2.09 * (kJ / (kg * K));
    auto T_gh = (-15 + 273.13) * K; 
    auto T_fus = 273.13 * K;
    auto lambda = 80 * (kcal / kg); 

    auto Q_gh = m_gh * lambda + m_gh * c_gh * (T_fus - T_gh);
    print("Q_gh", Q_gh);



    return 0; 

}