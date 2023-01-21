/**
 * @file    measurements_types.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-21
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief measurements namespace contains all the classes and functions of the measurements library
namespace scipp::measurements {


    using scalar_m = measurement<basis::scalar>;                                                                ///< scalar_m
    using length_m = measurement<basis::metre>;                                                                 ///< length_m 
    using time_m = measurement<basis::second>;                                                                  ///< time_m 
    using mass_m = measurement<basis::kilogram>;                                                                ///< mass_m 
    using angle_m = measurement<basis::radian>;                                                                 ///< angle_m 
    using temperature_m = measurement<basis::Kelvin>;                                                           ///< temperature_m
    using current_m = measurement<basis::Ampere>;                                                               ///< current_m
    using luminous_intensity_m = measurement<basis::candela>;                                                   ///< luminous_intensity_m
    using mole_m = measurement<basis::mole>;                                                                    ///< mole_m

    using speed_m = measurement<basis::metre / basis::second>;                                                  ///< speed_m 
    using acceleration_m = measurement<basis::metre / math::op::square(basis::second)>;                               ///< acceleration_m 
    using force_m = measurement<basis::kilogram * basis::metre / math::op::square(basis::second)>;                    ///< force_m 
    using energy_m = measurement<basis::kilogram * math::op::square(basis::metre) / math::op::square(basis::second)>; ///< energy_m 

    
} // namespace scipp::measurements