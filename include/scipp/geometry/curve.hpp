/**
 * @file    geometry/circumference.hpp
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
    struct curve : math::nary_function<POINT_TYPE, physics::scalar_m, POINT_TYPE::dim - 1> {


        std::function<POINT_TYPE(vector<physics::scalar_m, POINT_TYPE::dim - 1>)> f;


        constexpr curve(std::function<POINT_TYPE(vector<physics::scalar_m, POINT_TYPE::dim - 1>)>&& f) noexcept : 
            
            f(f) {}


        constexpr POINT_TYPE operator()(const vector<physics::scalar_m, POINT_TYPE::dim - 1>& params) const {

            for (auto t : params.data)
                if (t < 0.0 || t > 1.0) {
                    std::cerr << "Cannot evaluate segment at t = " << t << '\n';
                    throw std::out_of_range("t must be in the range [0, 1]");
                }

            return f(params);

        }


        // constexpr auto diff(const vector<physics::scalar_m, POINT_TYPE::dim - 1>& params, 
        //                     const vector<physics::scalar_m, POINT_TYPE::dim - 1>& increments) const {

        //     return (f(params + increments) - f(params)) / increments;

        // }


        constexpr bool is_closed() const noexcept {

            return f(0) == f(1);

        }


    }; // struct curve 


} // namespace scipp::geometry