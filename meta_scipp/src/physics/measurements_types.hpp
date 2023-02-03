/**
 * @file    measurements_types.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief measurements namespace contains all the classes and functions of the measurements library
namespace scipp::physics {
    

    using scalar_m = measurement<units::unitless>;                    ///< scalar_m
    using length_m = measurement<units::metre>;                       ///< length_m 
    using time_m = measurement<units::second>;                        ///< time_m 
    using mass_m = measurement<units::kilogram>;                      ///< mass_m 
    using angle_m = measurement<units::radian>;                       ///< angle_m 
    using temperature_m = measurement<units::kelvin>;                 ///< temperature_m
    using current_m = measurement<units::ampere>;                     ///< current_m
    using luminous_intensity_m = measurement<units::candela>;         ///< luminous_intensity_m
    using mole_m = measurement<units::mole>;                          ///< mole_m

    using speed_m = measurement<units::metre_per_second>;             ///< speed_m 
    using acceleration_m = measurement<units::metre_per_second2>;     ///< acceleration_m 
    using force_m = measurement<units::kilogram_metre_per_second2>;   ///< force_m 
    using energy_m = measurement<units::kilogram_metre2_per_second2>; ///< energy_m 

    
    // using scalar_um = umeasurement<basis::scalar>;                                                                ///< scalar_um
    // using length_um = umeasurement<basis::metre>;                                                                 ///< length_um 
    // using time_um = umeasurement<basis::second>;                                                                  ///< time_um 
    // using mass_um = umeasurement<basis::kilogram>;                                                                ///< mass_um 
    // using angle_um = umeasurement<basis::radian>;                                                                 ///< angle_um 
    // using temperature_um = umeasurement<basis::Kelvin>;                                                           ///< temperature_um
    // using current_um = umeasurement<basis::Ampere>;                                                               ///< current_um
    // using luminous_intensity_um = umeasurement<basis::candela>;                                                   ///< luminous_intensity_um
    // using mole_um = umeasurement<basis::mole>;                                                                    ///< mole_um

    // using speed_um = umeasurement<basis::metre / basis::second>;                                                  ///< speed_um 
    // using acceleration_um = umeasurement<basis::metre / math::op::square(basis::second)>;                               ///< acceleration_um 
    // using force_um = umeasurement<basis::kilogram * basis::metre / math::op::square(basis::second)>;                    ///< force_um 
    // using energy_um = umeasurement<basis::kilogram * math::op::square(basis::metre) / math::op::square(basis::second)>; ///< energy_um 


} // namespace scipp::physics