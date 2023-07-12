/**
 * @file    physics/measurements/base_quantity.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the base_quantity struct.
 * @date    2023-06-09
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {
    

    /// @brief This template meta-structure contains the dimensional information for a physical quantity.
    ///        It uses the powers of the international system base quantities to represent the dimensions.
    /// @note The powers must be integers                            
    template <int LENGTH, int TIME, int MASS, int TEMPERATURE, int ELETTRIC_CURRENT, int SUBSTANCE_AMOUNT, int LUMINOUS_INTENSITY> 
    struct base_quantity {


        using _t = base_quantity<LENGTH, TIME, MASS, TEMPERATURE, ELETTRIC_CURRENT, SUBSTANCE_AMOUNT, LUMINOUS_INTENSITY>; //< type of the base_quantity


        static constexpr int length = LENGTH;                           //< power of length
        
        static constexpr int time = TIME;                               //< power of time 
        
        static constexpr int mass = MASS;                               //< power of mass 
        
        static constexpr int temperature = TEMPERATURE;                 //< power of temperature 
        
        static constexpr int elettric_current = ELETTRIC_CURRENT;       //< power of elettric_current 
        
        static constexpr int substance_amount = SUBSTANCE_AMOUNT;       //< power of substance_amount 

        static constexpr int luminous_intensity = LUMINOUS_INTENSITY;   //< power of luminous intensity 
        

        //< array of the literals of the base quantities
        static constexpr std::array<std::string_view, 7> base_literals = {"m", "s", "kg", "K", "A", "mol", "cd"}; 

        
        /// @brief Returns the string representation of the base_quantity
        static constexpr std::string_view to_string() noexcept {

            std::stringstream ss;
            bool first_unit = true;

            auto print_unit = [&](int power, std::string_view unit) constexpr {

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

            print_unit(LENGTH, base_literals[0]);
            print_unit(TIME, base_literals[1]);
            print_unit(MASS, base_literals[2]);
            print_unit(TEMPERATURE, base_literals[3]);
            print_unit(ELETTRIC_CURRENT, base_literals[4]);
            print_unit(SUBSTANCE_AMOUNT, base_literals[5]);
            print_unit(LUMINOUS_INTENSITY, base_literals[6]);

            return ss.str();

        }


    }; // struct base_quantity


} // namespace scipp::physics