/**
 * @file    unit.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-02-05
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {

    
    /// @brief units namespace contains the implementation of units of measurements
    namespace units {


        /** 
         * @brief base use an array of powers to represent an unit_base for a physical unit
         *
         * @tparam metre_pow: power of metre
         * @tparam second_pow: power of second
         * @tparam kilogram_pow: power of kilogram
         * @tparam ampere_pow: power of ampere
         * @tparam kelvin_pow: power of kelvin
         * @tparam mole_pow: power of mole
         * @tparam candela_pow: power of candela
         * @tparam radian_pow: power of radian
         */
        template <int metre_pow, 
                  int second_pow, 
                  int kilogram_pow, 
                  int ampere_pow, 
                  int kelvin_pow, 
                  int mole_pow, 
                  int candela_pow, 
                  int radian_pow>
                  
        struct unit_base {


            using type = unit_base<metre_pow, 
                                   second_pow, 
                                   kilogram_pow, 
                                   ampere_pow, 
                                   kelvin_pow, 
                                   mole_pow, 
                                   candela_pow, 
                                   radian_pow>; ///< type of the unit_base


            // =============================================
            // methods
            // =============================================

                /**
                 * @brief Get the unit_base litterals to string
                 * 
                 * @return static constexpr std::string 
                 */
                static constexpr std::string to_string() {
                    
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


            // =============================================
            // static members
            // ============================================= 

                inline static constexpr int metre = metre_pow; ///< power of metre
                
                inline static constexpr int second = second_pow; ///< power of second
                
                inline static constexpr int kilogram = kilogram_pow; ///< power of kilogram
                
                inline static constexpr int ampere = ampere_pow; ///< power of ampere
                
                inline static constexpr int kelvin = kelvin_pow; ///< power of kelvin
                
                inline static constexpr int mole = mole_pow; ///< power of mole
                
                inline static constexpr int candela = candela_pow; ///< power of candela
                
                inline static constexpr int radian = radian_pow; ///< power of radian


        }; // struct base


        // =============================================
        // unit_base traits
        // =============================================

            /// @brief is_base is a trait to check if a type is an unit_base
            template <typename T>
            struct is_base : std::false_type {};

            /// @brief is_base is a trait to check if a type is an unit_base
            template <int metre_pow, 
                    int second_pow, 
                    int kilogram_pow, 
                    int ampere_pow, 
                    int kelvin_pow, 
                    int mole_pow, 
                    int candela_pow, 
                    int radian_pow>
            struct is_base<unit_base<metre_pow, 
                                    second_pow, 
                                    kilogram_pow, 
                                    ampere_pow, 
                                    kelvin_pow, 
                                    mole_pow, 
                                    candela_pow, 
                                    radian_pow>> : std::true_type {};

            /// @brief is_base is a trait to check if a type is an unit_base
            template <int metre_pow, 
                    int second_pow, 
                    int kilogram_pow, 
                    int ampere_pow, 
                    int kelvin_pow, 
                    int mole_pow, 
                    int candela_pow, 
                    int radian_pow>
            struct is_base<const unit_base<metre_pow, 
                                        second_pow, 
                                        kilogram_pow, 
                                        ampere_pow, 
                                        kelvin_pow, 
                                        mole_pow, 
                                        candela_pow, 
                                        radian_pow>> : std::true_type {};

            /// @brief is_base_v has the value of the is_base trait
            template <typename T>
            inline constexpr bool is_base_v = is_base<T>::value;
            

            /// @brief is_same_base is a trait to check if two unit_base are the same
            template <typename base1, typename base2, typename = std::enable_if_t<is_base_v<base1> && is_base_v<base2>>>
            struct is_same_base : public std::bool_constant<base1::metre == base2::metre && 
                                                            base1::second == base2::second && 
                                                            base1::kilogram == base2::kilogram && 
                                                            base1::ampere == base2::ampere && 
                                                            base1::kelvin == base2::kelvin && 
                                                            base1::mole == base2::mole && 
                                                            base1::candela == base2::candela && 
                                                            base1::radian == base2::radian> {};

            
            /// @brief is_same_base_v has the value of the is_same_base trait
            template <typename base1, typename base2, typename = std::enable_if_t<is_base_v<base1> && is_base_v<base2>>>
            inline constexpr bool is_same_base_v = is_same_base<base1, base2>::value;

        
        /** 
         * @brief unit is an union of an unit_base and an std::ratio prefix
         *
         * @tparam BASE: meta_base of the unit
         * @tparam PREFIX: std::ratio prefix of the unit
         */
        template <typename BASE, typename PREFIX = std::ratio<1, 1>, typename = std::enable_if_t<is_base_v<BASE>>>
        struct unit {


            // =============================================
            // aliases
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

                friend inline std::ostream& operator<<(std::ostream& os, const unit& units) noexcept {

                    return os << units.to_string();

                }


            // =============================================
            // methods
            // =============================================

                /// @brief prefix_char returns a char representation of the prefix
                inline static consteval char prefix_char() noexcept {

                    if constexpr (mult == 1.e-24) return 'y'; //< yocto prefix
                    else if constexpr (mult == 1.e-21) return 'z'; //< zepto prefix
                    else if constexpr (mult == 1.e-18) return 'a'; //< atto prefix
                    else if constexpr (mult == 1.e-15) return 'f'; //< femto prefix
                    else if constexpr (mult == 1.e-12) return 'p'; //< pico prefix
                    else if constexpr (mult == 1.e-9) return 'n'; //< nano prefix
                    else if constexpr (mult == 1.e-6) return 'u'; //< micro prefix
                    else if constexpr (mult == 1.e-3) return 'm'; //< milli prefix
                    else if constexpr (mult == 1.e-2) return 'c'; //< centi prefix
                    else if constexpr (mult == 1.e-1) return 'd'; //< deci prefix
                    else if constexpr (mult == 1.e2) return 'h'; //< hecto prefix
                    else if constexpr (mult == 1.e3) return 'K'; //< kilo prefix
                    else if constexpr (mult == 1.e6) return 'M'; //< mega prefix
                    else if constexpr (mult == 1.e9) return 'G'; //< giga prefix
                    else if constexpr (mult == 1.e12) return 'T'; //< tera prefix
                    else if constexpr (mult == 1.e15) return 'P'; //< peta prefix
                    else if constexpr (mult == 1.e18) return 'E'; //< exa prefix
                    else if constexpr (mult == 1.e21) return 'Z'; //< zetta prefix
                    else if constexpr (mult == 1.e24) return 'Y'; //< yotta prefix
                    else return ' ';

                }


                /// @brief to_string returns a string representation of the unit
                inline static constexpr std::string to_string() noexcept {

                    return prefix_char() + BASE::to_string(); 

                }


                /// @brief Convert a value from the base unit to another unit 
                template <typename UNIT, typename = std::enable_if_t<is_same_base_v<BASE, typename UNIT::base>>>
                inline static constexpr scalar convert(const scalar val, const UNIT&) noexcept {

                    return val * mult / UNIT::mult; 

                }


        }; // struct unit


        // =============================================
        // unit traits
        // =============================================

            /// @brief is_unit is a trait to check if a type is an unit
            template <typename T>
            struct is_unit : std::false_type {};

            template <typename BASE, typename PREFIX>
            struct is_unit<unit<BASE, PREFIX>> : std::true_type {};


            template <typename BASE, typename PREFIX>
            struct is_unit<const unit<BASE, PREFIX>> : std::true_type {};


            template <typename BASE, typename PREFIX>
            struct is_unit<unit<BASE, PREFIX>&> : std::true_type {};


            template <typename BASE, typename PREFIX>
            struct is_unit<const unit<BASE, PREFIX>&> : std::true_type {};


            template <typename BASE, typename PREFIX>
            struct is_unit<unit<BASE, PREFIX>&&> : std::true_type {};


            template <typename BASE, typename PREFIX>
            struct is_unit<const unit<BASE, PREFIX>&&> : std::true_type {};


            template <typename T>
            inline constexpr bool is_unit_v = is_unit<T>::value;
        

    } // namespace units


} // namespace scipp::physics