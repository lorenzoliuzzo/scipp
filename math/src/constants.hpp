/**
 * @file    constants.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-01
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp::math {


    namespace constants {


        constexpr double nan = std::numeric_limits<double>::signaling_NaN();

        constexpr double infinity = std::numeric_limits<double>::infinity();
        
        constexpr double pi = 3.14159265358979323846;
        
        constexpr double e = 2.7182818284590452353603;
        

    } // namespace constants


} // namespace scipp::math