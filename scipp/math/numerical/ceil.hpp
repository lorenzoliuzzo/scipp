/**
 * @file    math/numerical/ceil.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        /// @brief Get the ceil of a number
        template <typename T>
            requires is_number_v<T>
        struct ceil_impl<T> {

            static constexpr T f(const T& x) {
                    
                return std::ceil(x);

            }       

        };


        /// @brief Get the ceil of a measurement
        template <typename T>
            requires physics::is_measurement_v<T>
        struct ceil_impl<T> {

            static constexpr T f(const T& x) {
                    
                return std::ceil(x.value);

            }       

        };


    } // namespace op


} // namespace scipp::math