/**
 * @file    math/functions/trigonometric.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
            requires is_number_v<T>
		struct sine_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return std::sin(x);

			}

		};

        template <typename T>
            requires physics::is_scalar_measurement_v<T>
		struct sine_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return std::sin(x.value);

			}

		};



        template <typename T>
        struct sine_impl<calculus::expr_ptr<T>> {

            using result_t = calculus::expr_ptr<T>;

            inline static constexpr result_t f(const calculus::expr_ptr<T>& x) {

                return std::make_shared<calculus::sine_expr<T>>(sin(x->val), x);

            }

        };


        template <typename T>
        struct sine_impl<calculus::variable<T>> {

            using result_t = calculus::expr_ptr<T>;

            inline static constexpr result_t f(const calculus::variable<T>& x) {

                return sin(x.expr); 

            }

        };


        // template <typename T>
        //     requires physics::is_scalar_umeasurement_v<T>
		// struct sine_impl<T> {

		// 	inline static constexpr T f(const T& x) {
				
		// 		return {std::sin(x.value), x.uncertainty * std::fabs(std::cos(x.value))};

		// 	}

		// };

        // template <typename T>
        //     requires physics::is_scalar_complex_v<T>
		// struct sine_impl<T> {

		// 	inline static constexpr T f(const T& x) {
				
		// 		return { std::sin(x.real) * std::cosh(x.imag), 
		// 				 std::cos(x.real) * std::sinh(x.imag) };

		// 	}

		// };

        template <typename T>
            requires geometry::is_scalar_vector_v<T>
		struct sine_impl<T> {

			inline static constexpr T f(const T& x) {

                T x_sin;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), x_sin.data.begin(), [](const auto& x_i) { 
					return op::sin(x_i); });
                return x_sin;

			}

		};


        template <typename T>
            requires is_number_v<T>
		struct cosine_impl<T> {

			inline static constexpr T f(const T& x) {

				return std::cos(x);

			}

		};

        template <typename T>
            requires physics::is_scalar_measurement_v<T>
		struct cosine_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return std::cos(x.value);

			}

		};



        template <typename T>
        struct cosine_impl<calculus::expr_ptr<T>> {

            using result_t = calculus::expr_ptr<T>;

            inline static constexpr result_t f(const calculus::expr_ptr<T>& x) {

                return std::make_shared<calculus::cosine_expr<T>>(sin(x->val), x);

            }

        };


        template <typename T>
        struct cosine_impl<calculus::variable<T>> {

            using result_t = calculus::expr_ptr<T>;

            inline static constexpr result_t f(const calculus::variable<T>& x) {

                return sin(x.expr); 

            }

        };

        // template <typename T>
        //     requires physics::is_scalar_umeasurement_v<T>
		// struct cosine_impl<T> {

		// 	inline static constexpr T f(const T& x) {
				
		// 		return { std::cos(x.value), x.uncertainty * std::fabs(std::sin(x.value)) };

		// 	}

		// };

        // template <typename T>
        //     requires physics::is_scalar_complex_v<T>
		// struct cosine<T> {

		// 	inline static constexpr T f(const T& x) {
				
		// 		return { std::cos(x.real) * std::cosh(x.imag), 
		// 				-std::sin(x.real) * std::sinh(x.imag) };

		// 	}

		// };


        template <typename T>
            requires geometry::is_scalar_vector_v<T>
		struct cosine_impl<T> {

			inline static constexpr T f(const T& x) {
                
				T x_cos;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), x_cos.data.begin(), [](const auto& x_i) { return op::cos(x_i); });
                return x_cos;

			}

		};



		template <typename T>
			requires is_number_v<T>
		struct tangent_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return std::tan(x);

			}

		};


		template <typename T>
			requires is_number_v<T>
		struct cosecant_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return 1.0 / std::sin(x);

			}

		};


		template <typename T>
			requires is_number_v<T>
		struct secant_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return 1.0 / std::cos(x);

			}

		};


		template <typename T>
			requires is_number_v<T>
		struct cotangent_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return 1.0 / std::tan(x);

			}

		};


		template <typename T>
			requires is_number_v<T>
		struct arcsine_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return std::asin(x);

			}

		};


		template <typename T>
			requires is_number_v<T>
		struct arccosine_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return std::acos(x);

			}

		};


		template <typename T>
			requires is_number_v<T>
		struct arctangent_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return std::atan(x);

			}

		};


		template <typename T>
			requires is_number_v<T>
		struct arccosecant_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return std::asin(1.0 / x);

			}

		};


		template <typename T>
			requires is_number_v<T>
		struct arcsecant_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return std::acos(1.0 / x);

			}

		};


		template <typename T>
			requires is_number_v<T>
		struct arccotangent_impl<T> {

			inline static constexpr T f(const T& x) {
				
				return std::atan(1.0 / x);

			}

		};


	} // namespace op


} // namespace scipp::math