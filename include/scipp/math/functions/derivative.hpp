/**
 * @file    math/function/derivatives.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-09
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {


    namespace functions {


            // using _t = pippo<ARG_TYPE, ARG_DERIVATE_TYPEs...>;
            // using arg_t = ARG_TYPE;
            // using derivate_t = std::tuple<ARG_DERIVATE_TYPEs...>;


            // constexpr auto val(const arg_t& x) const {

            //     return std::get<0>(derivate_t{})(x);

            // }

            // constexpr auto derivate(const arg_t& x) const {

            //     return std::get<1>(derivate_t{})(x);

            // }


        template <typename FUNCTION>
            requires (is_unary_function_v<typename FUNCTION::type>)
        struct total_derivative : binary_function<decltype(typename FUNCTION::type::result_t{} / typename FUNCTION::type::arg_t{}), typename FUNCTION::type::arg_t, typename FUNCTION::type::arg_t> {


            constexpr total_derivative(const FUNCTION& f) noexcept : 

                f(f) {}

            
            constexpr total_derivative(FUNCTION&& f) noexcept :

                f(std::move(f)) {}


            constexpr auto operator()(const typename FUNCTION::type::arg_t& x, const typename FUNCTION::type::arg_t& h) const
                -> decltype(typename FUNCTION::type::result_t{} / typename FUNCTION::type::arg_t{}) 
                    override {

                return (f(x + h) - f(x)) / h;

            }

            const FUNCTION f;


        }; // struct total_derivative


        // template <typename FUNCTION>
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

