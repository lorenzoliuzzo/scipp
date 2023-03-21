/**
 * @file    physics/base_quantity.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementations of the base_quantity struct and type traits.
 * @note    
 * @date    2023-03-20
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
    /// @note the powers are all integers                            
    template <int LENGTH, int TIME, int MASS, int TEMPERATURE, int SUBSTANCE_AMOUNT, int ELETTRIC_CURRENT, int LUMINOUS_INTENSITY, int ANGLE> 
    struct base_quantity {


        // =============================================
        // aliases
        // =============================================

            using type = base_quantity<LENGTH, TIME, MASS, ELETTRIC_CURRENT, TEMPERATURE, SUBSTANCE_AMOUNT, LUMINOUS_INTENSITY, ANGLE>; //< type of the base_quantity


        // =============================================
        // static members
        // ============================================= 

            inline static constexpr int length_power = LENGTH; //< power of length
            
            inline static constexpr int time_power = TIME; //< power of time 
            
            inline static constexpr int mass_power = MASS; //< power of mass 
            
            inline static constexpr int elettric_current_power = ELETTRIC_CURRENT; //< power of ELETTRIC_current 
            
            inline static constexpr int temperature_power = TEMPERATURE; //< power of temperature 
            
            inline static constexpr int substance_amount_power = SUBSTANCE_AMOUNT; //< power of substance_amount 

            inline static constexpr int luminous_intensity_power = LUMINOUS_INTENSITY; //< power of luminous intensity 
            
            inline static constexpr int angle_power = ANGLE; //< power of angle


            static constexpr std::array<std::string_view, 8> base_litterals = {"m", "s", "kg", "K", "mol", "A", "cd", "rad"};


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
                print_unit(ELETTRIC_CURRENT, base_litterals[3]);
                print_unit(TEMPERATURE, base_litterals[4]);
                print_unit(SUBSTANCE_AMOUNT, base_litterals[5]);
                print_unit(LUMINOUS_INTENSITY, base_litterals[6]);
                print_unit(ANGLE, base_litterals[7]);

                return ss.str();

            }


            // static constexpr auto from_string(const std::string_view& other) {

            //     // TODO         
            //     return base_quantity<0, 0, 0, 0, 0, 0, 0, 0>();

            // }


    }; // struct base_quantity


    // constexpr auto base_quantity_from_string(const std::string& other) {
        
    //     int metre_pow = 0;
    //     int second_pow = 0;
    //     int kilogram_pow = 0;
    //     int ampere_pow = 0;
    //     int kelvin_pow = 0;
    //     int mole_pow = 0;
    //     int candela_pow = 0;
    //     int radian_pow = 0;

    //     if (!other.empty()) {


    //         std::size_t finder = other.find('m');
    //         if (finder != std::string::npos) {

    //             if (finder == other.size() - 1 || other.at(finder + 1) != '^') 
    //                 metre_pow = 1; 
    //             else {
    //                 if (other.at(finder + 2) == '-') 
    //                     metre_pow -= std::stoi(other.substr(finder + 3));
    //                 else 
    //                     metre_pow = std::stoi(other.substr(finder + 2));
    //             }
                
    //         }

    //         finder = other.find('s');
    //         if (finder != std::string::npos) {

    //             if (finder == other.size() - 1 || other.at(finder + 1) != '^') 
    //                 second_pow = 1; 
    //             else {
    //                 if (other.at(finder + 2) == '-') 
    //                     second_pow -= std::stoi(other.substr(finder + 3));
    //                 else 
    //                     second_pow = std::stoi(other.substr(finder + 2));
    //             }
                
    //         }

    //         finder = other.find("kg");
    //         if (finder != std::string::npos) {

    //             if (finder == other.size() - 1 || other.at(finder + 1) != '^') 
    //                 kilogram_pow = 1; 
    //             else {
    //                 if (other.at(finder + 2) == '-') 
    //                     kilogram_pow -= std::stoi(other.substr(finder + 3));
    //                 else 
    //                     kilogram_pow = std::stoi(other.substr(finder + 2));
    //             }

    //         }

    //         finder = other.find('A');
    //         if (finder != std::string::npos) {

    //             if (finder == other.size() - 1 || other.at(finder + 1) != '^') 
    //                 ampere_pow = 1; 
    //             else {
    //                 if (other.at(finder + 2) == '-') 
    //                     ampere_pow -= std::stoi(other.substr(finder + 3));
    //                 else 
    //                     ampere_pow = std::stoi(other.substr(finder + 2));
    //             }                            
    //         }

    //         finder = other.find('K');
    //         if (finder != std::string::npos) {

    //             if (finder == other.size() - 1 || other.at(finder + 1) != '^') 
    //                 kelvin_pow = 1; 
    //             else {
    //                 if (other.at(finder + 2) == '-') 
    //                     kelvin_pow -= std::stoi(other.substr(finder + 3));
    //                 else 
    //                     kelvin_pow = std::stoi(other.substr(finder + 2));
    //             }

    //         }

    //         finder = other.find("mol");
    //         if (finder != std::string::npos) {

    //             if (finder == other.size() - 1 || other.at(finder + 1) != '^') 
    //                 mole_pow = 1; 
    //             else {
    //                 if (other.at(finder + 2) == '-') 
    //                     mole_pow -= std::stoi(other.substr(finder + 3));
    //                 else 
    //                     mole_pow = std::stoi(other.substr(finder + 2));
    //             }

    //         }

    //         finder = other.find("cd");
    //         if (finder != std::string::npos) {

    //             if (finder == other.size() - 1 || other.at(finder + 1) != '^') 
    //                 candela_pow = 1; 
    //             else {
    //                 if (other.at(finder + 2) == '-') 
    //                     candela_pow -= std::stoi(other.substr(finder + 3));
    //                 else 
    //                     candela_pow = std::stoi(other.substr(finder + 2));
    //             }
                
    //         }

    //         finder = other.find("rad");
    //         if (finder != std::string::npos) {

    //             if (finder == other.size() - 1 || other.at(finder + 1) != '^') 
    //                 radian_pow = 1; 
    //             else {
    //                 if (other.at(finder + 2) == '-') 
    //                     radian_pow -= std::stoi(other.substr(finder + 3));
    //                 else 
    //                     radian_pow = std::stoi(other.substr(finder + 2));
    //             }
                
    //         }

    //     } 

    //     return base_quantity<metre_pow, second_pow, kilogram_pow, ampere_pow, kelvin_pow, mole_pow, candela_pow, radian_pow>();

    // }


    // =============================================
    // base_quantity type traits
    // =============================================
        
        template <typename T>
        struct is_base : public std::false_type {};

        template <int LENGTH, int TIME, int MASS, int TEMPERATURE, int SUBSTANCE_AMOUNT, int ELETTRIC_CURRENT, int LUMINOUS_INTENSITY, int ANGLE>
        struct is_base<base_quantity<LENGTH, TIME, MASS, TEMPERATURE, SUBSTANCE_AMOUNT, ELETTRIC_CURRENT, LUMINOUS_INTENSITY, ANGLE>> : public std::true_type {};

        template <typename T>
        constexpr bool is_base_v = is_base<T>::value;


        template <typename... Ts>
        struct are_base : public std::conjunction<is_base<Ts>...> {};

        template <typename... Ts>
        constexpr bool are_base_v = are_base<Ts...>::value;


        template <typename BASE1, typename BASE2> 
            requires (are_base_v<BASE1, BASE2>)
        struct is_same_base : public std::bool_constant<BASE1::length_power == BASE2::length_power &&
                                                        BASE1::time_power == BASE2::time_power &&
                                                        BASE1::mass_power == BASE2::mass_power &&
                                                        BASE1::temperature_power == BASE2::temperature_power &&
                                                        BASE1::substance_amount_power == BASE2::substance_amount_power &&
                                                        BASE1::elettric_current_power == BASE2::elettric_current_power &&
                                                        BASE1::luminous_intensity_power == BASE2::luminous_intensity_power &&
                                                        BASE1::angle_power == BASE2::angle_power> {};

        template <typename BASE1, typename BASE2>
        constexpr bool is_same_base_v = is_same_base<BASE1, BASE2>::value;


        template <typename BASE, typename... Ts> 
            requires (are_base_v<BASE, Ts...>)
        struct are_same_base : public std::conjunction<is_same_base<BASE, Ts>...> {};

        template <typename BASE, typename... Ts>
        constexpr bool are_same_base_v = are_same_base<BASE, Ts...>::value;


        template <typename BASE, int POWER> 
            requires (is_base_v<BASE>)
        struct has_valid_root : public std::bool_constant<BASE::length_power % POWER == 0 && 
                                                            BASE::time_power % POWER == 0 && 
                                                            BASE::mass_power % POWER == 0 && 
                                                            BASE::temperature_power % POWER == 0 && 
                                                            BASE::substance_amount_power % POWER == 0 && 
                                                            BASE::elettric_current_power % POWER == 0 && 
                                                            BASE::luminous_intensity_power % POWER == 0 && 
                                                            BASE::angle_power % POWER == 0> {};

        template <typename BASE, int POWER>
        constexpr bool has_valid_root_v = has_valid_root<BASE, POWER>::value;


} // namespace scipp::physics