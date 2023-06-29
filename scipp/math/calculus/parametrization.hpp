/**
 * @file    math/calculus/parametrization.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-06-29
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {    


        template <typename CURVE, typename... VARS> 
            requires is_curve_v<CURVE>
        struct parametrization {

            CURVE curve;

            template <typename FUNCTION, typename... VARS>
            inline constexpr parametrization(FUNCTION gamma, VARS&... variables) :

                curve(f, variables...) {}

        }


    } // namespace calculus


} // namespace scipp::math