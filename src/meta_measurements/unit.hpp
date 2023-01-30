/**
 * @file    unit.hpp
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


        template <typename BASE, typename PREFIX = std::ratio<1, 1>>
        struct meta_unit {


            using base = BASE;
            using prefix = PREFIX;
            using type = meta_unit<BASE, PREFIX>; 

            static constexpr double mult = PREFIX::num / PREFIX::den;


            // =============================================
            // operators
            // =============================================

                friend inline std::ostream& operator<<(std::ostream& os, const meta_unit& units) noexcept {

                    os << BASE::to_string(); 

                    return os; 

                }


                // static constexpr std::string to_string() {

                //     return BASE::to_string(); 

                // }


        }; // struct meta_unit


        template <typename unit>
        struct is_unit : std::false_type {};

        template <typename BASE, typename PREFIX>
        struct is_unit<meta_unit<BASE, PREFIX>> : std::true_type {};

        template <typename unit>
        inline constexpr bool is_unit_v = is_unit<unit>::value;


        template <typename unit1, typename unit2>
        struct unit_product {

            using type = meta_unit<base_product_t<typename unit1::base, typename unit2::base>, ratio_product_t<typename unit1::prefix, typename unit2::prefix>>;

        }; 

        template <typename unit1, typename unit2>
        using unit_product_t = typename unit_product<unit1, unit2>::type; 


        template <typename unit1, typename unit2>
        struct unit_division {

            using type = meta_unit<base_division_t<typename unit1::base, typename unit2::base>, ratio_division_t<typename unit1::prefix, typename unit2::prefix>>;

        }; 

        template <typename unit1, typename unit2>
        using unit_division_t = typename unit_division<unit1, unit2>::type; 


        template <typename units, int power>
        struct unit_pow {

            using type = meta_unit<base_pow_t<typename units::base, power>, ratio_pow_t<typename units::prefix, power>>;

        };


        template <typename units, int power>
        using unit_pow_t = typename unit_pow<units, power>::type;


        template <typename units, int power>
        struct unit_root {

            using type = meta_unit<base_root_t<typename units::base, power>, ratio_root_t<typename units::prefix, power>>;

        };


        template <typename units, int power>
        using unit_root_t = typename unit_root<units, power>::type;


        /**
         * @brief Perform a multiplication between unit 
         * 
         * @param other: base as l-value const reference
         *                      
         * @return consteval base
         */
        template <typename unit1, typename unit2, typename = std::enable_if_t<is_unit_v<unit1> && is_unit_v<unit2>>>
        consteval auto operator*(const unit1& ub1, const unit2& ub2) noexcept -> unit_product_t<typename unit1::type, typename unit2::type> {
            
            return unit_product_t<typename unit1::type, typename unit2::type>(); 
            
        } 


        /**
         * @brief Perform a division between unit 
         *
         * @param other: base as l-value const reference
         *                      
         * @return consteval base
         */
        template <typename unit1, typename unit2, typename = std::enable_if_t<is_unit_v<unit1> && is_unit_v<unit2>>>
        consteval auto operator/(const unit1& ub1, const unit2& ub2) noexcept -> unit_division_t<typename unit1::type, typename unit2::type> {
            
            return unit_division_t<typename unit1::type, typename unit2::type>(); 
            
        } 


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


        namespace __units {


            static constexpr _metre m;
            static constexpr _second s;
            static constexpr _kilogram kg;
            static constexpr _ampere A;
            static constexpr _kelvin K;
            static constexpr _mole mol;
            static constexpr _candela cd;
            static constexpr _radian rad;


            static constexpr _kilo_metre km;
            static constexpr _milli_metre mm;
            static constexpr _micro_metre um;
            static constexpr _nano_metre nm;
            static constexpr _pico_metre pm;


        }

        

    } // namespace units


} // namespace scipp::measurements