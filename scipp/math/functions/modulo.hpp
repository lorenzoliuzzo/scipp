/**
 * @file    math/functions/modulo.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-20
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {



        /// @brief Get the modulo of a number or a measurement
        template <typename T>
            requires (is_number_v<T> || physics::is_measurement_v<T> || physics::is_umeasurement_v<T>)
        struct modulo<T> {

            using function_t = unary_function<T, T>;                                          

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {
                    
                return (x < T{}) ? -x : x;

            }       

        };


        /// @brief Get the modulo of a cmeasurement
        template <typename CMEAS_TYPE>
            requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
        struct modulo<CMEAS_TYPE> {

            using function_t = unary_function<CMEAS_TYPE, typename CMEAS_TYPE::measurement_t>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                return op::sqrt(op::sq(x.real) + op::sq(x.imag));

            }

        };


        /// @brief Get the modulo of a vector
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        struct modulo<VECTOR_TYPE> : unary_function<VECTOR_TYPE, geometry::vector<modulo_t<typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>> {


            using result_t = geometry::vector<modulo_t<typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>; 


            inline static constexpr result_t f(const VECTOR_TYPE& x) {

                result_t x_abs;
                std::transform(x.data.begin(), x.data.end(), x_abs.data.begin(), [](const auto& x_i) { return op::abs(x_i); });
                return x_abs;

            }

        
        };


    } // namespace functions


} // namespace scipp::math