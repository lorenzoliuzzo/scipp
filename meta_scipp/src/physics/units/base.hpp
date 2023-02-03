/**
 * @file    base.hpp
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


        /** 
         * @brief base use an array of powers to represent a base for a physical unit
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
                                   radian_pow>; ///< type of this struct


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



        /// @brief is_base is a trait to check if a type is a base
        template <typename T>
        struct is_base : std::false_type {};

        /// @brief is_base is a trait to check if a type is a base
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

        /// @brief is_base is a trait to check if a type is a base
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
        

        template <typename base1, typename base2, typename = std::enable_if_t<is_base_v<base1> && is_base_v<base2>>>
        struct is_same_base : public std::bool_constant<base1::metre == base2::metre && 
                                                        base1::second == base2::second && 
                                                        base1::kilogram == base2::kilogram && 
                                                        base1::ampere == base2::ampere && 
                                                        base1::kelvin == base2::kelvin && 
                                                        base1::mole == base2::mole && 
                                                        base1::candela == base2::candela && 
                                                        base1::radian == base2::radian> {};

        
        template <typename base1, typename base2, typename = std::enable_if_t<is_base_v<base1> && is_base_v<base2>>>
        inline constexpr bool is_same_base_v = is_same_base<base1, base2>::value;


    } // namespace units


} // namespace scipp::physics