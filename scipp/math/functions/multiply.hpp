/**
 * @file    math/ops/multiply.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the multiply meta function 
 * @date    2023-05-17
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {


    namespace functions {
        

        /// @brief Multiply two physics::base_quantity
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_base_v<ARG_TYPE1, ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                physics::base_quantity<ARG_TYPE1::length + ARG_TYPE2::length, 
                                                                                       ARG_TYPE1::time + ARG_TYPE2::time,
                                                                                       ARG_TYPE1::mass + ARG_TYPE2::mass,
                                                                                       ARG_TYPE1::temperature + ARG_TYPE2::temperature,
                                                                                       ARG_TYPE1::elettric_current + ARG_TYPE2::elettric_current,
                                                                                       ARG_TYPE1::substance_amount + ARG_TYPE2::substance_amount,
                                                                                       ARG_TYPE1::luminous_intensity + ARG_TYPE2::luminous_intensity>> {

        
            using result_t = physics::base_quantity<ARG_TYPE1::length + ARG_TYPE2::length, 
                                                    ARG_TYPE1::time + ARG_TYPE2::time,
                                                    ARG_TYPE1::mass + ARG_TYPE2::mass,
                                                    ARG_TYPE1::temperature + ARG_TYPE2::temperature,
                                                    ARG_TYPE1::elettric_current + ARG_TYPE2::elettric_current,
                                                    ARG_TYPE1::substance_amount + ARG_TYPE2::substance_amount,
                                                    ARG_TYPE1::luminous_intensity + ARG_TYPE2::luminous_intensity>;

            inline static constexpr result_t f(const ARG_TYPE1&, const ARG_TYPE2&) noexcept {

                return {};

            }                                             
            

        };


        /// @brief Multiply two physics::base_quantity
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_prefix_v<ARG_TYPE1, ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                      std::ratio_multiply<ARG_TYPE1, ARG_TYPE2>> {

        
            using result_t = std::ratio_multiply<ARG_TYPE1, ARG_TYPE2>;

            inline static constexpr result_t f(const ARG_TYPE1&, const ARG_TYPE2&) noexcept {

                return {};

            }                                             
            

        };


        /// @brief Multiply an unit of measurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_units_v<ARG_TYPE1, ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                physics::unit<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>, 
                                                                              multiply_t<typename ARG_TYPE1::prefix_t, typename ARG_TYPE2::prefix_t>>> {


            using result_t = physics::unit<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>, 
                                            multiply_t<typename ARG_TYPE1::prefix_t, typename ARG_TYPE2::prefix_t>>;


            inline static constexpr result_t f(const ARG_TYPE1&, const ARG_TYPE2&) noexcept {

                return {};

            }       


        };


        /// @brief Multiply two measurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_measurements_v<ARG_TYPE1, ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                physics::measurement<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>, decltype(typename ARG_TYPE1::value_t{1.0} * typename ARG_TYPE2::value_t{1.0})>> {


            using result_t = physics::measurement<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>, decltype(typename ARG_TYPE1::value_t{1.0} * typename ARG_TYPE2::value_t{1.0})>; 


            inline static constexpr result_t f(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {

                return x.value * y.value; 

            }


        };
        

        /// @todo
        /// @brief Multiply two umeasurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_umeasurements_v<ARG_TYPE1, ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                physics::umeasurement<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>>> {


            using result_t = physics::umeasurement<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>>; 


            inline static constexpr result_t f(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {

                return x * y; 

            }


        };


        /// @brief Multiply two cmeasurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_cmeasurements_v<ARG_TYPE1, ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                physics::cmeasurement<multiply_t<typename ARG_TYPE1::measurement_t, typename ARG_TYPE2::measurement_t>>> {


            using result_t = physics::cmeasurement<multiply_t<typename ARG_TYPE1::measurement_t, typename ARG_TYPE2::measurement_t>>; 


            inline static constexpr result_t f(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {

                return {x.real * y.real - x.imag * y.imag, x.real * y.imag + x.imag * y.real}; 

            }


        };


        /// @brief Multiply a measurment and a number
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_measurement_v<ARG_TYPE1> && is_number_v<ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                ARG_TYPE1> {


            using result_t = ARG_TYPE1; 

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return x.value * y; 

            }


        };


        /// @brief Multiply a number and a measurment
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (is_number_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2> {


            using result_t = ARG_TYPE2; 

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return x * y.value; 

            }


        };



        /// @brief Multiply a measurement and an umeasurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_measurement_v<ARG_TYPE1> && physics::is_umeasurement_v<ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                physics::umeasurement<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>>> {


            using result_t = physics::umeasurement<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>>;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return x * y;

            }


        };


        /// @brief Multiply an umeasurement and a measurement 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_umeasurement_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                physics::umeasurement<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>>> {


            using result_t = physics::umeasurement<multiply_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>>;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return x * static_cast<first_arg_t>(y);

            }
            

        };


        /// @brief Multiply a measurement/umeasurement and a cmeasurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires ((physics::is_measurement_v<ARG_TYPE1> || physics::is_umeasurement_v<ARG_TYPE1>) && 
                      physics::is_cmeasurement_v<ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                physics::cmeasurement<multiply_t<ARG_TYPE1, typename ARG_TYPE2::measurement_t>>> {


            using result_t = physics::cmeasurement<multiply_t<ARG_TYPE1, typename ARG_TYPE2::measurement_t>>;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return static_cast<physics::cmeasurement<ARG_TYPE2>>(x) * y;

            }


        };


        /// @brief Multiply a cmeasurement and a measurement/umeasurement 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_cmeasurement_v<ARG_TYPE1> && 
                    (physics::is_measurement_v<ARG_TYPE2> || physics::is_umeasurement_v<ARG_TYPE2>))
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                physics::cmeasurement<multiply_t<typename ARG_TYPE1::measurement_t, ARG_TYPE2>>> {


            using result_t = physics::cmeasurement<multiply_t<typename ARG_TYPE1::measurement_t, ARG_TYPE2>>;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return x * static_cast<first_arg_t>(y);

            }
            

        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (geometry::is_column_vector_v<ARG_TYPE1> && geometry::is_row_vector_v<ARG_TYPE2> && ARG_TYPE1::dim == ARG_TYPE2::dim)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                geometry::matrix<geometry::column_vector<multiply_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>, ARG_TYPE1::dim>, ARG_TYPE2::dim>> {


            using result_t = geometry::matrix<geometry::column_vector<multiply_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>, ARG_TYPE1::dim>, ARG_TYPE2::dim>;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                result_t result; 

                for (size_t i{}; i < ARG_TYPE1::dim; ++i) 
                    for (size_t j{}; j < ARG_TYPE2::dim; ++j) 
                        result.data[i][j] = x.data[i] * y.data[j];

                return result;

            }


        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (geometry::is_row_vector_v<ARG_TYPE1> && geometry::is_column_vector_v<ARG_TYPE2> && ARG_TYPE1::dim == ARG_TYPE2::dim)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                multiply_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>> {


            using result_t = multiply_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return std::inner_product(x.data.begin(), x.data.end(), y.data.begin(), result_t{});

            }


        };


        /// @brief Multiply a generic_measurement/number and a vector
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires ((physics::is_generic_measurement_v<ARG_TYPE1> || is_number_v<ARG_TYPE1>) && 
                       geometry::is_vector_v<ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                geometry::vector<multiply_t<ARG_TYPE1, typename ARG_TYPE2::value_t>, ARG_TYPE2::dim, ARG_TYPE2::flag>> {


            using result_t = geometry::vector<multiply_t<ARG_TYPE1, typename ARG_TYPE2::value_t>, ARG_TYPE2::dim, ARG_TYPE2::flag>; 

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {
                
                result_t result;
                std::transform(std::execution::par, y.data.begin(), y.data.end(), result.data.begin(), [&x](const auto& y_i) { return x * y_i; });
                return result; 

            }

        
        };


        /// @brief Multiply a vector and a generic_measurement/number 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (geometry::is_vector_v<ARG_TYPE1> && 
                      (physics::is_generic_measurement_v<ARG_TYPE2> || is_number_v<ARG_TYPE1>))
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                geometry::vector<multiply_t<typename ARG_TYPE1::value_t, ARG_TYPE2>, ARG_TYPE1::dim, ARG_TYPE1::flag>> {


            using result_t = geometry::vector<multiply_t<typename ARG_TYPE1::value_t, ARG_TYPE2>, ARG_TYPE1::dim, ARG_TYPE1::flag>; 

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {
                
                result_t result;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), result.data.begin(), [&y](const auto& x_i) { return x_i * y; });
                return result; 

            }

        
        };


        /// @brief Multiply two matrices
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (geometry::are_matrices_v<ARG_TYPE1, ARG_TYPE2> && (ARG_TYPE1::columns == ARG_TYPE2::rows))
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                geometry::matrix<geometry::column_vector<multiply_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>, ARG_TYPE1::rows>, ARG_TYPE2::columns>> {

            
            using result_t = geometry::matrix<geometry::column_vector<multiply_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>, ARG_TYPE1::rows>, ARG_TYPE2::columns>;

            using first_arg_t = ARG_TYPE1; 

            using second_arg_t = ARG_TYPE2; 


            static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                result_t result; 
                const auto transposed = x.transpose();
                for (size_t i{}; i < ARG_TYPE2::columns; ++i)
                    for (size_t j{}; j < ARG_TYPE1::rows; ++j)
                        result.data[i][j] = op::dot(transposed.data[j], y.data[i]);

                return result; 

            }

        
        }; 


        /// @brief Multiply a generic_measurement/number and a matrix
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires ((physics::is_generic_measurement_v<ARG_TYPE1> || is_number_v<ARG_TYPE1>) && 
                    geometry::is_matrix_v<ARG_TYPE2>)
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                geometry::matrix<multiply_t<ARG_TYPE1, typename ARG_TYPE2::vector_t>, ARG_TYPE2::columns>> {


            using result_t = geometry::matrix<multiply_t<ARG_TYPE1, typename ARG_TYPE2::vector_t>, ARG_TYPE2::columns>; 

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {
                
                result_t result;
                std::transform(std::execution::par, y.data.begin(), y.data.end(), result.data.begin(), [&x](const auto& y_i) { return x * y_i; });
                return result; 

            }

        
        };


        /// @brief Multiply a matrix and a generic_measurement/number 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (geometry::is_matrix_v<ARG_TYPE1> && 
                      (physics::is_generic_measurement_v<ARG_TYPE2> || is_number_v<ARG_TYPE1>))
        struct multiply<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                geometry::matrix<multiply_t<typename ARG_TYPE1::vector_t, ARG_TYPE2>, ARG_TYPE1::columns>> {


            using result_t = geometry::matrix<multiply_t<typename ARG_TYPE1::vector_t, ARG_TYPE2>, ARG_TYPE1::columns>; 

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {
                
                result_t result;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), result.data.begin(), [&y](const auto& x_i) { return x_i * y; });
                return result; 

            }

        
        };


    } // namespace functions


} // namespace scipp::math