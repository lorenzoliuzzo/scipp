/**
 * @file    constants.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-01
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {


    namespace constants {


        constexpr scalar nan = std::numeric_limits<scalar>::signaling_NaN();

        constexpr scalar infinity = std::numeric_limits<scalar>::infinity();
        
        constexpr scalar pi = 3.14159265358979323846;
        
        constexpr scalar e = 2.7182818284590452353603;
        

    } // namespace constants


} // namespace scipp::math