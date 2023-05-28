/**
 * @file    math/functions/logarithm.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        /// @brief Logarithm of a number
        template <typename T>
            requires (is_number_v<T>)
        struct logarithm<T> {

            using function_t = unary_function<T, T>;                                           

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {
                    
                if (x <= 0.0) 
                    throw std::invalid_argument("logarithm of a negative number is not defined");

                return std::log(x);

            }       

        };


        /// @brief Logarithm of a measurement
        template <typename MEAS_TYPE>
            requires (physics::is_scalar_measurement_v<MEAS_TYPE>)
        struct logarithm<MEAS_TYPE> {
            
            using function_t = unary_function<MEAS_TYPE, MEAS_TYPE>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                if (x <= 0.0) 
                    throw std::invalid_argument("logarithm of a negative number is not defined");

                return std::log(x.value);

            }       

        };


        /// @brief Logarithm of a umeasurement
        template <typename UMEAS_TYPE>
            requires (physics::is_scalar_umeasurement_v<UMEAS_TYPE>)
        struct logarithm<UMEAS_TYPE> {
            
            using function_t = unary_function<UMEAS_TYPE, UMEAS_TYPE>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                if (x.value <= 0.0) 
                    throw std::invalid_argument("logarithm of a negative number is not defined");

                return { std::log(x.value), x.uncertainty / x.value };

            }       

        };


        /// @brief Logarithm of a cmeasurement
        template <typename CMEAS_TYPE>
            requires (physics::is_scalar_cmeasurement_v<CMEAS_TYPE>)
        struct logarithm<CMEAS_TYPE> {
            
            using function_t = unary_function<CMEAS_TYPE, CMEAS_TYPE>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                return { op::log(op::abs(x)), x.arg() };

            }

        };


        /// @brief Logarithm of a vector
        template <typename VECTOR_TYPE>
            requires (geometry::is_scalar_vector_v<VECTOR_TYPE>)
        struct logarithm<VECTOR_TYPE> {
            
            using function_t = unary_function<VECTOR_TYPE, VECTOR_TYPE>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                typename function_t::result_t x_exp;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), x_exp.data.begin(), [](const auto& x_i) { return op::log(x_i); });
                return x_exp;

            }

        };


    } // namespace functions


} // namespace scipp::math