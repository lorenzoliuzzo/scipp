/**
 * @file    physics/unit.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementations of the unit struct.
 * @note    
 * @date    2023-03-08
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {



    
    /// @brief unit is an union of an base_quantity and an std::ratio prefix
    /// @tparam BASE_TYPE: meta_base of the unit
    /// @tparam PREFIX_TYPE: std::ratio prefix of the unit
    template <typename BASE_TYPE, typename PREFIX_TYPE = std::ratio<1>> 
        requires (is_base_v<BASE_TYPE>)  
    struct unit {


        // =============================================
        // type aliases
        // =============================================

            using base = BASE_TYPE;

            using prefix = PREFIX_TYPE;

            using type = unit<base, prefix>; 


        // =============================================
        // static members
        // =============================================

            inline static constexpr double mult = static_cast<double>(prefix::num) / static_cast<double>(prefix::den);


        // =============================================
        // operators
        // =============================================

            friend inline constexpr std::ofstream& operator<<(std::ofstream& os, const unit&) noexcept {

                os << unit::to_string();
                return os;

            }


        // =============================================
        // methods
        // =============================================

            /// @brief prefix_symbol returns a char representation of the prefix
            inline static constexpr auto prefix_symbol() noexcept {

                if      constexpr (mult == 1.e-24) return "[y]"; //< yocto prefix
                else if constexpr (mult == 1.e-21) return "[z]"; //< zepto prefix
                else if constexpr (mult == 1.e-18) return "[a]"; //< atto prefix
                else if constexpr (mult == 1.e-15) return "[f]"; //< femto prefix
                else if constexpr (mult == 1.e-12) return "[p]"; //< pico prefix
                else if constexpr (mult == 1.e-9)  return "[n]"; //< nano prefix
                else if constexpr (mult == 1.e-6)  return "[u]"; //< micro prefix
                else if constexpr (mult == 1.e-3)  return "[m]"; //< milli prefix
                else if constexpr (mult == 1.e-2)  return "[c]"; //< centi prefix
                else if constexpr (mult == 1.e-1)  return "[d]"; //< deci prefix
                else if constexpr (mult == 1.e2)   return "[h]"; //< hecto prefix
                else if constexpr (mult == 1.e3)   return "[K]"; //< kilo prefix
                else if constexpr (mult == 1.e6)   return "[M]"; //< mega prefix
                else if constexpr (mult == 1.e9)   return "[G]"; //< giga prefix
                else if constexpr (mult == 1.e12)  return "[T]"; //< tera prefix
                else if constexpr (mult == 1.e15)  return "[P]"; //< peta prefix
                else if constexpr (mult == 1.e18)  return "[E]"; //< exa prefix
                else if constexpr (mult == 1.e21)  return "[Z]"; //< zetta prefix
                else if constexpr (mult == 1.e24)  return "[Y]"; //< yotta prefix
                else                               return ;

            }


            /// @brief to_string returns a string representation of the unit
            static constexpr std::string to_string() noexcept {

                return prefix_symbol() + base::to_string(); 

            }


            /// @brief Convert a value from the base unit to another unit 
            template <typename OTHER_UNIT> 
                requires(is_same_base_v<base, typename OTHER_UNIT::base>)
            static constexpr double convert(const double val, const OTHER_UNIT&) noexcept {

                return val * mult / OTHER_UNIT::mult; 

            }


    }; // struct unit


    // =============================================
    // unit traits
    // =============================================

        template <typename T>
        struct is_prefix : std::false_type {};

        template <intmax_t N, intmax_t D>
        struct is_prefix<std::ratio<N, D>> : std::true_type {};

        template <typename T>
        inline constexpr bool is_prefix_v = is_prefix<T>::value;


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


        template <typename... Ts>
        struct are_units : std::conjunction<is_unit<Ts>...> {};

        template <typename... Ts>
        inline constexpr bool are_units_v = are_units<Ts...>::value;
        

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


        template <typename T>
        struct is_prefixed : std::false_type {};

        template <typename BASE>
        struct is_prefixed<unit<BASE>> : std::false_type {};

        template <typename BASE, typename PREFIX>
        struct is_prefixed<unit<BASE, PREFIX>> : std::true_type {};

        template <typename T>
        inline constexpr bool is_prefixed_v = is_prefixed<T>::value;


        template <typename T>
        struct is_base_unit : std::false_type {};

        template <typename BASE>
        struct is_base_unit<unit<BASE>> : std::true_type {};

        template <typename T>
        inline constexpr bool is_base_unit_v = is_base_unit<T>::value;


} // namespace scipp::physics 