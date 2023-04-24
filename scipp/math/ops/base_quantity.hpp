/**
 * @file    math/ops/base_quantities.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the possible operations on base_quantity types.
 * @date    2023-04-23
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    
    
    namespace op {


        /// @brief Struct to compute the product of a list of base_quantity types
        template <typename... BASEs> 
            requires (physics::are_base_v<BASEs...>)
        struct base_product : physics::base_quantity<(BASEs::length + ...), 
                                                     (BASEs::time + ...),
                                                     (BASEs::mass + ...),
                                                     (BASEs::temperature + ...),
                                                     (BASEs::elettric_current + ...),
                                                     (BASEs::substance_amount + ...),
                                                     (BASEs::luminous_intensity + ...)> {};

        template <typename BASE>
            requires (physics::is_base_v<BASE>)
        struct base_product<BASE> : physics::base_quantity<BASE::length, 
                                                           BASE::time,
                                                           BASE::mass,
                                                           BASE::temperature,
                                                           BASE::elettric_current,
                                                           BASE::substance_amount,
                                                           BASE::luminous_intensity> {};
        
        template <typename... BASEs>
        using base_product_t = typename base_product<BASEs...>::_t;


        template <typename BASE, typename... BASEs>
        struct base_division {
            
            using type = typename base_division<BASE, base_product_t<BASEs...>>::_t;

        };

        /// @brief Struct to compute the division of two base_quantity types
        template <typename BASE1, typename BASE2> 
            requires (physics::are_base_v<BASE1, BASE2>)
        struct base_division<BASE1, BASE2> : physics::base_quantity<BASE1::length - BASE2::length, 
                                                                    BASE1::time - BASE2::time,
                                                                    BASE1::mass - BASE2::mass,
                                                                    BASE1::temperature - BASE2::temperature,
                                                                    BASE1::elettric_current - BASE2::elettric_current,
                                                                    BASE1::substance_amount - BASE2::substance_amount,
                                                                    BASE1::luminous_intensity - BASE2::luminous_intensity> {};

        template <typename BASE>
            requires (physics::is_base_v<BASE>)
        struct base_division<BASE> : physics::base_quantity<BASE::length, 
                                                            BASE::time,
                                                            BASE::mass,
                                                            BASE::temperature,
                                                            BASE::elettric_current,
                                                            BASE::substance_amount,
                                                            BASE::luminous_intensity> {};

        template <typename... BASEs> 
        using base_division_t = typename base_division<BASEs...>::_t; 


        /// @brief Struct to compute the inverse of a base_quantity type
        template <typename BASE> 
            requires (physics::is_base_v<BASE>)
        struct base_invert : physics::base_quantity<-BASE::length, 
                                                    -BASE::time,
                                                    -BASE::mass,
                                                    -BASE::temperature,
                                                    -BASE::elettric_current,
                                                    -BASE::substance_amount,
                                                    -BASE::luminous_intensity> {};

        template <typename BASE> 
        using base_invert_t = typename base_invert<BASE>::_t;

        
        /// @brief Struct to compute the power of a base_quantity type
        template <typename BASE, int POWER> 
            requires (physics::is_base_v<BASE>)
        struct base_pow : physics::base_quantity<BASE::length * POWER, 
                                                 BASE::time * POWER,
                                                 BASE::mass * POWER,
                                                 BASE::temperature * POWER,
                                                 BASE::elettric_current * POWER,
                                                 BASE::substance_amount * POWER,
                                                 BASE::luminous_intensity * POWER> {};

        template <typename BASE, int POWER> 
        using base_pow_t = typename base_pow<BASE, POWER>::_t;

        template <typename BASE>    
        using base_square_t = typename base_pow<BASE, 2>::_t;

        template <typename BASE>
        using base_cube_t = typename base_pow<BASE, 3>::_t;


        /// @brief Struct to compute the root power of a base_quantity type
        template <typename BASE, int POWER> 
            requires (physics::has_valid_root_v<BASE, POWER>)
        struct base_root : physics::base_quantity<BASE::length / POWER, 
                                                  BASE::time / POWER,
                                                  BASE::mass / POWER,
                                                  BASE::temperature / POWER,
                                                  BASE::elettric_current / POWER,
                                                  BASE::substance_amount / POWER,
                                                  BASE::luminous_intensity / POWER> {};

        template <typename BASE, int POWER> 
        using base_root_t = typename base_root<BASE, POWER>::_t;

        template <typename BASE>
        using base_sqrt_t = typename base_root<BASE, 2>::_t;

        template <typename BASE>
        using base_cbrt_t = typename base_root<BASE, 3>::_t;

    
    } // namespace op


} // namespace scipp::math