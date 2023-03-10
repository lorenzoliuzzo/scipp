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
    using position = geometry::vector<units::metre, DIM>; 

    using position2 = position<2>;
    using position3 = position<3>;


    template <std::size_t DIM> 
    using lin_velocity = geometry::vector<units::metre_per_second, DIM>; 

    using lin_velocity2 = lin_velocity<2>;
    using lin_velocity3 = lin_velocity<3>;


    // template <std::size_t DIM>
    // using ang_velocity = geometry::vector<ang_velocity_m, DIM>;

    // using ang_velocity2 = ang_velocity<2>;
    // using ang_velocity3 = ang_velocity<3>;


    template <std::size_t DIM> 
    using lin_acceleration = geometry::vector<units::metre_per_second2, DIM>; 

    using lin_acceleration2 = lin_acceleration<2>;
    using lin_acceleration3 = lin_acceleration<3>;


    // template <std::size_t DIM> 
    // using ang_acceleration = geometry::vector<ang_acceleration_m, DIM>; 

    // using ang_acceleration2 = ang_acceleration<2>;
    // using ang_acceleration3 = ang_acceleration<3>;


    // template <std::size_t DIM>
    // using force = geometry::vector<force_m, DIM>;

    // using force2 = force<2>;
    // using force3 = force<3>;


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


// 1) Displacement
// 2) Velocity
// 3) Acceleration
// 4) Force
// 5) Torque
// 6) Electric field
// 7) Magnetic field
// 8) Angular velocity
// 9) Linear Momentum
// 10) Dipole moment
// 11) Vector potential
// 12) Angular momentum
// 13) Weight
// 14) Current density
// 15) Thrust
// 16) Magnetic dipole moment
// 17) Magnetisation
// 18) Polarization
// 19) Electric Displacement
// 20) Poynting Vector.

} // namespace scipp::physics