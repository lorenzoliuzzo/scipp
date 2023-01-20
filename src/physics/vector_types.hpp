/**
 * @file position.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2023-01-20
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::physics {


    template <std::size_t DIM> 
    using position = geometry::vector<basis::metre, DIM>; 

    using position2 = position<2>;
    using position3 = position<3>;


    template <std::size_t DIM> 
    using lin_velocity = geometry::vector<basis::metre / basis::second, DIM>; 

    using lin_velocity2 = lin_velocity<2>;
    using lin_velocity3 = lin_velocity<3>;


    template <std::size_t DIM> 
    using lin_acceleration = geometry::vector<basis::metre / math::op::square(basis::second), DIM>; 

    using lin_acceleration2 = lin_acceleration<2>;
    using lin_acceleration3 = lin_acceleration<3>;


    template <std::size_t DIM> 
    using ang_acceleration = geometry::vector<basis::radian / math::op::square(basis::second), DIM>; 

    using ang_acceleration2 = ang_acceleration<2>;
    using ang_acceleration3 = ang_acceleration<3>;


} // namespace scipp::physics