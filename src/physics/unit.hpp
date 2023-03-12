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
    /// @tparam BASE: meta_base of the unit
    /// @tparam PREFIX: std::ratio prefix of the unit
    template <typename BASE, typename PREFIX = std::ratio<1>> 
        requires (is_base_v<BASE>)
        
    struct unit {


        // =============================================
        // type aliases
        // =============================================

            using base = BASE;

            using prefix = PREFIX;

            using type = unit<BASE, PREFIX>; 


        // =============================================
        // static members
        // =============================================

            inline static constexpr double mult = static_cast<double>(PREFIX::num) / static_cast<double>(PREFIX::den);


        // =============================================
        // operators
        // =============================================

            friend inline constexpr std::ostream& operator<<(std::ostream& os, const unit&) noexcept {

                return os << unit::to_string();

            }


        // =============================================
        // methods
        // =============================================

            /// @brief prefix_symbol returns a char representation of the prefix
            inline static constexpr char prefix_symbol() noexcept {

                if      constexpr (mult == 1.e-24) return 'y'; //< yocto prefix
                else if constexpr (mult == 1.e-21) return 'z'; //< zepto prefix
                else if constexpr (mult == 1.e-18) return 'a'; //< atto prefix
                else if constexpr (mult == 1.e-15) return 'f'; //< femto prefix
                else if constexpr (mult == 1.e-12) return 'p'; //< pico prefix
                else if constexpr (mult == 1.e-9)  return 'n'; //< nano prefix
                else if constexpr (mult == 1.e-6)  return 'u'; //< micro prefix
                else if constexpr (mult == 1.e-3)  return 'm'; //< milli prefix
                else if constexpr (mult == 1.e-2)  return 'c'; //< centi prefix
                else if constexpr (mult == 1.e-1)  return 'd'; //< deci prefix
                else if constexpr (mult == 1.e2)   return 'h'; //< hecto prefix
                else if constexpr (mult == 1.e3)   return 'K'; //< kilo prefix
                else if constexpr (mult == 1.e6)   return 'M'; //< mega prefix
                else if constexpr (mult == 1.e9)   return 'G'; //< giga prefix
                else if constexpr (mult == 1.e12)  return 'T'; //< tera prefix
                else if constexpr (mult == 1.e15)  return 'P'; //< peta prefix
                else if constexpr (mult == 1.e18)  return 'E'; //< exa prefix
                else if constexpr (mult == 1.e21)  return 'Z'; //< zetta prefix
                else if constexpr (mult == 1.e24)  return 'Y'; //< yotta prefix
                else                               return ' ';

            }


            /// @brief to_string returns a string representation of the unit
            static constexpr std::string to_string() noexcept {

                return prefix_symbol() + BASE::to_string(); 

            }


            /// @brief Convert a value from the base unit to another unit 
            template <typename UNIT> requires(is_same_base_v<BASE, typename UNIT::base>)
            static constexpr double convert(const double val, const UNIT&) noexcept {

                return val * mult / UNIT::mult; 

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


    // =============================================
    // ALGEBRIC FUNCTIONS
    // =============================================

        template <typename RATIO, int POWER>
        struct ratio_pow : public std::ratio<std::pow(RATIO::num, POWER), std::pow(RATIO::den, POWER)> {};

        template <typename RATIO, int POWER>
        using ratio_pow_t = typename ratio_pow<RATIO, POWER>::type;


        template <typename RATIO, int POWER>
        struct ratio_root : public std::ratio<std::pow(RATIO::num, 1. / POWER), std::pow(RATIO::den, 1. / POWER)> {};

        template <typename RATIO, int POWER>
        using ratio_root_t = typename ratio_root<RATIO, POWER>::type;


        template <typename RATIO>
        struct ratio_inv : public std::ratio<RATIO::den, RATIO::num> {}; 

        template <typename RATIO>
        using ratio_inv_t = typename ratio_inv<RATIO>::type;
    

        template <typename UNIT1, typename UNIT2> 
            requires (are_units_v<UNIT1, UNIT2>)
        struct unit_prod : public unit<base_prod_t<typename UNIT1::base, typename UNIT2::base>, 
                                       std::ratio_multiply<typename UNIT1::prefix, typename UNIT2::prefix>> {};

        template <typename UNIT1, typename UNIT2> 
            requires (are_units_v<UNIT1, UNIT2>)
        using unit_prod_t = typename unit_prod<UNIT1, UNIT2>::type; 


        template <typename UNIT1, typename UNIT2> 
            requires (are_units_v<UNIT1, UNIT2>)
        struct unit_div : public unit<base_div_t<typename UNIT1::base, typename UNIT2::base>, 
                                      std::ratio_divide<typename UNIT1::prefix, typename UNIT2::prefix>> {};


        template <typename UNIT1, typename UNIT2> 
            requires (are_units_v<UNIT1, UNIT2>)
        using unit_div_t = typename unit_div<UNIT1, UNIT2>::type; 


        template <typename UNIT, int POWER>
        struct unit_pow : public unit<base_pow_t<typename UNIT::base, POWER>, 
                                        ratio_pow_t<typename UNIT::prefix, POWER>> {};

        template <typename UNIT, int POWER>
        using unit_pow_t = typename unit_pow<UNIT, POWER>::type;


        template <typename UNIT, int POWER>
        struct unit_root : public unit<base_root_t<typename UNIT::base, POWER>, 
                                        ratio_root_t<typename UNIT::prefix, POWER>> {};


        template <typename UNIT, int POWER>
        using unit_root_t = typename unit_root<UNIT, POWER>::type;


        template <typename UNIT>
        struct unit_inv : public unit<base_inv_t<typename UNIT::base>,  
                                        ratio_inv_t<typename UNIT::prefix>> {}; 

        template <typename UNIT>
        using unit_inv_t = typename unit_inv<UNIT>::type;


        /// @brief Perform a multiplication between unit 
        template <typename unit1, typename unit2> requires (are_units_v<unit1, unit2>)
        constexpr auto operator*(const unit1&, const unit2&) noexcept -> unit_prod_t<typename unit1::type, typename unit2::type> {
            
            return unit_prod_t<typename unit1::type, typename unit2::type>(); 
            
        } 


        /// @brief Perform a division between unit 
        template <typename unit1, typename unit2> requires (are_units_v<unit1, unit2>)
        constexpr auto operator/(const unit1&, const unit2&) noexcept -> unit_div_t<typename unit1::type, typename unit2::type> {
            
            return unit_div_t<typename unit1::type, typename unit2::type>(); 
            
        } 


} // namespace scipp::physics 