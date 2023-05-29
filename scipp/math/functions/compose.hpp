/**
 * @file    math/functions/compose.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        template <typename FUNCTION_TYPE1, typename FUNCTION_TYPE2>
            requires (are_unary_functions_v<typename FUNCTION_TYPE1::function_t, typename FUNCTION_TYPE2::function_t> && 
                      std::is_same_v<typename FUNCTION_TYPE1::function_t::arg_t, typename FUNCTION_TYPE2::function_t::result_t>)
        struct compose {
            
            using function_t = unary_function<typename FUNCTION_TYPE2::function_t::arg_t, typename FUNCTION_TYPE1::function_t::result_t>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) noexcept {

                return FUNCTION_TYPE1::f(FUNCTION_TYPE2::f(x));

            }

        };


    } // namespace functions


} // namespace scipp::math