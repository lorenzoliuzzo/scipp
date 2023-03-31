/**
 * @file    math/constants.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-02-10
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {


    namespace constants {


        constexpr physics::scalar_m nan = std::numeric_limits<double>::signaling_NaN(); /// double Not a Number

        constexpr physics::scalar_m zero = 0.0; /// double Zero

        constexpr physics::scalar_m infinity = std::numeric_limits<double>::infinity(); /// double Infinity
        
        constexpr physics::scalar_m pi = 3.14159265358979323846; /// double Pi
        
        constexpr physics::scalar_m e = 2.7182818284590452353603; /// double Euler's number
        

    } // namespace constants


} // namespace scipp::math