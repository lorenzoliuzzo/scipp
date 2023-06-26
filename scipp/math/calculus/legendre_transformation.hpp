/**
 * @file    math/calculus/legendre_tranformation.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-06-21
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {   


        template <typename T1, typename T2>  
        inline auto legendre_tranformation(const variable<T1>& y, const variable<T2>& x) {

            return std::get<0>(derivatives(y, wrt(x))) * x - y; 

        }


    } // namespace calculus


} // namespace scipp::math