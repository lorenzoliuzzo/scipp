/**
 * @file    scipp/math/algebraic/negate.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-07-14
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
        struct negate_impl<calculus::expr_ptr<T>> {
            
            static constexpr calculus::expr_ptr<T> f(const calculus::expr_ptr<T>& x) noexcept {
                
                return std::make_shared<calculus::negate_expr<T>>(-x->val, x);

            }
                    
        };

        template <typename T>
        struct negate_impl<calculus::variable<T>> {

            static constexpr calculus::expr_ptr<T> f(const calculus::variable<T>& x) noexcept {

                return -x.expr;

            }

        };


        template <typename T>
            requires is_number_v<T>
        struct negate_impl<T> {

            static constexpr T f(const T& x) noexcept {

                return -x;

            }

        };


        template <typename T>
            requires physics::is_measurement_v<T>
        struct negate_impl<T> {

            static constexpr T f(const T& x) noexcept {

                return -x.value;

            }

        };


        template <typename T>
            requires is_complex_v<T> || is_dual_v<T>
        struct negate_impl<T> {

            static constexpr T f(const T& x) noexcept {

                return {-x.real, -x.imag};
            
            }

        };


        template <typename T>
            requires geometry::is_vector_v<T>
        struct negate_impl<T> {

            static constexpr T f(const T& x) noexcept {

                T result;
                std::transform(x.data.begin(), x.data.end(), result.data.begin(), 
                    [](const auto& val) { 
                        return -val; 
                    }
                );
                return result;

            }

        };

        template <typename T>
            requires geometry::is_matrix_v<T>
        struct negate_impl<T> {

            static constexpr T f(const T& x) noexcept {

                T result;
                std::transform(x.data.begin(), x.data.end(), result.data.begin(), 
                    [](const auto& val) { 
                        return -val; 
                    }
                );
                return result;

            }

        };


    } // namespace op


} // namespace scipp::math