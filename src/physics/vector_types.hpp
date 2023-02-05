/**
 * @file vector_types.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2023-02-05
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::physics {


    template <std::size_t DIM> 
    using position = geometry::vector<length_m, DIM>; 

    using position2 = position<2>;
    using position3 = position<3>;


    template <std::size_t DIM> 
    using lin_velocity = geometry::vector<velocity_m, DIM>; 

    using lin_velocity2 = lin_velocity<2>;
    using lin_velocity3 = lin_velocity<3>;


    template <std::size_t DIM>
    using ang_velocity = geometry::vector<ang_velocity_m, DIM>;

    using ang_velocity2 = ang_velocity<2>;
    using ang_velocity3 = ang_velocity<3>;


    template <std::size_t DIM> 
    using lin_acceleration = geometry::vector<acceleration_m, DIM>; 

    using lin_acceleration2 = lin_acceleration<2>;
    using lin_acceleration3 = lin_acceleration<3>;


    template <std::size_t DIM> 
    using ang_acceleration = geometry::vector<ang_acceleration_m, DIM>; 

    using ang_acceleration2 = ang_acceleration<2>;
    using ang_acceleration3 = ang_acceleration<3>;


    template <std::size_t DIM>
    using force = geometry::vector<force_m, DIM>;

    using force2 = force<2>;
    using force3 = force<3>;


    // template <std::size_t DIM>
    // using momentum = geometry::vector<basis::kilogram * basis::metre / basis::second, DIM>;

    // using momentum2 = momentum<2>;
    // using momentum3 = momentum<3>;


    // template <std::size_t DIM>
    // using angular_momentum = geometry::vector<basis::kilogram * basis::metre * basis::radian / basis::second, DIM>;

    // using angular_momentum2 = angular_momentum<2>;
    // using angular_momentum3 = angular_momentum<3>;


    // template <std::size_t DIM>
    // using torque = geometry::vector<basis::kilogram * basis::metre * basis::radian / math::op::square(basis::second), DIM>;

    // using torque2 = torque<2>;
    // using torque3 = torque<3>;


} // namespace scipp::physics