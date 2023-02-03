/**
 * @file    prefix.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {

    
    /// @brief units namespace contains all the units of the measurements library
    namespace units {


        std::map<double, char> prefix_map = {

            {1.e-24, 'y'}, //< yocto prefix

            {1.e-21, 'z'}, //< zepto prefix

            {1.e-18, 'a'}, //< atto prefix

            {1.e-15, 'f'}, //< femto prefix

            {1.e-12, 'p'}, //< pico prefix

            {1.e-9, 'n'}, //< nano prefix

            {1.e-6, 'u'}, //< micro prefix

            {1.e-3, 'm'}, //< milli prefix

            {1.e-2, 'c'}, //< centi prefix

            {1.e-1, 'd'}, //< deci prefix

            {1.e2, 'h'}, //< hecto prefix

            {1.e3, 'K'}, //< kilo prefix

            {1.e6, 'M'}, //< mega prefix

            {1.e9, 'G'}, //< giga prefix
    
            {1.e12, 'T'}, //< tera prefix

            {1.e15, 'P'}, //< peta prefix

            {1.e18, 'E'}, //< exa prefix

            {1.e21, 'Z'}, //< zetta prefix

            {1.e24, 'Y'} //< yotta prefix

        };


    } // namespace meta_units


} // namespace scipp::physics