/**
 * @file    math/ops/vectors.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-12
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {
    

    namespace op {


        /// @brief Invert a vector
        template <typename VECTOR_TYPE> 
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        constexpr auto inv(const VECTOR_TYPE& vec)
            -> geometry::vector<physics::measurements_inv_t<typename VECTOR_TYPE::measurement_type>, VECTOR_TYPE::dim> {

            geometry::vector<physics::measurements_inv_t<typename VECTOR_TYPE::measurement_type>, VECTOR_TYPE::dim> result;

            for (std::size_t i{}; i < VECTOR_TYPE::dim; ++i) 
                result.data[i] = op::inv(vec.data[i]);

            return result;

        }


        /// @brief Take the absolute value of a vector
        template <typename VECTOR_TYPE> 
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        constexpr auto abs(const VECTOR_TYPE& vec) noexcept
            -> VECTOR_TYPE {

            VECTOR_TYPE result;

            for (std::size_t i{}; i < VECTOR_TYPE::dim; ++i) 
                result.data[i] = op::abs(vec.data[i]);

            return result;

        }


        /// @brief Take the power of a vector
        template <int POWER, typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        constexpr auto pow(const VECTOR_TYPE& vec) noexcept
            -> std::conditional_t<physics::is_umeasurement_v<typename VECTOR_TYPE::measurement_type>, 
                geometry::vector<physics::umeasurement<physics::base_pow_t<typename VECTOR_TYPE::measurement_type::base, POWER>>, VECTOR_TYPE::dim>,
                geometry::vector<physics::measurement<physics::base_pow_t<typename VECTOR_TYPE::measurement_type::base, POWER>>, VECTOR_TYPE::dim>> {

            geometry::vector<auto, VECTOR_TYPE::dim> result;

            for (std::size_t i{}; i < VECTOR_TYPE::dim; ++i) 
                result.data[i] = op::pow<POWER>(vec.data[i]);

            return result;

        }
        

        // /// @brief Take the absolute value of a vector
        // /// @tparam BASE: physics::units::unit_base
        // /// @tparam DIM: size_t
        // /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
        // /// @return constexpr geometry::vector<units::base_inv_t<BASE>, DIM>
        // template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        // constexpr vector<units::base_inv_t<BASE>, DIM> abs(const vector<BASE, DIM>& vec) noexcept {

        //     vector<units::base_inv_t<BASE>, DIM> result;

        //     for (std::size_t i{}; i < DIM; ++i) 
        //         result[i] = op::abs(vec[i]);

        //     return result;

        // }


        // // /// @brief Take the power of a vector
        // // /// @tparam BASE: physics::units::unit_base
        // // /// @tparam DIM: size_t
        // // /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
        // // /// @param power: int as l-value const reference
        // // /// @return constexpr geometry::vector<units::base_pow_t<BASE, power>, DIM>
        // // template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        // // constexpr auto pow(const vector<BASE, DIM>& vec, const int&  power) noexcept -> vector<units::base_pow_t<BASE, power>, DIM> {

        // //     vector<units::base_pow_t<BASE, power>, DIM> result;

        // //     for (std::size_t i{}; i < DIM; ++i) 
        // //         result[i] = op::pow(vec[i], power);

        // //     return result;

        // // }


        // /// @brief Take the square of a vector
        // /// @tparam BASE: physics::units::unit_base
        // /// @tparam DIM: size_t
        // /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
        // /// @return constexpr geometry::vector<units::base_pow_t<BASE, 2>, DIM>
        // template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        // constexpr vector<units::base_pow_t<BASE, 2>, DIM> square(const vector<BASE, DIM>& vec) noexcept {

        //     vector<units::base_pow_t<BASE, 2>, DIM> result;

        //     for (std::size_t i{}; i < DIM; ++i) 
        //         result[i] = op::square(vec[i]);

        //     return result;

        // }


        // /// @brief Take the cube of a vector
        // /// @tparam BASE: physics::units::unit_base
        // /// @tparam DIM: size_t
        // /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
        // /// @return constexpr geometry::vector<units::base_pow_t<BASE, 3>, DIM>
        // template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        // constexpr vector<units::base_pow_t<BASE, 3>, DIM> cube(const vector<BASE, DIM>& vec) noexcept {

        //     vector<units::base_pow_t<BASE, 3>, DIM> result;

        //     for (std::size_t i{}; i < DIM; ++i) 
        //         result[i] = op::cube(vec[i]);

        //     return result;

        // }


        // /// @brief Take the square root of a vector
        // /// @tparam BASE: physics::units::unit_base
        // /// @tparam DIM: size_t
        // /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
        // /// @return constexpr geometry::vector<units::base_root_t<BASE, 2>, DIM>
        // template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        // constexpr vector<units::base_root_t<BASE, 2>, DIM> sqrt(const vector<BASE, DIM>& vec) {

        //     vector<units::base_root_t<BASE, 2>, DIM> result;

        //     for (std::size_t i{}; i < DIM; ++i) 
        //         result[i] = op::sqrt(vec[i]);

        //     return result;

        // }


        // /// @brief Take the cube root of a vector
        // /// @tparam BASE: physics::units::unit_base
        // /// @tparam DIM: size_t
        // /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
        // /// @return constexpr geometry::vector<units::base_root_t<BASE, 3>, DIM>
        // template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        // constexpr vector<units::base_root_t<BASE, 3>, DIM> cbrt(const vector<BASE, DIM>& vec) noexcept {

        //     vector<units::base_root_t<BASE, 3>, DIM> result;

        //     for (std::size_t i{}; i < DIM; ++i) 
        //         result[i] = op::cbrt(vec[i]);

        //     return result;

        // }


    } // namespace op


} // namespace scipp::math