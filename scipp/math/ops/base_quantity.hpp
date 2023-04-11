/**
 * @file    math/ops/base_quantities.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the possible operations on base_quantity types.
 * @date    2023-03-23
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    
    
    namespace op {


        /// @brief Struct to compute the inverse of a base_quantity type
        template <typename BASE> 
            requires (physics::is_base_v<BASE>)
        struct base_invert : public physics::base_quantity<-BASE::length, 
                                                           -BASE::time,
                                                           -BASE::mass,
                                                           -BASE::temperature,
                                                           -BASE::elettric_current,
                                                           -BASE::substance_amount,
                                                           -BASE::luminous_intensity> {};

        template <typename BASE> 
        using base_invert_t = typename base_invert<BASE>::type;
        
        /// @brief Struct to compute the product of a list of base_quantity types
        template <typename... BASES> 
            requires (physics::are_base_v<BASES...>)
        struct base_product : public physics::base_quantity<(BASES::length + ...), 
                                                            (BASES::time + ...),
                                                            (BASES::mass + ...),
                                                            (BASES::temperature + ...),
                                                            (BASES::elettric_current + ...),
                                                            (BASES::substance_amount + ...),
                                                            (BASES::luminous_intensity + ...)> {};

        template <typename... BASES>
        using base_product_t = typename base_product<BASES...>::type;


        /// @brief Struct to compute the division of two base_quantity types
        template <typename BASE1, typename BASE2> 
            requires (physics::are_base_v<BASE1, BASE2>)
        struct base_division : public physics::base_quantity<BASE1::length - BASE2::length, 
                                                             BASE1::time - BASE2::time,
                                                             BASE1::mass - BASE2::mass,
                                                             BASE1::temperature - BASE2::temperature,
                                                             BASE1::elettric_current - BASE2::elettric_current,
                                                             BASE1::substance_amount - BASE2::substance_amount,
                                                             BASE1::luminous_intensity - BASE2::luminous_intensity> {}; 

        template <typename BASE1, typename BASE2> 
        using base_division_t = typename base_division<BASE1, BASE2>::type; 


        /// @brief Struct to compute the power of a base_quantity type
        template <typename BASE, int POWER> 
            requires (physics::is_base_v<BASE>)
        struct base_pow : public physics::base_quantity<BASE::length * POWER, 
                                                        BASE::time * POWER,
                                                        BASE::mass * POWER,
                                                        BASE::temperature * POWER,
                                                        BASE::elettric_current * POWER,
                                                        BASE::substance_amount * POWER,
                                                        BASE::luminous_intensity * POWER> {};

        template <typename BASE, int POWER> 
        using base_pow_t = typename base_pow<BASE, POWER>::type;

        template <typename BASE>    
        using base_square_t = typename base_pow<BASE, 2>::type;

        template <typename BASE>
        using base_cube_t = typename base_pow<BASE, 3>::type;


        /// @brief Struct to compute the root power of a base_quantity type
        template <typename BASE, int POWER> 
            requires (physics::has_valid_root_v<BASE, POWER>)
        struct base_root : public physics::base_quantity<BASE::length / POWER, 
                                                         BASE::time / POWER,
                                                         BASE::mass / POWER,
                                                         BASE::temperature / POWER,
                                                         BASE::elettric_current / POWER,
                                                         BASE::substance_amount / POWER,
                                                         BASE::luminous_intensity / POWER> {};

        template <typename BASE, int POWER> 
        using base_root_t = typename base_root<BASE, POWER>::type;

        template <typename BASE>
        using base_sqrt_t = typename base_root<BASE, 2>::type;

        template <typename BASE>
        using base_cbrt_t = typename base_root<BASE, 3>::type;

    
    } // namespace op


} // namespace scipp::math