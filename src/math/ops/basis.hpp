/**
 * @file    math/ops/basis.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-12
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {
    
    
    namespace op {


        /// @brief base_invert is a struct to compute the inverse of a base
        template <typename BASE> 
            requires (physics::is_base_v<BASE>)
        struct base_invert : public physics::base_quantity<-BASE::length_power, 
                                                           -BASE::time_power,
                                                           -BASE::mass_power,
                                                           -BASE::temperature_power,
                                                           -BASE::substance_amount_power,
                                                           -BASE::elettric_current_power,
                                                           -BASE::luminous_intensity_power,
                                                           -BASE::angle_power> {};

        template <typename BASE> 
        using base_invert_t = typename base_invert<BASE>::type;
        

        /// @brief base_product is a struct to compute the product of bases in a parameter pack
        template <typename... BASES> 
            requires (physics::are_base_v<BASES...>)
        struct base_product : public physics::base_quantity<(BASES::length_power + ...), 
                                                            (BASES::time_power + ...),
                                                            (BASES::mass_power + ...),
                                                            (BASES::temperature_power + ...),
                                                            (BASES::substance_amount_power + ...),
                                                            (BASES::elettric_current_power + ...),
                                                            (BASES::luminous_intensity_power + ...),
                                                            (BASES::angle_power + ...)> {};

        template <typename... BASES>
        using base_product_t = typename base_product<BASES...>::type;


        /// @brief base_division is a struct to compute the division of two base
        template <typename BASE1, typename BASE2> 
            requires (physics::are_base_v<BASE1, BASE2>)
        struct base_division : public physics::base_quantity<BASE1::length_power - BASE2::length_power, 
                                                             BASE1::time_power - BASE2::time_power,
                                                             BASE1::mass_power - BASE2::mass_power,
                                                             BASE1::temperature_power - BASE2::temperature_power,
                                                             BASE1::substance_amount_power - BASE2::substance_amount_power,
                                                             BASE1::elettric_current_power - BASE2::elettric_current_power,
                                                             BASE1::luminous_intensity_power - BASE2::luminous_intensity_power,
                                                             BASE1::angle_power - BASE2::angle_power> {}; 

        template <typename BASE1, typename BASE2> 
        using base_division_t = typename base_division<BASE1, BASE2>::type; 


        /// @brief base_pow is a struct to compute the power of a base
        template <typename BASE, int POWER> 
            requires (physics::is_base_v<BASE>)
        struct base_pow : public physics::base_quantity<BASE::length_power * POWER, 
                                                        BASE::time_power * POWER,
                                                        BASE::mass_power * POWER,
                                                        BASE::temperature_power * POWER,
                                                        BASE::substance_amount_power * POWER,
                                                        BASE::elettric_current_power * POWER,
                                                        BASE::luminous_intensity_power * POWER,
                                                        BASE::angle_power * POWER> {};

        template <typename BASE, int POWER> 
        using base_pow_t = typename base_pow<BASE, POWER>::type;

        template <typename BASE>    
        using base_square_t = typename base_pow<BASE, 2>::type;

        template <typename BASE>
        using base_cube_t = typename base_pow<BASE, 3>::type;


        /// @brief base_root is a struct to compute the root of a base
        template <typename BASE, int POWER> 
            requires (physics::has_valid_root_v<BASE, POWER>)
        struct base_root : public physics::base_quantity<BASE::length_power / POWER, 
                                                         BASE::time_power / POWER,
                                                         BASE::mass_power / POWER,
                                                         BASE::temperature_power / POWER,
                                                         BASE::substance_amount_power / POWER,
                                                         BASE::elettric_current_power / POWER,
                                                         BASE::luminous_intensity_power / POWER,
                                                         BASE::angle_power / POWER> {};

        template <typename BASE, int POWER> 
        using base_root_t = typename base_root<BASE, POWER>::type;

        template <typename BASE>
        using base_sqrt_t = typename base_root<BASE, 2>::type;

        template <typename BASE>
        using base_cbrt_t = typename base_root<BASE, 3>::type;


template <typename RATIO, int POWER>
struct ratio_pow {
    static_assert(POWER >= 0, "Power must be non-negative");
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
struct ratio_root {
    static_assert(POWER > 0, "Power must be positive");
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

        // template <typename RATIO, int POWER>
        // struct ratio_pow {
            
        //     using type = std::ratio<(std::size_t) std::pow(RATIO::num, POWER), (std::size_t) std::pow(RATIO::den, POWER)>;

        // }; 

        // template <typename RATIO, int POWER>
        // using ratio_pow_t = typename ratio_pow<RATIO, POWER>::type;


        // template <typename RATIO, int POWER>
        // struct ratio_root {
            
        //     using type = std::ratio<std::pow(RATIO::num, 1. / POWER), std::pow(RATIO::den, 1. / POWER)>;

        // }; 

        // template <typename RATIO, int POWER>
        // using ratio_root_t = typename ratio_root<RATIO, POWER>::type;


        template <typename RATIO>
        struct ratio_inv {
            
            using type = std::ratio<RATIO::den, RATIO::num>; 

        }; 

        template <typename RATIO>
        using ratio_inv_t = typename ratio_inv<RATIO>::type;
    
    
    } // namespace op


} // namespace scipp::math