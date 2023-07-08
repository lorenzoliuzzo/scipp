/**
 * @file    math/calculus/expression.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-02
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        /// The abstract type of any node type in the expression tree.
        template <typename T>
        struct expr {

            /// The value of this expression node.
            T val{};


            /// Construct an expr object with given value.
            explicit constexpr expr(const T& v) noexcept : val(v) {}

            virtual constexpr ~expr() {}


            /// Bind a value pointer for writing the derivative during propagation
            virtual constexpr void bind_value(std::shared_ptr<void>) {}

            /// Bind an expression pointer for writing the derivative expression during propagation
            virtual constexpr void bind_expr(std::shared_ptr<void>) {}


            /// Update the contribution of this expression in the derivative of the root node of the expression tree.
            /// @param wprime The derivative of the root expression node w.r.t. the child expression of this expression node.
            virtual constexpr void propagate(std::shared_ptr<void>) = 0;

            /// Update the contribution of this expression in the derivative of the root node of the expression tree.
            /// @param wprime The derivative of the root expression node w.r.t. the child expression of this expression node (as an expression).
            // virtual 
            virtual constexpr void propagatex(std::shared_ptr<void>) = 0; 


            /// Update the value of this expression
            virtual constexpr void update() = 0;


        }; /// struct expr
        

        template <typename T, typename T1>
        struct unary_expr : expr<T> {

            expr_ptr<T1> x;

            constexpr unary_expr(const T& v, const expr_ptr<T1>& e) noexcept : expr<T>(v), x(e) {}

        };

        template <typename T, typename T1, typename T2>
        struct binary_expr : expr<T> {

            expr_ptr<T1> l; 
            expr_ptr<T2> r;

            constexpr binary_expr(const T& v, const expr_ptr<T1>& left, const expr_ptr<T2>& right) noexcept : expr<T>(v), l(left), r(right) {}

        };

        template <typename T, typename T1, typename T2, typename T3>
        struct ternary_expr : expr<T> {

            expr_ptr<T1> l; 
            expr_ptr<T2> c;
            expr_ptr<T3> r;

            constexpr ternary_expr(const T& x, const expr_ptr<T1>& left, const expr_ptr<T2>& center, const expr_ptr<T3>& right) noexcept : expr<T>(x), l(left), c(center), r(right) {}

        };


    } // namespace calculus


} // namespace scipp::math