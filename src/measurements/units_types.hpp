/**
 * @file    unit_types.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-21
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief measurements namespace contains all the classes and functions of the measurements library
namespace scipp::measurements {

    
    /// @brief units namespace contains all the units of the measurements library
    namespace units {


        /// @brief Namespace units type aliases
        namespace types {

            
            using scalar_unit = unit<basis::scalar>;
            using length_unit = unit<basis::metre>; 
            using time_unit = unit<basis::second>; 
            using mass_unit = unit<basis::kilogram>; 
            using temperature_unit = unit<basis::Kelvin>; 
            using mole_unit = unit<basis::mole>; 
            using angle_unit = unit<basis::radian>; 
            using current_unit = unit<basis::Ampere>;
            using luminous_intensity_unit = unit<basis::candela>;
            using mole_unit = unit<basis::mole>;


            // unitless 
            constexpr unit<basis::scalar> unitless;
            constexpr unit<basis::radian> rad;

            // SI units
            constexpr unit<basis::metre> m;
            constexpr unit<basis::second> s;
            constexpr unit<basis::kilogram> kg;
            constexpr unit<basis::Kelvin> K;
            constexpr unit<basis::Ampere> A;
            constexpr unit<basis::mole> mol;
            constexpr unit<basis::candela> cd;

            // // length units
            constexpr length_unit ym(prefixes::yocto);
            constexpr length_unit zm(prefixes::zepto);
            constexpr length_unit am(prefixes::atto);
            constexpr length_unit fm(prefixes::femto);
            constexpr length_unit pm(prefixes::pico);
            constexpr length_unit nm(prefixes::nano);
            constexpr length_unit um(prefixes::micro);
            constexpr length_unit mm(prefixes::milli);
            constexpr length_unit cm(prefixes::centi);
            constexpr length_unit dm(prefixes::deci);
            constexpr length_unit hm(prefixes::hecto);
            constexpr length_unit km(prefixes::kilo);
            constexpr length_unit Mm(prefixes::mega);
            constexpr length_unit Gm(prefixes::giga);
            constexpr length_unit Tm(prefixes::tera);
            constexpr length_unit Pm(prefixes::peta);
            constexpr length_unit Em(prefixes::exa);

            // // time units
            constexpr time_unit ys(prefixes::yocto);
            constexpr time_unit zs(prefixes::zepto);
            constexpr time_unit as(prefixes::atto);
            constexpr time_unit fs(prefixes::femto);
            constexpr time_unit ps(prefixes::pico);
            constexpr time_unit ns(prefixes::nano);
            constexpr time_unit us(prefixes::micro);
            constexpr time_unit ms(prefixes::milli);
            constexpr time_unit cs(prefixes::centi);
            constexpr time_unit ds(prefixes::deci);
            constexpr time_unit hs(prefixes::hecto);
            constexpr time_unit ks(prefixes::kilo);
            constexpr time_unit Ms(prefixes::mega);
            constexpr time_unit Gs(prefixes::giga);
            constexpr time_unit Ts(prefixes::tera);
            constexpr time_unit Ps(prefixes::peta);
            constexpr time_unit Es(prefixes::exa);

            // constexpr unit<basis::metre / basis::second> m_s;
            // constexpr unit<basis::metre / basis::second> km_s(prefixes::kilo);
            // constexpr unit<basis::metre / basis::second.square()> m_ss;


            // // composed units
            constexpr unit<math::op::inv(basis::second)> hertz;
            constexpr unit Hz = hertz;

            constexpr unit<math::op::inv(basis::second)> MHz(prefixes::mega); 
            constexpr unit<math::op::inv(basis::second)> GHz(prefixes::giga); 
                            
            constexpr unit<unit_base(2, -3, 1, -1, 0, 0, 0, 0)> volt;
            constexpr unit V = volt;

            constexpr unit<unit_base(1, -2, 1, 0, 0, 0, 0, 0)> newton;
            constexpr unit N = newton;

            constexpr unit<unit_base(-1, -2, 1, 0, 0, 0, 0, 0)> Pa;
            constexpr unit pascal = Pa;

            constexpr unit<unit_base(2, -2, 1, 0, 0, 0, 0, 0)> joule;
            constexpr unit J = joule;

            constexpr unit<unit_base(2, -3, 1, 0, 0, 0, 0, 0)> watt;
            constexpr unit W = watt;

            constexpr unit<unit_base(0, 1, 0, 1, 0, 0, 0, 0)> coulomb;
            constexpr unit C = coulomb;

            constexpr unit<unit_base(-2, 4, -1, 2, 0, 0, 0, 0)> farad;
            constexpr unit F = farad;

            constexpr unit<unit_base(2, -2, 1, -1, 0, 0, 0, 0)> weber;
            constexpr unit Wb = weber;

            constexpr unit<unit_base(0, -2, 1, -1, 0, 0, 0, 0)> tesla;
            constexpr unit T = tesla;

            constexpr unit<unit_base(2, -2, 1, -2, 0, 0, 0, 0)> henry;                    
            constexpr unit H = henry;


        }; // namespace types

        
        using namespace types; 


    } // namespace units


    using namespace units; 


} // namespace scipp::measurements