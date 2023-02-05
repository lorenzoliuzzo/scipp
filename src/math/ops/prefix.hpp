/**
 * @file    prefix.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::physics {


    namespace units {


        template <typename ratio1, typename ratio2>
        struct ratio_prod {

            using type = std::ratio<ratio1::num * ratio2::num, ratio1::den * ratio2::den>; 

        }; 

        template <typename ratio1, typename ratio2>
        using ratio_prod_t = typename ratio_prod<ratio1, ratio2>::type; 


        template <typename ratio1, typename ratio2>
        struct ratio_div {

            using type = std::ratio<ratio1::num / ratio2::num, ratio1::den / ratio2::den>; 

        }; 

        template <typename ratio1, typename ratio2>
        using ratio_div_t = typename ratio_div<ratio1, ratio2>::type; 


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


        template <typename ratio>
        struct ratio_inv {

            using type = std::ratio<ratio::den, ratio::num>; 

        };


        template <typename ratio>
        using ratio_inv_t = typename ratio_inv<ratio>::type;
        

    } // namespace units


} // namespace scipp::physics