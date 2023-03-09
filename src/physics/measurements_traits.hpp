/**
 * @file    measurements_traits.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-08-09
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {
    

    template <typename T>
    struct is_measurement : std::false_type {};

    template <typename BASE>
    struct is_measurement<measurement<BASE>> : std::true_type {};

    template <typename T>
    constexpr 
    bool is_measurement_v = is_measurement<T>::value;


    template <typename... Ts>
    struct are_measurements : std::conjunction<is_measurement<Ts>...> {};

    template <typename... Ts>
    constexpr 
    bool are_measurements_v = are_measurements<Ts...>::value;


    template <typename T, typename... Ts>
    struct are_same_measurements : std::false_type {};


    template <typename BASE>
    struct are_same_measurements<measurement<BASE>> : std::true_type {};

    
    template <typename BASE1, typename BASE2>
        requires (are_same_base_v<BASE1, BASE2>)
    struct are_same_measurements<measurement<BASE1>, measurement<BASE2>> : std::true_type {};


    template <typename T, typename... Ts>
    constexpr
    bool are_same_measurements_v = are_same_measurements<T, Ts...>::value;


} // namespace scipp::physics

