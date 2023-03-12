/**
 * @file    physics/measurements/unit.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementations of the structs unit_base and unit, their callable functions and type traits.
 * @note    The aim is to work with unit_base on the backend and unit on the frontend. So, the user should not use unit_base directly.
 * @date    2023-02-17
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {

    
    /// @brief units namespace contains the implementation of units of measurements
    namespace units {


        /// @brief unit_base is a struct that represents a base for a physical unit
        /// @tparam metre_pow: power of metre
        /// @tparam second_pow: power of second
        /// @tparam kilogram_pow: power of kilogram
        /// @tparam ampere_pow: power of ampere
        /// @tparam kelvin_pow: power of kelvin
        /// @tparam mole_pow: power of mole
        /// @tparam candela_pow: power of candela
        /// @tparam radian_pow: power of radian
        template <int metre_pow, 
                  int second_pow, 
                  int kilogram_pow, 
                  int ampere_pow, 
                  int kelvin_pow, 
                  int mole_pow, 
                  int candela_pow, 
                  int radian_pow>

        struct unit_base {


            // =============================================
            // aliases
            // =============================================

                using type = unit_base<metre_pow, 
                                       second_pow, 
                                       kilogram_pow, 
                                       ampere_pow, 
                                       kelvin_pow, 
                                       mole_pow, 
                                       candela_pow, 
                                       radian_pow>; /// type of the unit_base


            // =============================================
            // static members
            // ============================================= 

                inline static constexpr int metre = metre_pow;       /// power of metre
                
                inline static constexpr int second = second_pow;     /// power of second
                
                inline static constexpr int kilogram = kilogram_pow; /// power of kilogram
                
                inline static constexpr int ampere = ampere_pow;     /// power of ampere
                
                inline static constexpr int kelvin = kelvin_pow;     /// power of kelvin
                
                inline static constexpr int mole = mole_pow;         /// power of mole
                
                inline static constexpr int candela = candela_pow;   /// power of candela
                
                inline static constexpr int radian = radian_pow;     /// power of radian


            // =============================================
            // methods
            // =============================================

                /// @brief  Get the unit_base string as a concatenation of the base unit symbol with their powers.
                /// @return static constexpr std::string 
                static constexpr std::string to_string() noexcept {
                    
                    std::string base_string;   
                    
                    if constexpr (metre_pow != 0) {

                        base_string.append("m");

                        if constexpr (metre_pow != 1) 
                            base_string.append("^" + std::to_string(metre_pow)); 

                    }

                    if constexpr (second_pow != 0) {

                        base_string.append("s");

                        if constexpr (second_pow != 1) 
                            base_string.append("^" + std::to_string(second_pow)); 

                    }

                    if constexpr (kilogram_pow != 0) { 

                        base_string.append("kg"); 

                        if constexpr (kilogram_pow != 1) 
                            base_string.append("^" + std::to_string(kilogram_pow)); 

                    }

                    if constexpr (ampere_pow != 0) {

                        base_string.append("A"); 

                        if constexpr (ampere_pow != 1) 
                            base_string.append("^" + std::to_string(ampere_pow)); 

                    }

                    if constexpr (kelvin_pow != 0) {

                        base_string.append("K");

                        if constexpr (kelvin_pow != 1) 
                            base_string.append("^" + std::to_string(kelvin_pow)); 

                    }

                    if constexpr (mole_pow != 0) {

                        base_string.append("mol"); 

                        if constexpr (mole_pow != 1) 
                            base_string.append("^" + std::to_string(mole_pow)); 

                    }

                    if constexpr (candela_pow != 0) {

                        base_string.append("cd"); 

                        if constexpr (candela_pow != 1) 
                            base_string.append("^" + std::to_string(candela_pow)); 

                    }

                    if constexpr (radian_pow != 0) {

                        base_string.append("rad"); 

                        if constexpr (radian_pow != 1) 
                            base_string.append("^" + std::to_string(radian_pow)); 


                    }

                    return base_string; 
                
                }


        }; // struct base


        // =============================================
        // unit_base type traits
        // =============================================

            template <typename T>
            struct is_base : std::false_type {};

            template <int metre_pow, int second_pow, int kilogram_pow, int ampere_pow, int kelvin_pow, int mole_pow, int candela_pow, int radian_pow>
            struct is_base<unit_base<metre_pow, second_pow, kilogram_pow, ampere_pow, kelvin_pow, mole_pow, candela_pow, radian_pow>> : std::true_type {};

            template <typename T>
            inline constexpr bool is_base_v = is_base<T>::value;


            template <typename... BASES>
            struct are_base : std::conjunction<is_base<BASES>...> {};

            template <typename... BASES>
            inline constexpr bool are_base_v = are_base<BASES...>::value;


            template <typename BASE1, typename BASE2> requires (are_base_v<BASE1, BASE2>)
            struct is_same_base : public std::bool_constant<BASE1::metre == BASE2::metre && 
                                                            BASE1::second == BASE2::second && 
                                                            BASE1::kilogram == BASE2::kilogram && 
                                                            BASE1::ampere == BASE2::ampere && 
                                                            BASE1::kelvin == BASE2::kelvin && 
                                                            BASE1::mole == BASE2::mole && 
                                                            BASE1::candela == BASE2::candela && 
                                                            BASE1::radian == BASE2::radian> {};

            template <typename BASE1, typename BASE2> requires (are_base_v<BASE1, BASE2>)
            inline constexpr bool is_same_base_v = is_same_base<BASE1, BASE2>::value;


            template <typename... BASES>
            struct are_same_base : public std::conjunction<is_same_base<BASES, BASES>...> {};

            template <typename... BASES>
            inline constexpr bool are_same_base_v = are_same_base<BASES...>::value;


            template <typename base, int power> requires (is_base_v<base>)
            struct has_valid_root : public std::bool_constant<(base::metre % power == 0) && 
                                                              (base::second % power == 0) && 
                                                              (base::kilogram % power == 0) && 
                                                              (base::ampere % power == 0) && 
                                                              (base::kelvin % power == 0) && 
                                                              (base::mole % power == 0) && 
                                                              (base::candela % power == 0) && 
                                                              (base::radian % power == 0)> {};

            template <typename base, int power>
            inline constexpr bool has_valid_root_v = has_valid_root<base, power>::value;



        // =============================================
        // unit_base operations
        // =============================================

            /// @brief base_prod is a struct to compute the product of two base
            template <typename BASE1, typename BASE2> requires (are_base_v<BASE1, BASE2>)
            struct base_prod : public unit_base <BASE1::metre + BASE2::metre, 
                                                 BASE1::second + BASE2::second,
                                                 BASE1::kilogram + BASE2::kilogram,
                                                 BASE1::ampere + BASE2::ampere,
                                                 BASE1::kelvin + BASE2::kelvin,
                                                 BASE1::mole + BASE2::mole,
                                                 BASE1::candela + BASE2::candela,
                                                 BASE1::radian + BASE2::radian> {}; 

            template <typename BASE1, typename BASE2> requires (are_base_v<BASE1, BASE2>)
            using base_prod_t = typename base_prod<BASE1, BASE2>::type; 


            /// @brief base_div is a struct to compute the division of two base
            template <typename BASE1, typename BASE2> requires (are_base_v<BASE1, BASE2>)
            struct base_div : public unit_base <BASE1::metre - BASE2::metre, 
                                                BASE1::second - BASE2::second,
                                                BASE1::kilogram - BASE2::kilogram,
                                                BASE1::ampere - BASE2::ampere,
                                                BASE1::kelvin - BASE2::kelvin,
                                                BASE1::mole - BASE2::mole,
                                                BASE1::candela - BASE2::candela,
                                                BASE1::radian - BASE2::radian> {}; 

            template <typename BASE1, typename BASE2> requires (are_base_v<BASE1, BASE2>)
            using base_div_t = typename base_div<BASE1, BASE2>::type; 


            /// @brief base_pow is a struct to compute the power of a base
            template <typename BASE, int POWER> requires (is_base_v<BASE>)
            struct base_pow : public unit_base<BASE::metre * POWER, 
                                               BASE::second * POWER,
                                               BASE::kilogram * POWER,
                                               BASE::ampere * POWER,
                                               BASE::kelvin * POWER,
                                               BASE::mole * POWER,
                                               BASE::candela * POWER,
                                               BASE::radian * POWER> {};

            template <typename BASE, int POWER> requires (is_base_v<BASE>)
            using base_pow_t = typename base_pow<BASE, POWER>::type;


            /// @brief base_root is a struct to compute the root of a base
            template <typename BASE, int POWER> requires (has_valid_root_v<BASE, POWER>)
            struct base_root : public unit_base<BASE::metre / POWER, 
                                                BASE::second / POWER,
                                                BASE::kilogram / POWER,
                                                BASE::ampere / POWER,
                                                BASE::kelvin / POWER,
                                                BASE::mole / POWER,
                                                BASE::candela / POWER,
                                                BASE::radian / POWER> {};

            template <typename BASE, int POWER> requires (has_valid_root_v<BASE, POWER>)
            using base_root_t = typename base_root<BASE, POWER>::type;


            /// @brief base_inv is a struct to compute the inverse of a base
            template <typename BASE> requires (is_base_v<BASE>)
            struct base_inv : public unit_base<-BASE::metre, 
                                               -BASE::second,
                                               -BASE::kilogram,
                                               -BASE::ampere,
                                               -BASE::kelvin,
                                               -BASE::mole,
                                               -BASE::candela,
                                               -BASE::radian> {};

            template <typename base, typename = std::enable_if_t<is_base_v<base>>>
            using base_inv_t = typename base_inv<base>::type;


        /// @brief unit is an union of an unit_base and an std::ratio prefix
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

                inline static constexpr scalar mult = static_cast<scalar>(PREFIX::num) / static_cast<scalar>(PREFIX::den);


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
                inline static consteval char prefix_symbol() noexcept {

                    if constexpr (mult == 1.e-24)      return 'y'; //< yocto prefix
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
                    else return ' ';

                }


                /// @brief to_string returns a string representation of the unit
                static constexpr std::string to_string() noexcept {

                    return prefix_symbol() + BASE::to_string(); 

                }


                /// @brief Convert a value from the base unit to another unit 
                template <typename UNIT> requires(is_same_base_v<BASE, typename UNIT::base>)
                static constexpr scalar convert(const scalar val, const UNIT&) noexcept {

                    return val * mult / UNIT::mult; 

                }


        }; // struct unit


        // =============================================
        // unit traits
        // =============================================

            template <typename T>
            struct is_unit : std::false_type {};

            template <typename BASE>
            struct is_unit<unit<BASE>> : std::true_type {};

            template <typename BASE, typename PREFIX>
            struct is_unit<unit<BASE, PREFIX>> : std::true_type {};

            template <typename T>
            inline constexpr bool is_unit_v = is_unit<T>::value;


            template <typename T1, typename T2>
            struct is_same_unit : std::false_type {};

            template <typename BASE> requires (is_base_v<BASE>)
            struct is_same_unit<unit<BASE>, unit<BASE>> : std::true_type {};

            template <typename BASE, typename PREFIX> requires (is_base_v<BASE>)
            struct is_same_unit<unit<BASE>, unit<BASE, PREFIX>> : std::true_type {};

            template <typename BASE, typename PREFIX> requires (is_base_v<BASE>)
            struct is_same_unit<unit<BASE, PREFIX>, unit<BASE>> : std::true_type {};

            template <typename BASE, typename PREFIX> requires (is_base_v<BASE>)
            struct is_same_unit<unit<BASE, PREFIX>, unit<BASE, PREFIX>> : std::true_type {};

            template <typename T1, typename T2>
            inline constexpr bool is_same_unit_v = is_same_unit<T1, T2>::value;


            template <typename... Ts>
            struct are_units : std::conjunction<is_unit<Ts>...> {};

            template <typename... Ts>
            inline constexpr bool are_units_v = are_units<Ts...>::value;
            

            template <typename... Ts> requires (are_units_v<Ts...>)
            struct are_same_units : std::false_type {};

            template <typename T>
            struct are_same_units<T> : std::true_type {};

            template <typename T1, typename T2>
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
        

            template <typename UNIT1, typename UNIT2> requires (are_units_v<UNIT1, UNIT2>)
            struct unit_prod : public unit<base_prod_t<typename UNIT1::base, typename UNIT2::base>, 
                                           std::ratio_multiply<typename UNIT1::prefix, typename UNIT2::prefix>> {};

            template <typename UNIT1, typename UNIT2> requires (are_units_v<UNIT1, UNIT2>)
            using unit_prod_t = typename unit_prod<UNIT1, UNIT2>::type; 


            template <typename UNIT1, typename UNIT2> requires (are_units_v<UNIT1, UNIT2>)
            struct unit_div : public unit<base_div_t<typename UNIT1::base, typename UNIT2::base>, 
                                          std::ratio_divide<typename UNIT1::prefix, typename UNIT2::prefix>> {};


            template <typename UNIT1, typename UNIT2> requires (are_units_v<UNIT1, UNIT2>)
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


    } // namespace units


} // namespace scipp::physics