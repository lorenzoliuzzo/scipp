/**
 * @file    math/operations/algebraic/add.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * 
 * @brief   This file contains a collection of addition functions implemented in the scipp::math namespace. 
 *          These functions provide various ways to perform addition on different types of operands, 
 *          including numbers, measurements, complex numbers, vectors, and matrices.
 * 
 * @date    2023-06-20
 * @copyright Copyright (c) 2023
 */

    

namespace scipp::math {


    namespace op {
  

        /// @brief Add specialization for numbers
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires are_numbers_v<ARG_TYPE1, ARG_TYPE2>
        struct add_impl<ARG_TYPE1, ARG_TYPE2> {

            using result_t = decltype(static_cast<ARG_TYPE1>(1) + static_cast<ARG_TYPE2>(1));
            
            inline static constexpr result_t f(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {
                
                return x + y;   

            }
                    
        };


        /// @brief Add specialization for physics::measurement
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires physics::are_same_measurement_v<ARG_TYPE1, ARG_TYPE2>
        struct add_impl<ARG_TYPE1, ARG_TYPE2> {

            using result_t = physics::measurement<typename ARG_TYPE1::base_t, decltype(static_cast<typename ARG_TYPE1::value_t>(1.0) + static_cast<typename ARG_TYPE2::value_t>(1.0))>;
            
            inline static constexpr result_t f(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {
                
                return x.value + y.value;   

            }
            
        };


        /// @brief Add specialization for numbers and generic scalar physics::measurements
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (is_number_v<ARG_TYPE1> && physics::is_scalar_measurement_v<ARG_TYPE2>)
        struct add_impl<ARG_TYPE1, ARG_TYPE2> {

            using result_t = physics::measurement<physics::scalar_base, decltype(static_cast<ARG_TYPE1>(1.0) + static_cast<typename ARG_TYPE2::value_t>(1.0))>;

            inline static constexpr result_t f(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {

                return x + y.value;  

            } 
        
        };

        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_scalar_measurement_v<ARG_TYPE1> && is_number_v<ARG_TYPE2>)
        struct add_impl<ARG_TYPE1, ARG_TYPE2> {

            using result_t = physics::measurement<physics::scalar_base, decltype(static_cast<typename ARG_TYPE1::value_t>(1.0) + static_cast<ARG_TYPE2>(1.0))>;

            inline static constexpr result_t f(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {

                return x.value + y;   

            }
            
        };


        // /// @brief Add specialization for physics::umeasurement
        // /// @tparam T 
        // template <typename T>
        //     requires (physics::is_umeasurement_v<T>)
        // inline static constexpr auto f(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept 
        //     -> T
                
        //     return {x.value + y.value, std::hypot(x.uncertainty / x.value, y.uncertainty / y.value)};
                    
        // };


        // /// @brief Add specialization for complex/dual numbers
        // /// @tparam T
        // template <typename T>
        //     requires (is_complex_v<T> || is_dual_v<T>)
        // struct add_impl<T> {
            
        //     using function_t = binary_function<T, T, T>;

        //     inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 
                
        //         return {x.real + y.real, x.imag + y.imag};
            
        //     }

        // };



        
        // /// @brief Add specialization for physics::measurements and physics::umeasurements
        // /// @tparam ARG_TYPE1 
        // /// @tparam ARG_TYPE2 
        // template <typename ARG_TYPE1, typename ARG_TYPE2>
        //     requires (physics::is_measurement_v<ARG_TYPE1> && physics::is_umeasurement_v<ARG_TYPE2>)
        // struct add_impl<ARG_TYPE1, ARG_TYPE2> {

        //     using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2>;

        //     inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

        //         return static_cast<function_t::second_arg_t>(x) + y;

        //     }

        // };

        // template <typename ARG_TYPE1, typename ARG_TYPE2>
        //     requires (physics::is_umeasurement_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        // struct add_impl<ARG_TYPE1, ARG_TYPE2> {

        //     using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1>;

        //     inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

        //         return {x.value + y.value, x.uncertainty}; 

        //     }

        // };


        
        // /// @brief Add specialization for physics::measurements and complex measurements
        // /// @tparam ARG_TYPE1 
        // /// @tparam ARG_TYPE2 
        // template <typename ARG_TYPE1, typename ARG_TYPE2>
        //     requires (physics::is_measurement_v<ARG_TYPE1> && math::is_complex_v<ARG_TYPE2>)
        // struct add_impl<ARG_TYPE1, ARG_TYPE2> {

