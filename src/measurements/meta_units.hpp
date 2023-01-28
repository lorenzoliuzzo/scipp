/**
 * @file    unit_base.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-21
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief measurements namespace contains all the classes and functions of the measurements library
namespace scipp::measurements {

    
    /// @brief units namespace contains all the units of the measurements library
    namespace units {


        /// @brief unit_base use an array of powers of the some unit_base to represent a base for a physical unit
        template <int metre, 
                  int second, 
                  int kilogram, 
                  int ampere, 
                  int kelvin, 
                  int mole, 
                  int candela, 
                  int radian> 
                  
        struct meta_unit_base {


            // =============================================
            // operators
            // ============================================= 

                /**
                 * @brief Perform a multiplication by adding the powers together
                 * 
                 * @param other: meta_unit_base object to multiply with as l-value const reference
                 * 
                 * @return constexpr meta_unit_base 
                 */
                template <int other_metre, 
                          int other_second, 
                          int other_kilogram, 
                          int other_ampere, 
                          int other_kelvin, 
                          int other_mole, 
                          int other_candela, 
                          int other_radian>
                consteval auto operator*(const meta_unit_base<other_metre,
                                                          other_second,
                                                          other_kilogram,
                                                          other_ampere,
                                                          other_kelvin,
                                                          other_mole,
                                                          other_candela,
                                                          other_radian>& other) const noexcept -> meta_unit_base<metre + other_metre,                                                                                                
                                                                                                             second + other_second,
                                                                                                             kilogram + other_kilogram,
                                                                                                             ampere + other_ampere,
                                                                                                             kelvin + other_kelvin,
                                                                                                             mole + other_mole,
                                                                                                             candela + other_candela,
                                                                                                             radian + other_radian> {

                            
                            return meta_unit_base<metre + other_metre,
                                              second + other_second,
                                              kilogram + other_kilogram,
                                              ampere + other_ampere,
                                              kelvin + other_kelvin,
                                              mole + other_mole,
                                              candela + other_candela,
                                              radian + other_radian>();

                }
                                                                                                 

                /**
                 * @brief Perform a division by subtracting the powers
                 * 
                 * @param other: unit_base object to divide with as l-value const reference
                 * 
                 * @return constexpr unit_base 
                 */
                template <int other_metre, 
                          int other_second, 
                          int other_kilogram, 
                          int other_ampere, 
                          int other_kelvin, 
                          int other_mole, 
                          int other_candela, 
                          int other_radian>
                consteval auto operator/(const meta_unit_base<other_metre,
                                                          other_second,
                                                          other_kilogram,
                                                          other_ampere,
                                                          other_kelvin,
                                                          other_mole,
                                                          other_candela,
                                                          other_radian>& other) const noexcept -> meta_unit_base<metre - other_metre,                                                                                                
                                                                                              second - other_second,
                                                                                              kilogram - other_kilogram,
                                                                                              ampere - other_ampere,
                                                                                              kelvin - other_kelvin,
                                                                                              mole - other_mole,
                                                                                              candela - other_candela,
                                                                                              radian - other_radian> {

                            
                            return meta_unit_base<metre - other_metre,
                                              second - other_second,
                                              kilogram - other_kilogram,
                                              ampere - other_ampere,
                                              kelvin - other_kelvin,
                                              mole - other_mole,
                                              candela - other_candela,
                                              radian - other_radian>();
                                              
                }


                /**
                 * @brief Equality operator
                 * 
                 * @param other: unit_base object to compare with as l-value const reference
                 * 
                 * @return bool
                 */
                template <int other_metre, 
                          int other_second, 
                          int other_kilogram, 
                          int other_ampere, 
                          int other_kelvin, 
                          int other_mole, 
                          int other_candela, 
                          int other_radian>
                consteval bool operator==(const meta_unit_base<other_metre,
                                                               other_second,
                                                               other_kilogram,
                                                               other_ampere,
                                                               other_kelvin,
                                                               other_mole,
                                                               other_candela,
                                                               other_radian>& other) const noexcept {
                
                    return metre == other_metre &&
                           second == other_second &&
                           kilogram == other_kilogram &&
                           ampere == other_ampere &&
                           candela == other_candela &&
                           kelvin == other_kelvin &&
                           mole == other_mole &&
                           radian == other_radian; 

                }



                /**
                 * @brief Inequality operator
                 * 
                 * @param other: unit_base object to compare with as l-value const reference
                 * 
                 * @return bool
                 */
                template <int other_metre, 
                          int other_second, 
                          int other_kilogram, 
                          int other_ampere, 
                          int other_kelvin, 
                          int other_mole, 
                          int other_candela, 
                          int other_radian>
                consteval bool operator!=(const meta_unit_base<other_metre,
                                                               other_second,
                                                               other_kilogram,
                                                               other_ampere,
                                                               other_kelvin,
                                                               other_mole,
                                                               other_candela,
                                                               other_radian>& other) const noexcept {
                
                    return metre != other_metre &&
                           second != other_second &&
                           kilogram != other_kilogram &&
                           ampere != other_ampere &&
                           candela != other_candela &&
                           kelvin != other_kelvin &&
                           mole != other_mole &&
                           radian != other_radian; 

                }


                /**
                 * @brief Printing on video the unit_base litterals
                 * 
                 * @param os: std::ostream& 
                 * @param base: unit_base as l-value const reference
                 * 
                 * @return std::ostream&
                 */
                friend inline std::ostream& operator<<(std::ostream& os, const meta_unit_base& base) noexcept {

                    os << base.to_string(); 

                    return os; 

                }


            // =============================================
            // get methods
            // =============================================


                /**
                 * @brief Get the unit_base litterals to string
                 * 
                 * @return std::string 
                 */
                static constexpr std::string to_string() {
                    
                    std::string unit_base_string;   
                    
                    if constexpr (metre != 0) {
                        if constexpr (metre == 1) 
                            unit_base_string.append("m");
                        else 
                            unit_base_string.append("m^" + std::to_string(metre)); 
                    }

                    if constexpr (second != 0) {

                        unit_base_string.append("s");

                        if constexpr (second != 1) 
                            unit_base_string.append('^' + std::to_string(second)); 

                    }

                    if constexpr (kilogram != 0) { 
                        if constexpr (kilogram == 1) 
                            unit_base_string.append("kg"); 
                        else 
                            unit_base_string.append("kg^" + std::to_string(kilogram)); 
                    }

                    if constexpr (ampere != 0) {
                        if constexpr (ampere == 1) 
                            unit_base_string.append("A"); 
                        else 
                            unit_base_string.append("A^" + std::to_string(ampere)); 
                    }

                    if constexpr (kelvin != 0) {
                        if constexpr (kelvin == 1) 
                            unit_base_string.append("K");
                        else 
                            unit_base_string.append("K^" + std::to_string(kelvin)); 
                    }

                    if constexpr (mole != 0) {
                        if constexpr (mole == 1) 
                            unit_base_string.append("mol"); 
                        else 
                            unit_base_string.append("mol^" + std::to_string(mole)); 
                    }

                    if constexpr (candela != 0) {
                        if constexpr (candela == 1) 
                            unit_base_string.append("cd"); 
                        else 
                            unit_base_string.append("cd^" + std::to_string(candela)); 
                    }

                    if constexpr (radian != 0) {
                        if constexpr (radian == 1) 
                            unit_base_string.append("rad"); 
                        else 
                            unit_base_string.append("rad^" + std::to_string(radian)); 
                    
                    }

                    return unit_base_string; 
                
                }

            
            using metre_power = std::integral_constant<int, metre>; ///< power of the metre
            using second_power = std::integral_constant<int, second>; ///< power of the second
            using kilogram_power = std::integral_constant<int, kilogram>; ///< power of the kilogram
            using ampere_power = std::integral_constant<int, ampere>; ///< power of the ampere
            using kelvin_power = std::integral_constant<int, kelvin>; ///< power of the kelvin
            using mole_power = std::integral_constant<int, mole>; ///< power of the mole
            using candela_power = std::integral_constant<int, candela>; ///< power of the candela
            using radian_power = std::integral_constant<int, radian>; ///< power of the radian    


        }; // struct unit_base


        using meta_metre = meta_unit_base<1, 0, 0, 0, 0, 0, 0, 0>;
        using meta_second = meta_unit_base<0, 1, 0, 0, 0, 0, 0, 0>;
        using meta_kilogram = meta_unit_base<0, 0, 1, 0, 0, 0, 0, 0>;
        using meta_ampere = meta_unit_base<0, 0, 0, 1, 0, 0, 0, 0>;
        using meta_kelvin = meta_unit_base<0, 0, 0, 0, 1, 0, 0, 0>;
        using meta_mole = meta_unit_base<0, 0, 0, 0, 0, 1, 0, 0>;
        using meta_candela = meta_unit_base<0, 0, 0, 0, 0, 0, 1, 0>;
        using meta_radian = meta_unit_base<0, 0, 0, 0, 0, 0, 0, 1>;

        using _2metre = meta_unit_base<2, 0, 0, 0, 0, 0, 0, 0>;


        template <typename Base, typename Prefix = std::ratio<1, 1>>
        struct meta_unit {


            using base = Base;
            using prefix = Prefix;


            static consteval scalar convertion_factor() { 
                
                return static_cast<double>(Prefix::num) / static_cast<double>(Prefix::den); 
                
            }


            friend inline std::ostream& operator<<(std::ostream& os, const meta_unit& units) noexcept {

                os << Base::to_string(); 

                return os; 

            }


            static constexpr std::string to_string() {

                return Base::to_string(); 

            }



        }; // struct meta_unit


        using _metre = meta_unit<meta_metre>;
        using _second = meta_unit<meta_second>;
        using _kilogram = meta_unit<meta_kilogram>;
        using _ampere = meta_unit<meta_ampere>;
        using _kelvin = meta_unit<meta_kelvin>;
        using _mole = meta_unit<meta_mole>;
        using _candela = meta_unit<meta_candela>;
        using _radian = meta_unit<meta_radian>;

        using _kilo_metre = meta_unit<meta_metre, std::kilo>;
        using _milli_metre = meta_unit<meta_metre, std::milli>;
        using _micro_metre = meta_unit<meta_metre, std::micro>;
        using _nano_metre = meta_unit<meta_metre, std::nano>;
        using _pico_metre = meta_unit<meta_metre, std::pico>;


        constexpr _kilo_metre _km;



        template <typename base>
        class meta_measurement {


            public:

                consteval meta_measurement() noexcept : 
                    
                    value_{0.} {}


                constexpr meta_measurement(const scalar& value) noexcept : 
                    
                    value_{value} {}


                template <typename units>
                constexpr meta_measurement(const scalar& value, const units& unit) noexcept requires (std::is_same_v<base, typename units::base>) :
                
                    value_{value * units::convertion_factor()} {}


                // /**
                // * @brief Multiply this measurement by another measurement
                // * 
                // * @param other: measurement as r-value reference
                // * 
                // * @return constexpr measurement 
                // */
                // template <template <meta_unit_base UB2> class M>
                // constexpr auto operator*(const M& other) const noexcept { 
                    
                //     return meta_measurement<decltype(M::base_type() * base_type())>(this->value_ * other.value()); 
                
                // }


                constexpr scalar value() const noexcept { 
                    
                    return value_; 
                    
                }




            using units = base;

            scalar value_;


        }; // struct meta_measurement


        template <typename units>
        meta_measurement(const scalar&, const units&) -> meta_measurement<typename units::base>;


        template <typename base, std::size_t DIM>
        class vector2 {


            public:

            constexpr vector2() noexcept : data_{meta_measurement<base>{}} {}

            constexpr vector2(const std::array<meta_measurement<base>, DIM>& data) noexcept : data_{data} {}



            using base_type = base::type;

            std::array<meta_measurement<base>, DIM> data_;


        }; // struct vector2


        template <typename base, std::size_t DIM>
        vector2(const std::array<meta_measurement<base>, DIM>&) -> vector2<base, DIM>;



    } // namespace units


} // namespace scipp::measurements