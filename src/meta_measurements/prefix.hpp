/**
 * @file    prefix.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-30
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief measurements namespace contains all the classes and functions of the measurements library
namespace scipp::measurements {

    
    /// @brief units namespace contains all the units of the measurements library
    namespace meta_units {


        template <typename ratio1, typename ratio2>
        struct ratio_product {

            using type = std::ratio<ratio1::num * ratio2::num, ratio1::den * ratio2::den>; 

        }; 

        template <typename ratio1, typename ratio2>
        using ratio_product_t = typename ratio_product<ratio1, ratio2>::type; 


        template <typename ratio1, typename ratio2>
        struct ratio_division {

            using type = std::ratio<ratio1::num / ratio2::num, ratio1::den / ratio2::den>; 

        }; 

        template <typename ratio1, typename ratio2>
        using ratio_division_t = typename ratio_division<ratio1, ratio2>::type; 


        template <typename ratio, int power>
        struct ratio_pow {

            using type = std::ratio<std::pow(ratio::num, power), std::pow(ratio::den, power)>; 

        };

        template <typename ratio, int power>
        using ratio_pow_t = typename ratio_pow<ratio, power>::type;


        template <typename ratio, int power>
        struct ratio_root {

            using type = std::ratio<std::pow(ratio::num, 1. / power), std::pow(ratio::den, 1. / power)>; 

        };

        template <typename ratio, int power>
        using ratio_root_t = typename ratio_root<ratio, power>::type;


    } // namespace meta_units


} // namespace scipp::measurements