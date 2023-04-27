/**
 * @file    math/calculus/derivatives.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-09
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        template <typename FUNCTION>  
            requires (is_unary_function_v<typename FUNCTION::_t> && 
                      are_dual_measurements_v<typename FUNCTION::_t::result_t, typename FUNCTION::_t::arg_t>)
        struct derivative : unary_function<typename FUNCTION::_t::result_t::measurement_t, 
                                           typename FUNCTION::_t::arg_t> {

            
            using _t = derivative<FUNCTION>;

            using result_t = typename FUNCTION::_t::result_t::measurement_t;

            using arg_t = typename FUNCTION::_t::arg_t;

            using function_t = FUNCTION;


            constexpr result_t operator()(const arg_t& x) const noexcept override {

                return function_t()(x).eps;

            }


        }; // struct gradient


        template <typename FUNCTION>  
            requires (is_binary_function_v<typename FUNCTION::_t> && 
                      are_dual_measurements_v<typename FUNCTION::_t::result_t, 
                                              typename FUNCTION::_t::first_arg_t,
                                              typename FUNCTION::_t::second_arg_t>)
        struct gradient : binary_function<typename FUNCTION::_t::result_t::measurement_t, 
                                          typename FUNCTION::_t::first_arg_t,
                                          typename FUNCTION::_t::second_arg_t> {


            using _t = gradient<FUNCTION>;

            using result_t = typename FUNCTION::_t::result_t::measurement_t;

            using first_arg_t = typename FUNCTION::_t::first_arg_t;

            using second_arg_t = typename FUNCTION::_t::second_arg_t;

            using function_t = FUNCTION;


            constexpr result_t operator()(const first_arg_t& x, const second_arg_t& y) const noexcept override {
                
                return function_t()(x, y).eps; 

            }


        };





        // template <typename FUNCTION>
        //     requires (is_unary_function_v<typename FUNCTION::type>)
        // struct derivative : binary_function<decltype(typename FUNCTION::type::result_t{} / typename FUNCTION::type::arg_t{}), 
        //                                     typename FUNCTION::type::arg_t, 
        //                                     typename FUNCTION::type::arg_t> {


        //     constexpr derivative(const FUNCTION& f) noexcept : 

        //         f(f) {}

            
        //     constexpr derivative(FUNCTION&& f) noexcept :

        //         f(std::move(f)) {}


        //     constexpr auto operator()(const typename FUNCTION::type::arg_t& x, const typename FUNCTION::type::arg_t& h) const
        //         -> decltype(typename FUNCTION::type::result_t{} / typename FUNCTION::type::arg_t{}) 
        //             override {

        //         return (f(x + h) - f(x - h)) / (2.0 * h);

        //     }

        //     const FUNCTION f;


        // }; // struct derivative


        // template <std::size_t ORDER>
        // struct auto_derivative {

        //     template <typename FUNCTION, typename... DERIV_TYPES>
        //         requires (is_unary_function_v<typename FUNCTION::type>)
        //     constexpr auto operator()(const FUNCTION& f) const noexcept {

        //         std::tuple<DERIV_TYPES...> derivatives;

                

        //     }


        // }; // struct auto_derivative




        // // template <typename FUNCTION>
        //     requires (is_binary_function_v<typename FUNCTION::type>)
        // struct total_derivative : binary_function<decltype(typename FUNCTION::type::result_t{} / typename FUNCTION::type::first_arg_t{}), typename FUNCTION::type::first_arg_t, typename FUNCTION::type::first_arg_t> {
            
                
        //     constexpr total_derivative(const FUNCTION& f) noexcept : 

        //         f(f) {}

            
        //     constexpr total_derivative(FUNCTION&& f) noexcept :

        //         f(std::move(f)) {}


        //     const FUNCTION f;


        // }; // struct total_derivative

        
        

    } // namespace functions


} // namespace scipp::math



    // template <typename FUNCTION>
    //     // requires (is_unary_function_v<typename FUNCTION_TYPE::type>)
    // struct total_derivative : binary_function<decltype(typename FUNCTION::type::result_t{} / typename FUNCTION::type::args_t{}), typename FUNCTION::type::args_t, typename FUNCTION::type::args_t> {
        
            
    //     constexpr total_derivative(const FUNCTION& f) noexcept : 

    //         f(f) {}


    //     constexpr total_derivative(FUNCTION&& f) noexcept :
                
    //         f(std::move(f)) {}


    //     constexpr auto operator()(const typename FUNCTION::type::args_t& x, const typename FUNCTION::type::args_t& h) const 
    //         -> decltype(typename FUNCTION::type::result_t{} / typename FUNCTION::type::args_t{}) 
    //             override {

    //         return (f(x + h) - f(x)) / h;

    //     }

        
    //     const FUNCTION f;


    // };
    


    // template <typename FUNCTION_TYPE>
    //     requires (is_unary_function_v<typename FUNCTION_TYPE::type>)
    // struct total_derivative : binary_function<op::measurements_div_t<typename FUNCTION_TYPE::result_t::measurement_type, typename FUNCTION_TYPE::arg_t>, 
    //                                           typename FUNCTION_TYPE::arg_t, typename FUNCTION_TYPE::arg_t> {


    //     constexpr total_derivative(const FUNCTION_TYPE& f) noexcept : 

    //         f(f) {}


    //     constexpr total_derivative(FUNCTION_TYPE&& f) noexcept :

    //         f(std::move(f)) {}


    //     constexpr auto operator()(const typename FUNCTION_TYPE::arg_t& x, const typename FUNCTION_TYPE::arg_t& h) const 
    //         -> op::measurements_div_t<typename FUNCTION_TYPE::result_t::measurement_type, typename FUNCTION_TYPE::arg_t>
    //             override {

    //         return (f(x + h) - f(x)) / h;

    //     }


    //     FUNCTION_TYPE f;


    // };

