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


        constexpr scalar nan = std::numeric_limits<scalar>::signaling_NaN(); /// scalar Not a Number

        constexpr scalar zero = 0.0; /// scalar Zero

        constexpr scalar infinity = std::numeric_limits<scalar>::infinity(); /// scalar Infinity
        
        constexpr scalar pi = 3.14159265358979323846; /// scalar Pi
        
        constexpr scalar e = 2.7182818284590452353603; /// scalar Euler's number
        

    } // namespace constants


} // namespace scipp::math