/**
 * @file    math/functions/round.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        /// @brief Get the round of a number
        template <typename T>
            requires (is_number_v<T>)
        struct round<T> {


            using result_t = T;                                             


            inline static constexpr result_t f(const T& x) {
                    
                return std::round(x);

            }       


        };


        /// @brief Get the round of a measurement
        template <typename T>
            requires (physics::is_measurement_v<T>)
        struct round<T> {


            using result_t = T;                                             


            inline static constexpr result_t f(const T& x) {
                    
                return std::round(x.value);

            }       


        };


    } // namespace functions


} // namespace scipp::math