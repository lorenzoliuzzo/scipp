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


        /// @brief The abstract type of any node type in the expression tree.
        template <typename T>
        struct expr {

            
            T val{}; ///< The value of this expression node.


            /// Construct an expr object with given value.
            explicit constexpr expr(const T& v) noexcept : val(v) {}

            virtual constexpr ~expr() {}


            /// Bind a value pointer for writing the derivative during propagation
            virtual constexpr void bind_value(std::shared_ptr<void>) {}

            /// Update the contribution of this expression in the derivative of the root node of the expression tree.
            /// @param wprime The derivative of the root expression node w.r.t. the child expression of this expression node.
            virtual constexpr void propagate(std::shared_ptr<void>) = 0;


            // /// Bind an expression pointer for writing the derivative expression during propagation
            // virtual constexpr void bind_expr(std::shared_ptr<void>) {}

            // /// Update the contribution of this expression in the derivative of the root node of the expression tree.
            // /// @param wprime The derivative of the root expression node w.r.t. the child expression of this expression node (as an expression).
            // virtual constexpr void propagatex(std::shared_ptr<void>) = 0; 


            /// Update the value of this expression
            virtual constexpr void update() = 0;


        }; /// struct expr
        

        /// The node in the expression tree representing a constant expression.
        template <typename T>
        struct constant_expr : expr<T> {

            using expr<T>::expr;

            constexpr void propagate(std::shared_ptr<void>) override {}

            constexpr void update() override {}

        };


        /// The node in the expression tree representing a variable expression.
        template <typename T>
        struct variable_expr : expr<T> {

            std::shared_ptr<void> grad_ptr;
            std::shared_ptr<void> gradx_ptr;


            constexpr variable_expr(const T& v) noexcept : expr<T>(v) {}


            virtual constexpr void bind_value(std::shared_ptr<void> grad) {   

                grad_ptr = grad;

            }

            virtual constexpr void bind_expr(std::shared_ptr<void> gradx) {

                gradx_ptr = std::static_pointer_cast<expr<T>>(gradx);

            }

        };


        /// @brief The node in the expression tree representing an independent variable expression.
        template <typename T>
        struct independent_variable_expr : variable_expr<T> {

            using variable_expr<T>::grad_ptr;
            using variable_expr<T>::gradx_ptr;


            constexpr independent_variable_expr(const T& v) noexcept : variable_expr<T>(v) {}


            virtual constexpr void propagate(std::shared_ptr<void> wprime) {

                if (grad_ptr.get()) {

                    auto derivative = std::static_pointer_cast<T>(wprime);
                    auto value = std::static_pointer_cast<T>(grad_ptr);

                    *value += *derivative;
                    
                }

            }


            virtual constexpr void update() override {}

        };


        /// @brief The node in the expression tree representing a dependent variable expression.
        template <typename T>
        struct dependent_variable_expr : variable_expr<T> {

            using variable_expr<T>::grad_ptr;
            using variable_expr<T>::gradx_ptr;

            expr_ptr<T> expr;

            constexpr dependent_variable_expr(const expr_ptr<T>& e) noexcept
                : variable_expr<T>(e->val), expr(e) {}


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                if (grad_ptr.get()) {

                    auto derivative = std::static_pointer_cast<T>(wprime);
                    auto value = std::static_pointer_cast<T>(grad_ptr);

                    *value += *derivative;

                }

                expr->propagate(wprime);

            }


            constexpr void update() override {

                this->expr->update();
                this->val = this->expr->val;

            }
            
        };


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