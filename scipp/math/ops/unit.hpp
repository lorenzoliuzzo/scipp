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


        /// @brief Compute the inverse of an unit type
        template <typename UNIT>
            requires (physics::is_unit_v<UNIT>)
        inline static constexpr auto inv() noexcept
            -> physics::unit<base_invert_t<typename UNIT::base_t>, ratio_inv_t<typename UNIT::prefix_t>> {

            return {};  
        
        }; 


        template <typename UNIT, std::size_t POWER>
            requires (physics::is_unit_v<UNIT>)
        inline static constexpr auto pow(const UNIT&) noexcept
            -> physics::unit<op::base_pow_t<typename UNIT::base_t, POWER>, 
                             op::ratio_pow_t<typename UNIT::prefix_t, POWER>> {

            return {};  
        
        };


        template <typename UNIT, std::size_t POWER>
            requires (physics::is_unit_v<UNIT> && physics::has_valid_root_v<typename UNIT::base_t, POWER>)
        inline static constexpr auto root(const UNIT&) noexcept
            -> physics::unit<op::base_root_t<typename UNIT::base_t, POWER>, 
                             op::ratio_root_t<typename UNIT::prefix_t, POWER>> {

            return {};

        };


        template <typename UNIT>
            requires (physics::is_unit_v<UNIT>)
        inline static constexpr auto sqrt(const UNIT&) noexcept
            -> physics::unit<op::base_sqrt_t<typename UNIT::base_t>, 
                             op::ratio_sqrt_t<typename UNIT::prefix_t>> {

            return {};

        };


        template <typename UNIT>
            requires (physics::is_unit_v<UNIT>)
        inline static constexpr auto cbrt(const UNIT&) noexcept

            -> physics::unit<op::base_cbrt_t<typename UNIT::base_t>, 
                             op::ratio_cbrt_t<typename UNIT::prefix_t>> {

            return {};

        };


    } // namespace op


} // namespace scipp::math