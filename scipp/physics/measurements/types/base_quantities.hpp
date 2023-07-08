/**
 * @file    scipp/physics/measurements/types/base_quantities.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the aliases and declarations of units
 * @note    
 * @date    2023-07-08
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::physics {


    namespace base {


        // base_quantities
        using scalar = base_quantity<0, 0, 0, 0, 0, 0, 0>; ///< scalar base_quantity 
        using angle = base_quantity<0, 0, 0, 0, 0, 0, 0>; ///< radian base_quantity
        using length = base_quantity<1, 0, 0, 0, 0, 0, 0>; ///< metre base_quantity 
        using time = base_quantity<0, 1, 0, 0, 0, 0, 0>; ///< second base_quantity
        using mass = base_quantity<0, 0, 1, 0, 0, 0, 0>; ///< kilogram base_quantity
        using temperature = base_quantity<0, 0, 0, 1, 0, 0, 0>; ///< kelvin base_quantity
        using electric_current = base_quantity<0, 0, 0, 0, 1, 0, 0>; ///< ampere base_quantity
        using substance_amount = base_quantity<0, 0, 0, 0, 0, 1, 0>; ///< mole base_quantity
        using luminous_intensity = base_quantity<0, 0, 0, 0, 0, 0, 1>; ///< candela base_quantity

        // derived quantities
        using area = math::op::multiply_t<length, length>; ///< square_metre base_quantity
        using volume = math::op::multiply_t<length, area>; ///< cubic_metre base_quantity

        using velocity = math::op::divide_t<length, time>; ///< metre_per_second base_quantity
        using acceleration = math::op::divide_t<velocity, time>; ///< metre_per_second_squared base_quantity
        using angular_velocity = math::op::divide_t<angle, time>; ///< radian_per_second base_quantity
        using angular_acceleration = math::op::divide_t<angular_velocity, time>; ///< radian_per_second2 base_quantity

        using momentum = math::op::multiply_t<mass, velocity>; ///< kilogram_metre_per_second base_quantity
        using impulse = math::op::multiply_t<momentum, time>; ///< kilogram_metre_per_second base_quantity
        using angular_momentum = math::op::multiply_t<momentum, length>; ///< kilogram_metre_squared_per_second base_quantity
        using force = math::op::multiply_t<mass, acceleration>; ///< newton base_quantity
        using torque = math::op::multiply_t<force, length>; ///< newton_metre base_quantity
        using energy = math::op::multiply_t<force, length>; ///< joule base_quantity
        using action = math::op::multiply_t<energy, time>; ///< joule_second base_quantity
        using power = math::op::divide_t<energy, time>; ///< watt base_quantity
        using pressure = math::op::divide_t<force, area>; ///< pascal base_quantity
        using density = math::op::divide_t<mass, volume>; ///< kilogram_per_cubic_metre base_quantity
        using frequency = math::op::invert_t<time>; ///< hertz base_quantity

        using electric_charge = math::op::multiply_t<electric_current, time>; ///< coulomb base_quantity
        using electric_field = math::op::divide_t<force, electric_charge>; ///< volt_per_metre base_quantity
        using voltage = math::op::divide_t<power, electric_current>; ///< volt base_quantity
        using resistance = math::op::divide_t<voltage, electric_current>; ///< ohm base_quantity
        using capacitance = math::op::divide_t<electric_charge, voltage>; ///< farad base_quantity
        using magnetic_field = math::op::divide_t<force, electric_current>; ///< tesla base_quantity
        using magnetic_flux = math::op::multiply_t<magnetic_field, area>; ///< weber base_quantity
        using inductance = math::op::divide_t<magnetic_flux, electric_current>; ///< henry base_quantity
        // using luminous_flux = math::op::multiply_t<luminous_intensity, solid_angle>; ///< lumen base_quantity
        // using illuminance = math::op::divide_t<luminous_flux, area>; ///< lux base_quantity
        using radioactivity = math::op::divide_t<substance_amount, time>; ///< becquerel base_quantity
        using absorbed_dose = math::op::divide_t<energy, mass>; ///< gray base_quantity
        // using dose_equivalent = math::op::multiply_t<absorbed_dose, radiation_weighting_factor>; ///< sievert base_quantity


    } // namespace base


} // namespace scipp::physics