        //     using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2>;

        //     inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

        //         return static_cast<function_t::second_arg_t>(x) + y;

        //     }

        // };

        // template <typename ARG_TYPE1, typename ARG_TYPE2>
        //     requires (math::is_complex_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        // struct add_impl<ARG_TYPE1, ARG_TYPE2> {

        //     using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1>;

        //     inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

        //         return {x.real + y.value, x.imag};

        //     }

        // };


        /// @brief Add specialization for geometry::vector
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (geometry::are_column_vectors_v<ARG_TYPE1, ARG_TYPE2> || geometry::are_row_vectors_v<ARG_TYPE1, ARG_TYPE2>) && 
                    geometry::have_same_dimension_v<ARG_TYPE1, ARG_TYPE2>
        struct add_impl<ARG_TYPE1, ARG_TYPE2> {

            using result_t = geometry::vector<add_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>, ARG_TYPE1::dim, ARG_TYPE1::flag>;

            inline static constexpr result_t f(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept { 

                result_t result;
                std::for_each(std::execution::par, result.data.begin(), result.data.end(), 
                    [&](auto& elem) {
                        auto index = &elem - result.data.data();
                        elem = x.data[index] + y.data[index];
                    }
                );
                
                return result;
            
            }

        };


        // /// @brief Add specialization for geometry::matrix
        // /// @tparam ARG_TYPE1 
        // /// @tparam ARG_TYPE2 
        // template <typename ARG_TYPE1, typename ARG_TYPE2>
        //    requires (geometry::are_matrix_v<ARG_TYPE1, ARG_TYPE2> && ARG_TYPE1::rows == ARG_TYPE2::rows && ARG_TYPE1::columns == ARG_TYPE2::columns)
        // struct add_impl<ARG_TYPE1, ARG_TYPE2> {

        //     using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, geometry::matrix<add_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>, ARG_TYPE1::columns>>;

        //     inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

        //         typename function_t::result_t result;
        //         std::for_each(std::execution::par, result.data.begin(), result.data.end(), 
        //             [&](auto& elem) {
        //                 auto index = &elem - result.data.data();
        //                 elem = x.data[index] + y.data[index];
        //             }
        //         );
                
        //         return result;
            
        //     }

        // };


        // /// @brief Add specialization for unary_function
        // /// @tparam FUNC_TYPE1 
        // /// @tparam FUNC_TYPE2 
        // /// @return unary_function
        // template <typename FUNC_TYPE1, typename FUNC_TYPE2>
        //     requires (are_unary_functions_v<typename FUNC_TYPE1::function_t, typename FUNC_TYPE2::function_t> && 
        //               std::is_same_v<typename FUNC_TYPE1::result_t, typename FUNC_TYPE2::result_t> && 
        //               std::is_same_v<typename FUNC_TYPE1::back_t, typename FUNC_TYPE2::back_t> && 
        //               std::is_same_v<typename FUNC_TYPE1::arg_t, typename FUNC_TYPE2::arg_t>)
        // struct add_impl<FUNC_TYPE1, FUNC_TYPE2> {

        //     using function_t = unary_function<typename FUNC_TYPE1::arg_t, typename FUNC_TYPE1::result_t, typename FUNC_TYPE1::back_t>;

        //     inline static constexpr function_t::result_t f(const function_t::arg_t& x) { 

        //         return FUNC_TYPE1::f(x) + FUNC_TYPE2::f(x);

        //     }
            
        // };


        // /// @brief Add specialization for unary_function
        // /// @tparam FUNC_TYPE1 
        // /// @tparam FUNC_TYPE2 
        // /// @return binary_function
        // template <typename FUNC_TYPE1, typename FUNC_TYPE2>
        //     requires (are_unary_functions_v<typename FUNC_TYPE1::function_t, typename FUNC_TYPE2::function_t> && 
        //               std::is_same_v<typename FUNC_TYPE1::result_t, typename FUNC_TYPE2::result_t>)
        // struct add_impl<FUNC_TYPE1, FUNC_TYPE2> {

        //     using function_t = binary_function<typename FUNC_TYPE1::arg_t, typename FUNC_TYPE2::arg_t, typename FUNC_TYPE1::result_t>;

        //     inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) { 

        //         return FUNC_TYPE1::f(x) + FUNC_TYPE2::f(y);

        //     }

        // };



