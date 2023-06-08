/**
 * @file    math/functions/exponential.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        /// @brief Exponential of a number
        template <typename T>
            requires (is_number_v<T>)
        struct exponential<T> {

            using function_t = unary_function<T, T>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) noexcept {
                    
                return std::exp(x);

            }       

        };


        /// @brief Exponential of a measurement
        template <typename MEAS_TYPE>
            requires (physics::is_scalar_measurement_v<MEAS_TYPE>)
        struct exponential<MEAS_TYPE> {
            
            using function_t = unary_function<MEAS_TYPE, MEAS_TYPE>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) noexcept {

                return std::exp(x.value);

            }       

        };


        /// @brief Exponential of a umeasurement
        template <typename UMEAS_TYPE>
            requires (physics::is_scalar_umeasurement_v<UMEAS_TYPE>)
        struct exponential<UMEAS_TYPE> {
            
            using function_t = unary_function<UMEAS_TYPE, UMEAS_TYPE>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) noexcept {

                constexpr auto exp = std::exp(x.value); 
                return {exp, exp * x.uncertainty};

            }       

        };


        /// @brief Exponential of a complex
        template <typename CMEAS_TYPE>
            requires (physics::is_scalar_complex_v<CMEAS_TYPE>)
        struct exponential<CMEAS_TYPE> {
            
            using function_t = unary_function<CMEAS_TYPE, CMEAS_TYPE>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) noexcept {

                return typename function_t::result_t::polar(std::exp(x.real), x.imag);

            }

        };


        /// @brief Exponential of a vector
        template <typename VECTOR_TYPE>
            requires (geometry::is_scalar_vector_v<VECTOR_TYPE>)
        struct exponential<VECTOR_TYPE> {
            
            using function_t = unary_function<VECTOR_TYPE, VECTOR_TYPE>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) noexcept {

                typename function_t::result_t x_exp;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), x_exp.data.begin(), [](const auto& x_i) { return op::exp(x_i); });
                return x_exp;

            }
        
        };


    } // namespace functions


} // namespace scipp::math