/**
 * @file    scipp/math/algebraic/add.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains a collection of addition functions implemented in the scipp::math namespace. 
 *          These functions provide various ways to perform addition on different types of operands, 
 *          including numbers, measurements, complex numbers, vectors, and matrices.
 * @date    2023-07-14
 * 
 * @copyright Copyright (c) 2023
 */

    

namespace scipp::math {


    namespace op {
  

        template <typename T1, typename T2>
        struct add_impl<calculus::expr_ptr<T1>, calculus::expr_ptr<T2>> {

            using result_t = calculus::expr_ptr<add_t<T1, T2>>;
            
            static constexpr result_t f(const calculus::expr_ptr<T1>& x, const calculus::expr_ptr<T2>& y) noexcept {
                
                return std::make_shared<calculus::add_expr<add_t<T1, T2>, T1, T2>>(x->val + y->val, x, y);

            }
                    
        };


        template <typename T1, typename T2>
            requires (is_number_v<T2> || physics::is_measurement_v<T2>)
        struct add_impl<calculus::expr_ptr<T1>, T2> {

            using result_t = calculus::expr_ptr<add_t<T1, T2>>;
            
            static constexpr result_t f(const calculus::expr_ptr<T1>& x, const T2& y) noexcept {
                
                return x + calculus::constant<T2>(y);

            }
                    
        };


        template <typename T1, typename T2>
            requires (is_number_v<T1> || physics::is_measurement_v<T1>)
        struct add_impl<T1, calculus::expr_ptr<T2>> {

            using result_t = calculus::expr_ptr<add_t<T1, T2>>;
            
            static constexpr result_t f(const T1& x, const calculus::expr_ptr<T2>& y) noexcept {
                
                return calculus::constant<T1>(x) + y;

            }
                    
        };


        template <typename T1, typename T2>
        struct add_impl<calculus::variable<T1>, calculus::expr_ptr<T2>> {

            using result_t = calculus::expr_ptr<add_t<T1, T2>>;
            
            static constexpr result_t f(const calculus::variable<T1>& x, const calculus::expr_ptr<T2>& y) noexcept {
                
                return x.expr + y;   

            }
                    
        };
        

        template <typename T1, typename T2>
        struct add_impl<calculus::expr_ptr<T1>, calculus::variable<T2>> {

            using result_t = calculus::expr_ptr<add_t<T1, T2>>;
            
            static constexpr result_t f(const calculus::expr_ptr<T1>& x, const calculus::variable<T2>& y) noexcept {
                
                return x + y.expr;   

            }
                    
        };


        template <typename T1, typename T2>
        struct add_impl<calculus::variable<T1>, calculus::variable<T2>> {

            using result_t = calculus::expr_ptr<add_t<T1, T2>>;
            
            static constexpr result_t f(const calculus::variable<T1>& x, const calculus::variable<T2>& y) noexcept {
                
                return x.expr + y.expr;   

            }
                    
        };


        template <typename T1, typename T2>
            requires (is_number_v<T1> || physics::is_measurement_v<T1>)
        struct add_impl<T1, calculus::variable<T2>> {

            using result_t = calculus::expr_ptr<add_t<T1, T2>>;
            
            static constexpr result_t f(const T1& x, const calculus::variable<T2>& y) noexcept {
                
                return x + y.expr;   

            }
                    
        };


        template <typename T1, typename T2>
            requires (is_number_v<T2> || physics::is_measurement_v<T2>)
        struct add_impl<calculus::variable<T1>, T2> {

            using result_t = calculus::expr_ptr<add_t<T1, T2>>;
            
            static constexpr result_t f(const calculus::variable<T1>& x, const T2& y) noexcept {
                
                return x.expr + y;   

            }
                    
        };


        template <typename T1, typename T2>
            requires are_numbers_v<T1, T2>
        struct add_impl<T1, T2> {

            using result_t = decltype(static_cast<T1>(1) + static_cast<T2>(1));
            
            static constexpr result_t f(const T1& x, const T2& y) noexcept {
                
                return x + y;   

            }
                    
        };


        template <typename T1, typename T2>
            requires physics::are_same_measurement_v<T1, T2>
        struct add_impl<T1, T2> {

