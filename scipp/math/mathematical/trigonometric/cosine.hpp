    /**
 * @file    scipp/math/mathematical/trigonometric/cosine.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the cosine function
 * @date    2023-07-16
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
        struct cosine_impl<calculus::expr_ptr<T>> {

            static constexpr calculus::expr_ptr<T> f(const calculus::expr_ptr<T>& x) {

                return std::make_shared<calculus::cosine_expr<T>>(cos(x->val), x);

            }

        };


        template <typename T>
        struct cosine_impl<calculus::variable<T>> {

            static constexpr calculus::expr_ptr<T> f(const calculus::variable<T>& x) {

                return cos(x.expr); 

            }

        };


        template <typename T>
            requires is_number_v<T>
		struct cosine_impl<T> {

			static constexpr T f(const T& x) {
				
				return std::cos(x);

			}

		};


        template <typename T>
            requires physics::is_scalar_measurement_v<T>
		struct cosine_impl<T> {

			static constexpr T f(const T& x) {
				
				return std::cos(x.value);

			}

		};


        template <typename T>
            requires geometry::is_scalar_vector_v<T>
		struct cosine_impl<T> {

			static constexpr T f(const T& x) {

                T x_cos;
                std::transform(std::execution::par,     
                    x.data.begin(), x.data.end(), 
                    x_cos.data.begin(), 
                    [](const auto& x_i) { 
					    return cos(x_i); 
                    }
                );

                return x_cos;

			}

        };


    } // namespace op


} // namespace scipp::math