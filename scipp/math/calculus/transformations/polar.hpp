/**
 * @file    math/calculus/transformations/polar.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the polar transformation.
 * @date    2023-07-18
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {   


        template <typename T>  
        constexpr auto polar(const variable<T>& modulus, const variable<double>& theta) {

            return modulus * geometry::make_vector(op::cos(theta), op::sin(theta));

        }


        template <typename T>  
        constexpr auto polar(const T& modulus, const variable<double>& theta) {

            return modulus * geometry::make_vector(op::cos(theta), op::sin(theta));

        }


    } // namespace calculus


} // namespace scipp::math