            using result_t = physics::measurement<typename T1::base_t, decltype(static_cast<typename T1::value_t>(1.0) + static_cast<typename T2::value_t>(1.0))>;
            
            static constexpr result_t f(const T1& x, const T2& y) noexcept {
                
                return x.value + y.value;   

            }
            
        };


        template <typename T1, typename T2>
            requires (is_number_v<T1> && physics::is_scalar_measurement_v<T2>)
        struct add_impl<T1, T2> {

            using result_t = physics::measurement<physics::scalar_base, decltype(static_cast<T1>(1.0) + static_cast<typename T2::value_t>(1.0))>;

            static constexpr result_t f(const T1& x, const T2& y) noexcept {

                return x + y.value;  

            } 
        
        };

        template <typename T1, typename T2>
            requires (physics::is_scalar_measurement_v<T1> && is_number_v<T2>)
        struct add_impl<T1, T2> {

            using result_t = physics::measurement<physics::scalar_base, decltype(static_cast<typename T1::value_t>(1.0) + static_cast<T2>(1.0))>;

            static constexpr result_t f(const T1& x, const T2& y) noexcept {

                return x.value + y;   

            }
            
        };


        template <typename T1, typename T2>
            requires (geometry::are_column_vectors_v<T1, T2> || geometry::are_row_vectors_v<T1, T2>) && geometry::have_same_dimension_v<T1, T2>
        struct add_impl<T1, T2> {

            using result_t = geometry::vector<add_t<typename T1::value_t, typename T2::value_t>, T1::dim, T1::flag>;

            static constexpr result_t f(const T1& x, const T2& y) noexcept { 

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
        

    } // namespace op


} // namespace scipp::math



        // template <typename T1, typename T2>
        //     requires (are_complex_v<T1. T2> || are_dual_v<T1. T2>)
        // struct add_impl<T1, T2> {
            
        //     using function_t = binary_function<T, T, T>;

        //     static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 
                
        //         return {x.real + y.real, x.imag + y.imag};
            
        //     }

        // };



        // /// @brief Add specialization for physics::measurements and physics::umeasurements
        // /// @tparam T1 
        // /// @tparam T2 
        // template <typename T1, typename T2>
        //     requires (physics::is_measurement_v<T1> && physics::is_umeasurement_v<T2>)
        // struct add_impl<T1, T2> {

        //     using function_t = binary_function<T1, T2, T2>;

        //     static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

        //         return static_cast<function_t::second_arg_t>(x) + y;

        //     }

        // };

        // template <typename T1, typename T2>
        //     requires (physics::is_umeasurement_v<T1> && physics::is_measurement_v<T2>)
        // struct add_impl<T1, T2> {

        //     using function_t = binary_function<T1, T2, T1>;

        //     static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

        //         return {x.value + y.value, x.uncertainty}; 

        //     }

        // };


        
        // /// @brief Add specialization for physics::measurements and complex measurements
        // /// @tparam T1 
        // /// @tparam T2 
        // template <typename T1, typename T2>
        //     requires (physics::is_measurement_v<T1> && math::is_complex_v<T2>)
        // struct add_impl<T1, T2> {

        //     using function_t = binary_function<T1, T2, T2>;

        //     static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

        //         return static_cast<function_t::second_arg_t>(x) + y;

        //     }

        // };

        // template <typename T1, typename T2>
        //     requires (math::is_complex_v<T1> && physics::is_measurement_v<T2>)
        // struct add_impl<T1, T2> {

        //     using function_t = binary_function<T1, T2, T1>;

        //     static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

        //         return {x.real + y.value, x.imag};

        //     }

        // };



        // /// @brief Add specialization for geometry::matrix
        // /// @tparam T1 
        // /// @tparam T2 
        // template <typename T1, typename T2>
        //    requires (geometry::are_matrix_v<T1, T2> && T1::rows == T2::rows && T1::columns == T2::columns)
        // struct add_impl<T1, T2> {

        //     using function_t = binary_function<T1, T2, geometry::matrix<add_t<typename T1::value_t, typename T2::value_t>, T1::columns>>;

        //     static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

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

        //     static constexpr function_t::result_t f(const function_t::arg_t& x) { 

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

        //     static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) { 

        //         return FUNC_TYPE1::f(x) + FUNC_TYPE2::f(y);

        //     }

        // };
