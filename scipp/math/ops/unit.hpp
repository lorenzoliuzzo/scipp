/**
 * @file    math/ops/units.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains all the possible mathematical operations among physics::unit
 * @date    2023-04-24
 * @todo    All this shit could be useless, check if it is used for real.
 * @copyright Copyright (c) 2023
 */



/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {
    
    
    /// @brief op namespace contains all the classes and functions for doing mathematical operations
    namespace op {




        // template <typename UNIT_TYPE>
        //     requires (physics::is_unit_v<UNIT_TYPE>)
        // inline static constexpr auto square(const UNIT_TYPE&) noexcept
        //     -> meta::square_t<UNIT_TYPE> {

        //     return {};

        // };


        template <typename UNIT_TYPE>
            requires (physics::is_unit_v<UNIT_TYPE>)
        inline static constexpr auto cube(const UNIT_TYPE&) noexcept
            -> meta::cube_t<UNIT_TYPE> {

            return {};

        };


        template <typename UNIT_TYPE, std::size_t POWER>
            requires (physics::is_unit_v<UNIT_TYPE> && physics::has_valid_root_v<typename UNIT_TYPE::base_t, POWER>)
        inline static constexpr auto root(const UNIT_TYPE&) noexcept
            -> meta::root_t<UNIT_TYPE, POWER> {

            return {};

        };


        template <typename UNIT_TYPE>
            requires (physics::is_unit_v<UNIT_TYPE>)
        inline static constexpr auto sqrt(const UNIT_TYPE&) noexcept
            -> meta::sqrt_t<UNIT_TYPE> {

            return {};

        };


        template <typename UNIT_TYPE>
            requires (physics::is_unit_v<UNIT_TYPE>)
        inline static constexpr auto cbrt(const UNIT_TYPE&) noexcept
            -> meta::cbrt_t<UNIT_TYPE> {

            return {};

        };


    } // namespace op


} // namespace scipp::math