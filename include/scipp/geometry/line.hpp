/**
 * @file    geometry/line.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-04-04
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief geometry namespace contains all the classes and functions of the geometry library
namespace scipp::geometry {
    

    template <typename POINT_TYPE>
        requires (is_vector_v<POINT_TYPE>)
    struct line : math::functions::unary_function<POINT_TYPE, double> {


        using type = line<POINT_TYPE>;

        using point_type = POINT_TYPE;


        point_type zero;

        point_type direction;         


        constexpr line(const point_type& point, const point_type& dir) noexcept : 
            
            zero(point), direction(dir) {}


        constexpr line(point_type&& A, point_type&& dir) noexcept : 
            
            zero(std::move(A)), direction(std::move(dir)) {}



        constexpr point_type operator()(const physics::scalar_m& t) const noexcept override {

            return zero + t * direction;

        }


    };


    template <typename T>
    struct is_line : std::false_type {};

    template <typename POINT_TYPE>
    struct is_line<line<POINT_TYPE>> : std::true_type {};

    template <typename T>
    concept is_line_v = is_line<T>::value;

    
} // namespace scipp::geometry