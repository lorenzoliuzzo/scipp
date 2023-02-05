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


        /// @brief base_square is a struct to compute the square power of a base
        template <typename base, typename = std::enable_if_t<is_base_v<base>>>
        struct base_square : public unit_base<base::metre * 2, 
                                              base::second * 2,
                                              base::kilogram * 2,
                                              base::ampere * 2,
                                              base::kelvin * 2,
                                              base::mole * 2,
                                              base::candela * 2,
                                              base::radian * 2> {};

        /// @brief base_square_t has the type of the base_square trait
        template <typename base, typename = std::enable_if_t<is_base_v<base>>>
        using base_square_t = typename base_square<base>::type;


        /// @brief base_cube is a struct to compute the cube power of a base
        template <typename base, typename = std::enable_if_t<is_base_v<base>>>
        struct base_cube : public unit_base<base::metre * 3, 
                                            base::second * 3,
                                            base::kilogram * 3,
                                            base::ampere * 3,
                                            base::kelvin * 3,
                                            base::mole * 3,
                                            base::candela * 3,
                                            base::radian * 3> {};

        /// @brief base_cube_t has the type of the base_cube trait
        template <typename base, typename = std::enable_if_t<is_base_v<base>>>
        using base_cube_t = typename base_cube<base>::type;


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


        /// @brief base_sqrt is a struct to compute the square root of a base
        template <typename base, typename = std::enable_if_t<is_base_v<base>>>
        struct base_sqrt : public unit_base<base::metre / 2, 
                                            base::second / 2,
                                            base::kilogram / 2,
                                            base::ampere / 2,
                                            base::kelvin / 2,
                                            base::mole / 2,
                                            base::candela / 2,
                                            base::radian / 2> {};

        /// @brief base_sqrt_t has the type of the base_sqrt trait
        template <typename base, typename = std::enable_if_t<is_base_v<base>>>
        using base_sqrt_t = typename base_sqrt<base>::type;


        /// @brief base_cbrt is a struct to compute the cube root of a base
        template <typename base, typename = std::enable_if_t<is_base_v<base>>>
        struct base_cbrt : public unit_base<base::metre / 3, 
                                            base::second / 3,
                                            base::kilogram / 3,
                                            base::ampere / 3,
                                            base::kelvin / 3,
                                            base::mole / 3,
                                            base::candela / 3,
                                            base::radian / 3> {};

        /// @brief base_cbrt_t has the type of the base_cbrt trait
        template <typename base, typename = std::enable_if_t<is_base_v<base>>>
        using base_cbrt_t = typename base_cbrt<base>::type;


        /// @brief base_inv is a struct to compute the inverse of a base
        template <typename base, typename = std::enable_if_t<is_base_v<base>>>
        struct base_inv : public unit_base<-base::metre, 
                                          -base::second,
                                          -base::kilogram,
                                          -base::ampere,
                                          -base::kelvin,
                                          -base::mole,
                                          -base::candela,
                                          -base::radian> {};


        /// @brief base_inv_t has the type of the base_inv trait
        template <typename base, typename = std::enable_if_t<is_base_v<base>>>
        using base_inv_t = typename base_inv<base>::type;


    } // namespace units

    
} // namespace scipp::math