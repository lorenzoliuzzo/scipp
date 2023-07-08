/**
 * @file    math/calculus/interval.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-07
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {
    
    
    namespace calculus {
        

        // Norm function for tuples
        template <typename... Ts, size_t... Indices>
        constexpr auto tuple_norm_impl(const std::tuple<Ts...>& tuple, std::index_sequence<Indices...>) {
            return op::sqrt((op::square(std::get<Indices>(tuple)) + ...));
        }

        template <typename... Ts>
        constexpr auto norm(const std::tuple<Ts...>& tuple) {

            return tuple_norm_impl(tuple, std::index_sequence_for<Ts...>{});
            
        }


    } // namespace calculus


} // namespace scipp::math