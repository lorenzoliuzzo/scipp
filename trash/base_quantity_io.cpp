
            // static constexpr std::string to_string() noexcept {

            //     std::stringstream ss;

            //     if constexpr (LENGTH != 0) {

            //         ss << "m";
            //         if constexpr (LENGTH != 1) 
            //             ss << "^" << LENGTH;

            //     }

            //     if constexpr (TIME != 0) {

            //         if (ss.str() != "") 
            //             ss << " ";

            //         ss << "s";

            //         if constexpr (TIME != 1) 
            //             ss << "^" << TIME;
                    
            //     }

            //     if constexpr (MASS != 0) {

            //         if (ss.str() != "") 
            //             ss << " ";

            //         ss << "kg";

            //         if constexpr (MASS != 1) 
            //             ss << "^" << MASS;
                    
            //     }

            //     if constexpr (ELETTRIC_CURRENT != 0) {

            //         if (ss.str() != "") 
            //             ss << " ";
                    
            //         ss << "A";
                    
            //         if constexpr (ELETTRIC_CURRENT != 1) 
            //             ss << "^" << ELETTRIC_CURRENT;
                    
            //     }

            //     if constexpr (TEMPERATURE != 0) {

            //         if (ss.str() != "") 
            //             ss << " ";
                    
            //         ss << "K";
                    
            //         if constexpr (TEMPERATURE != 1) 
            //             ss << "^" << TEMPERATURE;
                    
            //     }

            //     if constexpr (SUBSTANCE_AMOUNT != 0) {

            //         if (ss.str() != "") 
            //             ss << " ";
                    
            //         ss << "mol";
                    
            //         if constexpr (SUBSTANCE_AMOUNT != 1) 
            //             ss << "^" << SUBSTANCE_AMOUNT;
                    
            //     }

            //     if constexpr (LUMINOUS_INTENSITY != 0) {

            //         if (ss.str() != "") 
            //             ss << " ";
                    
            //         ss << "cd";
                    
            //         if constexpr (LUMINOUS_INTENSITY != 1) 
            //             ss << "^" << LUMINOUS_INTENSITY;
                    
            //     }

            //     if constexpr (ANGLE != 0) {

            //         if (ss.str() != "") 
            //             ss << " ";
                    
            //         if constexpr (ANGLE == 1) 
            //             ss << "rad";

            //         else if constexpr (ANGLE == 2)
            //             ss << "sr";
                    
            //         else 
            //             ss << "rad^" << ANGLE;

            //     }"A"

            //     return ss.str();

            // }



        // // Define units array
        // constexpr std::array<std::string_view, 8> units = {"m", "s", "kg", "A", "K", "mol", "cd", "rad"};

        // // Helper function to print a unit to a string
        // template<int LENGTH, int TIME, int MASS, int TEMPERATURE, int SUBSTANCE_AMOUNT, int ELETTRIC_CURRENT, int LUMINOUS_INTENSITY, int ANGLE>
        // std::string to_unit_string(const base_quantity<LENGTH, TIME, MASS, TEMPERATURE, SUBSTANCE_AMOUNT, ELETTRIC_CURRENT, LUMINOUS_INTENSITY, ANGLE>&) noexcept {

        //     std::string result;
        //     bool first_unit = true;

        //     auto print_unit = [&](int power, std::string_view unit) {
        //         if (power != 0) {
        //             if (!first_unit)
        //                 result += ' ';
        //             first_unit = false;

        //             result += unit;

        //             if (power != 1)
        //                 result += '^' + std::to_string(power);
        //         }
        //     };

        //     print_unit(LENGTH, units[0]);
        //     print_unit(TIME, units[1]);
        //     print_unit(MASS, units[2]);
        //     print_unit(ELETTRIC_CURRENT, units[3]);
        //     print_unit(TEMPERATURE, units[4]);
        //     print_unit(SUBSTANCE_AMOUNT, units[5]);
        //     print_unit(LUMINOUS_INTENSITY, units[6]);
        //     print_unit(ANGLE, units[7]);

        //     return result;

        // }

        // // Define std::map<std::string, std::pair<std::string, std::string>> implementation
        // std::map<std::string, std::pair<std::string, std::string>> base_quantity_map() {
        //     std::map<std::string, std::pair<std::string, std::string>> result;
        //     result["m"] = std::make_pair("length", to_unit_string(metre()));
        //     result["kg"] = std::make_pair("mass", to_unit_string(kilogram()));
        //     result["s"] = std::make_pair("time", to_unit_string(second()));
        //     result["A"] = std::make_pair("electric current", to_unit_string(ampere()));
        //     result["K"] = std::make_pair("thermodynamic temperature", to_unit_string(kelvin()));
        //     result["mol"] = std::make_pair("amount of substance", to_unit_string(mole()));
        //     result["cd"] = std::make_pair("luminous intensity", to_unit_string(candela()));
        //     result["rad"] = std::make_pair("angle", to_unit_string(radian()));
        //     return result;
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


    // /// @brief from_string returns a unit from a string representation
    // auto unit_from_string(const std::string& str) {

    //     if (str.empty()) 
    //         throw std::invalid_argument("The string is empty");

    //     for (const auto& [mult, prefix] : prefix_map) {
                
    //             if (str.find(prefix) == 0) {
    
    //                 auto base = str.substr(prefix.size());
    //                 if (base.empty()) 
    //                     throw std::invalid_argument("The string does not represent a unit");
    
    //                 auto base_unit = base_from_string(base);
    //                 if constexpr (is_base_v<decltype(base_unit)>) 
    //                     return unit<decltype(base_unit), std::ratio<static_cast<int>(mult), 1>>{};
    //                 else
    //                     throw std::invalid_argument("The string does not represent a unit");
    
    //             }
    
    //         }

    //     auto base_unit = base_from_string(str);
    //     if constexpr (is_base_v<decltype(base_unit)>) 
    //         return unit<decltype(base_unit)>{};
    //     else
    //         throw std::invalid_argument("The string does not represent a unit");

    // }


            // /// @brief prefix_symbol returns a char representation of the prefix
            // inline static constexpr auto prefix_symbol() noexcept {

            //     if      constexpr (mult == 1.e-24) return "[y]"; //< yocto prefix
            //     else if constexpr (mult == 1.e-21) return "[z]"; //< zepto prefix
            //     else if constexpr (mult == 1.e-18) return "[a]"; //< atto prefix
            //     else if constexpr (mult == 1.e-15) return "[f]"; //< femto prefix
            //     else if constexpr (mult == 1.e-12) return "[p]"; //< pico prefix
            //     else if constexpr (mult == 1.e-9)  return "[n]"; //< nano prefix
            //     else if constexpr (mult == 1.e-6)  return "[u]"; //< micro prefix
            //     else if constexpr (mult == 1.e-3)  return "[m]"; //< milli prefix
            //     else if constexpr (mult == 1.e-2)  return "[c]"; //< centi prefix
            //     else if constexpr (mult == 1.e-1)  return "[d]"; //< deci prefix
            //     else if constexpr (mult == 1.e2)   return "[h]"; //< hecto prefix
            //     else if constexpr (mult == 1.e3)   return "[K]"; //< kilo prefix
            //     else if constexpr (mult == 1.e6)   return "[M]"; //< mega prefix
            //     else if constexpr (mult == 1.e9)   return "[G]"; //< giga prefix
            //     else if constexpr (mult == 1.e12)  return "[T]"; //< tera prefix
            //     else if constexpr (mult == 1.e15)  return "[P]"; //< peta prefix
            //     else if constexpr (mult == 1.e18)  return "[E]"; //< exa prefix
            //     else if constexpr (mult == 1.e21)  return "[Z]"; //< zetta prefix
            //     else if constexpr (mult == 1.e24)  return "[Y]"; //< yotta prefix
            //     else                               return ;

            // }

