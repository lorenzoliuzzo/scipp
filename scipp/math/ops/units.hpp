/**
 * @file    math/ops/units.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains all the possible mathematical operations among physics::unit
 * @date    2023-04-23
 * @todo    All this shit could be useless, check if it is used for real.
 * @copyright Copyright (c) 2023
 */



/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {
    
    
    /// @brief op namespace contains all the classes and functions for doing mathematical operations
    namespace op {


        /// @brief Struct to compute the inverse of an unit type
        template <typename UNIT>
            requires (physics::is_unit_v<UNIT>)
        struct unit_invert {
            
            using _t = physics::unit<base_invert_t<typename UNIT::base_t>,  
                                       ratio_inv_t<typename UNIT::prefix_t>>; 
        
        }; 

        template <typename UNIT>
        using unit_invert_t = typename unit_invert<UNIT>::_t;


        /// @brief Struct to compute the product between two unit types
        template <typename UNIT1, typename UNIT2> 
            requires (physics::are_units_v<UNIT1, UNIT2>)
        struct unit_product {
                
            using _t = physics::unit<base_product_t<typename UNIT1::base_t, typename UNIT2::base_t>, 
                                       std::ratio_multiply<typename UNIT1::prefix_t, typename UNIT2::prefix_t>>;

        };

        template <typename UNIT1, typename UNIT2> 
            requires (physics::are_units_v<UNIT1, UNIT2>)
        using unit_product_t = typename unit_product<UNIT1, UNIT2>::_t; 


        /// @brief Struct to compute the division between two unit types
        template <typename UNIT1, typename UNIT2> 
            requires (physics::are_units_v<UNIT1, UNIT2>)
        struct unit_division {
                
            using _t = physics::unit<base_division_t<typename UNIT1::base_t, typename UNIT2::base_t>, 
                                                    std::ratio_divide<typename UNIT1::prefix_t, typename UNIT2::prefix_t>>;

        };

        template <typename UNIT1, typename UNIT2> 
            requires (physics::are_units_v<UNIT1, UNIT2>)
        using unit_division_t = typename unit_division<UNIT1, UNIT2>::_t; 


        /// @brief Struct to compute the power of an unit type
        template <typename UNIT, std::size_t POWER>
        struct unit_pow {
                
            using _t = physics::unit<base_pow_t<typename UNIT::base_t, POWER>, 
                                       ratio_pow_t<typename UNIT::prefix_t, POWER>>; 
        
        };

        template <typename UNIT, std::size_t POWER>
        using unit_pow_t = typename unit_pow<UNIT, POWER>::_t;

        template <typename UNIT>
        using unit_square_t = unit_pow_t<UNIT, 2>;

        template <typename UNIT>
        using unit_cube_t = unit_pow_t<UNIT, 3>;

        
        /// @brief Struct to compute the root power of an unit type
        template <typename UNIT, std::size_t POWER>
        struct unit_root {
            
            using _t = physics::unit<base_root_t<typename UNIT::base_t, POWER>, 
                                       ratio_root_t<typename UNIT::prefix_t, POWER>>;

        };


        template <typename UNIT, std::size_t POWER>
        using unit_root_t = typename unit_root<UNIT, POWER>::_t;

        template <typename UNIT>
        using unit_sqrt_t = unit_root_t<UNIT, 2>;

        template <typename UNIT>
        using unit_cbrt_t = unit_root_t<UNIT, 3>;


    } // namespace op


} // namespace scipp::math