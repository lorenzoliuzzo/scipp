/**
 * @file    units.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::physics {


    namespace units {


        // =============================================
        // ALGEBRIC FUNCTIONS
        // =============================================
            
            template <typename unit1, typename unit2, typename = std::enable_if_t<is_unit_v<unit1> && is_unit_v<unit2>>>
            struct unit_prod {

                using type = unit<base_prod_t<typename unit1::base, typename unit2::base>, ratio_prod_t<typename unit1::prefix, typename unit2::prefix>>;

            }; 

            template <typename unit1, typename unit2, typename = std::enable_if_t<is_unit_v<unit1> && is_unit_v<unit2>>>
            using unit_prod_t = typename unit_prod<unit1, unit2>::type; 


            template <typename unit1, typename unit2, typename = std::enable_if_t<is_unit_v<unit1> && is_unit_v<unit2>>>
            struct unit_div {

                using type = unit<base_div_t<typename unit1::base, typename unit2::base>, ratio_div_t<typename unit1::prefix, typename unit2::prefix>>;

            }; 

            template <typename unit1, typename unit2, typename = std::enable_if_t<is_unit_v<unit1> && is_unit_v<unit2>>>
            using unit_div_t = typename unit_div<unit1, unit2>::type; 


            template <typename units, int power>
            struct unit_pow {

                using type = unit<base_pow_t<typename units::base, power>, ratio_pow_t<typename units::prefix, power>>;

            };

            template <typename units, int power>
            using unit_pow_t = typename unit_pow<units, power>::type;


            template <typename units, int power>
            struct unit_root {

                using type = unit<base_root_t<typename units::base, power>, ratio_root_t<typename units::prefix, power>>;

            };

            template <typename units, int power>
            using unit_root_t = typename unit_root<units, power>::type;


            template <typename units>
            struct unit_inv {

                using type = unit<base_inv_t<typename units::base>, ratio_inv_t<typename units::prefix>>;

            };


            template <typename units>
            using unit_inv_t = typename unit_inv<units>::type;


            /// @brief Perform a multiplication between unit 
            template <typename unit1, typename unit2, typename = std::enable_if_t<is_unit_v<unit1> && is_unit_v<unit2>>>
            consteval auto operator*(const unit1& ub1, const unit2& ub2) noexcept -> unit_prod_t<typename unit1::type, typename unit2::type> {
                
                return unit_prod_t<typename unit1::type, typename unit2::type>(); 
                
            } 


            /// @brief Perform a division between unit 
            template <typename unit1, typename unit2, typename = std::enable_if_t<is_unit_v<unit1> && is_unit_v<unit2>>>
            consteval auto operator/(const unit1& ub1, const unit2& ub2) noexcept -> unit_div_t<typename unit1::type, typename unit2::type> {
                
                return unit_div_t<typename unit1::type, typename unit2::type>(); 
                
            } 


    } // namespace units


} // namespace scipp::physics