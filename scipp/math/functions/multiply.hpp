/**
 * @file    math/ops/multiply.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * 
 * @brief   This file contains a collection of multiplication functions implemented in the scipp::math namespace. 
 *          These functions provide various ways to perform multiplication on different types of operands, 
 *          including numbers, measurements, complex numbers, vectors, and matrices.
 * 
 * @date    2023-05-28
 * @copyright Copyright (c) 2023
 */



/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {


    namespace functions {
        

        /// @brief Multiply two base_quantities
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_base_v<ARG_TYPE1, ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, physics::base_quantity<ARG_TYPE1::length + ARG_TYPE2::length, 
                                                                                            ARG_TYPE1::time + ARG_TYPE2::time,
                                                                                            ARG_TYPE1::mass + ARG_TYPE2::mass,
                                                                                            ARG_TYPE1::temperature + ARG_TYPE2::temperature,
                                                                                            ARG_TYPE1::elettric_current + ARG_TYPE2::elettric_current,
                                                                                            ARG_TYPE1::substance_amount + ARG_TYPE2::substance_amount,
                                                                                            ARG_TYPE1::luminous_intensity + ARG_TYPE2::luminous_intensity>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t&, const function_t::second_arg_t&) noexcept {

                return {};

            }                                             

        };


        /// @brief Multiply two prefixes
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_prefix_v<ARG_TYPE1, ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, std::ratio_multiply<ARG_TYPE1, ARG_TYPE2>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t&, const function_t::second_arg_t&) noexcept {

                return {};

            }                                             
            
        };


        /// @brief Multiply two units of measurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_units_v<ARG_TYPE1, ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> { 
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, physics::unit<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>, 
                                                                                   multiply_t<typename ARG_TYPE1::prefix_t, typename ARG_TYPE2::prefix_t>>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t&, const function_t::second_arg_t&) noexcept {

                return {};

            }       

        };


        /// @brief Multiply a number and an unit of measurement
        template <typename SCALAR_TYPE, typename UNIT_TYPE>
            requires (is_number_v<SCALAR_TYPE> && physics::is_unit_v<UNIT_TYPE>)
        struct multiply<SCALAR_TYPE, UNIT_TYPE> { 
            
            using function_t = binary_function<SCALAR_TYPE, UNIT_TYPE, physics::measurement<typename UNIT_TYPE::base_t, SCALAR_TYPE>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t&) noexcept {

                return { x * UNIT_TYPE::mult };

            }       

        };


        /// @brief Multiply two numbers
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (are_numbers_v<ARG_TYPE1, ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, decltype(ARG_TYPE1{1.0} * ARG_TYPE2{1.0})>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {

                return x * y; 

            }

        };

        
        /// @brief Multiply two measurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_measurements_v<ARG_TYPE1, ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, physics::measurement<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>, multiply_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {

                return x.value * y.value; 

            }

        };
        

        /// @todo
        /// @brief Multiply two umeasurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_umeasurements_v<ARG_TYPE1, ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> { 
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, physics::umeasurement<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {

                return x * y; 

            }

        };


        /// @brief Multiply two cmeasurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_cmeasurements_v<ARG_TYPE1, ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, physics::cmeasurement<multiply_t<typename ARG_TYPE1::measurement_t, typename ARG_TYPE2::measurement_t>>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {

                return {x.real * y.real - x.imag * y.imag, x.real * y.imag + x.imag * y.real}; 

            }

        };


        /// @brief Multiply a measurment and a number
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_measurement_v<ARG_TYPE1> && is_number_v<ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {

                return x.value * y; 

            }

        };


        /// @brief Multiply a number and a measurment
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (is_number_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {

                return x * y.value; 

            }

        };


        /// @todo
        /// @brief Multiply a measurement and an umeasurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_measurement_v<ARG_TYPE1> && physics::is_umeasurement_v<ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, physics::umeasurement<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {

                return x * y;

            }

        };


        /// @brief Multiply an umeasurement and a measurement 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_umeasurement_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, physics::umeasurement<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {

                return x * static_cast<function_t::first_arg_t>(y);

            }
            
        };


        /// @brief Multiply a measurement/umeasurement and a cmeasurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires ((physics::is_measurement_v<ARG_TYPE1> || physics::is_umeasurement_v<ARG_TYPE1>) && physics::is_cmeasurement_v<ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, physics::cmeasurement<multiply_t<ARG_TYPE1, typename ARG_TYPE2::measurement_t>>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {

                return static_cast<function_t::second_arg_t>(x) * y;

            }

        };


        /// @brief Multiply a cmeasurement and a measurement/umeasurement 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_cmeasurement_v<ARG_TYPE1> && (physics::is_measurement_v<ARG_TYPE2> || physics::is_umeasurement_v<ARG_TYPE2>))
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, physics::cmeasurement<multiply_t<typename ARG_TYPE1::measurement_t, ARG_TYPE2>>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {

                return x * static_cast<function_t::first_arg_t>(y);

            }

        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (geometry::is_column_vector_v<ARG_TYPE1> && geometry::is_row_vector_v<ARG_TYPE2> && ARG_TYPE1::dim == ARG_TYPE2::dim)
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, geometry::matrix<geometry::column_vector<multiply_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>, ARG_TYPE1::dim>, ARG_TYPE2::dim>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {

                typename function_t::result_t result; 
                for (size_t i{}; i < ARG_TYPE1::dim; ++i) 
                    for (size_t j{}; j < ARG_TYPE2::dim; ++j) 
                        result.data[i][j] = x.data[i] * y.data[j];

                return result;

            }


        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (geometry::is_row_vector_v<ARG_TYPE1> && geometry::is_column_vector_v<ARG_TYPE2> && ARG_TYPE1::dim == ARG_TYPE2::dim)
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, multiply_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {

                return std::inner_product(x.data.begin(), x.data.end(), y.data.begin(), typename function_t::result_t{});

            }

        };


        /// @brief Multiply a generic_measurement/number and a vector
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires ((physics::is_generic_measurement_v<ARG_TYPE1> || is_number_v<ARG_TYPE1>) && geometry::is_vector_v<ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, geometry::vector<multiply_t<ARG_TYPE1, typename ARG_TYPE2::value_t>, ARG_TYPE2::dim, ARG_TYPE2::flag>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {
                
                typename function_t::result_t result;
                std::transform(std::execution::par, y.data.begin(), y.data.end(), result.data.begin(), [&x](const auto& y_i) { return x * y_i; });
                return result; 

            }
        
        };


        /// @brief Multiply a vector and a generic_measurement/number 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (geometry::is_vector_v<ARG_TYPE1> && (physics::is_generic_measurement_v<ARG_TYPE2> || is_number_v<ARG_TYPE1>))
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, geometry::vector<multiply_t<typename ARG_TYPE1::value_t, ARG_TYPE2>, ARG_TYPE1::dim, ARG_TYPE1::flag>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {
                
                typename function_t::result_t result;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), result.data.begin(), [&y](const auto& x_i) { return x_i * y; });
                return result; 

            }
        
        };


        /// @brief Multiply two matrices
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (geometry::are_matrices_v<ARG_TYPE1, ARG_TYPE2> && (ARG_TYPE1::columns == ARG_TYPE2::rows))
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, geometry::matrix<geometry::column_vector<multiply_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>, ARG_TYPE1::rows>, ARG_TYPE2::columns>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {

                typename function_t::result_t result;
                const auto transposed = x.transpose();
                for (size_t i{}; i < ARG_TYPE2::columns; ++i)
                    for (size_t j{}; j < ARG_TYPE1::rows; ++j)
                        result.data[i][j] = op::dot(transposed.data[j], y.data[i]);

                return result; 

            }
        
        }; 


        /// @brief Multiply a generic_measurement/number and a matrix
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires ((physics::is_generic_measurement_v<ARG_TYPE1> || is_number_v<ARG_TYPE1>) && geometry::is_matrix_v<ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, geometry::matrix<multiply_t<ARG_TYPE1, typename ARG_TYPE2::vector_t>, ARG_TYPE2::columns>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {
                
                typename function_t::result_t result;
                std::transform(std::execution::par, y.data.begin(), y.data.end(), result.data.begin(), [&x](const auto& y_i) { return x * y_i; });
                return result; 

            }
        
        };


        /// @brief Multiply a matrix and a generic_measurement/number 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (geometry::is_matrix_v<ARG_TYPE1> && (physics::is_generic_measurement_v<ARG_TYPE2> || is_number_v<ARG_TYPE1>))
        struct multiply<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, geometry::matrix<multiply_t<typename ARG_TYPE1::vector_t, ARG_TYPE2>, ARG_TYPE1::columns>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {
                
                typename function_t::result_t result;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), result.data.begin(), [&y](const auto& x_i) { return x_i * y; });
                return result; 

            }
        
        };


    } // namespace functions


} // namespace scipp::math