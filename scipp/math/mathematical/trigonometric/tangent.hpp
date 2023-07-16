/**
 * @file    scipp/math/mathematical/trigonometric/tangent.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the tangent function
 * @date    2023-07-16
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
        struct tangent_impl<calculus::expr_ptr<T>> {

            static constexpr calculus::expr_ptr<T> f(const calculus::expr_ptr<T>& x) {

                return std::make_shared<calculus::tangent_expr<T>>(tan(x->val), x);

            }

        };


        template <typename T>
        struct tangent_impl<calculus::variable<T>> {

            static constexpr calculus::expr_ptr<T> f(const calculus::variable<T>& x) {

                return tan(x.expr); 

            }

        };


        template <typename T>
            requires is_number_v<T>
		struct tangent_impl<T> {

			static constexpr T f(const T& x) {
				
				return std::tan(x);

			}

		};
        

        template <typename T>
            requires physics::is_scalar_measurement_v<T>
		struct tangent_impl<T> {

			static constexpr T f(const T& x) {
				
				return std::tan(x.value);

			}

		};


        template <typename T>
            requires geometry::is_scalar_vector_v<T>
		struct tangent_impl<T> {

			static constexpr T f(const T& x) {

                T x_tan;
                std::transform(std::execution::par,     
                    x.data.begin(), x.data.end(), 
                    x_tan.data.begin(), 
                    [](const auto& x_i) { 
					    return tan(x_i); 
                    }
                );

                return x_tan;

			}

        };


    } // namespace op


} // namespace scipp::math