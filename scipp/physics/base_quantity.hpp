/**
 * @file    scipp/physics/base_quantity.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the base_quantity struct.
 * @date    2023-06-12
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {
    

    /// @brief This template meta-structure contains the dimensional information for a physical quantity.
    template <int LENGTH, int TIME, int MASS, int TEMPERATURE, int ELETTRIC_CURRENT, int SUBSTANCE_AMOUNT, int LUMINOUS_INTENSITY> 
    struct base_quantity {


        static constexpr int length = LENGTH;                         //< power of length
        
        static constexpr int time = TIME;                             //< power of time 
        
        static constexpr int mass = MASS;                             //< power of mass 
        
        static constexpr int temperature = TEMPERATURE;               //< power of temperature 
        
        static constexpr int elettric_current = ELETTRIC_CURRENT;     //< power of elettric_current 
        
        static constexpr int substance_amount = SUBSTANCE_AMOUNT;     //< power of substance_amount 

        static constexpr int luminous_intensity = LUMINOUS_INTENSITY; //< power of luminous intensity 
        

        static constexpr std::array<int, 7> powers = {length, time, mass, temperature, elettric_current, substance_amount, luminous_intensity}; //< powers of the base_quantity
        
        static constexpr std::array<std::string_view, 7> base_literals = {"m", "s", "kg", "K", "A", "mol", "cd"};                               //< unit literals of the base quantities

        
        /// @brief Returns the string representation of the base_quantity
        static constexpr std::string_view to_string() noexcept {

            std::stringstream ss;

            // Iterate over the base quantities and their powers
            meta::for_<7>([&](auto i) constexpr {

                if constexpr (powers[i] != 0) {

                    if constexpr (powers[i] == 1) // Append the base quantity to the string builder
                        ss << base_literals[i]; 

                    else // Append the base quantity and its power to the string builder
                        ss << base_literals[i] << "^" << powers[i]; 

                }
                
            });

            return ss.str();

        }


    }; // struct base_quantity


} // namespace scipp::physics