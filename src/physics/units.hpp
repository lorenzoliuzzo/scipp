/**
 * @file    physics/units.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the aliases and declarations of units
 * @note    
 * @date    2023-03-08
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


#include "base_quantity.hpp"
#include "unit.hpp"


namespace scipp::physics {
    


    /// @brief Perform a multiplication between unit 
    template <typename unit1, typename unit2> 
        requires (physics::are_units_v<unit1, unit2>)
    constexpr auto operator*(const unit1&, const unit2&) noexcept 
        -> math::op::unit_product_t<typename unit1::type, typename unit2::type> {
        
        return math::op::unit_product_t<typename unit1::type, typename unit2::type>(); 
        
    } 


    /// @brief Perform a division between unit 
    template <typename unit1, typename unit2> 
        requires (physics::are_units_v<unit1, unit2>)
    constexpr auto operator/(const unit1&, const unit2&) noexcept 
        -> math::op::unit_division_t<typename unit1::type, typename unit2::type> {
        
        return math::op::unit_division_t<typename unit1::type, typename unit2::type>(); 
        
    } 


    /// @brief units namespace contains the implementation of units of measurements
    namespace units {


        using scalar = base_quantity<0, 0, 0, 0, 0, 0, 0, 0>; ///< scalar base_quantity 

        using metre = base_quantity<1, 0, 0, 0, 0, 0, 0, 0>; ///< metre base_quantity 
        
        using second = base_quantity<0, 1, 0, 0, 0, 0, 0, 0>; ///< second base_quantity

        using kilogram = base_quantity<0, 0, 1, 0, 0, 0, 0, 0>; ///< kilogram base_quantity

        using ampere = base_quantity<0, 0, 0, 1, 0, 0, 0, 0>; ///< ampere base_quantity

        using kelvin = base_quantity<0, 0, 0, 0, 1, 0, 0, 0>; ///< kelvin base_quantity

        using mole = base_quantity<0, 0, 0, 0, 0, 1, 0, 0>; ///< mole base_quantity

        using candela = base_quantity<0, 0, 0, 0, 0, 0, 1, 0>; ///< candela base_quantity

        using radian = base_quantity<0, 0, 0, 0, 0, 0, 0, 1>; ///< radian base_quantity

        using metre2 = base_quantity<2, 0, 0, 0, 0, 0, 0, 0>; ///< metre2 base_quantity 

        using metre3 = base_quantity<3, 0, 0, 0, 0, 0, 0, 0>; ///< metre3 base_quantity 

        using second2 = base_quantity<0, 2, 0, 0, 0, 0, 0, 0>; ///< second2 base_quantity 

        using second3 = base_quantity<0, 3, 0, 0, 0, 0, 0, 0>; ///< second3 base_quantity 

        using kilogram2 = base_quantity<0, 0, 2, 0, 0, 0, 0, 0>; ///< kilogram2 base_quantity 

        using kilogram3 = base_quantity<0, 0, 3, 0, 0, 0, 0, 0>; ///< kilogram3 base_quantity 

        using ampere2 = base_quantity<0, 0, 0, 2, 0, 0, 0, 0>; ///< ampere2 base_quantity 

        using ampere3 = base_quantity<0, 0, 0, 3, 0, 0, 0, 0>; ///< ampere3 base_quantity 

        using kelvin2 = base_quantity<0, 0, 0, 0, 2, 0, 0, 0>; ///< kelvin2 base_quantity 

        using kelvin3 = base_quantity<0, 0, 0, 0, 3, 0, 0, 0>; ///< kelvin3 base_quantity 

        using mole2 = base_quantity<0, 0, 0, 0, 0, 2, 0, 0>; ///< mole2 base_quantity 

        using mole3 = base_quantity<0, 0, 0, 0, 0, 3, 0, 0>; ///< mole3 base_quantity 

        using candela2 = base_quantity<0, 0, 0, 0, 0, 0, 2, 0>; ///< candela2 base_quantity 

        using candela3 = base_quantity<0, 0, 0, 0, 0, 0, 3, 0>; ///< candela3 base_quantity 

        using radian2 = base_quantity<0, 0, 0, 0, 0, 0, 0, 2>; ///< radian2 base_quantity 

        using radian3 = base_quantity<0, 0, 0, 0, 0, 0, 0, 3>; ///< radian3 base_quantity 

        using hertz = base_quantity<0, -1, 0, 0, 0, 0, 0, 0>; ///< hertz base_quantity  

        using metre_per_second = base_quantity<1, -1, 0, 0, 0, 0, 0, 0>; ///< metre_per_second base_quantity 

        using metre_per_second2 = base_quantity<1, -2, 0, 0, 0, 0, 0, 0>; ///< metre_per_second2 base_quantity 

        using metre_per_second3 = base_quantity<1, -3, 0, 0, 0, 0, 0, 0>; ///< metre_per_second3 base_quantity 

        using metre2_per_second = base_quantity<2, -1, 0, 0, 0, 0, 0, 0>; ///< metre2_per_second base_quantity 

        using metre2_per_second2 = base_quantity<2, -2, 0, 0, 0, 0, 0, 0>; ///< metre2_per_second2 base_quantity 

        using metre2_per_second3 = base_quantity<2, -3, 0, 0, 0, 0, 0, 0>; ///< metre2_per_second3 base_quantity 

        using metre3_per_second = base_quantity<3, -1, 0, 0, 0, 0, 0, 0>; ///< metre3_per_second base_quantity 

        using metre3_per_second2 = base_quantity<3, -2, 0, 0, 0, 0, 0, 0>; ///< metre3_per_second2 base_quantity 

        using metre3_per_second3 = base_quantity<3, -3, 0, 0, 0, 0, 0, 0>; ///< metre3_per_second3 base_quantity 

        using metre_per_kilogram = base_quantity<1, 0, -1, 0, 0, 0, 0, 0>; ///< metre_per_kilogram base_quantity 

        using metre_per_kilogram2 = base_quantity<1, 0, -2, 0, 0, 0, 0, 0>; ///< metre_per_kilogram2 base_quantity 

        using metre_per_kilogram3 = base_quantity<1, 0, -3, 0, 0, 0, 0, 0>; ///< metre_per_kilogram3 base_quantity 

        using metre2_per_kilogram = base_quantity<2, 0, -1, 0, 0, 0, 0, 0>; ///< metre2_per_kilogram base_quantity 

        using metre2_per_kilogram2 = base_quantity<2, 0, -2, 0, 0, 0, 0, 0>; ///< metre2_per_kilogram2 base_quantity 

        using metre2_per_kilogram3 = base_quantity<2, 0, -3, 0, 0, 0, 0, 0>; ///< metre2_per_kilogram3 base_quantity 

        using metre3_per_kilogram = base_quantity<3, 0, -1, 0, 0, 0, 0, 0>; ///< metre3_per_kilogram base_quantity 

        using metre3_per_kilogram2 = base_quantity<3, 0, -2, 0, 0, 0, 0, 0>; ///< metre3_per_kilogram2 base_quantity 

        using metre3_per_kilogram3 = base_quantity<3, 0, -3, 0, 0, 0, 0, 0>; ///< metre3_per_kilogram3 base_quantity 

        using metre_per_ampere = base_quantity<1, 0, 0, -1, 0, 0, 0, 0>; ///< metre_per_ampere base_quantity 

        using metre_per_ampere2 = base_quantity<1, 0, 0, -2, 0, 0, 0, 0>; ///< metre_per_ampere2 base_quantity 

        using metre_per_ampere3 = base_quantity<1, 0, 0, -3, 0, 0, 0, 0>; ///< metre_per_ampere3 base_quantity 

        using metre2_per_ampere = base_quantity<2, 0, 0, -1, 0, 0, 0, 0>; ///< metre2_per_ampere base_quantity 

        using metre2_per_ampere2 = base_quantity<2, 0, 0, -2, 0, 0, 0, 0>; ///< metre2_per_ampere2 base_quantity 

        using metre2_per_ampere3 = base_quantity<2, 0, 0, -3, 0, 0, 0, 0>; ///< metre2_per_ampere3 base_quantity 

        using metre3_per_ampere = base_quantity<3, 0, 0, -1, 0, 0, 0, 0>; ///< metre3_per_ampere base_quantity 

        using metre3_per_ampere2 = base_quantity<3, 0, 0, -2, 0, 0, 0, 0>; ///< metre3_per_ampere2 base_quantity 

        using metre3_per_ampere3 = base_quantity<3, 0, 0, -3, 0, 0, 0, 0>; ///< metre3_per_ampere3 base_quantity 

        using metre_per_kelvin = base_quantity<1, 0, 0, 0, -1, 0, 0, 0>; ///< metre_per_kelvin base_quantity 

        using metre_per_kelvin2 = base_quantity<1, 0, 0, 0, -2, 0, 0, 0>; ///< metre_per_kelvin2 base_quantity 

        using metre_per_kelvin3 = base_quantity<1, 0, 0, 0, -3, 0, 0, 0>; ///< metre_per_kelvin3 base_quantity 

        using metre2_per_kelvin = base_quantity<2, 0, 0, 0, -1, 0, 0, 0>; ///< metre2_per_kelvin base_quantity 

        using metre2_per_kelvin2 = base_quantity<2, 0, 0, 0, -2, 0, 0, 0>; ///< metre2_per_kelvin2 base_quantity 

        using metre2_per_kelvin3 = base_quantity<2, 0, 0, 0, -3, 0, 0, 0>; ///< metre2_per_kelvin3 base_quantity 

        using metre3_per_kelvin = base_quantity<3, 0, 0, 0, -1, 0, 0, 0>; ///< metre3_per_kelvin base_quantity 

        using metre3_per_kelvin2 = base_quantity<3, 0, 0, 0, -2, 0, 0, 0>; ///< metre3_per_kelvin2 base_quantity 

        using metre3_per_kelvin3 = base_quantity<3, 0, 0, 0, -3, 0, 0, 0>; ///< metre3_per_kelvin3 base_quantity 


        using kilogram_metre_per_second2 = base_quantity<1, -2, 1, 0, 0, 0, 0, 0>; ///< kilogram_metre_per_second2 base_quantity  

        using kilogram_metre2_per_second2 = base_quantity<2, -2, 1, 0, 0, 0, 0, 0>; ///< kilogram_metre2_per_second2 base_quantity  

        using radian_per_second = base_quantity<0, -1, 0, 0, 0, 0, 0, 1>; ///< radian_per_second base_quantity

        using radian_per_second2 = base_quantity<0, -2, 0, 0, 0, 0, 0, 1>; ///< radian_per_second2 base_quantity



        static constexpr unit<metre> m; ///< m; unit
        static constexpr unit<second> s; ///< s unit
        static constexpr unit<kilogram> kg; ///< kg unit
        static constexpr unit<ampere> A; ///< A unit
        static constexpr unit<kelvin> K; ///< K unit
        static constexpr unit<mole> mol; ///< mol unit
        static constexpr unit<candela> cd; ///< cd unit
        static constexpr unit<radian> rad; ///< rad unit


        static constexpr unit<metre_per_second> m_s; ///< m_s unit
        static constexpr unit<metre_per_second2> m_ss; ///< m_s unit


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


} // namespace scipp::physics