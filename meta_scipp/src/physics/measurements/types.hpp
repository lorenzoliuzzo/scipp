/**
 * @file    units_types.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-03
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {

    
    /// @brief units namespace contains the implementation of units of measurements
    namespace units {


        using unitless = unit_base<0, 0, 0, 0, 0, 0, 0, 0>;

        using metre = unit_base<1, 0, 0, 0, 0, 0, 0, 0>;
        
        using second = unit_base<0, 1, 0, 0, 0, 0, 0, 0>;
        
        using kilogram = unit_base<0, 0, 1, 0, 0, 0, 0, 0>;
        
        using ampere = unit_base<0, 0, 0, 1, 0, 0, 0, 0>;
        
        using kelvin = unit_base<0, 0, 0, 0, 1, 0, 0, 0>;
        
        using mole = unit_base<0, 0, 0, 0, 0, 1, 0, 0>;
        
        using candela = unit_base<0, 0, 0, 0, 0, 0, 1, 0>;
        
        using radian = unit_base<0, 0, 0, 0, 0, 0, 0, 1>;


        using metre2 = unit_base<2, 0, 0, 0, 0, 0, 0, 0>;

        using metre3 = unit_base<3, 0, 0, 0, 0, 0, 0, 0>;

        using second2 = unit_base<0, 2, 0, 0, 0, 0, 0, 0>;

        using second3 = unit_base<0, 3, 0, 0, 0, 0, 0, 0>;

        using kilogram2 = unit_base<0, 0, 2, 0, 0, 0, 0, 0>;

        using kilogram3 = unit_base<0, 0, 3, 0, 0, 0, 0, 0>;

        using ampere2 = unit_base<0, 0, 0, 2, 0, 0, 0, 0>;

        using ampere3 = unit_base<0, 0, 0, 3, 0, 0, 0, 0>;

        using kelvin2 = unit_base<0, 0, 0, 0, 2, 0, 0, 0>;

        using kelvin3 = unit_base<0, 0, 0, 0, 3, 0, 0, 0>;

        using mole2 = unit_base<0, 0, 0, 0, 0, 2, 0, 0>;

        using mole3 = unit_base<0, 0, 0, 0, 0, 3, 0, 0>;

        using candela2 = unit_base<0, 0, 0, 0, 0, 0, 2, 0>;

        using candela3 = unit_base<0, 0, 0, 0, 0, 0, 3, 0>;

        using radian2 = unit_base<0, 0, 0, 0, 0, 0, 0, 2>;

        using radian3 = unit_base<0, 0, 0, 0, 0, 0, 0, 3>;

        using hertz = unit_base<0, -1, 0, 0, 0, 0, 0, 0>; 

        using metre_per_second = unit_base<1, -1, 0, 0, 0, 0, 0, 0>;

        using metre_per_second2 = unit_base<1, -2, 0, 0, 0, 0, 0, 0>;

        using metre_per_second3 = unit_base<1, -3, 0, 0, 0, 0, 0, 0>;

        using metre2_per_second = unit_base<2, -1, 0, 0, 0, 0, 0, 0>;

        using metre2_per_second2 = unit_base<2, -2, 0, 0, 0, 0, 0, 0>;

        using metre2_per_second3 = unit_base<2, -3, 0, 0, 0, 0, 0, 0>;

        using metre3_per_second = unit_base<3, -1, 0, 0, 0, 0, 0, 0>;

        using metre3_per_second2 = unit_base<3, -2, 0, 0, 0, 0, 0, 0>;

        using metre3_per_second3 = unit_base<3, -3, 0, 0, 0, 0, 0, 0>;

        using metre_per_kilogram = unit_base<1, 0, -1, 0, 0, 0, 0, 0>;

        using metre_per_kilogram2 = unit_base<1, 0, -2, 0, 0, 0, 0, 0>;

        using metre_per_kilogram3 = unit_base<1, 0, -3, 0, 0, 0, 0, 0>;

        using metre2_per_kilogram = unit_base<2, 0, -1, 0, 0, 0, 0, 0>;

        using metre2_per_kilogram2 = unit_base<2, 0, -2, 0, 0, 0, 0, 0>;

        using metre2_per_kilogram3 = unit_base<2, 0, -3, 0, 0, 0, 0, 0>;

        using metre3_per_kilogram = unit_base<3, 0, -1, 0, 0, 0, 0, 0>;

        using metre3_per_kilogram2 = unit_base<3, 0, -2, 0, 0, 0, 0, 0>;

        using metre3_per_kilogram3 = unit_base<3, 0, -3, 0, 0, 0, 0, 0>;

        using metre_per_ampere = unit_base<1, 0, 0, -1, 0, 0, 0, 0>;

        using metre_per_ampere2 = unit_base<1, 0, 0, -2, 0, 0, 0, 0>;

        using metre_per_ampere3 = unit_base<1, 0, 0, -3, 0, 0, 0, 0>;

        using metre2_per_ampere = unit_base<2, 0, 0, -1, 0, 0, 0, 0>;

        using metre2_per_ampere2 = unit_base<2, 0, 0, -2, 0, 0, 0, 0>;

        using metre2_per_ampere3 = unit_base<2, 0, 0, -3, 0, 0, 0, 0>;

        using metre3_per_ampere = unit_base<3, 0, 0, -1, 0, 0, 0, 0>;

        using metre3_per_ampere2 = unit_base<3, 0, 0, -2, 0, 0, 0, 0>;

        using metre3_per_ampere3 = unit_base<3, 0, 0, -3, 0, 0, 0, 0>;

        using metre_per_kelvin = unit_base<1, 0, 0, 0, -1, 0, 0, 0>;

        using metre_per_kelvin2 = unit_base<1, 0, 0, 0, -2, 0, 0, 0>;

        using metre_per_kelvin3 = unit_base<1, 0, 0, 0, -3, 0, 0, 0>;

        using metre2_per_kelvin = unit_base<2, 0, 0, 0, -1, 0, 0, 0>;

        using metre2_per_kelvin2 = unit_base<2, 0, 0, 0, -2, 0, 0, 0>;

        using metre2_per_kelvin3 = unit_base<2, 0, 0, 0, -3, 0, 0, 0>;

        using metre3_per_kelvin = unit_base<3, 0, 0, 0, -1, 0, 0, 0>;

        using metre3_per_kelvin2 = unit_base<3, 0, 0, 0, -2, 0, 0, 0>;

        using metre3_per_kelvin3 = unit_base<3, 0, 0, 0, -3, 0, 0, 0>;


        using kilogram_metre_per_second2 = unit_base<1, -2, 1, 0, 0, 0, 0, 0>; 

        using kilogram_metre2_per_second2 = unit_base<2, -2, 1, 0, 0, 0, 0, 0>; 



        static constexpr unit<metre> m;
        static constexpr unit<second> s;
        static constexpr unit<kilogram> kg;
        static constexpr unit<ampere> A;
        static constexpr unit<kelvin> K;
        static constexpr unit<mole> mol;
        static constexpr unit<candela> cd;
        static constexpr unit<radian> rad;


        static constexpr unit<metre, std::kilo> Km;
        static constexpr unit<metre, std::milli> mm;
        static constexpr unit<metre, std::micro> um;
        static constexpr unit<metre, std::nano> nm;
        static constexpr unit<metre, std::pico> pm;

        static constexpr unit<metre2, std::kilo> Km2;

        static constexpr unit<second, std::nano> ns; 

        static constexpr unit<second, std::ratio<60, 1>> min; 

        static constexpr unit<hertz, std::giga> GHz;

        static constexpr unit<kilogram2> kg2;
        static constexpr unit<metre2> m2;
        static constexpr unit<second2> s2;
        static constexpr unit<ampere2> A2;

        static constexpr auto N = kg * m / s2;
        static constexpr auto Pa = N / m2;
        static constexpr auto J = N * m;
        static constexpr auto W = J / s;
        static constexpr auto C = A * s;
        static constexpr auto V = W / A;


    } // namespace units


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

    
    // using frequency_m = measurement<units::hertz>;                    ///< frequency_m
    // using power_m = measurement<units::watt>;                         ///< power_m
    // using charge_m = measurement<units::coulomb>;                     ///< charge_m
    // using voltage_m = measurement<units::volt>;                       ///< voltage_m
    // using capacitance_m = measurement<units::farad>;                  ///< capacitance_m
    // using resistance_m = measurement<units::ohm>;                     ///< resistance_m
    // using conductance_m = measurement<units::siemens>;                ///< conductance_m
    // using magnetic_flux_m = measurement<units::weber>;                ///< magnetic_flux_m
    // using magnetic_field_m = measurement<units::tesla>;               ///< magnetic_field_m
    // using inductance_m = measurement<units::henry>;                   ///< inductance_m
    // using luminous_flux_m = measurement<units::lumen>;                ///< luminous_flux_m
    // using illuminance_m = measurement<units::lux>;                    ///< illuminance_m
    // using radioactivity_m = measurement<units::becquerel>;            ///< radioactivity_m
    // using absorbed_dose_m = measurement<units::gray>;                 ///< absorbed_dose_m
    // using dose_equivalent_m = measurement<units::sievert>;            ///< dose_equivalent_m
    // using catalytic_activity_m = measurement<units::katal>;           ///< catalytic_activity_m


} // namespace scipp::physics