/**
 * @file    physics/base_quantity.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementations of the base_quantity struct and type traits.
 * @note    
 * @date    2023-03-17
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


        // =============================================
        // methods
        // =============================================

            static constexpr std::string to_string() noexcept {

                std::stringstream ss;

                if constexpr (LENGTH != 0) {

                    ss << "m";
                    if constexpr (LENGTH != 1) 
                        ss << "^" << LENGTH;

                }

                if constexpr (TIME != 0) {

                    if (ss.str() != "") 
                        ss << " ";

                    ss << "s";

                    if constexpr (TIME != 1) 
                        ss << "^" << TIME;
                    
                }

                if constexpr (MASS != 0) {

                    if (ss.str() != "") 
                        ss << " ";

                    ss << "kg";

                    if constexpr (MASS != 1) 
                        ss << "^" << MASS;
                    
                }

                if constexpr (ELETTRIC_CURRENT != 0) {

                    if (ss.str() != "") 
                        ss << " ";
                    
                    ss << "A";
                    
                    if constexpr (ELETTRIC_CURRENT != 1) 
                        ss << "^" << ELETTRIC_CURRENT;
                    
                }

                if constexpr (TEMPERATURE != 0) {

                    if (ss.str() != "") 
                        ss << " ";
                    
                    ss << "K";
                    
                    if constexpr (TEMPERATURE != 1) 
                        ss << "^" << TEMPERATURE;
                    
                }

                if constexpr (SUBSTANCE_AMOUNT != 0) {

                    if (ss.str() != "") 
                        ss << " ";
                    
                    ss << "mol";
                    
                    if constexpr (SUBSTANCE_AMOUNT != 1) 
                        ss << "^" << SUBSTANCE_AMOUNT;
                    
                }

                if constexpr (LUMINOUS_INTENSITY != 0) {

                    if (ss.str() != "") 
                        ss << " ";
                    
                    ss << "cd";
                    
                    if constexpr (LUMINOUS_INTENSITY != 1) 
                        ss << "^" << LUMINOUS_INTENSITY;
                    
                }

                if constexpr (ANGLE != 0) {

                    if (ss.str() != "") 
                        ss << " ";
                    
                    if constexpr (ANGLE == 1) 
                        ss << "rad";

                    else if constexpr (ANGLE == 2)
                        ss << "sr";
                    
                    else 
                        ss << "rad^" << ANGLE;

                }

                return ss.str();

            }


            // static constexpr std::string_view to_string2() noexcept {

            //     constexpr char unit_str[] = {
            //         (LENGTH != 0 ? 'm' : '\0'), (LENGTH != 1 ? '^' : '\0'), (LENGTH != 1 ? ('0' + LENGTH) : '\0'),
            //         (TIME != 0 ? 's' : '\0'), (TIME != 1 ? '^' : '\0'), (TIME != 1 ? ('0' + TIME) : '\0'),
            //         (MASS != 0 ? 'k' : '\0'), (MASS != 1 ? 'g' : '\0'), (MASS != 1 ? '^' : '\0'), (MASS != 1 ? ('0' + MASS) : '\0'),
            //         (ELETTRIC_CURRENT != 0 ? 'A' : '\0'), (ELETTRIC_CURRENT != 1 ? '^' : '\0'), (ELETTRIC_CURRENT != 1 ? ('0' + ELETTRIC_CURRENT) : '\0'),
            //         (TEMPERATURE != 0 ? 'K' : '\0'), (TEMPERATURE != 1 ? '^' : '\0'), (TEMPERATURE != 1 ? ('0' + TEMPERATURE) : '\0'),
            //         (SUBSTANCE_AMOUNT != 0 ? 'm' : '\0'), (SUBSTANCE_AMOUNT != 1 ? 'o' : '\0'), (SUBSTANCE_AMOUNT != 1 ? 'l' : '\0'), (SUBSTANCE_AMOUNT != 1 ? '^' : '\0'), (SUBSTANCE_AMOUNT != 1 ? ('0' + SUBSTANCE_AMOUNT) : '\0'),
            //         (LUMINOUS_INTENSITY != 0 ? 'c' : '\0'), (LUMINOUS_INTENSITY != 1 ? 'd' : '\0'), (LUMINOUS_INTENSITY != 1 ? '^' : '\0'), (LUMINOUS_INTENSITY != 1 ? ('0' + LUMINOUS_INTENSITY) : '\0'),
            //         (ANGLE != 0 ? ' ' : '\0'), (ANGLE == 1 ? 'r' : '\0'), (ANGLE == 1 ? 'a' : '\0'), (ANGLE == 1 ? 'd' : '\0'),
            //         (ANGLE == 2 ? ' ' : '\0'), (ANGLE == 2 ? 's' : '\0'), (ANGLE == 2 ? 'r' : '\0'),
            //         (ANGLE > 2 ? 'r' : '\0'), (ANGLE > 2 ? 'a' : '\0'), (ANGLE > 2 ? 'd' : '\0'), (ANGLE > 2 ? '^' : '\0'), (ANGLE > 2 ? ('0' + ANGLE) : '\0'),
            //         '\0'
            //     };
            //     return std::string_view(unit_str, sizeof(unit_str) - 1);

            // }


            // static constexpr std::string_view unit_string() noexcept {
            //     constexpr int buffer_size = 32; // adjust size as needed
            //     std::array<char, buffer_size> buffer{};
            //     int pos = 0;

            //     if constexpr (LENGTH != 0) {
            //         buffer[pos++] = 'm';
            //         if constexpr (LENGTH != 1) 
            //             pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "^%d", LENGTH);
            //     }

            //     if constexpr (TIME != 0) {
            //         if (pos != 0) 
            //             buffer[pos++] = ' ';
            //         pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "s");
            //         if constexpr (TIME != 1) 
            //             pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "^%d", TIME);
            //     }


            //     if constexpr (MASS != 0) {
            //         if (pos != 0) 
            //             buffer[pos++] = ' ';
            //         pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "kg");
            //         if constexpr (MASS != 1) 
            //             pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "^%d", MASS);
            //     }


            //     if constexpr (ELETTRIC_CURRENT != 0) {
            //         if (pos != 0) 
            //             buffer[pos++] = ' ';
            //         pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "A");
            //         if constexpr (ELETTRIC_CURRENT != 1) 
            //             pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "^%d", ELETTRIC_CURRENT);
            //     }


            //     if constexpr (TEMPERATURE != 0) {
            //         if (pos != 0) 
            //             buffer[pos++] = ' ';
            //         pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "K");
            //         if constexpr (TEMPERATURE != 1) 
            //             pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "^%d", TEMPERATURE);
            //     }


            //     if constexpr (SUBSTANCE_AMOUNT != 0) {
            //         if (pos != 0) 
            //             buffer[pos++] = ' ';
            //         pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "mol");
            //         if constexpr (SUBSTANCE_AMOUNT != 1) 
            //             pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "^%d", SUBSTANCE_AMOUNT);
            //     }


            //     if constexpr (LUMINOUS_INTENSITY != 0) {
            //         if (pos != 0) 
            //             buffer[pos++] = ' ';
            //         pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "cd");
            //         if constexpr (LUMINOUS_INTENSITY != 1) 
            //             pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "^%d", LUMINOUS_INTENSITY);
            //     }


            //     if constexpr (ANGLE != 0) {
            //         if (pos != 0) 
            //             buffer[pos++] = ' ';
            //         if constexpr (ANGLE == 1) {
            //             pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "rad");
            //         } else if constexpr (ANGLE == 2) {
            //             pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "sr");
            //         } else {
            //             pos += std::snprintf(buffer.data() + pos, buffer_size - pos, "rad^%d", ANGLE);
            //         }
            //     }

            //     return std::string_view(buffer.data(), pos);

            // }


    }; // struct base_quantity


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