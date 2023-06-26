/**
 * @file    math/operations/algebraic/negate.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * 
 * @date    2023-06-12
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
            requires is_number_v<T>
        struct negate_impl<T> {

            inline static constexpr T f(const T& x) noexcept {

                return -x;

            }

        };


        template <typename T>
            requires physics::is_measurement_v<T>
        struct negate_impl<T> {

            inline static constexpr T f(const T& x) noexcept {

                return -x.value;

            }

        };


        template <typename T>
            requires physics::is_umeasurement_v<T>
        struct negate_impl<T> {

            inline static constexpr T f(const T& x) noexcept {

                return { -x.value, x.uncertainty };

            }

        };


        // Specialization for complex/dual numbers
        template <typename T>
            requires is_complex_v<T> || is_dual_v<T>
        struct negate_impl<T> {

            inline static constexpr T f(const T& x) noexcept {

                return {-x.real, -x.imag};
            
            }

        };

        // Specialization for vectors
        template <typename T>
            requires geometry::is_vector_v<T>
        struct negate_impl<T> {

            inline static constexpr T f(const T& x) noexcept {

                T result;
                std::transform(x.data.begin(), x.data.end(), result.data.begin(), 
                    [](const auto& val) { 
                        return op::negate(val); 
                    }
                );
                return result;

            }

        };

        // Specialization for matrices
        template <typename T>
            requires geometry::is_matrix_v<T>
        struct negate_impl<T> {

            inline static constexpr T f(const T& x) noexcept {

                T result;
                std::transform(x.data.begin(), x.data.end(), result.data.begin(), 
                    [](const auto& val) { 
                        return op::negate(val); 
                    }
                );
                return result;

            }

        };


        /// @brief Negate specialization for expr_ptr
        /// @tparam T
        template <typename T>
        struct negate_impl<calculus::expr_ptr<T>> {

            using result_t = calculus::expr_ptr<T>;
            
            inline static constexpr result_t f(const calculus::expr_ptr<T>& x) noexcept {
                
                return std::make_shared<calculus::neg_expr<T>>(-x->val, x);

            }
                    
        };

        template <typename T>
        struct negate_impl<calculus::variable<T>> {

            using result_t = calculus::expr_ptr<T>;

            inline static constexpr result_t f(const calculus::variable<T>& x) noexcept {

                return -x.expr;

            }

        };


    } // namespace op


} // namespace scipp::math