/**
 * @file    physics/measurements/unit.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the unit type traits.
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    /// @brief Type trait to check if a type is an unit
    template <typename T>
    struct is_unit : std::false_type {};

    template <typename BASE>
        requires (is_base_v<BASE>)
    struct is_unit<unit<BASE>> : std::true_type {};

    template <typename BASE, typename PREFIX>
        requires (is_base_v<BASE> && is_prefix_v<PREFIX>)
    struct is_unit<unit<BASE, PREFIX>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_unit_v = is_unit<T>::value;


    /// @brief Type trait to check if a type is the same unit as another unit type
    template <typename T1, typename T2>
    struct is_same_unit : std::false_type {};

    template <typename BASE> 
        requires (is_base_v<BASE>)
    struct is_same_unit<unit<BASE>, unit<BASE>> : std::true_type {};

    template <typename BASE, typename PREFIX> 
        requires (is_base_v<BASE> && is_prefix_v<PREFIX>)
    struct is_same_unit<unit<BASE>, unit<BASE, PREFIX>> : std::true_type {};

    template <typename BASE, typename PREFIX> 
        requires (is_base_v<BASE> && is_prefix_v<PREFIX>)
    struct is_same_unit<unit<BASE, PREFIX>, unit<BASE>> : std::true_type {};

    template <typename BASE, typename PREFIX> 
        requires (is_base_v<BASE>)
    struct is_same_unit<unit<BASE, PREFIX>, unit<BASE, PREFIX>> : std::true_type {};

    template <typename T1, typename T2>
    inline constexpr bool is_same_unit_v = is_same_unit<T1, T2>::value;


    /// @brief Type trait to check if a list of types are unit types
    template <typename... Ts>
    struct are_units : std::conjunction<is_unit<Ts>...> {};

    template <typename... Ts>
    inline constexpr bool are_units_v = are_units<Ts...>::value;
    

    /// @brief Type trait to check if a list of types are the same unit type
    template <typename... Ts> 
        requires (are_units_v<Ts...>)
    struct are_same_units : std::false_type {};

    template <typename T>
        requires (is_unit_v<T>)
    struct are_same_units<T> : std::true_type {};

    template <typename T1, typename T2>
        requires (are_units_v<T1, T2>)
    struct are_same_units<T1, T2> : is_same_unit<T1, T2> {};

    template <typename T1, typename... Ts> 
    struct are_same_units<T1, Ts...> : std::conjunction<are_same_units<Ts..., Ts...>> {};

    template <typename... Ts>
    inline constexpr bool are_same_units_v = are_same_units<Ts...>::value;


    /// @brief Type trait to check if an unit type is prefixed
    template <typename T>
    struct is_prefixed : std::false_type {};

    template <typename BASE>
    struct is_prefixed<unit<BASE>> : std::false_type {};

    template <typename BASE, typename PREFIX>
    struct is_prefixed<unit<BASE, PREFIX>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_prefixed_v = is_prefixed<T>::value;


    /// @brief Type trait to check if an unit type is a base unit type
    template <typename T>
    struct is_base_unit : std::false_type {};

    template <typename BASE>
    struct is_base_unit<unit<BASE>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_base_unit_v = is_base_unit<T>::value;


} // namespace scipp::physics