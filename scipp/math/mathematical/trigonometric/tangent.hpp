/**
 * @file    math/operations/mathematical/tangent.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-25
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
            requires is_number_v<T>
		struct tangent_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return std::tan(x);

			}

		};

        template <typename T>
            requires physics::is_scalar_measurement_v<T>
		struct tangent_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return std::tan(x.value);

			}

		};



        template <typename T>
        struct tangent_impl<calculus::expr_ptr<T>> {

            using result_t = calculus::expr_ptr<T>;

            inline static constexpr result_t f(const calculus::expr_ptr<T>& x) {

                return std::make_shared<calculus::tangent_expr<T>>(tan(x->val), x);

            }

        };


        template <typename T>
        struct tangent_impl<calculus::variable<T>> {

            using result_t = calculus::expr_ptr<T>;

            inline static constexpr result_t f(const calculus::variable<T>& x) {

                return tan(x.expr); 

            }

        };


        // template <typename T>
        //     requires physics::is_scalar_umeasurement_v<T>
		// struct tangent_impl<T> {

		// 	inline static constexpr T f(const T& x) {
				
		// 		return {std::tan(x.value), x.uncertainty * std::fabs(std::cos(x.value))};

		// 	}

		// };

        // template <typename T>
        //     requires physics::is_scalar_complex_v<T>
		// struct tangent_impl<T> {

		// 	inline static constexpr T f(const T& x) {
				
		// 		return { std::tan(x.real) * std::cosh(x.imag), 
		// 				 std::cos(x.real) * std::sinh(x.imag) };

		// 	}

		// };

        template <typename T>
            requires geometry::is_scalar_vector_v<T>
		struct tangent_impl<T> {

			inline static constexpr T f(const T& x) {

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