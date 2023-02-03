/**
 * @file    units_types.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
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

        static constexpr unit<second, std::nano> ns; 

        static constexpr unit<second, std::ratio<60, 1>> min; 

        static constexpr unit<hertz, std::giga> GHz;


        static constexpr auto m2 = unit<metre2>();
        static constexpr auto s2 = unit<second2>();
        

        static_assert(is_unit_v<decltype(m)>);
        static_assert(is_unit_v<decltype(Km)>);


        static constexpr auto N = kg * m / s2;


    } // namespace units


} // namespace scipp::physics