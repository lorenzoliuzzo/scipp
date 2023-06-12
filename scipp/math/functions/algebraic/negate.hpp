/**
 * @file    math/functions/algebraic/negate.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * 
 * @date    2023-06-12
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        template <typename T>
            requires (is_number_v<T>)
        struct negate<T> {

            using function_t = unary_function<T, T>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) noexcept {

                return -x;

            }

        };


        template <typename T>
            requires (physics::is_measurement_v<T>)
        struct negate<T> {

            using function_t = unary_function<T, T>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) noexcept {

                return -x.value;

            }

        };


        template <typename T>
            requires (physics::is_umeasurement_v<T>)
        struct negate<T> {

            using function_t = unary_function<T, T>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) noexcept {

                return { -x.value, x.uncertainty };

            }

        };


        // Specialization for complex/dual numbers
        template <typename T>
            requires (is_complex_v<T> || is_dual_v<T>)
        struct negate<T> {

            using function_t = unary_function<T, T>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) noexcept {

                return {-x.real, -x.imag};
            
            }

        };

        // Specialization for vectors
        template <typename T>
            requires (geometry::is_vector_v<T>)
        struct negate<T> {

            using function_t = unary_function<T, T>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) noexcept {

                typename function_t::result_t result;
                std::transform(x.data.begin(), x.data.end(), result.data.begin(), 
                    [](const auto& val) { return op::neg(val); }
                );
                return result;

            }

        };

        // Specialization for matrices
        template <typename T>
            requires (geometry::is_matrix_v<T>)
        struct negate<T> {

            using function_t = unary_function<T, T>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) noexcept {

                typename function_t::result_t result;
                std::transform(x.data.begin(), x.data.end(), result.data.begin(), 
                    [](const auto& val) { return op::neg(val); }
                );
                return result;

            }

        };


    } // namespace functions


} // namespace scipp::math