        /// @brief Add specialization for expr_ptrs
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
        struct add_impl<calculus::expr_ptr<ARG_TYPE1>, calculus::expr_ptr<ARG_TYPE2>> {

            using result_t = calculus::expr_ptr<add_t<ARG_TYPE1, ARG_TYPE2>>;
            
            inline static constexpr result_t f(const calculus::expr_ptr<ARG_TYPE1>& x, const calculus::expr_ptr<ARG_TYPE2>& y) noexcept {
                
                return std::make_shared<calculus::add_expr<add_t<ARG_TYPE1, ARG_TYPE2>, ARG_TYPE1, ARG_TYPE2>>(x->val + y->val, x, y);

            }
                    
        };

        /// @brief Add specialization for expr_ptr and value
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (is_number_v<ARG_TYPE2> || physics::is_measurement_v<ARG_TYPE2>)
        struct add_impl<calculus::expr_ptr<ARG_TYPE1>, ARG_TYPE2> {

            using result_t = calculus::expr_ptr<add_t<ARG_TYPE1, ARG_TYPE2>>;
            
            inline static constexpr result_t f(const calculus::expr_ptr<ARG_TYPE1>& x, const ARG_TYPE2& y) noexcept {
                
                return x + calculus::constant<ARG_TYPE2>(y);

            }
                    
        };

        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (is_number_v<ARG_TYPE1> || physics::is_measurement_v<ARG_TYPE1>)
        struct add_impl<ARG_TYPE1, calculus::expr_ptr<ARG_TYPE2>> {

            using result_t = calculus::expr_ptr<add_t<ARG_TYPE1, ARG_TYPE2>>;
            
            inline static constexpr result_t f(const ARG_TYPE1& x, const calculus::expr_ptr<ARG_TYPE2>& y) noexcept {
                
                return calculus::constant<ARG_TYPE1>(x) + y;

            }
                    
        };


        /// @brief Add specialization for variable and expr_ptr
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
        struct add_impl<calculus::variable<ARG_TYPE1>, calculus::expr_ptr<ARG_TYPE2>> {

            using result_t = calculus::expr_ptr<add_t<ARG_TYPE1, ARG_TYPE2>>;
            
            inline static constexpr result_t f(const calculus::variable<ARG_TYPE1>& x, const calculus::expr_ptr<ARG_TYPE2>& y) noexcept {
                
                return x.expr + y;   

            }
                    
        };

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        struct add_impl<calculus::expr_ptr<ARG_TYPE1>, calculus::variable<ARG_TYPE2>> {

            using result_t = calculus::expr_ptr<add_t<ARG_TYPE1, ARG_TYPE2>>;
            
            inline static constexpr result_t f(const calculus::expr_ptr<ARG_TYPE1>& x, const calculus::variable<ARG_TYPE2>& y) noexcept {
                
                return x + y.expr;   

            }
                    
        };


        /// @brief Add specialization for variables
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
        struct add_impl<calculus::variable<ARG_TYPE1>, calculus::variable<ARG_TYPE2>> {

            using result_t = calculus::expr_ptr<add_t<ARG_TYPE1, ARG_TYPE2>>;
            
            inline static constexpr result_t f(const calculus::variable<ARG_TYPE1>& x, const calculus::variable<ARG_TYPE2>& y) noexcept {
                
                return x.expr + y.expr;   

            }
                    
        };


        /// @brief Add specialization for variable and value
        /// @tparam ARG_TYPE1 
        /// @tparam ARG_TYPE2 
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (is_number_v<ARG_TYPE1> || physics::is_measurement_v<ARG_TYPE1>)
        struct add_impl<ARG_TYPE1, calculus::variable<ARG_TYPE2>> {

            using result_t = calculus::expr_ptr<add_t<ARG_TYPE1, ARG_TYPE2>>;
            
            inline static constexpr result_t f(const ARG_TYPE1& x, const calculus::variable<ARG_TYPE2>& y) noexcept {
                
                return x + y.expr;   

            }
                    
        };

        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (is_number_v<ARG_TYPE2> || physics::is_measurement_v<ARG_TYPE2>)
        struct add_impl<calculus::variable<ARG_TYPE1>, ARG_TYPE2> {

            using result_t = calculus::expr_ptr<add_t<ARG_TYPE1, ARG_TYPE2>>;
            
            inline static constexpr result_t f(const calculus::variable<ARG_TYPE1>& x, const ARG_TYPE2& y) noexcept {
                
                return x.expr + y;   

            }
                    
        };


    } // namespace op


} // namespace scipp::math