/**
 * @file    physics/measurements/base_quantity_traits.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the base_quantity type traits.
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {
    
        
    /// @brief Type trait to check if a type is a base_quantity
    template <typename T>
    struct is_base : public std::false_type {};

    template <int LENGTH, int TIME, int MASS, int TEMPERATURE, int ELETTRIC_CURRENT, 
                int SUBSTANCE_AMOUNT, int LUMINOUS_INTENSITY>
    struct is_base<base_quantity<LENGTH, TIME, MASS, TEMPERATURE, ELETTRIC_CURRENT, 
                                    SUBSTANCE_AMOUNT, LUMINOUS_INTENSITY>> : public std::true_type {};

    template <typename T>
    constexpr bool is_base_v = is_base<T>::value;


    /// @brief Type trait to check if a list of types are base_quantities
    template <typename... Ts>
    struct are_base : public std::conjunction<is_base<Ts>...> {};

    template <typename... Ts>
    constexpr bool are_base_v = are_base<Ts...>::value;


    /// @brief Type trait to check if two base_quantity types are the same
    template <typename BASE1, typename BASE2> 
        requires (are_base_v<BASE1, BASE2>)
    struct is_same_base : public std::bool_constant<BASE1::length == BASE2::length &&
                                                    BASE1::time == BASE2::time &&
                                                    BASE1::mass == BASE2::mass &&
                                                    BASE1::temperature == BASE2::temperature &&
                                                    BASE1::elettric_current == BASE2::elettric_current &&
                                                    BASE1::substance_amount == BASE2::substance_amount &&
                                                    BASE1::luminous_intensity == BASE2::luminous_intensity> {};

    template <typename BASE1, typename BASE2>
    constexpr bool is_same_base_v = is_same_base<BASE1, BASE2>::value;


    /// @brief Type trait to check if a list of base_quantity types are the same
    template <typename BASE, typename... Ts> 
        requires (are_base_v<BASE, Ts...>)
    struct are_same_base : public std::conjunction<is_same_base<BASE, Ts>...> {};

    template <typename BASE, typename... Ts>
    constexpr bool are_same_base_v = are_same_base<BASE, Ts...>::value;


    /// @brief Type trait to check if a base_quantity type has valid root
    template <typename BASE, int POWER> 
        requires (is_base_v<BASE>)
    struct has_valid_root : public std::bool_constant<BASE::length % POWER == 0 && 
                                                        BASE::time % POWER == 0 && 
                                                        BASE::mass % POWER == 0 && 
                                                        BASE::temperature % POWER == 0 && 
                                                        BASE::elettric_current % POWER == 0 && 
                                                        BASE::substance_amount % POWER == 0 && 
                                                        BASE::luminous_intensity % POWER == 0> {};

    template <typename BASE, int POWER>
    constexpr bool has_valid_root_v = has_valid_root<BASE, POWER>::value;


    template <typename T>
    struct is_scalar : public std::false_type {};

    template <>
    struct is_scalar<base_quantity<0, 0, 0, 0, 0, 0, 0>> : public std::true_type {};


} // namespace scipp::physics