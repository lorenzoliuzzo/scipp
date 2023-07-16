/**
 * @file    scipp/math/mathematical/trigonometric/inverse/arcsine.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the arcsine function
 * @date    2023-07-15
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
        struct arcsine_impl<calculus::expr_ptr<T>> {

            static constexpr calculus::expr_ptr<T> f(const calculus::expr_ptr<T>& x) {

                return std::make_shared<calculus::arcsine_expr<T>>(asin(x->val), x);

            }

        };


        template <typename T>
        struct arcsine_impl<calculus::variable<T>> {

            static constexpr calculus::expr_ptr<T> f(const calculus::variable<T>& x) {

                return asin(x.expr); 

            }

        };
        
                
        template <typename T>
            requires is_number_v<T>
		struct arcsine_impl<T> {

			static constexpr T f(const T& x) {
				
				return std::asin(x);

			}

		};


        template <typename T>
            requires physics::is_scalar_measurement_v<T>
		struct arcsine_impl<T> {

			static constexpr T f(const T& x) {
				
				return std::asin(x.value);

			}

		};


        template <typename T>
            requires geometry::is_scalar_vector_v<T>
		struct arcsine_impl<T> {

			static constexpr T f(const T& x) {

                T x_asin;
                std::transform(std::execution::par,     
                    x.data.begin(), x.data.end(), 
                    x_asin.data.begin(), 
                    [](const auto& x_i) { 
					    return asin(x_i); 
                    }
                );

                return x_asin;

			}

        };


    } // namespace op


} // namespace scipp::math