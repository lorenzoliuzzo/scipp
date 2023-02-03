/**
 * @file    measurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::physics {


    /// @brief Multiply two measurements
    template <typename MEAS1, typename MEAS2, typename = std::enable_if_t<is_measurement_v<MEAS1> && is_measurement_v<MEAS2>>>
    inline constexpr auto operator*(const MEAS1& meas1, const MEAS2& meas2) noexcept -> measurement<units::base_prod_t<typename MEAS1::base, typename MEAS2::base>> { 
        
        return measurement<units::base_prod_t<typename MEAS1::base, typename MEAS2::base>>(meas1.value * meas2.value); 
        
    }


    /// @brief Divide two measurements
    template <typename MEAS1, typename MEAS2, typename = std::enable_if_t<is_measurement_v<MEAS1> && is_measurement_v<MEAS2>>>
    inline constexpr auto operator/(const MEAS1& meas1, const MEAS2& meas2) noexcept -> measurement<units::base_div_t<typename MEAS1::base, typename MEAS2::base>> { 
        
        return measurement<units::base_div_t<typename MEAS1::base, typename MEAS2::base>>(meas1.value / meas2.value); 
        
    }
   

    template <typename MEAS, typename = std::enable_if_t<is_measurement_v<MEAS>>>
    inline constexpr auto operator*(const MEAS& meas, const scalar& val) noexcept -> MEAS {

        return MEAS(meas.value * val); 

    }


    template <typename MEAS, typename = std::enable_if_t<is_measurement_v<MEAS>>>
    inline constexpr auto operator*(const scalar& val, const MEAS& meas) noexcept -> MEAS {

        return MEAS(val * meas.value); 
        
    }


    template <typename MEAS, typename = std::enable_if_t<is_measurement_v<MEAS>>>
    inline constexpr auto operator/(const MEAS& meas, const scalar& val) noexcept -> MEAS {

        return MEAS(meas.value / val); 

    }


    // template <typename MEAS, typename = std::enable_if_t<is_measurement_v<MEAS>>>
    // inline constexpr auto operator/(const scalar& val, const MEAS& meas) noexcept ->  {

    //     return MEAS(val / meas.value); 
        
    // }


} // namespace scipp::physics


namespace scipp::math {
    
    
    namespace op {


        /// @brief Get the absolute of a measurement
        template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS>>>
        inline constexpr auto abs(const MEAS& meas) noexcept -> MEAS { 
            
            return (meas.value < 0.0) ? -meas : meas; 
        
        }
    

        /// @brief Get the sine of an angle_measurement
        template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::radian, typename MEAS::base>>>
        inline constexpr auto sin(const MEAS& meas) noexcept -> physics::measurement<physics::units::unitless> { 
                        
            return physics::measurement<physics::units::unitless>(std::sin(meas.value));
        
        }


    } // namespace op


} // namespace scipp::math