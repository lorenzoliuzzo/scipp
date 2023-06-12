/**
 * @file    math/functions/algebraic/add.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * 
 * @brief   This file contains a collection of addition functions implemented in the scipp::math namespace. 
 *          These functions provide various ways to perform addition on different types of operands, 
 *          including numbers, measurements, complex numbers, vectors, and matrices.
 * 
 * @date    2023-06-12
 * @copyright Copyright (c) 2023
 */

    

namespace scipp::math {


    namespace functions {

        
        /// @brief Add specialization for numbers
        /// @tparam T 
        template <typename T>
            requires (is_number_v<T>)
        struct add<T> {

            using function_t = binary_function<T, T, T>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return x + y;   
            
            }

        };

        /// @brief Add specialization for numbers
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (are_numbers_v<ARG_TYPE1, ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, decltype(ARG_TYPE1{1} + ARG_TYPE2{1})>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return x + y;   
            
            }
        
        };


        /// @brief Add specialization for physics::measurement
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_same_measurement_v<ARG_TYPE1, ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> {
                        
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, physics::measurement<typename ARG_TYPE1::base_t, add_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return x.value + y.value;   
            
            }

        };


        /// @brief Add specialization for physics::umeasurement
        /// @tparam T 
        template <typename T>
            requires (physics::is_umeasurement_v<T>)
        struct add<T> {
            
            using function_t = binary_function<T, T, T>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 
                
                return {x.value + y.value, std::hypot(x.uncertainty / x.value, y.uncertainty / y.value)};
            
            }
        
        };


        /// @brief Add specialization for complex/dual numbers
        /// @tparam T
        template <typename T>
            requires (is_complex_v<T> || is_dual_v<T>)
        struct add<T> {
            
            using function_t = binary_function<T, T, T>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 
                
                return {x.real + y.real, x.imag + y.imag};
            
            }

        };


        /// @brief Add specialization for numbers and generic scalar physics::measurements
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (is_number_v<ARG_TYPE1> && physics::is_generic_measurement_v<ARG_TYPE2> && physics::is_scalar_base_v<typename ARG_TYPE2::base_t>)
        struct add<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return static_cast<function_t::second_arg_t>(x) + y;   
            
            }

        };

        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_generic_measurement_v<ARG_TYPE1> && physics::is_scalar_base_v<typename ARG_TYPE1::base_t> && is_number_v<ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return x + static_cast<function_t::first_arg_t>(y);   
            
            }
        
        };

        
        /// @brief Add specialization for physics::measurements and physics::umeasurements
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_measurement_v<ARG_TYPE1> && physics::is_umeasurement_v<ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return static_cast<function_t::second_arg_t>(x) + y;

            }

        };

        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_umeasurement_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return {x.value + y.value, x.uncertainty}; 

            }

        };


        
        /// @brief Add specialization for physics::measurements and complex measurements
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_measurement_v<ARG_TYPE1> && math::is_complex_v<ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return static_cast<function_t::second_arg_t>(x) + y;

            }

        };

        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (math::is_complex_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return {x.real + y.value, x.imag};

            }

        };


        /// @brief Add specialization for geometry::vector
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires ((geometry::are_column_vectors_v<ARG_TYPE1, ARG_TYPE2> || geometry::are_row_vectors_v<ARG_TYPE1, ARG_TYPE2>) && geometry::have_same_dimension_v<ARG_TYPE1, ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, geometry::vector<add_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>, ARG_TYPE1::dim, ARG_TYPE1::flag>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                typename function_t::result_t result;
                std::for_each(std::execution::par, result.data.begin(), result.data.end(), 
                    [&](auto& elem) {
                        auto index = &elem - result.data.data();
                        elem = x.data[index] + y.data[index];
                    }
                );
                
                return result;
            
            }

        };


        /// @brief Add specialization for geometry::matrix
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
           requires (geometry::are_matrix_v<ARG_TYPE1, ARG_TYPE2> && ARG_TYPE1::rows == ARG_TYPE2::rows && ARG_TYPE1::columns == ARG_TYPE2::columns)
        struct add<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, geometry::matrix<add_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>, ARG_TYPE1::columns>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                typename function_t::result_t result;
                std::for_each(std::execution::par, result.data.begin(), result.data.end(), 
                    [&](auto& elem) {
                        auto index = &elem - result.data.data();
                        elem = x.data[index] + y.data[index];
                    }
                );
                
                return result;
            
            }

        };


        /// @brief Add specialization for unary_function
        /// @tparam FUNC_TYPE1 
        /// @tparam FUNC_TYPE2 
        /// @return unary_function
        template <typename FUNC_TYPE1, typename FUNC_TYPE2>
            requires (are_unary_functions_v<typename FUNC_TYPE1::function_t, typename FUNC_TYPE2::function_t> && 
                      std::is_same_v<typename FUNC_TYPE1::result_t, typename FUNC_TYPE2::result_t> && 
                      std::is_same_v<typename FUNC_TYPE1::arg_t, typename FUNC_TYPE2::arg_t>)
        struct add<FUNC_TYPE1, FUNC_TYPE2> {

            using function_t = unary_function<typename FUNC_TYPE1::arg_t, typename FUNC_TYPE1::result_t>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) { 

                return FUNC_TYPE1::f(x) + FUNC_TYPE2::f(x);

            }

        };


        /// @brief Add specialization for unary_function
        /// @tparam FUNC_TYPE1 
        /// @tparam FUNC_TYPE2 
        /// @return binary_function
        template <typename FUNC_TYPE1, typename FUNC_TYPE2>
            requires (are_unary_functions_v<typename FUNC_TYPE1::function_t, typename FUNC_TYPE2::function_t> && 
                      std::is_same_v<typename FUNC_TYPE1::result_t, typename FUNC_TYPE2::result_t>)
        struct add<FUNC_TYPE1, FUNC_TYPE2> {

            using function_t = binary_function<typename FUNC_TYPE1::arg_t, typename FUNC_TYPE2::arg_t, typename FUNC_TYPE1::result_t>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) { 

                return FUNC_TYPE1::f(x) + FUNC_TYPE2::f(y);

            }

        };


    } // namespace functions


} // namespace scipp::math