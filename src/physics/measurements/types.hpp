/**
 * @file    units_types.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-05
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {

    
    /// @brief units namespace contains the implementation of units of measurements
    namespace units {


        using unitless = unit_base<0, 0, 0, 0, 0, 0, 0, 0>; ///< unitless unit_base 

        using metre = unit_base<1, 0, 0, 0, 0, 0, 0, 0>; ///< metre unit_base 
        
        using second = unit_base<0, 1, 0, 0, 0, 0, 0, 0>; ///< second unit_base 
        
        using kilogram = unit_base<0, 0, 1, 0, 0, 0, 0, 0>; ///< kilogram unit_base 
        
        using ampere = unit_base<0, 0, 0, 1, 0, 0, 0, 0>; ///< ampere unit_base 
        
        using kelvin = unit_base<0, 0, 0, 0, 1, 0, 0, 0>; ///< kelvin unit_base 
        
        using mole = unit_base<0, 0, 0, 0, 0, 1, 0, 0>; ///< mole unit_base 
        
        using candela = unit_base<0, 0, 0, 0, 0, 0, 1, 0>; ///< candela unit_base 
        
        using radian = unit_base<0, 0, 0, 0, 0, 0, 0, 1>; ///< radian unit_base 


        using metre2 = unit_base<2, 0, 0, 0, 0, 0, 0, 0>; ///< metre2 unit_base 

        using metre3 = unit_base<3, 0, 0, 0, 0, 0, 0, 0>; ///< metre3 unit_base 

        using second2 = unit_base<0, 2, 0, 0, 0, 0, 0, 0>; ///< second2 unit_base 

        using second3 = unit_base<0, 3, 0, 0, 0, 0, 0, 0>; ///< second3 unit_base 

        using kilogram2 = unit_base<0, 0, 2, 0, 0, 0, 0, 0>; ///< kilogram2 unit_base 

        using kilogram3 = unit_base<0, 0, 3, 0, 0, 0, 0, 0>; ///< kilogram3 unit_base 

        using ampere2 = unit_base<0, 0, 0, 2, 0, 0, 0, 0>; ///< ampere2 unit_base 

        using ampere3 = unit_base<0, 0, 0, 3, 0, 0, 0, 0>; ///< ampere3 unit_base 

        using kelvin2 = unit_base<0, 0, 0, 0, 2, 0, 0, 0>; ///< kelvin2 unit_base 

        using kelvin3 = unit_base<0, 0, 0, 0, 3, 0, 0, 0>; ///< kelvin3 unit_base 

        using mole2 = unit_base<0, 0, 0, 0, 0, 2, 0, 0>; ///< mole2 unit_base 

        using mole3 = unit_base<0, 0, 0, 0, 0, 3, 0, 0>; ///< mole3 unit_base 

        using candela2 = unit_base<0, 0, 0, 0, 0, 0, 2, 0>; ///< candela2 unit_base 

        using candela3 = unit_base<0, 0, 0, 0, 0, 0, 3, 0>; ///< candela3 unit_base 

        using radian2 = unit_base<0, 0, 0, 0, 0, 0, 0, 2>; ///< radian2 unit_base 

        using radian3 = unit_base<0, 0, 0, 0, 0, 0, 0, 3>; ///< radian3 unit_base 

        using hertz = unit_base<0, -1, 0, 0, 0, 0, 0, 0>; ///< hertz unit_base  

        using metre_per_second = unit_base<1, -1, 0, 0, 0, 0, 0, 0>; ///< metre_per_second unit_base 

        using metre_per_second2 = unit_base<1, -2, 0, 0, 0, 0, 0, 0>; ///< metre_per_second2 unit_base 

        using metre_per_second3 = unit_base<1, -3, 0, 0, 0, 0, 0, 0>; ///< metre_per_second3 unit_base 

        using metre2_per_second = unit_base<2, -1, 0, 0, 0, 0, 0, 0>; ///< metre2_per_second unit_base 

        using metre2_per_second2 = unit_base<2, -2, 0, 0, 0, 0, 0, 0>; ///< metre2_per_second2 unit_base 

        using metre2_per_second3 = unit_base<2, -3, 0, 0, 0, 0, 0, 0>; ///< metre2_per_second3 unit_base 

        using metre3_per_second = unit_base<3, -1, 0, 0, 0, 0, 0, 0>; ///< metre3_per_second unit_base 

        using metre3_per_second2 = unit_base<3, -2, 0, 0, 0, 0, 0, 0>; ///< metre3_per_second2 unit_base 

        using metre3_per_second3 = unit_base<3, -3, 0, 0, 0, 0, 0, 0>; ///< metre3_per_second3 unit_base 

        using metre_per_kilogram = unit_base<1, 0, -1, 0, 0, 0, 0, 0>; ///< metre_per_kilogram unit_base 

        using metre_per_kilogram2 = unit_base<1, 0, -2, 0, 0, 0, 0, 0>; ///< metre_per_kilogram2 unit_base 

        using metre_per_kilogram3 = unit_base<1, 0, -3, 0, 0, 0, 0, 0>; ///< metre_per_kilogram3 unit_base 

        using metre2_per_kilogram = unit_base<2, 0, -1, 0, 0, 0, 0, 0>; ///< metre2_per_kilogram unit_base 

        using metre2_per_kilogram2 = unit_base<2, 0, -2, 0, 0, 0, 0, 0>; ///< metre2_per_kilogram2 unit_base 

        using metre2_per_kilogram3 = unit_base<2, 0, -3, 0, 0, 0, 0, 0>; ///< metre2_per_kilogram3 unit_base 

        using metre3_per_kilogram = unit_base<3, 0, -1, 0, 0, 0, 0, 0>; ///< metre3_per_kilogram unit_base 

        using metre3_per_kilogram2 = unit_base<3, 0, -2, 0, 0, 0, 0, 0>; ///< metre3_per_kilogram2 unit_base 

        using metre3_per_kilogram3 = unit_base<3, 0, -3, 0, 0, 0, 0, 0>; ///< metre3_per_kilogram3 unit_base 

        using metre_per_ampere = unit_base<1, 0, 0, -1, 0, 0, 0, 0>; ///< metre_per_ampere unit_base 

        using metre_per_ampere2 = unit_base<1, 0, 0, -2, 0, 0, 0, 0>; ///< metre_per_ampere2 unit_base 

        using metre_per_ampere3 = unit_base<1, 0, 0, -3, 0, 0, 0, 0>; ///< metre_per_ampere3 unit_base 

        using metre2_per_ampere = unit_base<2, 0, 0, -1, 0, 0, 0, 0>; ///< metre2_per_ampere unit_base 

        using metre2_per_ampere2 = unit_base<2, 0, 0, -2, 0, 0, 0, 0>; ///< metre2_per_ampere2 unit_base 

        using metre2_per_ampere3 = unit_base<2, 0, 0, -3, 0, 0, 0, 0>; ///< metre2_per_ampere3 unit_base 

        using metre3_per_ampere = unit_base<3, 0, 0, -1, 0, 0, 0, 0>; ///< metre3_per_ampere unit_base 

        using metre3_per_ampere2 = unit_base<3, 0, 0, -2, 0, 0, 0, 0>; ///< metre3_per_ampere2 unit_base 

        using metre3_per_ampere3 = unit_base<3, 0, 0, -3, 0, 0, 0, 0>; ///< metre3_per_ampere3 unit_base 

        using metre_per_kelvin = unit_base<1, 0, 0, 0, -1, 0, 0, 0>; ///< metre_per_kelvin unit_base 

        using metre_per_kelvin2 = unit_base<1, 0, 0, 0, -2, 0, 0, 0>; ///< metre_per_kelvin2 unit_base 

        using metre_per_kelvin3 = unit_base<1, 0, 0, 0, -3, 0, 0, 0>; ///< metre_per_kelvin3 unit_base 

        using metre2_per_kelvin = unit_base<2, 0, 0, 0, -1, 0, 0, 0>; ///< metre2_per_kelvin unit_base 

        using metre2_per_kelvin2 = unit_base<2, 0, 0, 0, -2, 0, 0, 0>; ///< metre2_per_kelvin2 unit_base 

        using metre2_per_kelvin3 = unit_base<2, 0, 0, 0, -3, 0, 0, 0>; ///< metre2_per_kelvin3 unit_base 

        using metre3_per_kelvin = unit_base<3, 0, 0, 0, -1, 0, 0, 0>; ///< metre3_per_kelvin unit_base 

        using metre3_per_kelvin2 = unit_base<3, 0, 0, 0, -2, 0, 0, 0>; ///< metre3_per_kelvin2 unit_base 

        using metre3_per_kelvin3 = unit_base<3, 0, 0, 0, -3, 0, 0, 0>; ///< metre3_per_kelvin3 unit_base 


        using kilogram_metre_per_second2 = unit_base<1, -2, 1, 0, 0, 0, 0, 0>; ///< kilogram_metre_per_second2 unit_base  

        using kilogram_metre2_per_second2 = unit_base<2, -2, 1, 0, 0, 0, 0, 0>; ///< kilogram_metre2_per_second2 unit_base  

        using radian_per_second = unit_base<0, -1, 0, 0, 0, 0, 0, 1>; ///< radian_per_second unit_base

        using radian_per_second2 = unit_base<0, -2, 0, 0, 0, 0, 0, 1>; ///< radian_per_second2 unit_base



        static constexpr unit<metre> m; ///< m; unit
        static constexpr unit<second> s; ///< s unit
        static constexpr unit<kilogram> kg; ///< kg unit
        static constexpr unit<ampere> A; ///< A unit
        static constexpr unit<kelvin> K; ///< K unit
        static constexpr unit<mole> mol; ///< mol unit
        static constexpr unit<candela> cd; ///< cd unit
        static constexpr unit<radian> rad; ///< rad unit


        static constexpr unit<metre_per_second> m_s; ///< m_s unit


        static constexpr unit<metre, std::kilo> Km; ///< Km unit
        static constexpr unit<metre, std::milli> mm; ///< mm unit
        static constexpr unit<metre, std::micro> um; ///< um unit
        static constexpr unit<metre, std::nano> nm; ///< nm unit
        static constexpr unit<metre, std::pico> pm; ///< pm unit

        static constexpr unit<metre2, std::kilo> Km2; ///< Km2 unit

        static constexpr unit<second, std::nano> ns; ///< ns unit 

        static constexpr unit<second, std::ratio<60, 1>> min; ///< min unit 

        static constexpr unit<hertz, std::giga> GHz; ///< GHz unit

        static constexpr unit<kilogram2> kg2; ///< kg2 unit
        static constexpr unit<metre2> m2; ///< m2 unit
        static constexpr unit<second2> s2; ///< s2 unit
        static constexpr unit<ampere2> A2; ///< A2 unit

        static constexpr auto N = kg * m / s2; ///< s2 unit
        static constexpr auto Pa = N / m2; ///< m2 unit
        static constexpr auto J = N * m; ///< J unit
        static constexpr auto W = J / s; ///< W unit
        static constexpr auto C = A * s; ///< C unit
        static constexpr auto V = W / A; ///< V unit


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

    using velocity_m = measurement<units::metre_per_second>;          ///< velocity_m 
    using ang_velocity_m = measurement<units::radian_per_second>;     ///< ang_velocity_m
    using acceleration_m = measurement<units::metre_per_second2>;     ///< acceleration_m 
    using ang_acceleration_m = measurement<units::radian_per_second2>;    ///< ang_acceleration_m
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


    /// @brief Measurement litteral for length

    inline constexpr auto operator""m(long double value) noexcept -> length_m {

        return length_m(value);

    }

    inline constexpr auto operator""Km(long double value) noexcept -> length_m {

        return length_m(value, units::Km);

    }


} // namespace scipp::physics