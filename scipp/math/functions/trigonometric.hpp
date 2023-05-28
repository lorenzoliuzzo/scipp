/**
 * @file    math/functions/trigonometric.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-23
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        template <typename T>
            requires (is_number_v<T>)
		struct sine<T> : unary_function<T, T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return std::sin(x);
			}
		};

        template <typename T>
            requires (physics::is_scalar_measurement_v<T>)
		struct sine<T> : unary_function<T, T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return std::sin(x.value);
			}
		};

        template <typename T>
            requires (physics::is_scalar_umeasurement_v<T>)
		struct sine<T> : unary_function<T, T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return {std::sin(x.value), x.uncertainty * std::fabs(std::cos(x.value))};
			}
		};

        template <typename T>
            requires (physics::is_scalar_cmeasurement_v<T>)
		struct sine<T> : unary_function<T, T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return { std::sin(x.real) * std::cosh(x.imag), 
						 std::cos(x.real) * std::sinh(x.imag) };
			}
		};

        template <typename T>
            requires (geometry::is_scalar_vector_v<T>)
		struct sine<T> : unary_function<T, T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
                result_t x_sin;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), x_sin.data.begin(), [](const auto& x_i) { return op::sin(x_i); });
                return x_sin;
			}
		};


        template <typename T>
            requires (is_number_v<T>)
		struct cosine<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return std::cos(x);
			}
		};

        template <typename T>
            requires (physics::is_scalar_measurement_v<T>)
		struct cosine<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return std::cos(x.value);
			}
		};

        template <typename T>
            requires (physics::is_scalar_umeasurement_v<T>)
		struct cosine<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return { std::cos(x.value), x.uncertainty * std::fabs(std::sin(x.value)) };
			}
		};

        template <typename T>
            requires (physics::is_scalar_cmeasurement_v<T>)
		struct cosine<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return { std::cos(x.real) * std::cosh(x.imag), 
						-std::sin(x.real) * std::sinh(x.imag) };
			}
		};


        template <typename T>
            requires (geometry::is_scalar_vector_v<T>)
		struct cosine<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
                result_t x_cos;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), x_cos.data.begin(), [](const auto& x_i) { return op::cos(x_i); });
                return x_cos;
			}
		};



		template <typename T>
			requires (is_number_v<T>)
		struct tangent<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return std::tan(x);
			}
		};


		template <typename T>
			requires (is_number_v<T>)
		struct cosecant<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return 1.0 / std::sin(x);
			}
		};


		template <typename T>
			requires (is_number_v<T>)
		struct secant<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return 1.0 / std::cos(x);
			}
		};


		template <typename T>
			requires (is_number_v<T>)
		struct cotangent<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return 1.0 / std::tan(x);
			}
		};


		template <typename T>
			requires (is_number_v<T>)
		struct arcsine<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return std::asin(x);
			}
		};


		template <typename T>
			requires (is_number_v<T>)
		struct arccosine<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return std::acos(x);
			}
		};


		template <typename T>
			requires (is_number_v<T>)
		struct arctangent<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return std::atan(x);
			}
		};


		template <typename T>
			requires (is_number_v<T>)
		struct arccosecant<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return std::asin(1.0 / x);
			}
		};


		template <typename T>
			requires (is_number_v<T>)
		struct arcsecant<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return std::acos(1.0 / x);
			}
		};


		template <typename T>
			requires (is_number_v<T>)
		struct arccotangent<T> {
			using result_t = T;

			inline static constexpr result_t f(const T& x) {
				return std::atan(1.0 / x);
			}
		};

	} // namespace functions


} // namespace scipp::math