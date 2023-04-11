/**
 * @file    math/ops/prefixes.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains all the possible mathematical operations among physics::units::prefix
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */





/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {

    
    /// @brief op namespace contains all the classes and functions for doing mathematical operations
    namespace op {


        /// @brief Struct to compute the power of an std::ratio
        template <typename RATIO, std::size_t POWER>
            requires (physics::is_prefix_v<RATIO>)
        struct ratio_pow {

            static constexpr auto value = std::pow(RATIO::num, POWER);
            static constexpr auto denom_pow = std::pow(RATIO::den, POWER);
            static constexpr std::size_t denom = denom_pow;
            static_assert(value <= std::numeric_limits<std::size_t>::max() / denom, "Overflow in constant expression");

            using type = std::ratio<static_cast<std::size_t>(value * denom), denom>;

        };

        template <typename RATIO, std::size_t POWER>
        using ratio_pow_t = typename ratio_pow<RATIO, POWER>::type;


        /// @brief Struct to compute the root power of an std::ratio
        template <typename RATIO, int POWER>
            requires (physics::is_prefix_v<RATIO>)
        struct ratio_root {

            static constexpr auto num_pow = std::pow(RATIO::num, 1. / POWER);
            static_assert(num_pow <= std::numeric_limits<std::size_t>::max(), "Overflow in constant expression");
            static constexpr auto denom_pow = std::pow(RATIO::den, 1. / POWER);

            using type = std::ratio<static_cast<std::size_t>(num_pow), static_cast<std::size_t>(denom_pow)>;

        };

        template <typename RATIO, int POWER>
        using ratio_root_t = typename ratio_root<RATIO, POWER>::type;


        /// @brief Struct to compute the inverse of an std::ratio
        template <typename RATIO>
            requires (physics::is_prefix_v<RATIO>)
        struct ratio_inv {
            
            using type = std::ratio<RATIO::den, RATIO::num>; 

        }; 

        template <typename RATIO>
        using ratio_inv_t = typename ratio_inv<RATIO>::type;
    
    
    } // namespace op


} // namespace scipp::math