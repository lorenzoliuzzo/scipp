/**
 * @file    math/ops/prefixes.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-21
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {
    
    
    namespace op {


        template <typename RATIO, int POWER>
            requires (physics::units::is_prefix_v<RATIO> && POWER >= 0)
        struct ratio_pow {

            static constexpr auto value = std::pow(RATIO::num, POWER);
            static constexpr auto denom_pow = std::pow(RATIO::den, POWER);
            static_assert(denom_pow > 0, "Denominator must be positive");
            static constexpr std::size_t denom = denom_pow;
            static_assert(value <= std::numeric_limits<std::size_t>::max() / denom, "Overflow in constant expression");
            static constexpr std::size_t num = value * denom;

            using type = std::ratio<num, denom>;

        };

        template <typename RATIO, int POWER>
        using ratio_pow_t = typename ratio_pow<RATIO, POWER>::type;


        template <typename RATIO, int POWER>
            requires (physics::units::is_prefix_v<RATIO> && POWER >= 0)
        struct ratio_root {

            static constexpr auto num_pow = std::pow(RATIO::num, 1. / POWER);
            static_assert(num_pow <= std::numeric_limits<std::size_t>::max(), "Overflow in constant expression");
            static constexpr std::size_t num = static_cast<std::size_t>(num_pow);
            static constexpr auto denom_pow = std::pow(RATIO::den, 1. / POWER);
            static_assert(denom_pow > 0, "Denominator must be positive");
            static constexpr std::size_t denom = static_cast<std::size_t>(denom_pow);

            using type = std::ratio<num, denom>;

        };

        template <typename RATIO, int POWER>
        using ratio_root_t = typename ratio_root<RATIO, POWER>::type;


        template <typename RATIO>
        struct ratio_inv {
            
            using type = std::ratio<RATIO::den, RATIO::num>; 

        }; 

        template <typename RATIO>
        using ratio_inv_t = typename ratio_inv<RATIO>::type;
    
    
    } // namespace op


} // namespace scipp::math