/**
 * @file    math/functions/algebraic/multiply.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * 
 * @brief   This file contains a collection of multiplication functions implemented in the scipp::math namespace. 
 *          These functions provide various ways to perform multiplication on different types of operands, 
 *          including numbers, complex numbers, measurements, vectors, and matrices.
 * 
 * @todo    umeasurement multiplies
 * 
 * @date    2023-06-12
 * @copyright Copyright (c) 2023
 */



/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {


    namespace op {
        

        /// @brief Multiply specialization for expr_ptrs
        /// @tparam T1 
        /// @tparam T2 
        template <typename T1, typename T2>
        struct multiply_impl<calculus::expr_ptr<T1>, calculus::expr_ptr<T2>> {

            using result_t = calculus::expr_ptr<multiply_t<T1, T2>>;
            
            static constexpr result_t f(const calculus::expr_ptr<T1>& x, const calculus::expr_ptr<T2>& y) noexcept {
                
                return std::make_shared<calculus::multiply_expr<multiply_t<T1, T2>, T1, T2>>(x->val * y->val, x, y);

            }
                    
        };

        /// @brief Multiply specialization for expr_ptr and value
        /// @tparam T1 
        /// @tparam T2 
        template <typename T1, typename T2>
            requires (is_number_v<T2> || physics::is_measurement_v<T2>)
        struct multiply_impl<calculus::expr_ptr<T1>, T2> {

            using result_t = calculus::expr_ptr<multiply_t<T1, T2>>;
            
            static constexpr result_t f(const calculus::expr_ptr<T1>& x, const T2& y) noexcept {
                
                return x * calculus::constant<T2>(y);

            }
                    
        };

        template <typename T1, typename T2>
            requires (is_number_v<T1> || physics::is_measurement_v<T1>)
        struct multiply_impl<T1, calculus::expr_ptr<T2>> {

            using result_t = calculus::expr_ptr<multiply_t<T1, T2>>;
            
            static constexpr result_t f(const T1& x, const calculus::expr_ptr<T2>& y) noexcept {
                
                return calculus::constant<T1>(x) * y;

            }
                    
        };


        /// @brief Multiply specialization for variable and expr_ptr
        /// @tparam T1 
        /// @tparam T2 
        template <typename T1, typename T2>
        struct multiply_impl<calculus::variable<T1>, calculus::expr_ptr<T2>> {

            using result_t = calculus::expr_ptr<multiply_t<T1, T2>>;
            
            static constexpr result_t f(const calculus::variable<T1>& x, const calculus::expr_ptr<T2>& y) noexcept {
                
                return x.expr * y;   

            }
                    
        };

        template <typename T1, typename T2>
        struct multiply_impl<calculus::expr_ptr<T1>, calculus::variable<T2>> {

            using result_t = calculus::expr_ptr<multiply_t<T1, T2>>;
            
            static constexpr result_t f(const calculus::expr_ptr<T1>& x, const calculus::variable<T2>& y) noexcept {
                
                return x * y.expr;   

            }
                    
        };


        /// @brief Multiply specialization for variables
        /// @tparam T1 
        /// @tparam T2 
        template <typename T1, typename T2>
        struct multiply_impl<calculus::variable<T1>, calculus::variable<T2>> {

            using result_t = calculus::expr_ptr<multiply_t<T1, T2>>;
            
            static constexpr result_t f(const calculus::variable<T1>& x, const calculus::variable<T2>& y) noexcept {
                
                return x.expr * y.expr;   

            }
                    
        };


        /// @brief Multiply specialization for variable and value
        /// @tparam T1 
        /// @tparam T2 
        template <typename T1, typename T2>
            requires (is_number_v<T1> || physics::is_measurement_v<T1>)
        struct multiply_impl<T1, calculus::variable<T2>> {

            using result_t = calculus::expr_ptr<multiply_t<T1, T2>>;
            
            static constexpr result_t f(const T1& x, const calculus::variable<T2>& y) noexcept {
                
                return x * y.expr;   

            }
                    
        };

        template <typename T1, typename T2>
            requires (is_number_v<T2> || physics::is_measurement_v<T2>)
        struct multiply_impl<calculus::variable<T1>, T2> {

            using result_t = calculus::expr_ptr<multiply_t<T1, T2>>;
            
            static constexpr result_t f(const calculus::variable<T1>& x, const T2& y) noexcept {
                
                return x.expr * y;   

            }
                    
        };
        

        // /// @brief Multiply specialization for complex numbers
        // /// @tparam T1
        // /// @tparam T2
        // template <typename T1, typename T2>
        //     requires (are_complex_v<T1, T2>)
        // struct multiply_impl<T1, T2> {
            
        //     using result_t = complex<multiply_t<typename T1::value_t, typename T2::value_t>>;

        //     static constexpr result_t f(const T1& x, const T2& y) noexcept {

        //         return {x.real * y.real - x.imag * y.imag, x.real * y.imag + x.imag * y.real}; 

        //     }

        // };                


        // /// @brief Multiply specialization for complex numbers and numbers
        // /// @tparam T1
        // /// @tparam T2
        // template <typename T1, typename T2>
        //     requires (is_complex_v<T1> && is_number_v<T2>)
        // struct multiply_impl<T1, T2> {
            
        //     using result_t = complex<multiply_t<typename T1::value_t, T2>>;

        //     static constexpr result_t f(const T1& x, const T2& y) noexcept {

        //         return {x.real * y, x.imag * y}; 

        //     }

        // };

        // template <typename T1, typename T2>
        //     requires (is_number_v<T1> && is_complex_v<T2>)
        // struct multiply_impl<T1, T2> {
            
        //     using result_t = complex<multiply_t<T1, typename T2::value_t>>;

        //     static constexpr result_t f(const T1& x, const T2& y) noexcept {

        //         return {x * y.real, x * y.imag}; 

        //     }

        // };


        // /// @brief Multiply specialization for dual numbers
        // /// @tparam T1
        // /// @tparam T2
        // template <typename T1, typename T2>
        //     requires (are_duals_v<T1, T2>)
        // struct multiply_impl<T1, T2> {
            
        //     using result_t = dual<multiply_t<typename T1::value_t, typename T2::value_t>, multiply_t<typename T1::value_t, typename T2::value_t>>;

        //     static constexpr result_t f(const T1& x, const T2& y) noexcept {

        //         return {x.real * y.real, x.real * y.imag + x.imag * y.real};

        //     }

        // };


        // /// @brief Multiply specialization for dual numbers and numbers
        // /// @tparam T1
        // /// @tparam T2
        // template <typename T1, typename T2>
        //     requires (is_dual_v<T1> && is_number_v<T2>)
        // struct multiply_impl<T1, T2> {
            
        //     using result_t = dual<multiply_t<typename T1::value_t, T2>, multiply_t<typename T1::value_t, T2>>;

        //     static constexpr result_t f(const T1& x, const T2& y) noexcept {

        //         return {x.real * y, x.imag * y}; 

        //     }

        // };

        // template <typename T1, typename T2>
        //     requires (is_number_v<T1> && is_dual_v<T2>)
        // struct multiply_impl<T1, T2> {
            
        //     using function_t = binary_function<T1, T2, dual<multiply_t<T1, typename T2::value_t>, multiply_t<typename T1::value_t, T2>>>;

        //     static constexpr result_t f(const function_t::first_arg_t& x, const T2& y) noexcept {

        //         return {x * y.real, x * y.imag}; 

        //     }

        // };


        /// @brief Multiply specialization for numbers
        /// @tparam T1
        /// @tparam T2
        template <typename T1, typename T2>
            requires (are_numbers_v<T1, T2>)
        struct multiply_impl<T1, T2> {
            
            using result_t = decltype(static_cast<T1>(1) * static_cast<T2>(1));

            static constexpr result_t f(const T1& x, const T2& y) noexcept {

                return x * y; 

            }

        };


        /// @brief Multiply specialization for physics::base_quantity
        /// @tparam T1
        /// @tparam T2
        template <typename T1, typename T2>
            requires (physics::are_base_v<T1, T2>)
        struct multiply_impl<T1, T2> {

            using result_t = physics::base_quantity<T1::length + T2::length, 
                                                    T1::time + T2::time,
                                                    T1::mass + T2::mass,
                                                    T1::temperature + T2::temperature,
                                                    T1::elettric_current + T2::elettric_current,
                                                    T1::substance_amount + T2::substance_amount,
                                                    T1::luminous_intensity + T2::luminous_intensity>;

            static constexpr result_t f(const T1&, const T2&) noexcept {

                return {};

            }                                             

        };



        /// @brief Multiply specialization for prefix
        /// @tparam T1
        /// @tparam T2
        template <typename T1, typename T2>
            requires (physics::are_prefix_v<T1, T2>)
        struct multiply_impl<T1, T2> {
            
            using result_t = std::ratio_multiply<T1, T2>;

            static constexpr result_t f(const T1&, const T2&) noexcept {

                return {};

            }                                             
            
        };


        /// @brief Multiply specialization for prefix and unit
        /// @tparam T1
        /// @tparam T2
        template <typename T1, typename T2>
        requires (physics::is_prefix_v<T1> && physics::is_unit_v<T2>)
        struct multiply_impl<T1, T2> {
            
            using result_t = physics::unit<typename T2::base_t, multiply_t<T1, typename T2::prefix_t>>;

            static constexpr result_t f(const T1&, const T2&) noexcept {
                return {};
            }
            
        };

        /// @brief Multiply specialization for physics::unit
        /// @tparam T1
        /// @tparam T2
        template <typename T1, typename T2>
            requires (physics::are_units_v<T1, T2>)
        struct multiply_impl<T1, T2> { 
            
            using result_t = physics::unit<multiply_t<typename T1::base_t, typename T2::base_t>, 
                                           multiply_t<typename T1::prefix_t, typename T2::prefix_t>>;

            static constexpr result_t f(const T1&, const T2&) noexcept {

                return {};

            }       

        };


        /// @brief Multiply specialization for numbers and physics::units
        /// @tparam T1
        /// @tparam T2
        template <typename VALUE_T, typename UNIT_T>
            requires (is_number_v<VALUE_T> && physics::is_unit_v<UNIT_T>)
        struct multiply_impl<VALUE_T, UNIT_T> { 
            
            using result_t = physics::measurement<typename UNIT_T::base_t, VALUE_T>;

            static constexpr result_t f(const VALUE_T& x, const UNIT_T&) noexcept {

                using prefix_t = typename UNIT_T::prefix_t;
                constexpr auto factor = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den);
                return x * factor;

            }       

        };


        /// @brief Multiply specialization for physics::measurement
        /// @tparam T1
        /// @tparam T2
        template <typename T1, typename T2>
            requires (physics::are_measurements_v<T1, T2>)
        struct multiply_impl<T1, T2> {

            using result_t = physics::measurement<multiply_t<typename T1::base_t, typename T2::base_t>, 
                                                  multiply_t<typename T1::value_t, typename T2::value_t>>;

            static constexpr result_t f(const T1& x, const T2& y) noexcept {

                return x.value * y.value; 

            }

        };
        

        // /// @brief Multiply specialization for physics::umeasurement
        // /// @tparam T1
        // /// @tparam T2
        // template <typename T1, typename T2>
        //     requires (physics::are_umeasurements_v<T1, T2>)
        // struct multiply_impl<T1, T2> { 
            
        //     using function_t = binary_function<T1, T2, physics::umeasurement<multiply_t<typename T1::base_t, typename T2::base_t>>>;

        //     static constexpr result_t f(const function_t::first_arg_t& x, const T2& y) noexcept {

        //         return x * y; /// @todo

        //     }

        // };


        // /// @brief Multiply specialization for physics::measurement and physics::umeasurement
        // /// @tparam T1
        // /// @tparam T2
        // template <typename T1, typename T2>
        //     requires (physics::is_measurement_v<T1> && physics::is_umeasurement_v<T2>)
        // struct multiply_impl<T1, T2> {
            
        //     using result_t = physics::umeasurement<multiply_t<typename T1::base_t, typename T2::base_t>>;

        //     static constexpr result_t f(const T1& x, const T2& y) noexcept {

        //         return static_cast<T2>(x) * y;

        //     }

        // };

        // template <typename T1, typename T2>
        //     requires (physics::is_umeasurement_v<T1> && physics::is_measurement_v<T2>)
        // struct multiply_impl<T1, T2> {
            
        //     using function_t = binary_function<T1, T2, physics::umeasurement<multiply_t<typename T1::base_t, typename T2::base_t>>>;

        //     static constexpr result_t f(const function_t::first_arg_t& x, const T2& y) noexcept {

        //         return x * static_cast<function_t::first_arg_t>(y);

        //     }
            
        // };


        /// @brief Multiply specialization for physics::measurement and number
        /// @tparam T1
        /// @tparam T2
        template <typename T1, typename T2>
            requires (physics::is_measurement_v<T1> && is_number_v<T2>)
        struct multiply_impl<T1, T2> {
            
            using result_t = T1;

            static constexpr result_t f(const T1& x, const T2& y) noexcept {

                return x.value * y; 

            }

        };

        template <typename T1, typename T2>
            requires (is_number_v<T1> && physics::is_measurement_v<T2>)
        struct multiply_impl<T1, T2> {
            
            using result_t = T2;

            static constexpr result_t f(const T1& x, const T2& y) noexcept {

                return x * y.value; 

            }

        };


        // /// @brief Multiply specialization for physics::measurement and complex number
        // /// @tparam T1
        // /// @tparam T2
        // template <typename T1, typename T2>
        //     requires (physics::is_measurement_v<T1> && is_complex_v<T2>)
        // struct multiply_impl<T1, T2> {
            
        //     using function_t = binary_function<T1, T2, complex<multiply_t<T1, typename T2::value_t>>>;

        //     static constexpr result_t f(const function_t::first_arg_t& x, const T2& y) noexcept {

        //         return static_cast<T2>(x) * y;

        //     }

        // };

        // template <typename T1, typename T2>
        //     requires (is_complex_v<T1> && physics::is_measurement_v<T2>)
        // struct multiply_impl<T1, T2> {
            
        //     using function_t = binary_function<T1, T2, complex<multiply_t<typename T1::value_t, T2>>>;

        //     static constexpr result_t f(const function_t::first_arg_t& x, const T2& y) noexcept {

        //         return x * static_cast<function_t::first_arg_t>(y);

        //     }

        // };


        // /// @brief Multiply specialization for physics::measurement and dual number
        // /// @tparam T1
        // /// @tparam T2
        // template <typename T1, typename T2>
        //     requires (physics::is_measurement_v<T1> && is_dual_v<T2>)
        // struct multiply_impl<T1, T2> {
            
        //     using function_t = binary_function<T1, T2, dual<multiply_t<T1, typename T2::value_t>, multiply_t<typename T1::value_t, T2>>>;

        //     static constexpr result_t f(const function_t::first_arg_t& x, const T2& y) noexcept {

        //         return static_cast<T2>(x) * y;

        //     }

        // };

        // template <typename T1, typename T2>
        //     requires (is_dual_v<T1> && physics::is_measurement_v<T2>)
        // struct multiply_impl<T1, T2> {
            
        //     using function_t = binary_function<T1, T2, dual<multiply_t<typename T1::value_t, T2>, multiply_t<typename T1::value_t, T2>>>;

        //     static constexpr result_t f(const function_t::first_arg_t& x, const T2& y) noexcept {

        //         return x * static_cast<function_t::first_arg_t>(y);

        //     }

        // };


        // /// @brief Multiply specialization for geometry::column_vector and geometry::row_vector
        // /// @tparam T1
        // /// @tparam T2
        // template <typename T1, typename T2>
        //     requires (geometry::is_column_vector_v<T1> && geometry::is_row_vector_v<T2> && geometry::have_same_dimension_v<T1, T2>)
        // struct multiply_impl<T1, T2> {
            
        //     using result_t = geometry::matrix<geometry::column_vector<multiply_t<typename T1::value_t, typename T2::value_t>, T1::dim>, T2::dim>>;

        //     static constexpr result_t f(const function_t::first_arg_t& x, const T2& y) noexcept {

        //         result_t result{}; 
        //         for (size_t i{}; i < T1::dim; ++i) 
        //             for (size_t j{}; j < T2::dim; ++j) 
        //                 result.data[i][j] = x.data[i] * y.data[j];

        //         return result;

        //     }


        // };

        template <typename T1, typename T2>
            requires (geometry::is_row_vector_v<T1> && geometry::is_column_vector_v<T2> && T1::dim == T2::dim)
        struct multiply_impl<T1, T2> {
            
            using result_t = multiply_t<typename T1::value_t, typename T2::value_t>;

            static constexpr result_t f(const T1& x, const T2& y) noexcept {

                return std::inner_product(x.data.begin(), x.data.end(), y.data.begin(), result_t{});

            }

        };


        /// @brief Multiply specialization for geometry::vector and generic physics::measurements / numbers
        /// @tparam T1
        /// @tparam T2
        template <typename T1, typename T2>
            requires ((physics::is_generic_measurement_v<T1> || is_generic_number_v<T1>) && geometry::is_vector_v<T2>)
        struct multiply_impl<T1, T2> {
            
            using result_t = geometry::vector<multiply_t<T1, typename T2::value_t>, T2::dim, T2::flag>;

            static constexpr result_t f(const T1& x, const T2& y) noexcept {
                
                result_t result{};
                std::transform(
                    std::execution::par, 
                    y.data.begin(), y.data.end(), 
                    result.data.begin(), 
                    [&x](const auto& y_i) { 
                        return x * y_i; 
                    }
                );

                return result; 

            }
        
        };

        template <typename T1, typename T2>
            requires (geometry::is_vector_v<T1> && (physics::is_generic_measurement_v<T2> || is_generic_number_v<T1>))
        struct multiply_impl<T1, T2> {
            
            using result_t = geometry::vector<multiply_t<typename T1::value_t, T2>, T1::dim, T1::flag>;

            static constexpr result_t f(const T1& x, const T2& y) noexcept {
                
                result_t result{};
                std::transform(
                    std::execution::par, 
                    x.data.begin(), x.data.end(), 
                    result.data.begin(), 
                    [&y](const auto& x_i) { 
                        return x_i * y; 
                    }
                );

                return result; 

            }
        
        };


        // /// @brief Multiply specialization for geometry::matrix
        // /// @tparam T1
        // /// @tparam T2
        // template <typename T1, typename T2>
        //     requires (geometry::are_matrix_v<T1, T2> && (T1::columns == T2::rows))
        // struct multiply_impl<T1, T2> {
            
        //     using function_t = binary_function<T1, T2, geometry::matrix<geometry::column_vector<multiply_t<typename T1::value_t, typename T2::value_t>, T1::rows>, T2::columns>>;

        //     static constexpr result_t f(const T1& x, const T2& y) noexcept {

        //         typename result_t result;
        //         const auto transposed = x.transpose();
        //         for (size_t i{}; i < T2::columns; ++i)
        //             for (size_t j{}; j < T1::rows; ++j)
        //                 result.data[i][j] = op::dot(transposed.data[j], y.data[i]);

        //         return result; 

        //     }
        
        // }; 


        // /// @brief Multiply specialization for geometry::matrix and physics::measurements / generic numbers
        // /// @tparam T1
        // /// @tparam T2
        // template <typename T1, typename T2>
        //     requires ((physics::is_measurement_v<T1> || is_generic_number_v<T1>) && geometry::is_matrix_v<T2>)
        // struct multiply_impl<T1, T2> {
            
        //     using function_t = binary_function<T1, T2, geometry::matrix<multiply_t<T1, typename T2::value_t>, T2::columns>>;

        //     static constexpr result_t f(const function_t::first_arg_t& x, const T2& y) noexcept {
                
        //         typename result_t result;
        //         std::transform(std::execution::par, y.data.begin(), y.data.end(), result.data.begin(), [&x](const auto& y_i) { return x * y_i; });
        //         return result; 

        //     }
        
        // };

        // template <typename T1, typename T2>
        //     requires (geometry::is_matrix_v<T1> && (physics::is_measurement_v<T2> || is_generic_number_v<T1>))
        // struct multiply_impl<T1, T2> {
            
        //     using function_t = binary_function<T1, T2, geometry::matrix<multiply_t<typename T1::value_t, T2>, T1::columns>>;

        //     static constexpr result_t f(const function_t::first_arg_t& x, const T2& y) noexcept {
                
        //         typename result_t result;
        //         std::transform(std::execution::par, x.data.begin(), x.data.end(), result.data.begin(), [&y](const auto& x_i) { return x_i * y; });
        //         return result; 

        //     }
        
        // };


    } // namespace op


} // namespace scipp::math