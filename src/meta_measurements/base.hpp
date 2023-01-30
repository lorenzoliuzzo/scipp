/**
 * @file    base.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-30
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief measurements namespace contains all the classes and functions of the measurements library
namespace scipp::measurements {

    
    /// @brief units namespace contains all the units of the measurements library
    namespace meta_units {


        /// @brief unit_base use an array of powers of the some unit_base to represent a base for a physical unit
        template <int metre_pow, 
                  int second_pow, 
                  int kilogram_pow, 
                  int ampere_pow, 
                  int kelvin_pow, 
                  int mole_pow, 
                  int candela_pow, 
                  int radian_pow>
        struct meta_base {


            // =============================================
            // static members
            // ============================================= 

                static constexpr int metre = metre_pow;
                
                static constexpr int second = second_pow;
                
                static constexpr int kilogram = kilogram_pow;
                
                static constexpr int ampere = ampere_pow;
                
                static constexpr int kelvin = kelvin_pow;
                
                static constexpr int mole = mole_pow;
                
                static constexpr int candela = candela_pow;
                
                static constexpr int radian = radian_pow;


                using type = meta_base<metre_pow, 
                                       second_pow, 
                                       kilogram_pow, 
                                       ampere_pow, 
                                       kelvin_pow, 
                                       mole_pow, 
                                       candela_pow, 
                                       radian_pow>; 


            // =============================================
            // operators
            // ============================================= 

                /**
                 * @brief Equality operator
                 * 
                 * @param other: unit_base object to compare with as l-value const reference
                 * 
                 * @return bool
                 */
                template <typename base2>
                consteval bool operator==(const base2& other) const noexcept {
                
                    return std::is_same_v<type, base2>; 

                }


                /**
                 * @brief Printing on video the unit_base litterals
                 * 
                 * @param os: std::ostream& 
                 * @param base: unit_base as l-value const reference
                 * 
                 * @return std::ostream&
                 */
                friend inline std::ostream& operator<<(std::ostream& os, const meta_base& base) noexcept {

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
                    
                    std::string base_string;   
                    
                    if constexpr (metre_pow != 0) {
                        if constexpr (metre_pow == 1) 
                            base_string.append("m");
                        else 
                            base_string.append("m^" + std::to_string(metre_pow)); 
                    }

                    if constexpr (second_pow != 0) {

                        base_string.append("s");

                        if constexpr (second_pow != 1) 
                            base_string.append("^" + std::to_string(second_pow)); 

                    }

                    if constexpr (kilogram_pow != 0) { 
                        if constexpr (kilogram_pow == 1) 
                            base_string.append("kg"); 
                        else 
                            base_string.append("kg^" + std::to_string(kilogram_pow)); 
                    }

                    if constexpr (ampere_pow != 0) {
                        if constexpr (ampere_pow == 1) 
                            base_string.append("A"); 
                        else 
                            base_string.append("A^" + std::to_string(ampere_pow)); 
                    }

                    if constexpr (kelvin_pow != 0) {
                        if constexpr (kelvin_pow == 1) 
                            base_string.append("K");
                        else 
                            base_string.append("K^" + std::to_string(kelvin_pow)); 
                    }

                    if constexpr (mole_pow != 0) {
                        if constexpr (mole_pow == 1) 
                            base_string.append("mol"); 
                        else 
                            base_string.append("mol^" + std::to_string(mole_pow)); 
                    }

                    if constexpr (candela_pow != 0) {
                        if constexpr (candela_pow == 1) 
                            base_string.append("cd"); 
                        else 
                            base_string.append("cd^" + std::to_string(candela_pow)); 
                    }

                    if constexpr (radian_pow != 0) {
                        if constexpr (radian_pow == 1) 
                            base_string.append("rad"); 
                        else 
                            base_string.append("rad^" + std::to_string(radian_pow)); 
                    
                    }

                    return base_string; 
                
                }


        }; // struct unit_base


        /// @brief is_base is a trait to check if a type is a unit_base
        template <typename T>
        struct is_base : std::false_type {};


        template <int metre_pow, 
                  int second_pow, 
                  int kilogram_pow, 
                  int ampere_pow, 
                  int kelvin_pow, 
                  int mole_pow, 
                  int candela_pow, 
                  int radian_pow>
        struct is_base<meta_base<metre_pow, 
                                 second_pow, 
                                 kilogram_pow, 
                                 ampere_pow, 
                                 kelvin_pow, 
                                 mole_pow, 
                                 candela_pow, 
                                 radian_pow>> : std::true_type {};


        template <typename T>
        inline constexpr bool is_base_v = is_base<T>::value;
        

        template <typename base1, typename base2>
        struct base_product {

            using type = meta_base<base1::metre + base2::metre, 
                                   base1::second + base2::second,
                                   base1::kilogram + base2::kilogram,
                                   base1::ampere + base2::ampere,
                                   base1::kelvin + base2::kelvin,
                                   base1::mole + base2::mole,
                                   base1::candela + base2::candela,
                                   base1::radian + base2::radian>;

        }; 

        template <typename base1, typename base2>
        using base_product_t = typename base_product<base1, base2>::type; 


        template <typename base1, typename base2>
        struct base_division {

            using type = meta_base<base1::metre_pow - base2::metre_pow, 
                                   base1::second_pow - base2::second_pow,
                                   base1::kilogram_pow - base2::kilogram_pow,
                                   base1::ampere_pow - base2::ampere_pow,
                                   base1::kelvin_pow - base2::kelvin_pow,
                                   base1::mole_pow - base2::mole_pow,
                                   base1::candela_pow - base2::candela_pow,
                                   base1::radian_pow - base2::radian_pow>;

        }; 

        template <typename base1, typename base2>
        using base_division_t = typename base_division<base1, base2>::type; 


        template <typename base, int power>
        struct base_pow {

            using type = meta_base<base::metre * power, 
                                   base::second * power,
                                   base::kilogram * power,
                                   base::ampere * power,
                                   base::kelvin * power,
                                   base::mole * power,
                                   base::candela * power,
                                   base::radian * power>;

        };

        template <typename base, int power>
        using base_pow_t = typename base_pow<base, power>::type;


        template <typename base, int power>
        struct base_root {

            using type = meta_base<base::metre / power, 
                                   base::second / power,
                                   base::kilogram / power,
                                   base::ampere / power,
                                   base::kelvin / power,
                                   base::mole / power,
                                   base::candela / power,
                                   base::radian / power>;

        };

        template <typename base, int power>
        using base_root_t = typename base_root<base, power>::type;



        /**
        * @brief Perform a multiplication between unit_base 
        * 
        * @param other: base as l-value const reference
        *                      
        * @return consteval base
        */
        template <typename base1, typename base2, typename = std::enable_if_t<is_base_v<base1> && is_base_v<base2>>>
        consteval auto operator*(const base1& ub1, const base2& ub2) noexcept -> base_product_t<typename base1::type, typename base2::type> {
            
            return base_product_t<typename base1::type, typename base2::type>(); 
            
        } 


        /**
        * @brief Perform a division between unit_base 
        * 
        * @param other: base as l-value const reference
        *                      
        * @return consteval base
        */
        template <typename base1, typename base2>
        consteval auto operator/(const base1& ub1, const base2& ub2) noexcept -> base_division_t<typename base1::type, typename base2::type> {
            
            return base_division_t<typename base1::type, typename base2::type>(); 
            
        } 



        using meta_metre = meta_base<1, 0, 0, 0, 0, 0, 0, 0>;
        
        using meta_second = meta_base<0, 1, 0, 0, 0, 0, 0, 0>;
        
        using meta_kilogram = meta_base<0, 0, 1, 0, 0, 0, 0, 0>;
        
        using meta_ampere = meta_base<0, 0, 0, 1, 0, 0, 0, 0>;
        
        using meta_kelvin = meta_base<0, 0, 0, 0, 1, 0, 0, 0>;
        
        using meta_mole = meta_base<0, 0, 0, 0, 0, 1, 0, 0>;
        
        using meta_candela = meta_base<0, 0, 0, 0, 0, 0, 1, 0>;
        
        using meta_radian = meta_base<0, 0, 0, 0, 0, 0, 0, 1>;


        namespace base {


            static constexpr meta_metre metre;
            
            static constexpr meta_second second;
            
            static constexpr meta_kilogram kilogram;
            
            static constexpr meta_ampere ampere;
            
            static constexpr meta_kelvin kelvin;
            
            static constexpr meta_mole mole;
            
            static constexpr meta_candela candela;
            
            static constexpr meta_radian radian;


            static constexpr auto metre2 = base_pow_t<meta_metre, 2>();

            static constexpr auto metre3 = base_pow_t<meta_metre, 3>();

            static constexpr auto second2 = base_pow_t<meta_second, 2>();
                    

        }; 

    } // namespace units


} // namespace scipp::measurements