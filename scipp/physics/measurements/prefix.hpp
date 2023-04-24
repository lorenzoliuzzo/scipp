/**
 * @file    physics/measurements/prefix.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the type traits for the a prefix and the map converting multipliers to prefix symbols
 * @date    2023-03-24
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    template <intmax_t N, intmax_t D>
    struct is_prefix<std::ratio<N, D>> : std::true_type {};


    /// @brief The prefix map contains all SI prefix multipliers and char representation
    static std::map<double, char> prefix_map = {

        {1.0e-24, 'y'}, //< yocto prefix
        {1.0e-21, 'z'}, //< zepto prefix
        {1.0e-18, 'a'}, //< atto prefix
        {1.0e-15, 'f'}, //< femto prefix
        {1.0e-12, 'p'}, //< pico prefix
        {1.0e-9,  'n'}, //< nano prefix
        {1.0e-6,  'u'}, //< micro prefix
        {1.0e-3,  'm'}, //< milli prefix
        {1.0e-2,  'c'}, //< centi prefix
        {1.0e-1,  'd'}, //< deci prefix
        {1.0e2,   'h'}, //< hecto prefix
        {1.0e3,   'k'}, //< kilo prefix
        {1.0e6,   'M'}, //< mega prefix
        {1.0e9,   'G'}, //< giga prefix
        {1.0e12,  'T'}, //< tera prefix
        {1.0e15,  'P'}, //< peta prefix
        {1.0e18,  'E'}, //< exa prefix
        {1.0e21,  'Z'}, //< zetta prefix
        {1.0e24,  'Y'}, //< yotta prefix

    }; 


} // namespace scipp::physics