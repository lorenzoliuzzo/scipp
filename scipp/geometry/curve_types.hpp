/**
 * @file    geometry/curve_types.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-04-04
 * 
 * @copyright Copyright (c) 2023
 */





/// @brief geometry namespace contains all the classes and functions of the geometry library
namespace scipp::geometry {
    

    // template <typename POINT_TYPE>
    // constexpr auto segment(const POINT_TYPE& p0, const POINT_TYPE& p1) {
            
    //     return math::curve<POINT_TYPE>([&p0, &p1](const physics::scalar_m& t) {

    //         return p0 + t * (p1 - p0);

    //     });

    // }


    template <typename POINT_TYPE>
        requires (POINT_TYPE::dim == 2)
    constexpr auto circumference(const POINT_TYPE& center, const auto& radius) {

        return math::curve<POINT_TYPE>([center, radius](const std::array<double, 1>& t) {
            
            physics::scalar_m t_ = t[0] * 2.0 * math::constants::pi;
            return POINT_TYPE(center.x() + radius * math::op::cos(t_), center.y() + radius * math::op::sin(t_));

        });

    }    


    template <typename POINT_TYPE>
        requires (POINT_TYPE::dim == 2)
    constexpr auto ellipse(const POINT_TYPE& center, const typename POINT_TYPE::measurement_t& a, const typename POINT_TYPE::measurement_t& b) {

        return math::curve<POINT_TYPE>([center, a, b](const double& t) {

            return center + make_vector(a * math::op::cos(2.0 * math::constants::pi * t), 
                                        b * math::op::sin(2.0 * math::constants::pi * t));

        });

    }


    template <typename POINT_TYPE>
        requires (POINT_TYPE::dim == 3)
    constexpr auto sphere(const POINT_TYPE& center, const typename POINT_TYPE::measurement_t& radius) {

        return math::curve<POINT_TYPE>([center, radius](const std::array<double, 2>& t) {

            return center + radius * make_vector(math::op::cos(2.0 * math::constants::pi * t[0]) * math::op::sin(math::constants::pi * t[1]),
                                                 math::op::sin(2.0 * math::constants::pi * t[0]) * math::op::sin(math::constants::pi * t[1]),
                                                 math::op::cos(math::constants::pi * t[1]));

        });

    }


    template <typename POINT_TYPE>
        requires (POINT_TYPE::dim == 2)
    constexpr auto asteroid(const POINT_TYPE& center, const typename POINT_TYPE::measurement_t& radius) {

        return math::curve<POINT_TYPE>([center, radius](const std::array<double, 1>& t) {

            return center + radius * make_vector(math::op::cube(math::op::cos(2.0 * math::constants::pi * t[0])), 
                                                 math::op::cube(math::op::sin(2.0 * math::constants::pi * t[0]))); 

        });

    }


    // template <typename POINT_TYPE>
    //     requires (is_vector_v<POINT_TYPE> && POINT_TYPE::dim == 2)
    // constexpr auto parabola(const POINT_TYPE& center, const typename POINT_TYPE::measurement_t& radius_x, const typename POINT_TYPE::measurement_t& radius_y) {

    //     return math::curve<POINT_TYPE>([&center, &radius_x, &radius_y](const physics::scalar_m& t) {

    //         // return center + radius_x * make_vector(math::op::cos(t), math::op::sin(t)) + radius_y * make_vector(math::op::cos(t), math::op::sin(t));

    //     }, 0.0, 2.0 * math::constants::pi);

    // }


    // template <typename POINT_TYPE>
    //     requires (is_vector_v<POINT_TYPE> && POINT_TYPE::dim == 2)
    // constexpr auto hyperbola(const POINT_TYPE& center, const typename POINT_TYPE::measurement_t& radius_x, const typename POINT_TYPE::measurement_t& radius_y) {

    //     return math::curve<POINT_TYPE>([&center, &radius_x, &radius_y](const physics::scalar_m& t) {

    //         // return center + radius_x * make_vector(math::op::cos(t), math::op::sin(t)) + radius_y * make_vector(math::op::cos(t), math::op::sin(t));

    //     }, 0.0, 2.0 * math::constants::pi);

    // }


    // template <typename POINT_TYPE>
    //     requires (is_vector_v<POINT_TYPE> && POINT_TYPE::dim == 2)
    // constexpr auto spiral(const POINT_TYPE& center, const typename POINT_TYPE::measurement_t& radius_x, const typename POINT_TYPE::measurement_t& radius_y) {

    //     return math::curve<POINT_TYPE>([center, radius_x, radius_y](const physics::scalar_m& t) {

    //         // return center + radius_x * make_vector(math::op::cos(t), math::op::sin(t)) + radius_y * make_vector(math::op::cos(t), math::op::sin(t));

    //     }, 0.0, 2.0 * math::constants::pi);

    // }


    // template <typename POINT_TYPE>
    //     requires (is_vector_v<POINT_TYPE> && POINT_TYPE::dim == 2)
    // constexpr auto cardiod(const POINT_TYPE& center, const typename POINT_TYPE::measurement_t& radius) {

    //     return math::curve<POINT_TYPE>([&center, &radius](const vector<physics::scalar_m, 1>& t) {

    //         return center + radius * make_vector(math::op::cos(2.0 * math::constants::pi * t[0]) * (1.0 + math::op::sin(2.0 * math::constants::pi * t[0])), math::op::sin(2.0 * math::constants::pi * t[0]) * (1.0 + math::op::sin(2.0 * math::constants::pi * t[0])));

    //     });

    // }




} // namespace scipp::geometry