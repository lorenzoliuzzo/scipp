/**
 * @file    math/ops/prefixes.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains all the possible mathematical operations among physics::units::prefix
 * @date    2023-04-23
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {

    
    /// @brief op namespace contains all the classes and functions for doing mathematical operations
    namespace op {


        /// @brief Compute the product of a list of std::ratio
        template <typename RATIO, typename... RATIOS>
            requires (physics::are_prefix_v<RATIO, RATIOS...>)
        struct prefix_product {

            using type = std::ratio_multiply<RATIO, typename prefix_product<RATIOS...>::type>;

        };


        /// @brief Compute the product of a list of std::ratio
        template <typename RATIO>
            requires (physics::is_prefix_v<RATIO>)
        struct prefix_product<RATIO> {

            using type = RATIO;

        };


        template <typename RATIO, typename... RATIOS>
        using prefix_product_t = typename prefix_product<RATIO, RATIOS...>::type;


        /// @brief Compute the division of a list of std::ratio
        template <typename RATIO, typename... RATIOS>
            requires (physics::are_prefix_v<RATIO, RATIOS...>)
        struct prefix_division {

            using type = std::ratio_divide<RATIO, typename prefix_division<RATIOS...>::type>;

        };


        /// @brief Compute the division of a list of std::ratio
        template <typename RATIO>
            requires (physics::is_prefix_v<RATIO>)
        struct prefix_division<RATIO> {

            using type = RATIO;

        };


        template <typename RATIO, typename... RATIOS>
        using prefix_division_t = typename prefix_division<RATIO, RATIOS...>::type;


        /// @brief Struct to compute the inverse of an std::ratio
        template <typename RATIO>
            requires (physics::is_prefix_v<RATIO>)
        struct ratio_inv {
            
            using type = std::ratio<RATIO::den, RATIO::num>; 

        }; 

        template <typename RATIO>
        using ratio_inv_t = typename ratio_inv<RATIO>::type;


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


        template <typename RATIO>
        using ratio_square_t = ratio_pow_t<RATIO, 2>;

        template <typename RATIO>
        using ratio_cube_t = ratio_pow_t<RATIO, 3>;


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


        template <typename RATIO>
        using ratio_sqrt_t = ratio_root_t<RATIO, 2>;

        template <typename RATIO>
        using ratio_cbrt_t = ratio_root_t<RATIO, 3>;
    
    
    } // namespace op


} // namespace scipp::math