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


        inline static constexpr int length = LENGTH; //< power of length
        
        inline static constexpr int time = TIME; //< power of time 
        
        inline static constexpr int mass = MASS; //< power of mass 
        
        inline static constexpr int temperature = TEMPERATURE; //< power of temperature 
        
        inline static constexpr int elettric_current = ELETTRIC_CURRENT; //< power of elettric_current 
        
        inline static constexpr int substance_amount = SUBSTANCE_AMOUNT; //< power of substance_amount 

        inline static constexpr int luminous_intensity = LUMINOUS_INTENSITY; //< power of luminous intensity 
        

        inline static constexpr std::array<std::string_view, 7> base_litterals = {"m", "s", "kg", "K", "A", "mol", "cd"}; //< array of the litterals of the base quantities

        
        /// @brief Returns the string representation of the base_quantity
        static constexpr std::string_view to_string() noexcept {

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

            return ss.str();

        }


    }; // struct base_quantity


} // namespace scipp::physics