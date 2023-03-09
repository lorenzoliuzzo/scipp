/**
 * @file    math/ops/vectors.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-02-11
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::geometry {


    /// @brief Multiply a vector by a scalar
    /// @tparam DIM: size_t
    /// @tparam MEAS_TYPES: list of physics::measurement types
    /// @param lhs: geometry::vector2<DIM, MEAS_TYPES...> as l-value reference
    /// @param rhs: scalar as l-value const reference
    /// @return geometry::vector2<DIM, MEAS_TYPES...>&
    template <std::size_t DIM, typename... MEAS_TYPES> 
        requires (physics::are_measurements_v<MEAS_TYPES...>)
    inline constexpr
    vector2<DIM, MEAS_TYPES...>& operator*=(vector2<DIM, MEAS_TYPES...>& lhs, 
                                            const scalar& rhs) noexcept {

        std::apply([&](auto&... lhs_components) { 

            ((lhs_components *= rhs), ...);

        }, lhs.data());

        return lhs;

    }


    /// @brief Divide a vector by a scalar
    /// @tparam DIM: size_t
    /// @tparam MEAS_TYPES: list of physics::measurement types
    /// @param lhs: geometry::vector2<DIM, MEAS_TYPES...> as l-value reference
    /// @param rhs: scalar as l-value const reference
    /// @return geometry::vector2<DIM, MEAS_TYPES...>&
    template <std::size_t DIM, typename... MEAS_TYPES> 
        requires (physics::are_measurements_v<MEAS_TYPES...>)
    inline constexpr
    vector2<DIM, MEAS_TYPES...>& operator/=(vector2<DIM, MEAS_TYPES...>& lhs, 
                                            const scalar& rhs) noexcept {

        std::apply([&](auto&... lhs_components) { 

            ((lhs_components /= rhs), ...);

        }, lhs.data());

        return lhs;

    }


    /// @brief Add two vectors
    /// @tparam DIM: size_t
    /// @tparam MEAS_TYPES: list of physics::measurement types
    /// @param lhs: geometry::vector2<DIM, MEAS_TYPES...> as l-value const reference
    /// @param rhs: geometry::vector2<DIM, MEAS_TYPES...> as l-value const reference
    /// @return geometry::vector2<DIM, MEAS_TYPES...>&
    template <std::size_t DIM, typename... MEAS_TYPES> 
        requires (physics::are_measurements_v<MEAS_TYPES...>)
    inline constexpr
    vector2<DIM, MEAS_TYPES...> operator+(const vector2<DIM, MEAS_TYPES...>& lhs, 
                                          const vector2<DIM, MEAS_TYPES...>& rhs) noexcept {

        vector2<DIM, MEAS_TYPES...> result(lhs);
        result += rhs;

        return result;
    
    }


    /// @brief Subtract two vectors
    /// @tparam DIM: size_t
    /// @tparam MEAS_TYPES: list of physics::measurement types
    /// @param lhs: geometry::vector2<DIM, MEAS_TYPES...> as l-value reference
    /// @param rhs: geometry::vector2<DIM, MEAS_TYPES...> as l-value const reference
    /// @return geometry::vector2<DIM, MEAS_TYPES...>&
    template <std::size_t DIM, typename... MEAS_TYPES> 
        requires (physics::are_measurements_v<MEAS_TYPES...>)
    inline constexpr
    vector2<DIM, MEAS_TYPES...> operator-(const vector2<DIM, MEAS_TYPES...>& lhs, 
                                          const vector2<DIM, MEAS_TYPES...>& rhs) noexcept {

        vector2<DIM, MEAS_TYPES...> result(lhs);
        result -= rhs;

        return result;
    
    }


    /// @brief Multiply a vector by a scalar
    /// @tparam DIM: size_t
    /// @tparam MEAS_TYPES: list of physics::measurement types
    /// @param lhs: geometry::vector2<DIM, MEAS_TYPES...> as l-value reference
    /// @param rhs: scalar as l-value const reference
    /// @return geometry::vector2<DIM, MEAS_TYPES...>&
    template <std::size_t DIM, typename... MEAS_TYPES> 
        requires (physics::are_measurements_v<MEAS_TYPES...>)
    inline constexpr
    vector2<DIM, MEAS_TYPES...> operator*(const vector2<DIM, MEAS_TYPES...>& lhs, 
                                          const scalar& rhs) noexcept {

        vector2<DIM, MEAS_TYPES...> result(lhs);
        result *= rhs;

        return result;
    
    }


    /// @brief Divide a vector by a scalar
    /// @tparam DIM: size_t
    /// @tparam MEAS_TYPES: list of physics::measurement types
    /// @param lhs: geometry::vector2<DIM, MEAS_TYPES...> as l-value reference
    /// @param rhs: scalar as l-value const reference
    /// @return geometry::vector2<DIM, MEAS_TYPES...>&
    template <std::size_t DIM, typename... MEAS_TYPES> 
        requires (physics::are_measurements_v<MEAS_TYPES...>)
    inline constexpr
    vector2<DIM, MEAS_TYPES...> operator/(const vector2<DIM, MEAS_TYPES...>& lhs, 
                                          const scalar& rhs) noexcept {

        vector2<DIM, MEAS_TYPES...> result(lhs);
        result /= rhs;

        return result;
    
    }


    /// @brief Multiply a scalar by a vector
    /// @tparam DIM: size_t
    /// @tparam MEAS_TYPES: list of physics::measurement types
    /// @param lhs: scalar as l-value const reference
    /// @param rhs: geometry::vector2<DIM, MEAS_TYPES...> as l-value reference
    /// @return geometry::vector2<DIM, MEAS_TYPES...>&
    template <std::size_t DIM, typename... MEAS_TYPES> 
        requires (physics::are_measurements_v<MEAS_TYPES...>)
    inline constexpr
    vector2<DIM, MEAS_TYPES...> operator*(const scalar& lhs, 
                                          const vector2<DIM, MEAS_TYPES...>& rhs) noexcept {

        return rhs * lhs;
    
    }


    // /// @brief Divide a scalar by a vector
    // /// @tparam DIM: size_t
    // /// @tparam MEAS_TYPES: list of physics::measurement types
    // /// @param lhs: scalar as l-value const reference
    // /// @param rhs: geometry::vector2<DIM, MEAS_TYPES...> as l-value reference
    // /// @return geometry::vector2<DIM, MEAS_TYPES...>&
    // template <std::size_t DIM, typename... MEAS_TYPES> 
    //     requires (physics::are_measurements_v<MEAS_TYPES...>)
    // inline constexpr
    

    // /// @brief Multiply a vector by a measurement
    // /// @tparam DIM: size_t
    // /// @tparam MEAS_TYPES: list of physics::measurement types
    // /// @tparam MEAS_TYPE: physics::measurement type
    // /// @param lhs: geometry::vector2<DIM, MEAS_TYPES...> as l-value reference
    // /// @param rhs: MEAS_TYPE as l-value const reference
    // /// @return geometry::vector2<DIM, MEAS_TYPES...>&
    // template <std::size_t DIM, typename... MEAS_TYPES, typename MEAS_TYPE> 
    //     requires (physics::are_measurements_v<MEAS_TYPES...> && physics::is_measurement_v<MEAS_TYPE>)
    // inline constexpr
    // vector2<DIM, physics::measurement_prod_t<MEAS_TYPES..., MEAS_TYPE>> operator*(const vector2<DIM, MEAS_TYPES...>& lhs, 
    //                                                                               const MEAS_TYPE& rhs) noexcept {

    //     vector2<DIM, physics::measurement_prod_t<MEAS_TYPES..., MEAS_TYPE>> result;
        
    //     [...]

    //     return lhs;

    // }


    /// @brief Add two vectors
    /// @tparam BASE: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param lhs: geometry::vector<BASE, DIM> as l-value reference
    /// @param rhs: geometry::vector<BASE, DIM> as l-value const reference
    /// @return constexpr geometry::vector<BASE, DIM>&
    template <typename BASE, size_t DIM> requires (physics::units::is_base_v<BASE>)
    constexpr vector<BASE, DIM>& operator+=(vector<BASE, DIM>& lhs, const vector<BASE, DIM>& rhs) noexcept {

        for (std::size_t i{}; i < DIM; ++i) 
            lhs[i] += rhs[i];

        return lhs;

    }


    /// @brief Subtract two vectors
    /// @tparam BASE: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param lhs: geometry::vector<BASE, DIM> as l-value reference
    /// @param rhs: geometry::vector<BASE, DIM> as l-value const reference
    /// @return constexpr geometry::vector<BASE, DIM>&
    template <typename BASE, size_t DIM> requires (physics::units::is_base_v<BASE>)
    constexpr vector<BASE, DIM>& operator-=(vector<BASE, DIM>& lhs, const vector<BASE, DIM>& rhs) noexcept {

        for (std::size_t i{}; i < DIM; ++i) 
            lhs[i] -= rhs[i];

        return lhs;

    }


    /// @brief Multiply a vector by a scalar
    /// @tparam BASE: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param lhs: geometry::vector<BASE, DIM> as l-value reference
    /// @param rhs: scalar as l-value const reference
    /// @return constexpr geometry::vector<BASE, DIM>&
    template <typename BASE, size_t DIM> requires (physics::units::is_base_v<BASE>)
    constexpr vector<BASE, DIM>& operator*=(vector<BASE, DIM>& lhs, const scalar& rhs) noexcept {

        for (std::size_t i{}; i < DIM; ++i) 
            lhs[i] *= rhs;

        return lhs;

    }


    /// @brief Divide a vector by a scalar
    /// @tparam BASE: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param lhs: geometry::vector<BASE, DIM> as l-value reference
    /// @param rhs: scalar as l-value const reference
    /// @return constexpr geometry::vector<BASE, DIM>&
    template <typename BASE, size_t DIM> requires (physics::units::is_base_v<BASE>)
    constexpr vector<BASE, DIM>& operator/=(vector<BASE, DIM>& lhs, const scalar& rhs) noexcept {

        if  (rhs == 0.0) 
            throw std::runtime_error("Cannot divide a vector by zero");

        for (std::size_t i{}; i < DIM; ++i) 
            lhs[i] /= rhs;

        return lhs;

    }


    /// @brief Add two vectors
    /// @tparam BASE: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param lhs: geometry::vector<BASE, DIM> as l-value const reference
    /// @param rhs: geometry::vector<BASE, DIM> as l-value const reference
    /// @return constexpr geometry::vector<BASE, DIM>&
    template <typename BASE, size_t DIM> requires (physics::units::is_base_v<BASE>)
    constexpr vector<BASE, DIM>& operator+(const vector<BASE, DIM>& lhs, const vector<BASE, DIM>& rhs) noexcept {

        vector<BASE, DIM> result(lhs);
        result += rhs;

        return result;

    }


    /// @brief Subtract two vectors
    /// @tparam BASE: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param lhs: geometry::vector<BASE, DIM> as l-value const reference
    /// @param rhs: geometry::vector<BASE, DIM> as l-value const reference
    /// @return constexpr geometry::vector<BASE, DIM>&
    template <typename BASE, size_t DIM> requires (physics::units::is_base_v<BASE>)
    constexpr vector<BASE, DIM>& operator-(const vector<BASE, DIM>& lhs, const vector<BASE, DIM>& rhs) noexcept {

        vector<BASE, DIM> result{lhs};
        result -= rhs;

        return result;

    }


    /// @brief Negate a vector
    /// @tparam BASE: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
    /// @return constexpr geometry::vector<BASE, DIM>&
    template <typename BASE, size_t DIM> requires (physics::units::is_base_v<BASE>)
    constexpr vector<BASE, DIM>& operator-(const vector<BASE, DIM>& vec) noexcept {

        vector<BASE, DIM> result;

        for (std::size_t i{}; i < DIM; ++i) 
            result[i] = -vec[i];

        return result;

    }


    /// @brief Multiply a vector by a scalar
    /// @tparam BASE: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param lhs: geometry::vector<BASE, DIM> as l-value const reference
    /// @param rhs: scalar as l-value const reference
    /// @return constexpr geometry::vector<BASE, DIM>&
    template <typename BASE, size_t DIM> requires (physics::units::is_base_v<BASE>)
    constexpr vector<BASE, DIM>& operator*(const vector<BASE, DIM>& lhs, const scalar& rhs) noexcept {

        vector<BASE, DIM> result{lhs};
        result *= rhs;

        return result;

    }


    /// @brief Multiply a vector by a scalar
    /// @tparam BASE: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param lhs: scalar as l-value const reference
    /// @param rhs: geometry::vector<BASE, DIM> as l-value const reference
    /// @return constexpr geometry::vector<BASE, DIM>&
    template <typename BASE, size_t DIM> requires (physics::units::is_base_v<BASE>)
    constexpr vector<BASE, DIM>& operator*(const scalar& lhs, const vector<BASE, DIM>& rhs) noexcept {

        vector<BASE, DIM> result{rhs};
        result *= lhs;

        return result;

    }


    /// @brief Divide a vector by a scalar
    /// @tparam BASE: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param lhs: geometry::vector<BASE, DIM> as l-value const reference
    /// @param rhs: scalar as l-value const reference
    /// @return constexpr geometry::vector<BASE, DIM>&
    template <typename BASE, size_t DIM> requires (physics::units::is_base_v<BASE>)
    constexpr vector<BASE, DIM>& operator/(const vector<BASE, DIM>& lhs, const scalar& rhs) noexcept {

        vector<BASE, DIM> result{lhs};
        result /= rhs;

        return result;

    }


    /// @brief Divide a scalar by a vector
    /// @tparam BASE: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param lhs: scalar as l-value const reference
    /// @param rhs: geometry::vector<BASE, DIM> as l-value const reference
    /// @return constexpr geometry::vector<physics::units::base_inv_t<BASE>, DIM>&
    template <typename BASE, size_t DIM> requires (physics::units::is_base_v<BASE>)
    constexpr vector<physics::units::base_inv_t<BASE>, DIM>& operator/(const scalar& lhs, const vector<BASE, DIM>& rhs) noexcept {

        vector<physics::units::base_inv_t<BASE>, DIM> result;

        for (std::size_t i{}; i < DIM; ++i) 
            result[i] = lhs / rhs[i];

        return result;

    }


    /// @brief Multiply a vector by a measurement
    /// @tparam BASE1: physics::units::unit_base
    /// @tparam BASE2: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param lhs: geometry::vector<BASE1, DIM> as l-value const reference
    /// @param rhs: physics::measurement<BASE2> as l-value const reference
    /// @return constexpr geometry::vector<physics::units::base_prod_t<BASE1, BASE2>, DIM>&
    template <typename BASE1, typename BASE2, size_t DIM> requires (physics::units::are_base_v<BASE1, BASE2>)
    constexpr vector<physics::units::base_prod_t<BASE1, BASE2>, DIM> operator*(const vector<BASE1, DIM>& lhs, const physics::measurement<BASE2>& rhs) noexcept {

        vector<physics::units::base_prod_t<BASE1, BASE2>, DIM> result;

        for (std::size_t i{}; i < DIM; ++i) 
            result[i] = lhs[i] * rhs;

        return result;

    }


    /// @brief Multiply a physics::measurement by a vector
    /// @tparam BASE1: physics::units::unit_base
    /// @tparam BASE2: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param lhs: physics::measurement<BASE1> as l-value const reference
    /// @param rhs: geometry::vector<BASE2, DIM> as l-value const reference
    /// @return constexpr geometry::vector<physics::units::base_prod_t<BASE1, BASE2>, DIM>&
    template <typename BASE1, typename BASE2, size_t DIM> requires (physics::units::are_base_v<BASE1, BASE2>)
    constexpr vector<physics::units::base_prod_t<BASE1, BASE2>, DIM> operator*(const physics::measurement<BASE1>& lhs, const vector<BASE2, DIM>& rhs) noexcept {

        vector<physics::units::base_prod_t<BASE1, BASE2>, DIM> result;

        for (std::size_t i{}; i < DIM; ++i) 
            result[i] = lhs * rhs[i];

        return result;

    }


    /// @brief Divide a vector by a physics::measurement
    /// @tparam BASE1: physics::units::unit_base
    /// @tparam BASE2: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param lhs: geometry::vector<BASE1, DIM> as l-value const reference
    /// @param rhs: physics::measurement<BASE2> as l-value const reference
    /// @return constexpr geometry::vector<physics::units::base_div_t<BASE1, BASE2>, DIM>&
    template <typename BASE1, typename BASE2, size_t DIM> requires (physics::units::are_base_v<BASE1, BASE2>)
    constexpr vector<physics::units::base_div_t<BASE1, BASE2>, DIM> operator/(const vector<BASE1, DIM>& lhs, const physics::measurement<BASE2>& rhs) noexcept {

        vector<physics::units::base_div_t<BASE1, BASE2>, DIM> result;

        for (std::size_t i{}; i < DIM; ++i) 
            result[i] = lhs[i] / rhs;

        return result;

    }


    /// @brief Divide a physics::measurement by a vector
    /// @tparam BASE1: physics::units::unit_base
    /// @tparam BASE2: physics::units::unit_base
    /// @tparam DIM: size_t
    /// @param lhs: physics::measurement<BASE1> as l-value const reference
    /// @param rhs: geometry::vector<BASE2, DIM> as l-value const reference
    /// @return constexpr geometry::vector<physics::units::base_div_t<BASE1, BASE2>, DIM>&
    template <typename BASE1, typename BASE2, size_t DIM> requires (physics::units::are_base_v<BASE1, BASE2>)
    constexpr vector<physics::units::base_div_t<BASE1, BASE2>, DIM> operator/(const physics::measurement<BASE1>& lhs, const vector<BASE2, DIM>& rhs) noexcept {

        vector<physics::units::base_div_t<BASE1, BASE2>, DIM> result;

        for (std::size_t i{}; i < DIM; ++i) 
            result[i] = lhs / rhs[i];

        return result;

    }


} // namespace scipp::geometry



namespace scipp::math {


    namespace op {


        using namespace physics; 
        using namespace geometry;


        /// @brief Invert a vector
        /// @tparam BASE: physics::units::unit_base
        /// @tparam DIM: size_t
        /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
        /// @return constexpr geometry::vector<units::base_inv_t<BASE>, DIM>
        template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        constexpr vector<units::base_inv_t<BASE>, DIM> invert(const vector<BASE, DIM>& vec) {

            vector<units::base_inv_t<BASE>, DIM> result;

            for (std::size_t i{}; i < DIM; ++i) 
                result[i] = op::invert(vec[i]);

            return result;

        }


        /// @brief Take the absolute value of a vector
        /// @tparam BASE: physics::units::unit_base
        /// @tparam DIM: size_t
        /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
        /// @return constexpr geometry::vector<units::base_inv_t<BASE>, DIM>
        template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        constexpr vector<units::base_inv_t<BASE>, DIM> abs(const vector<BASE, DIM>& vec) noexcept {

            vector<units::base_inv_t<BASE>, DIM> result;

            for (std::size_t i{}; i < DIM; ++i) 
                result[i] = op::abs(vec[i]);

            return result;

        }


        // /// @brief Take the power of a vector
        // /// @tparam BASE: physics::units::unit_base
        // /// @tparam DIM: size_t
        // /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
        // /// @param power: int as l-value const reference
        // /// @return constexpr geometry::vector<units::base_pow_t<BASE, power>, DIM>
        // template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        // constexpr auto pow(const vector<BASE, DIM>& vec, const int&  power) noexcept -> vector<units::base_pow_t<BASE, power>, DIM> {

        //     vector<units::base_pow_t<BASE, power>, DIM> result;

        //     for (std::size_t i{}; i < DIM; ++i) 
        //         result[i] = op::pow(vec[i], power);

        //     return result;

        // }


        /// @brief Take the square of a vector
        /// @tparam BASE: physics::units::unit_base
        /// @tparam DIM: size_t
        /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
        /// @return constexpr geometry::vector<units::base_pow_t<BASE, 2>, DIM>
        template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        constexpr vector<units::base_pow_t<BASE, 2>, DIM> square(const vector<BASE, DIM>& vec) noexcept {

            vector<units::base_pow_t<BASE, 2>, DIM> result;

            for (std::size_t i{}; i < DIM; ++i) 
                result[i] = op::square(vec[i]);

            return result;

        }


        /// @brief Take the cube of a vector
        /// @tparam BASE: physics::units::unit_base
        /// @tparam DIM: size_t
        /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
        /// @return constexpr geometry::vector<units::base_pow_t<BASE, 3>, DIM>
        template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        constexpr vector<units::base_pow_t<BASE, 3>, DIM> cube(const vector<BASE, DIM>& vec) noexcept {

            vector<units::base_pow_t<BASE, 3>, DIM> result;

            for (std::size_t i{}; i < DIM; ++i) 
                result[i] = op::cube(vec[i]);

            return result;

        }


        /// @brief Take the square root of a vector
        /// @tparam BASE: physics::units::unit_base
        /// @tparam DIM: size_t
        /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
        /// @return constexpr geometry::vector<units::base_root_t<BASE, 2>, DIM>
        template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        constexpr vector<units::base_root_t<BASE, 2>, DIM> sqrt(const vector<BASE, DIM>& vec) {

            vector<units::base_root_t<BASE, 2>, DIM> result;

            for (std::size_t i{}; i < DIM; ++i) 
                result[i] = op::sqrt(vec[i]);

            return result;

        }


        /// @brief Take the cube root of a vector
        /// @tparam BASE: physics::units::unit_base
        /// @tparam DIM: size_t
        /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
        /// @return constexpr geometry::vector<units::base_root_t<BASE, 3>, DIM>
        template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        constexpr vector<units::base_root_t<BASE, 3>, DIM> cbrt(const vector<BASE, DIM>& vec) noexcept {

            vector<units::base_root_t<BASE, 3>, DIM> result;

            for (std::size_t i{}; i < DIM; ++i) 
                result[i] = op::cbrt(vec[i]);

            return result;

        }


        /**
         * @brief Compute the dot product between two vectors
         * 
         * @tparam BASE1: physics::units::unit_base
         * @tparam BASE2: physics::units::unit_base
         * @tparam DIM: size_t
         * 
         * @param v1: geometry::vector<BASE1, DIM> as l-value const reference
         * @param v2: geometry::vector<BASE2, DIM> as l-value const reference
         * @param dot_function: std::function<measurement<units::base_prod_t<BASE1, BASE2>>(const vector<BASE1, DIM>&, const vector<BASE2, DIM>&)> 
         * 
         * @note 
         *  The dot_function is a function that takes two vectors as input and returns a measurement<units::base_prod_t<BASE1, BASE2>>.
         *  The default dot_function is the standard dot product.
         * 
         * @return constexpr measurement<BASE1 * BASE2>
         */
        template <typename BASE1, typename BASE2, size_t DIM> requires (units::are_base_v<BASE1, BASE2>)
        inline constexpr measurement<units::base_prod_t<BASE1, BASE2>> dot(const vector<BASE1, DIM>& v1, 
                                                                           const vector<BASE2, DIM>& v2, 
                                                                           const std::function<measurement<units::base_prod_t<BASE1, BASE2>>(const vector<BASE1, DIM>&, const vector<BASE2, DIM>&)>& 
                                                                        
                                                                             dot_function = [](const vector<BASE1, DIM>& v1, const vector<BASE2, DIM>& v2) { 

                                                                                 measurement<units::base_prod_t<BASE1, BASE2>> result;
                                                                                 for (std::size_t i{0}; i < DIM; ++i) 
                                                                                     result += v1[i] * v2[i]; 

                                                                                 return result; 

                                                                             }

                                                                          ) noexcept {

            return dot_function(v1, v2);
        
        }


        /// @brief Compute the cross product between two vectors
        /// @tparam BASE1: physics::units::unit_base
        /// @tparam BASE2: physics::units::unit_base
        /// @tparam DIM: size_t
        /// @param v1: geometry::vector<BASE1, DIM> as l-value const reference
        /// @param v2: geometry::vector<BASE2, DIM> as l-value const reference
        /// @return constexpr geometry::vector<units::base_prod_t<BASE1, BASE2>, DIM>
        template <typename BASE1, typename BASE2, size_t DIM> requires (units::are_base_v<BASE1, BASE2>)
        constexpr vector<units::base_prod_t<BASE1, BASE2>, DIM> cross(const vector<BASE1, DIM>& v1, const vector<BASE2, DIM>& v2) noexcept {

            std::array<measurement<units::base_prod_t<BASE1, BASE2>>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i) 
                result[i] = v1[(i + 1) % DIM] * v2[(i + 2) % DIM] - v1[(i + 2) % DIM] * v2[(i + 1) % DIM]; 

            return result;
    
        }


        /// @brief Get the magnitude of the vector
        /// @brief Normalize a geometry::vector
        /// @tparam BASE: physics::units::unit_base
        /// @tparam DIM: size_t
        /// @param vec: geometry::vector<BASE, DIM> as l-value const reference
        /// @return measurement<BASE>
        template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        inline constexpr measurement<BASE> norm(const vector<BASE, DIM>& vec) noexcept {

            return op::sqrt(op::dot(vec, vec));

        }


        /// @brief Normalize a geometry::vector
        /// @tparam BASE: physics::units::unit_base
        /// @tparam DIM: size_t
        /// @return constexpr geometry::vector<units::unitless> 
        template <typename BASE, size_t DIM> requires (units::is_base_v<BASE>)
        inline constexpr vector<units::unitless, DIM> normalize(const vector<BASE, DIM>& vec) noexcept {

            return vec / op::norm(vec);

        }


        /// @brief Compute the angle between two vectors
        /// @tparam BASE1: physics::units::unit_base
        /// @tparam BASE2: physics::units::unit_base
        /// @tparam DIM: size_t
        /// @param v1: geometry::vector<BASE1, DIM> as l-value const reference
        /// @param v2: geometry::vector<BASE2, DIM> as l-value const reference
        /// @return constexpr angle_m
        template <typename BASE1, typename BASE2, size_t DIM> requires (units::are_base_v<BASE1, BASE2>)
        inline constexpr angle_m angle(const vector<BASE1, DIM>& v1, const vector<BASE2, DIM>& v2) noexcept {

            return op::acos(op::dot(v1, v2) / (op::norm(v1) * op::norm(v2)));

        }


    }


} // namespace scipp::math


    // /**
    //  * @brief Take the power of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as l-value const reference
    //  * @param power: int
    //  *  
    //  * @return constexpr geometry::vector<op::pow(UB, power), DIM>
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr auto pow(const geometry::vector<UB, DIM>& other, const int& power) noexcept {

    //     std::array<measurement<op::pow(UB, power)>, DIM> result;
    //     for (std::size_t i{}; i < DIM; ++i)
    //         result[i] = op::pow(other[i], power);
        
    //     return result;

    // }


    // /**
    //  * @brief Take the power of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as r-value reference
    //  * @param power: int
    //  *  
    //  * @return constexpr geometry::vector<op::pow(UB, power), DIM>
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr auto pow(geometry::vector<UB, DIM>&& other, const int& power) noexcept {

    //     std::array<measurement<op::pow(UB, power)>, DIM> result;
    //     for (std::size_t i{}; i < DIM; ++i)
    //         result[i] = op::pow(other[i], power);
        
    //     return result;

    // }


    // /**
    //  * @brief Take the square power of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as l-value const reference
    //  *  
    //  * @return constexpr geometry::vector<op::square(UB), DIM>
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr geometry::vector<op::square(UB), DIM> square(const geometry::vector<UB, DIM>& other) noexcept {

    //     std::array<measurement<op::square(UB)>, DIM> result;
    //     for (std::size_t i{}; i < DIM; ++i)
    //         result[i] = op::square(other[i]);
        
    //     return result;

    // }


    // /**
    //  * @brief Take the square power of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as r-value reference
    //  *  
    //  * @return constexpr geometry::vector<op::square(UB), DIM>
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr geometry::vector<op::square(UB), DIM> square(geometry::vector<UB, DIM>&& other) noexcept {

    //     std::array<measurement<op::square(UB)>, DIM> result;
    //     for (std::size_t i{}; i < DIM; ++i)
    //         result[i] = op::square(other[i]);
        
    //     return result;

    // }


    // /**
    //  * @brief Take the cube power of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as l-value const reference
    //  *  
    //  * @return constexpr geometry::vector<op::cube(UB), DIM>
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr geometry::vector<op::cube(UB), DIM> cube(const geometry::vector<UB, DIM>& other) noexcept {

    //     std::array<measurement<op::cube(UB)>, DIM> result;
    //     for (std::size_t i{}; i < DIM; ++i)
    //         result[i] = op::cube(other[i]);
        
    //     return result;

    // }


    // /**
    //  * @brief Take the cube power of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as r-value reference
    //  *  
    //  * @return constexpr geometry::vector<op::cube(UB), DIM>
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr geometry::vector<op::cube(UB), DIM> cube(geometry::vector<UB, DIM>&& other) noexcept {

    //     std::array<measurement<op::cube(UB)>, DIM> result;
    //     for (std::size_t i{}; i < DIM; ++i)
    //         result[i] = op::cube(other[i]);
        
    //     return result;

    // }


    // /**
    //  * @brief Take the root of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as l-value const reference
    //  * @param power: int
    //  * 
    //  * @return constexpr geometry::vector<op::root(UB, power), DIM>
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr auto root(const geometry::vector<UB, DIM>& other, const int& power) {

    //     std::array<measurement<op::root(UB, power)>, DIM> result;
    //     for (std::size_t i{}; i < DIM; ++i)
    //         result[i] = op::root(other[i], power);
        
    //     return result;

    // }


    // /**
    //  * @brief Take the root of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as r-value reference
    //  * @param power: int
    //  * 
    //  * @return constexpr geometry::vector<op::root(UB, power), DIM>
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr auto root(geometry::vector<UB, DIM>&& other, const int& power) {

    //     std::array<measurement<op::root(UB, power)>, DIM> result;
    //     for (std::size_t i{}; i < DIM; ++i)
    //         result[i] = op::root(other[i], power);
        
    //     return result;

    // }


    // /**
    //  * @brief Take the square root of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as l-value const reference
    //  *  
    //  * @return constexpr geometry::vector<op::sqrt(UB), DIM>
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr geometry::vector<op::sqrt(UB), DIM> sqrt(const geometry::vector<UB, DIM>& other) noexcept {

    //     std::array<measurement<op::sqrt(UB)>, DIM> result;
    //     for (std::size_t i{}; i < DIM; ++i)
    //         result[i] = op::sqrt(other[i]);
        
    //     return result;

    // }


    // /**
    //  * @brief Take the square root of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as r-value reference
    //  *  
    //  * @return constexpr geometry::vector<op::sqrt(UB), DIM>
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr geometry::vector<op::sqrt(UB), DIM> sqrt(geometry::vector<UB, DIM>&& other) noexcept {

    //     std::array<measurement<op::sqrt(UB)>, DIM> result;
    //     for (std::size_t i{}; i < DIM; ++i)
    //         result[i] = op::sqrt(other[i]);
        
    //     return result;

    // }


    // /**
    //  * @brief Take the cubic root of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as l-value const reference
    //  *  
    //  * @return constexpr geometry::vector<op::cbrt(UB), DIM>
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr geometry::vector<op::cbrt(UB), DIM> cbrt(const geometry::vector<UB, DIM>& other) noexcept {

    //     std::array<measurement<op::cbrt(UB)>, DIM> result;
    //     for (std::size_t i{}; i < DIM; ++i)
    //         result[i] = op::cbrt(other[i]);
        
    //     return result;

    // }


    // /**
    //  * @brief Take the cubic root of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as r-value reference
    //  *  
    //  * @return constexpr geometry::vector<op::cbrt(UB), DIM>
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr geometry::vector<op::cbrt(UB), DIM> cbrt(geometry::vector<UB, DIM>&& other) noexcept {

    //     std::array<measurement<op::cbrt(UB)>, DIM> result;
    //     for (std::size_t i{}; i < DIM; ++i)
    //         result[i] = op::cbrt(other[i]);
        
    //     return result;

    // }


    // /**
    //  * @brief Get the norm of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as l-value const reference
    //  *
    //  * @return constexpr measurement 
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr measurement<UB> norm(const geometry::vector<UB, DIM>& other) noexcept { 

    //     if constexpr (DIM == 1) 
    //         return other[0];

    //     geometry::vector<op::square(UB), DIM> squared = op::square(other);

    //     return op::sqrt(std::accumulate(squared.data().begin(), squared.data().end(), measurement<op::square(UB)>()));

    // }


    // /**
    //  * @brief Get the norm of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as r-value reference
    //  *
    //  * @return constexpr measurement 
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr measurement<UB> norm(geometry::vector<UB, DIM>&& other) noexcept { 

    //     if constexpr (DIM == 1) 
    //         return other[0];

    //     geometry::vector<op::square(UB), DIM> squared = op::square(other);

    //     return op::sqrt(std::accumulate(squared.data().begin(), squared.data().end(), measurement<op::square(UB)>()));

    // }


    // /**
    //  * @brief Get the norm squared of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as l-value const reference
    //  *
    //  * @return constexpr measurement 
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr measurement<op::square(UB)> norm2(const geometry::vector<UB, DIM>& other) noexcept { 

    //     if constexpr (DIM == 1) 
    //         return other[0];

    //     geometry::vector<op::square(UB), DIM> squared = op::square(other);

    //     return std::accumulate(squared.data().begin(), squared.data().end(), measurement<op::square(UB)>());

    // }


    // /**
    //  * @brief Get the norm squared of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as r-value reference
    //  *
    //  * @return constexpr measurement 
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr measurement<op::square(UB)> norm2(geometry::vector<UB, DIM>&& other) noexcept { 

    //     if constexpr (DIM == 1) 
    //         return other[0];

    //     geometry::vector<op::square(UB), DIM> squared = op::square(other);

    //     return std::accumulate(squared.data().begin(), squared.data().end(), measurement<op::square(UB)>());

    // }


    // /**
    //  * @brief Compute the cross product between two geometry::vectors
    //  * 
    //  * @param v1: geometry::vector<UB1, DIM> as l-value const reference
    //  * @param v2: geometry::vector<UB2, DIM> as l-value const reference
    //  * 
    //  * @return constexpr geometry::vector<UB1 * UB2, DIM>
    //  */
    // template <unit_base UB1, unit_base UB2, std::size_t DIM>
    // constexpr geometry::vector<UB1 * UB2, DIM> cross(const geometry::vector<UB1, DIM>& v1, 
    //                                                     const geometry::vector<UB2, DIM>& v2) {

    //     std::array<measurement<UB1 * UB2>, DIM> result;
    //     for (std::size_t i{}; i < DIM; ++i) 
    //         result[i] = v1[(i + 1) % v1.size()] * v2[(i + 2) % v1.size()] - v1[(i + 2) % v1.size()] * v2[(i + 1) % v1.size()]; 

    //     return result;
    
    // }

    
    // /**
    //  * @brief Compute the cross product between two geometry::vectors
    //  * 
    //  * @param v1: geometry::vector<UB1, DIM> as r-value reference
    //  * @param v2: geometry::vector<UB2, DIM> as r-value reference
    //  * 
    //  * @return constexpr geometry::vector<UB1 * UB2, DIM>
    //  */
    // template <unit_base UB1, unit_base UB2, std::size_t DIM>
    // constexpr geometry::vector<UB1 * UB2, DIM> cross(geometry::vector<UB1, DIM>&& v1, 
    //                                                     geometry::vector<UB2, DIM>&& v2) {

    //     std::array<measurement<UB1 * UB2>, DIM> result;
    //     for (std::size_t i{}; i < DIM; ++i) 
    //         result[i] = v1[(i + 1) % v1.size()] * v2[(i + 2) % v1.size()] - v1[(i + 2) % v1.size()] * v2[(i + 1) % v1.size()]; 

    //     return result;
    
    // }





    // /**
    //  * @brief Get the normalization of the geometry::vector
    //  *
    //  * @param other: geometry::vector<UB, DIM> as l-value const reference
    //  *
    //  * @return constexpr geometry::vector 
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr geometry::vector<basis::scalar, DIM> normalize(const geometry::vector<UB, DIM>& other) {

    //     return other / op::norm(other); 

    // } 


    // /**
    //  * @brief Get the normalization of the geometry::vector
    //  * 
    //  * @param other: geometry::vector<UB, DIM> as r-value reference
    //  *
    //  * @return constexpr geometry::vector 
    //  */
    // template <unit_base UB, std::size_t DIM>
    // constexpr geometry::vector<basis::scalar, DIM> normalize(geometry::vector<UB, DIM>&& other) {

    //     return other / op::norm(other); 

    // }     
    






            // /**
            //  * @brief Return the opposite of the current vector
            //  * 
            //  * @return constexpr vector 
            //  */
            // constexpr vector operator-() const noexcept {

            //     std::array<value_type, DIM> result; 
            //     for (std::size_t i{}; i < DIM; ++i)
            //         result[i] = -data_[i]; 
                
            //     return result;

            // }


            // /**
            //  * @brief Sum the current vector and another vector
            //  * 
            //  * @param other: vector to add as l-value const reference
            //  * 
            //  * @return constexpr vector 
            //  * 
            //  * @note: the two vectors must have the same unit of measurement and the same size
            //  */
            // constexpr vector operator+(const vector& other) const {

            //     std::array<value_type, DIM> result; 
            //     for (std::size_t i{}; i < DIM; ++i)
            //         result[i] = this->data_[i] + other.data_[i]; 
                
            //     return result;

            // }


            // /**
            //  * @brief Subtract the current vector and another vector
            //  * 
            //  * @param other: vector to subtract as l-value const reference
            //  * 
            //  * @return constexpr vector 
            //  * 
            //  * @note: the two vectors must have the same unit of measurement and the same size
            //  */
            // constexpr vector operator-(const vector& other) const {

            //     std::array<value_type, DIM> result; 
            //     for (std::size_t i{}; i < DIM; ++i)
            //         result[i] = this->data_[i] - other.data_[i]; 
                
            //     return result;

            // }




   