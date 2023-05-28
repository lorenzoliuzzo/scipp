/**
 * @file    math/functions/add.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * 
 * @brief   This file contains a collection of addition functions implemented in the scipp::math namespace. 
 *          These functions provide various ways to perform addition on different types of operands, 
 *          including numbers, measurements, complex numbers, vectors, and matrices.
 * 
 * @date    2023-05-28
 * @copyright Copyright (c) 2023
 */

    

namespace scipp::math {


    namespace functions {


        template <typename T>
            requires (is_number_v<T>)
        struct add<T> {

            using function_t = binary_function<T, T, T>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return x + y;   
            
            }

        };

        
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (are_numbers_v<ARG_TYPE1, ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, decltype(ARG_TYPE1{1} + ARG_TYPE2{1})>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return x + y;   
            
            }
        
        };


        template <typename T>
            requires (physics::is_measurement_v<T>)
        struct add<T> {

            using function_t = binary_function<T, T, T>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 
                
                return x.value + y.value; 
            
            }
        
        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_same_measurement_v<ARG_TYPE1, ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> {
                        
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, physics::measurement<typename ARG_TYPE1::base_t, add_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return x.value + y.value;   
            
            }

        };


        template <typename T>
            requires (physics::is_umeasurement_v<T>)
        struct add<T> {
            
            using function_t = binary_function<T, T, T>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 
                
                return {x.value + y.value, std::hypot(x.uncertainty / x.value, y.uncertainty / y.value)};
            
            }
        
        };


        template <typename T>
            requires (physics::is_cmeasurement_v<T>)
        struct add<T> {
            
            using function_t = binary_function<T, T, T>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 
                
                return {x.real + y.real, x.imag + y.imag};
            
            }

        };


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


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_measurement_v<ARG_TYPE1> && physics::is_cmeasurement_v<ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return static_cast<function_t::second_arg_t>(x) + y;

            }

        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_cmeasurement_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return {x.real + y.value, x.imag};

            }

        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires ((geometry::are_column_vectors_v<ARG_TYPE1, ARG_TYPE2> || geometry::are_row_vectors_v<ARG_TYPE1, ARG_TYPE2>) &&
                      geometry::have_same_dimension_v<ARG_TYPE1, ARG_TYPE2> && physics::are_same_base_v<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>)
        struct add<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, geometry::vector<add_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>, ARG_TYPE1::dim, ARG_TYPE1::flag>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                typename function_t::result_t result;
                std::ranges::transform(x.data, y.data, result.data, std::plus<typename function_t::result_t::value_t>());
                // std::for_each(std::execution::par, 
                //               result.data.begin(), result.data.end(), 
                //               [&](auto& elem) { 
                //                 elem = x.data[&elem - result.data.data()] + y.data[&elem - result.data.data()]; 
                //               });

                return result;
            
            }

        };


        template <typename T>
            requires (geometry::is_matrix_v<T>)
        struct add<T> {
            
            using function_t = binary_function<T, T, T>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                typename function_t::result_t result;
                std::transform(std::execution::par,
                               x.data.begin(), x.data.end(), 
                               y.data.begin(), 
                               result.data.begin(), 
                               std::plus<typename function_t::result_t::value_t>());
                
                return result;
            
            }
        
        };


        // template <typename T, typename U>
        //     requires (std::is_same_v<typename T::result_t, typename U::result_t>) //are_unary_functions_v<T, U> && 
        // struct add<T, U> {

        //     using function_t = binary_function<T, U, typename T::result_t>;

        //     inline static constexpr function_t::result_t f(const function_t::first_arg_t::arg_t& x, const function_t::second_arg_t::arg_t& y) noexcept { 

        //         return function_t::first_arg_t::f(x) + function_t::second_arg_t::f(y);

        //     }

        // };


    } // namespace functions


} // namespace scipp::math