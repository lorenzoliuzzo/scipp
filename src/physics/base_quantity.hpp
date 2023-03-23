/**
 * @file    physics/base_quantity.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the base_quantity struct and its type traits.
 * @date    2023-03-23
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {
    

    /// @brief base_quantity is a struct that represents a base for a physical quantity
    /// @tparam LENGTH: power of length                              
    /// @tparam TIME: power of time                                  
    /// @tparam MASS: power of mass                                  
    /// @tparam TEMPERATURE: power of temperature                    
    /// @tparam SUBSTANCE_AMOUNT: power of substance amount          
    /// @tparam ELETTRIC_CURRENT: power of elettric current          
    /// @tparam LUMINOUS_INTENSITY: power of luminous intensity      
    /// @tparam ANGLE: power of angle    
    /// @tparam SOLID_ANGLE: power of solid angle
    /// @note the powers are all integers                            
    template <int LENGTH, int TIME, int MASS, int TEMPERATURE, int ELETTRIC_CURRENT,
              int SUBSTANCE_AMOUNT, int LUMINOUS_INTENSITY, int ANGLE, int SOLID_ANGLE> 
    struct base_quantity {


        // =============================================
        // aliases
        // =============================================

            using type = base_quantity<LENGTH, TIME, MASS, TEMPERATURE, ELETTRIC_CURRENT, 
                                       SUBSTANCE_AMOUNT, LUMINOUS_INTENSITY, ANGLE, SOLID_ANGLE>; //< type of the base_quantity


        // =============================================
        // static members
        // ============================================= 

            inline static constexpr int length = LENGTH; //< power of length
            
            inline static constexpr int time = TIME; //< power of time 
            
            inline static constexpr int mass = MASS; //< power of mass 
            
            inline static constexpr int temperature = TEMPERATURE; //< power of temperature 
            
            inline static constexpr int elettric_current = ELETTRIC_CURRENT; //< power of ELETTRIC_current 
            
            inline static constexpr int substance_amount = SUBSTANCE_AMOUNT; //< power of substance_amount 

            inline static constexpr int luminous_intensity = LUMINOUS_INTENSITY; //< power of luminous intensity 
            
            inline static constexpr int angle = ANGLE; //< power of angle

            inline static constexpr int solid_angle = SOLID_ANGLE; //< power of solid_angle


            inline static constexpr std::array<std::string_view, 9> base_litterals = {"m", "s", "kg", "K", "A", "mol", "cd", "rad", "sr"};


        // =============================================
        // methods
        // =============================================

            static constexpr std::string to_string() noexcept {

                std::stringstream ss;
                bool first_unit = true;

                auto print_unit = [&](int power, std::string_view unit) {

                    if (power != 0) {

                        if (!first_unit)
                            ss << ' ';
                        else
                            first_unit = false;

                        ss << unit;

                        if (power != 1)
                            ss << '^' << power;
                    }

                };

                print_unit(LENGTH, base_litterals[0]);
                print_unit(TIME, base_litterals[1]);
                print_unit(MASS, base_litterals[2]);
                print_unit(TEMPERATURE, base_litterals[3]);
                print_unit(ELETTRIC_CURRENT, base_litterals[4]);
                print_unit(SUBSTANCE_AMOUNT, base_litterals[5]);
                print_unit(LUMINOUS_INTENSITY, base_litterals[6]);
                print_unit(ANGLE, base_litterals[7]);
                print_unit(SOLID_ANGLE, base_litterals[8]);

                return ss.str();

            }


    }; // struct base_quantity


    // =============================================
    // base_quantity type traits
    // =============================================
        
        /// @brief Type trait to check if a type is a base_quantity
        template <typename T>
        struct is_base : public std::false_type {};

        template <int LENGTH, int TIME, int MASS, int TEMPERATURE, int ELETTRIC_CURRENT, 
                  int SUBSTANCE_AMOUNT, int LUMINOUS_INTENSITY, int ANGLE, int SOLID_ANGLE>
        struct is_base<base_quantity<LENGTH, TIME, MASS, TEMPERATURE, ELETTRIC_CURRENT, 
                                     SUBSTANCE_AMOUNT, LUMINOUS_INTENSITY, ANGLE, SOLID_ANGLE>> : public std::true_type {};

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
                                                        BASE1::luminous_intensity == BASE2::luminous_intensity &&
                                                        BASE1::angle == BASE2::angle &&
                                                        BASE1::solid_angle == BASE2::solid_angle> {};

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
                                                          BASE::luminous_intensity % POWER == 0 && 
                                                          BASE::angle % POWER == 0 &&
                                                          BASE::solid_angle % POWER == 0> {};

        template <typename BASE, int POWER>
        constexpr bool has_valid_root_v = has_valid_root<BASE, POWER>::value;


} // namespace scipp::physics