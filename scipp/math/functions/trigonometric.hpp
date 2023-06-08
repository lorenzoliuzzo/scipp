/**
 * @file    math/functions/trigonometric.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        template <typename T>
            requires (is_number_v<T>)
		struct sine<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return std::sin(x);

			}

		};

        template <typename T>
            requires (physics::is_scalar_measurement_v<T>)
		struct sine<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return std::sin(x.value);

			}

		};

        template <typename T>
            requires (physics::is_scalar_umeasurement_v<T>)
		struct sine<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return {std::sin(x.value), x.uncertainty * std::fabs(std::cos(x.value))};

			}

		};

        template <typename T>
            requires (physics::is_scalar_complex_v<T>)
		struct sine<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return { std::sin(x.real) * std::cosh(x.imag), 
						 std::cos(x.real) * std::sinh(x.imag) };

			}

		};

        template <typename T>
            requires (geometry::is_scalar_vector_v<T>)
		struct sine<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {

                typename function_t::result_t x_sin;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), x_sin.data.begin(), [](const auto& x_i) { 
					return op::sin(x_i); });
                return x_sin;

			}

		};


        template <typename T>
            requires (is_number_v<T>)
		struct cosine<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {

				return std::cos(x);

			}

		};

        template <typename T>
            requires (physics::is_scalar_measurement_v<T>)
		struct cosine<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return std::cos(x.value);

			}

		};

        template <typename T>
            requires (physics::is_scalar_umeasurement_v<T>)
		struct cosine<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return { std::cos(x.value), x.uncertainty * std::fabs(std::sin(x.value)) };

			}

		};

        template <typename T>
            requires (physics::is_scalar_complex_v<T>)
		struct cosine<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return { std::cos(x.real) * std::cosh(x.imag), 
						-std::sin(x.real) * std::sinh(x.imag) };

			}

		};


        template <typename T>
            requires (geometry::is_scalar_vector_v<T>)
		struct cosine<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
                
				typename function_t::result_t x_cos;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), x_cos.data.begin(), [](const auto& x_i) { return op::cos(x_i); });
                return x_cos;

			}

		};



		template <typename T>
			requires (is_number_v<T>)
		struct tangent<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return std::tan(x);

			}

		};


		template <typename T>
			requires (is_number_v<T>)
		struct cosecant<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return 1.0 / std::sin(x);

			}

		};


		template <typename T>
			requires (is_number_v<T>)
		struct secant<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return 1.0 / std::cos(x);

			}

		};


		template <typename T>
			requires (is_number_v<T>)
		struct cotangent<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return 1.0 / std::tan(x);

			}

		};


		template <typename T>
			requires (is_number_v<T>)
		struct arcsine<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return std::asin(x);

			}

		};


		template <typename T>
			requires (is_number_v<T>)
		struct arccosine<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return std::acos(x);

			}

		};


		template <typename T>
			requires (is_number_v<T>)
		struct arctangent<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return std::atan(x);

			}

		};


		template <typename T>
			requires (is_number_v<T>)
		struct arccosecant<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return std::asin(1.0 / x);

			}

		};


		template <typename T>
			requires (is_number_v<T>)
		struct arcsecant<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return std::acos(1.0 / x);

			}

		};


		template <typename T>
			requires (is_number_v<T>)
		struct arccotangent<T> {

			using function_t = unary_function<T, T>;

			inline static constexpr function_t::result_t f(const T& x) {
				
				return std::atan(1.0 / x);

			}

		};


	} // namespace functions


} // namespace scipp::math