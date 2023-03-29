/**
 * @file    physics/units.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the aliases and declarations of units
 * @note    
 * @date    2023-03-24
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::physics {


    /// @brief units namespace contains the implementation of units of measurements
    namespace units {


        using scalar = base_quantity<0, 0, 0, 0, 0, 0, 0, 0, 0>; ///< scalar base_quantity 

        using metre = base_quantity<1, 0, 0, 0, 0, 0, 0, 0, 0>; ///< metre base_quantity 
        using metre2 = base_quantity<2, 0, 0, 0, 0, 0, 0, 0, 0>; ///< metre2 base_quantity 
        using metre3 = base_quantity<3, 0, 0, 0, 0, 0, 0, 0, 0>; ///< metre3 base_quantity 

        using second = base_quantity<0, 1, 0, 0, 0, 0, 0, 0, 0>; ///< second base_quantity
        using second2 = base_quantity<0, 2, 0, 0, 0, 0, 0, 0, 0>; ///< second base_quantity
        using second3 = base_quantity<0, 3, 0, 0, 0, 0, 0, 0, 0>; ///< second base_quantity

        using kilogram = base_quantity<0, 0, 1, 0, 0, 0, 0, 0, 0>; ///< kilogram base_quantity
        using kilogram2 = base_quantity<0, 0, 2, 0, 0, 0, 0, 0, 0>; ///< kilogram base_quantity
        using kilogram3 = base_quantity<0, 0, 3, 0, 0, 0, 0, 0, 0>; ///< kilogram base_quantity

        using kelvin = base_quantity<0, 0, 0, 1, 0, 0, 0, 0, 0>; ///< kelvin base_quantity
        using kelvin2 = base_quantity<0, 0, 0, 2, 0, 0, 0, 0, 0>; ///< kelvin base_quantity
        using kelvin3 = base_quantity<0, 0, 0, 3, 0, 0, 0, 0, 0>; ///< kelvin base_quantity
                
        using ampere = base_quantity<0, 0, 0, 0, 1, 0, 0, 0, 0>; ///< ampere base_quantity
        using ampere2 = base_quantity<0, 0, 0, 0, 2, 0, 0, 0, 0>; ///< ampere base_quantity
        using ampere3 = base_quantity<0, 0, 0, 0, 3, 0, 0, 0, 0>; ///< ampere base_quantity

        using mole = base_quantity<0, 0, 0, 0, 0, 1, 0, 0, 0>; ///< mole base_quantity
        using mole2 = base_quantity<0, 0, 0, 0, 0, 2, 0, 0, 0>; ///< mole base_quantity

        using candela = base_quantity<0, 0, 0, 0, 0, 0, 1, 0, 0>; ///< candela base_quantity
        using candela2 = base_quantity<0, 0, 0, 0, 0, 0, 2, 0, 0>; ///< candela base_quantity

        using radian = base_quantity<0, 0, 0, 0, 0, 0, 0, 1, 0>; ///< radian base_quantity
        using radian2 = base_quantity<0, 0, 0, 0, 0, 0, 0, 2, 0>; ///< radian base_quantity

        using steradian = base_quantity<0, 0, 0, 0, 0, 0, 0, 0, 1>; ///< steradian base_quantity    
        using steradian2 = base_quantity<0, 0, 0, 0, 0, 0, 0, 0, 2>; ///< steradian base_quantity

        using metre_per_second = base_quantity<1, -1, 0, 0, 0, 0, 0, 0, 0>; ///< metre_per_second base_quantity 

        using metre_per_second2 = base_quantity<1, -2, 0, 0, 0, 0, 0, 0, 0>; ///< metre_per_second2 base_quantity 

        using metre_per_second3 = base_quantity<1, -3, 0, 0, 0, 0, 0, 0, 0>; ///< metre_per_second3 base_quantity 

        using metre2_per_second = base_quantity<2, -1, 0, 0, 0, 0, 0, 0, 0>; ///< metre2_per_second base_quantity 

        using metre2_per_second2 = base_quantity<2, -2, 0, 0, 0, 0, 0, 0, 0>; ///< metre2_per_second2 base_quantity 

        using metre2_per_second3 = base_quantity<2, -3, 0, 0, 0, 0, 0, 0, 0>; ///< metre2_per_second3 base_quantity 

        using metre3_per_second = base_quantity<3, -1, 0, 0, 0, 0, 0, 0, 0>; ///< metre3_per_second base_quantity 

        using metre3_per_second2 = base_quantity<3, -2, 0, 0, 0, 0, 0, 0, 0>; ///< metre3_per_second2 base_quantity 

        using metre3_per_second3 = base_quantity<3, -3, 0, 0, 0, 0, 0, 0, 0>; ///< metre3_per_second3 base_quantity 

        using metre_per_kilogram = base_quantity<1, 0, -1, 0, 0, 0, 0, 0, 0>; ///< metre_per_kilogram base_quantity 

        using metre_per_kilogram2 = base_quantity<1, 0, -2, 0, 0, 0, 0, 0, 0>; ///< metre_per_kilogram2 base_quantity 

        using metre_per_kilogram3 = base_quantity<1, 0, -3, 0, 0, 0, 0, 0, 0>; ///< metre_per_kilogram3 base_quantity 

        using metre2_per_kilogram = base_quantity<2, 0, -1, 0, 0, 0, 0, 0, 0>; ///< metre2_per_kilogram base_quantity 

        using metre2_per_kilogram2 = base_quantity<2, 0, -2, 0, 0, 0, 0, 0, 0>; ///< metre2_per_kilogram2 base_quantity 

        using metre2_per_kilogram3 = base_quantity<2, 0, -3, 0, 0, 0, 0, 0, 0>; ///< metre2_per_kilogram3 base_quantity 

        using metre3_per_kilogram = base_quantity<3, 0, -1, 0, 0, 0, 0, 0, 0>; ///< metre3_per_kilogram base_quantity 

        using metre3_per_kilogram2 = base_quantity<3, 0, -2, 0, 0, 0, 0, 0, 0>; ///< metre3_per_kilogram2 base_quantity 

        using metre3_per_kilogram3 = base_quantity<3, 0, -3, 0, 0, 0, 0, 0, 0>; ///< metre3_per_kilogram3 base_quantity 

        using metre_per_ampere = base_quantity<1, 0, 0, -1, 0, 0, 0, 0, 0>; ///< metre_per_ampere base_quantity 

        using metre_per_ampere2 = base_quantity<1, 0, 0, -2, 0, 0, 0, 0, 0>; ///< metre_per_ampere2 base_quantity 

        using metre_per_ampere3 = base_quantity<1, 0, 0, -3, 0, 0, 0, 0, 0>; ///< metre_per_ampere3 base_quantity 

        using metre2_per_ampere = base_quantity<2, 0, 0, -1, 0, 0, 0, 0, 0>; ///< metre2_per_ampere base_quantity 

        using metre2_per_ampere2 = base_quantity<2, 0, 0, -2, 0, 0, 0, 0, 0>; ///< metre2_per_ampere2 base_quantity 

        using metre2_per_ampere3 = base_quantity<2, 0, 0, -3, 0, 0, 0, 0, 0>; ///< metre2_per_ampere3 base_quantity 

        using metre3_per_ampere = base_quantity<3, 0, 0, -1, 0, 0, 0, 0, 0>; ///< metre3_per_ampere base_quantity 

        using metre3_per_ampere2 = base_quantity<3, 0, 0, -2, 0, 0, 0, 0, 0>; ///< metre3_per_ampere2 base_quantity 

        using metre3_per_ampere3 = base_quantity<3, 0, 0, -3, 0, 0, 0, 0, 0>; ///< metre3_per_ampere3 base_quantity 

        using metre_per_kelvin = base_quantity<1, 0, 0, 0, -1, 0, 0, 0, 0>; ///< metre_per_kelvin base_quantity 

        using metre_per_kelvin2 = base_quantity<1, 0, 0, 0, -2, 0, 0, 0, 0>; ///< metre_per_kelvin2 base_quantity 

        using metre_per_kelvin3 = base_quantity<1, 0, 0, 0, -3, 0, 0, 0, 0>; ///< metre_per_kelvin3 base_quantity 

        using metre2_per_kelvin = base_quantity<2, 0, 0, 0, -1, 0, 0, 0, 0>; ///< metre2_per_kelvin base_quantity 

        using metre2_per_kelvin2 = base_quantity<2, 0, 0, 0, -2, 0, 0, 0, 0>; ///< metre2_per_kelvin2 base_quantity 

        using metre2_per_kelvin3 = base_quantity<2, 0, 0, 0, -3, 0, 0, 0, 0>; ///< metre2_per_kelvin3 base_quantity 

        using metre3_per_kelvin = base_quantity<3, 0, 0, 0, -1, 0, 0, 0, 0>; ///< metre3_per_kelvin base_quantity 

        using metre3_per_kelvin2 = base_quantity<3, 0, 0, 0, -2, 0, 0, 0, 0>; ///< metre3_per_kelvin2 base_quantity 

        using metre3_per_kelvin3 = base_quantity<3, 0, 0, 0, -3, 0, 0, 0, 0>; ///< metre3_per_kelvin3 base_quantity 


        using kilogram_metre_per_second2 = base_quantity<1, -2, 1, 0, 0, 0, 0, 0, 0>; ///< kilogram_metre_per_second2 base_quantity  

        using kilogram_metre2_per_second2 = base_quantity<2, -2, 1, 0, 0, 0, 0, 0, 0>; ///< kilogram_metre2_per_second2 base_quantity  

        using radian_per_second = base_quantity<0, -1, 0, 0, 0, 0, 0, 1, 0>; ///< radian_per_second base_quantity

        using radian_per_second2 = base_quantity<0, -2, 0, 0, 0, 0, 0, 1, 0>; ///< radian_per_second2 base_quantity


    /// =================================================
    /// Composed base_quantity
    /// =================================================

        using hertz = base_quantity<0, -1, 0, 0, 0, 0, 0, 0, 0>; ///< hertz base_quantity  

        using newton = base_quantity<1, -2, 1, 0, 0, 0, 0, 0, 0>; ///< newton base_quantity

        using pascal = base_quantity<-1, -2, 1, 0, 0, 0, 0, 0, 0>; ///< pascal base_quantity

        using joule = base_quantity<2, -2, 1, 0, 0, 0, 0, 0, 0>; ///< joule base_quantity

        using watt = base_quantity<2, -3, 1, 0, 0, 0, 0, 0, 0>; ///< watt base_quantity

        using coulomb = base_quantity<0, 0, 1, 1, 0, 0, 0, 0, 0>; ///< coulomb base_quantity

        using volt = base_quantity<2, -3, 1, -1, 0, 0, 0, 0, 0>; ///< volt base_quantity

        using farad = base_quantity<-2, -2, -1, 2, 0, 0, 0, 0, 0>; ///< farad base_quantity

        using ohm = base_quantity<2, -3, 1, -2, 0, 0, 0, 0, 0>; ///< ohm base_quantity

        using siemens = base_quantity<-2, -3, -1, 2, 0, 0, 0, 0, 0>; ///< siemens base_quantity

        using weber = base_quantity<2, -2, 1, -1, 0, 0, 0, 0, 0>; ///< weber base_quantity

        using tesla = base_quantity<0, -2, 1, -1, 0, 0, 0, 0, 0>; ///< tesla base_quantity

        using henry = base_quantity<2, -2, 1, -2, 0, 0, 0, 0, 0>; ///< henry base_quantity


    /// =================================================
    /// Length units
    /// =================================================

        inline static constexpr unit<metre> m; ///< m; unit

        using kilometre = unit<metre, std::kilo>; ///< kilometre unit
        inline static constexpr kilometre km; ///< Km unit

        using hectometre = unit<metre, std::hecto>; ///< hectometre unit
        inline static constexpr hectometre hm; ///< hm unit

        using decametre = unit<metre, std::deca>; ///< decametre unit
        inline static constexpr decametre dam; ///< dam unit

        using centimetre = unit<metre, std::centi>; 
        inline static constexpr centimetre cm; ///< cm unit

        using millimetre = unit<metre, std::milli>; ///< millimetre unit
        inline static constexpr millimetre mm; ///< mm unit

        using micrometre = unit<metre, std::micro>; ///< micrometre unit
        inline static constexpr micrometre um; ///< um unit

        using nanometre = unit<metre, std::nano>; ///< nanometre unit
        inline static constexpr nanometre nm; ///< nm unit

        using picometre = unit<metre, std::pico>; ///< picometre unit
        inline static constexpr picometre pm; ///< pm unit

        using inch = unit<metre, std::ratio<254, 10000>>; ///< inch unit
        inline static constexpr inch in; ///< in unit

        using foot = unit<metre, std::ratio<3048, 10000>>; ///< foot unit
        inline static constexpr foot ft; ///< ft unit

        using yard = unit<metre, std::ratio<9144, 10000>>; ///< yard unit
        inline static constexpr yard yd; ///< yd unit

        using mile = unit<metre, std::ratio<1609344, 10000>>; ///< mile unit
        inline static constexpr mile mi; ///< mi unit

        using nautical_mile = unit<metre, std::ratio<1852000, 10000>>; ///< nautical_mile unit
        inline static constexpr nautical_mile nmi; ///< nmi unit

        using kilometre2 = unit<metre2, std::kilo>; ///< kilometre2 unit
        inline static constexpr kilometre2 km2; ///< km2 unit

        using hectometre2 = unit<metre2, std::hecto>; ///< hectometre2 unit
        inline static constexpr hectometre2 hm2; ///< hm2 unit

        using decametre2 = unit<metre2, std::deca>; ///< decametre2 unit
        inline static constexpr decametre2 dam2; ///< dam2 unit

        using centimetre2 = unit<metre2, std::centi>; ///< centimetre2 unit
        inline static constexpr centimetre2 cm2; ///< cm2 unit

        using millimetre2 = unit<metre2, std::milli>; ///< millimetre2 unit
        inline static constexpr millimetre2 mm2; ///< mm2 unit

        using micrometre2 = unit<metre2, std::micro>; ///< micrometre2 unit
        inline static constexpr micrometre2 um2; ///< um2 unit

        using nanometre2 = unit<metre2, std::nano>; ///< nanometre2 unit
        inline static constexpr nanometre2 nm2; ///< nm2 unit

        using picometre2 = unit<metre2, std::pico>; ///< picometre2 unit
        inline static constexpr picometre2 pm2; ///< pm2 unit


        inline static constexpr unit<second> s; ///< s unit
        inline static constexpr unit<kilogram> kg; ///< kg unit
        inline static constexpr unit<ampere> A; ///< A unit
        inline static constexpr unit<kelvin> K; ///< K unit
        inline static constexpr unit<mole> mol; ///< mol unit
        inline static constexpr unit<candela> cd; ///< cd unit
        inline static constexpr unit<radian> rad; ///< rad unit


        inline static constexpr unit<metre_per_second> m_s; ///< m_s unit
        inline static constexpr unit<metre_per_second2> m_ss; ///< m_s unit

        inline static constexpr unit<metre2, std::kilo> Km2; ///< Km2 unit

        inline static constexpr unit<second, std::nano> ns; ///< ns unit 

        inline static constexpr unit<second, std::ratio<60, 1>> min; ///< min unit 

        inline static constexpr unit<hertz, std::giga> GHz; ///< GHz unit

        inline static constexpr unit<kilogram2> kg2; ///< kg2 unit
        inline static constexpr unit<metre2> m2; ///< m2 unit
        inline static constexpr unit<second2> s2; ///< s2 unit
        inline static constexpr unit<ampere2> A2; ///< A2 unit

        inline static constexpr auto N = kg * m / s2; ///< s2 unit
        inline static constexpr auto Pa = N / m2; ///< m2 unit
        inline static constexpr auto J = N * m; ///< J unit
        inline static constexpr auto W = J / s; ///< W unit
        inline static constexpr auto C = A * s; ///< C unit
        inline static constexpr auto V = W / A; ///< V unit


    } // namespace units


} // namespace scipp::physics