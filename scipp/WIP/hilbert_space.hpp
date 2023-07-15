/**
 * @file    math/calculus/hilbert_space.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-05-03
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    template <typename T>
    struct hilbert_space {

        
        template <typename FUNC_TYPE>
            requires (is_binary_function_v<FUNC_TYPE>)
        constexpr auto inner_product(const T& v1, const T& v2) const noexcept {

            return FUNC_TYPE()(v1, v2);

        }


    };



} // namespace scipp::math