/**
 * @file    physics/measurements/scalars.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains operators between scalars and measurements
 * @date    2023-04-26
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {



    
    /// @brief Divide a double with an unit to get a measurement
    template <typename NUMBER_TYPE, typename UNIT_TYPE> 
        requires (math::is_number_v<NUMBER_TYPE> && is_unit_v<UNIT_TYPE>)
    inline constexpr auto operator/(const NUMBER_TYPE& val, const UNIT_TYPE&) noexcept
        -> measurement<math::meta::invert_t<typename UNIT_TYPE::base_t>> { 
        
        return static_cast<double>(val) / UNIT_TYPE::mult; 
        
    }

    /// @brief Divide a double with an unit to get a measurement
    template <typename NUMBER_TYPE, typename UNIT_TYPE> 
        requires (math::is_number_v<NUMBER_TYPE> && is_unit_v<UNIT_TYPE>)
    inline constexpr auto operator/(NUMBER_TYPE&& val, const UNIT_TYPE&) noexcept
        -> measurement<math::meta::invert_t<typename UNIT_TYPE::base_t>> { 
        
        return std::move(static_cast<double>(val)) / UNIT_TYPE::mult; 
        
    }


    template <typename NUMBER_TYPE, typename MEAS_TYPE>
        requires (math::is_number_v<NUMBER_TYPE> && is_generic_measurement_v<MEAS_TYPE>)
    inline static constexpr MEAS_TYPE operator*(const NUMBER_TYPE& scalar, const MEAS_TYPE& meas) {

        return meas * static_cast<double>(scalar);

    }


    template <typename NUMBER_TYPE, typename MEAS_TYPE>
        requires (math::is_number_v<NUMBER_TYPE> && is_generic_measurement_v<MEAS_TYPE>)
    inline static constexpr MEAS_TYPE operator*(NUMBER_TYPE&& scalar, MEAS_TYPE&& meas) {

        return std::move(meas) * std::move(static_cast<double>(scalar));
        
    }


    template <typename NUMBER_TYPE, typename MEAS_TYPE>
        requires (math::is_number_v<NUMBER_TYPE> && is_generic_measurement_v<MEAS_TYPE>)
    inline static constexpr math::meta::invert_t<MEAS_TYPE> operator/(const NUMBER_TYPE& scalar, const MEAS_TYPE& meas) {

        return math::op::inv(meas) * static_cast<double>(scalar);

    }


    template <typename NUMBER_TYPE, typename MEAS_TYPE>
        requires (math::is_number_v<NUMBER_TYPE> && is_generic_measurement_v<MEAS_TYPE>)
    inline static constexpr math::meta::invert_t<MEAS_TYPE> operator/(NUMBER_TYPE&& scalar, MEAS_TYPE&& meas) {

        return math::op::inv(std::move(meas)) * std::move(static_cast<double>(scalar));
        
    }


} // namespace scipp::physics