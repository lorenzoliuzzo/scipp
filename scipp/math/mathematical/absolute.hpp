/**
 * @file    scipp/math/mathematical/absolute.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the absolute function
 * @date    2023-07-16
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
        struct absolute_impl<calculus::expr_ptr<T>> {

            static constexpr calculus::expr_ptr<T> f(const calculus::expr_ptr<T>& x) {

                return std::make_shared<calculus::absolute_expr<T>>(abs(x->val), x);

            }

        };


        template <typename T>
        struct absolute_impl<calculus::variable<T>> {

            static constexpr calculus::expr_ptr<T> f(const calculus::variable<T>& x) {

                return abs(x.expr); 

            }

        };


        template <typename T>
            requires is_number_v<T>
		struct absolute_impl<T> {

			static constexpr T f(const T& x) {
				
				return std::abs(x);

			}

		};


        template <typename T>
            requires physics::is_measurement_v<T>
		struct absolute_impl<T> {

			static constexpr T f(const T& x) {
				
				return std::abs(x.value);

			}

		};


        template <typename T>
            requires geometry::is_scalar_vector_v<T>
		struct absolute_impl<T> {

			static constexpr T f(const T& x) {

                T x_abs;
                std::transform(std::execution::par,     
                    x.data.begin(), x.data.end(), 
                    x_abs.data.begin(), 
                    [](const auto& x_i) { 
					    return abs(x_i); 
                    }
                );

                return x_abs;

			}

        };


    } /// namespace op


} // namespace scipp::math