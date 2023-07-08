/**
 * @file    math/calculus/constant.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-02
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        /// The node in the expression tree representing a constant expression.
        template <typename T>
        struct constant_expr : expr<T> {

            using expr<T>::expr;

            constexpr void propagate(std::shared_ptr<void>) override {}

            constexpr void propagatex(std::shared_ptr<void>) override {}

            constexpr void update() override {}

        };

        template <typename T> 
        inline constexpr expr_ptr<T> constant(const T& val) { 
            
            return std::make_shared<constant_expr<T>>(val); 
            
        }


    } // namespace calculus


} // namespace scipp::math