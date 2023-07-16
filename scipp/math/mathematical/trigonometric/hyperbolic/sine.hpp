/**
 * @file    scipp/math/mathematical/trigonometric/hyperbolic/sine.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the hyperbolic sine function
 * @date    2023-07-15
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
        struct hyperbolic_sine_impl<calculus::expr_ptr<T>> {

            static constexpr calculus::expr_ptr<T> f(const calculus::expr_ptr<T>& x) {

                return std::make_shared<calculus::hyperbolic_sine_expr<T>>(sinh(x->val), x);

            }

        };


        template <typename T>
        struct hyperbolic_sine_impl<calculus::variable<T>> {

            static constexpr calculus::expr_ptr<T> f(const calculus::variable<T>& x) {

                return sinh(x.expr); 

            }

        };


        template <typename T>
            requires is_number_v<T>
		struct hyperbolic_sine_impl<T> {

			static constexpr T f(const T& x) {
				
				return std::sinh(x);

			}

		};

        template <typename T>
            requires physics::is_scalar_measurement_v<T>
		struct hyperbolic_sine_impl<T> {

			static constexpr T f(const T& x) {
				
				return std::sinh(x.value);

			}

		};


        template <typename T>
            requires geometry::is_scalar_vector_v<T>
		struct hyperbolic_sine_impl<T> {

			static constexpr T f(const T& x) {

                T x_sinh;
                std::transform(std::execution::par,     
                    x.data.begin(), x.data.end(), 
                    x_sinh.data.begin(), 
                    [](const auto& x_i) { 
					    return sinh(x_i); 
                    }
                );

                return x_sinh;

			}


        // template <typename T>
        //     requires physics::is_scalar_umeasurement_v<T>
		// struct hyperbolic_sine_impl<T> {

		// 	static constexpr T f(const T& x) {
				
		// 		return {std::sin(x.value), x.uncertainty * std::fabs(std::cos(x.value))};

		// 	}

		// };

        // template <typename T>
        //     requires physics::is_scalar_complex_v<T>
		// struct hyperbolic_sine_impl<T> {

		// 	static constexpr T f(const T& x) {
				
		// 		return { std::sin(x.real) * std::cosh(x.imag), 
		// 				 std::cos(x.real) * std::sinh(x.imag) };

		// 	}

		// };


		};


    } // namespace op


} // namespace scipp::math