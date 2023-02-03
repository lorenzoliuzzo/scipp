/**
 * @file    unit_base.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::physics {


    namespace units {


        /// @brief base_prod is a struct to compute the product of two base
        template <typename base1, typename base2, typename = std::enable_if_t<is_base_v<base1> && is_base_v<base2>>>
        struct base_prod : public unit_base <base1::metre + base2::metre, 
                                             base1::second + base2::second,
                                             base1::kilogram + base2::kilogram,
                                             base1::ampere + base2::ampere,
                                             base1::kelvin + base2::kelvin,
                                             base1::mole + base2::mole,
                                             base1::candela + base2::candela,
                                             base1::radian + base2::radian> {}; 

        /// @brief base_prod_t has the type of the base_prod trait
        template <typename base1, typename base2, typename = std::enable_if_t<is_base_v<base1> && is_base_v<base2>>>
        using base_prod_t = typename base_prod<base1, base2>::type; 


        /// @brief base_div is a struct to compute the division of two base
        template <typename base1, typename base2, typename = std::enable_if_t<is_base_v<base1> && is_base_v<base2>>>
        struct base_div : public unit_base <base1::metre - base2::metre, 
                                            base1::second - base2::second,
                                            base1::kilogram - base2::kilogram,
                                            base1::ampere - base2::ampere,
                                            base1::kelvin - base2::kelvin,
                                            base1::mole - base2::mole,
                                            base1::candela - base2::candela,
                                            base1::radian - base2::radian> {}; 

        /// @brief base_div_t has the type of the base_div trait
        template <typename base1, typename base2, typename = std::enable_if_t<is_base_v<base1> && is_base_v<base2>>>
        using base_div_t = typename base_div<base1, base2>::type; 


        /// @brief base_pow is a struct to compute the power of a base
        template <typename base, int power, typename = std::enable_if_t<is_base_v<base>>>
        struct base_pow : public unit_base<base::metre * power, 
                                           base::second * power,
                                           base::kilogram * power,
                                           base::ampere * power,
                                           base::kelvin * power,
                                           base::mole * power,
                                           base::candela * power,
                                           base::radian * power> {};

        /// @brief base_pow_t has the type of the base_pow trait
        template <typename base, int power, typename = std::enable_if_t<is_base_v<base>>>
        using base_pow_t = typename base_pow<base, power>::type;


        /// @brief has_valid_root is a struct to check if a base has a valid root
        template <typename base, int power, typename = std::enable_if_t<is_base_v<base>>>
        struct has_valid_root {

            static constexpr bool value = (base::metre % power == 0) && 
                                          (base::second % power == 0) && 
                                          (base::kilogram % power == 0) && 
                                          (base::ampere % power == 0) && 
                                          (base::kelvin % power == 0) && 
                                          (base::mole % power == 0) && 
                                          (base::candela % power == 0) && 
                                          (base::radian % power == 0);

        };

        /// @brief has_valid_root_v has the value of the has_valid_root trait
        template <typename base, int power, typename = std::enable_if_t<is_base_v<base>>>
        inline constexpr bool has_valid_root_v = has_valid_root<base, power>::value;


        /// @brief base_root is a struct to compute the root of a base
        template <typename base, int power, typename = std::enable_if_t<is_base_v<base>>>
        struct base_root : public unit_base<base::metre / power, 
                                            base::second / power,
                                            base::kilogram / power,
                                            base::ampere / power,
                                            base::kelvin / power,
                                            base::mole / power,
                                            base::candela / power,
                                            base::radian / power> {};

        /// @brief base_root_t has the type of the base_root trait
        template <typename base, int power, typename = std::enable_if_t<has_valid_root_v<base, power>>>
        using base_root_t = typename base_root<base, power>::type;


    } // namespace units

    
} // namespace scipp::math