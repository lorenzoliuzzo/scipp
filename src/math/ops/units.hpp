/**
 * @file    math/ops/units.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-12
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {
    
    
    namespace op {


        template <typename UNIT>
            requires (physics::is_unit_v<UNIT>)
        struct unit_invert : public physics::unit<base_invert_t<typename UNIT::base>,  
                                                  ratio_inv_t<typename UNIT::prefix>> {}; 

        template <typename UNIT>
        using unit_invert_t = typename unit_invert<UNIT>::type;


        template <typename UNIT1, typename UNIT2> 
            requires (physics::are_units_v<UNIT1, UNIT2>)
        struct unit_product : public physics::unit<base_product_t<typename UNIT1::base, typename UNIT2::base>, 
                                                   std::ratio_multiply<typename UNIT1::prefix, typename UNIT2::prefix>> {};

        template <typename UNIT1, typename UNIT2> 
            requires (physics::are_units_v<UNIT1, UNIT2>)
        using unit_product_t = typename unit_product<UNIT1, UNIT2>::type; 


        template <typename UNIT1, typename UNIT2> 
            requires (physics::are_units_v<UNIT1, UNIT2>)
        struct unit_division : public physics::unit<base_division_t<typename UNIT1::base, typename UNIT2::base>, 
                                                    std::ratio_divide<typename UNIT1::prefix, typename UNIT2::prefix>> {};


        template <typename UNIT1, typename UNIT2> 
            requires (physics::are_units_v<UNIT1, UNIT2>)
        using unit_division_t = typename unit_division<UNIT1, UNIT2>::type; 


        template <typename UNIT, int POWER>
        struct unit_pow : public physics::unit<base_pow_t<typename UNIT::base, POWER>, 
                                               ratio_pow_t<typename UNIT::prefix, POWER>> {};

        template <typename UNIT, int POWER>
        using unit_pow_t = typename unit_pow<UNIT, POWER>::type;

        template <typename UNIT>
        using unit_square_t = unit_pow_t<UNIT, 2>;

        template <typename UNIT>
        using unit_cube_t = unit_pow_t<UNIT, 3>;

        
        template <typename UNIT, int POWER>
        struct unit_root : public physics::unit<base_root_t<typename UNIT::base, POWER>, 
                                                ratio_root_t<typename UNIT::prefix, POWER>> {};


        template <typename UNIT, int POWER>
        using unit_root_t = typename unit_root<UNIT, POWER>::type;

        template <typename UNIT>
        using unit_sqrt_t = unit_root_t<UNIT, 2>;

        template <typename UNIT>
        using unit_cbrt_t = unit_root_t<UNIT, 3>;


    } // namespace op


} // namespace scipp::math