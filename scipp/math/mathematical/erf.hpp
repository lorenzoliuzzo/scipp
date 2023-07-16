/**
 * @file    scipp/math/mathematical/erf.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the erf function
 * @date    2023-07-16
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
        struct erf_impl<calculus::expr_ptr<T>> {

            static constexpr calculus::expr_ptr<T> f(const calculus::expr_ptr<T>& x) {

                return std::make_shared<calculus::erf_expr<T>>(erf(x->val), x);

            }

        };


        template <typename T>
        struct erf_impl<calculus::variable<T>> {

            static constexpr calculus::expr_ptr<T> f(const calculus::variable<T>& x) {

                return erf(x.expr); 

            }

        };


        template <typename T>
            requires is_number_v<T>
		struct erf_impl<T> {

			static constexpr T f(const T& x) {
				
				return std::erf(x);

			}

		};


        template <typename T>
            requires physics::is_scalar_measurement_v<T>
		struct erf_impl<T> {

			static constexpr T f(const T& x) {
				
				return std::erf(x.value);

			}

		};


        template <typename T>
            requires geometry::is_scalar_vector_v<T>
		struct erf_impl<T> {

			static constexpr T f(const T& x) {

                T x_erf;
                std::transform(std::execution::par,     
                    x.data.begin(), x.data.end(), 
                    x_erf.data.begin(), 
                    [](const auto& x_i) { 
					    return erf(x_i); 
                    }
                );

                return x_erf;

			}

        };


    } /// namespace op


} // namespace scipp::math