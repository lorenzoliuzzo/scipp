/**
 * @file    math/calculus/differentials/variable.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-06-09
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    

    namespace differentials {


        template <typename T>
        struct expr;
        
        template <typename T>
        using expr_ptr = std::shared_ptr<expr<T>>;


        template <typename T>
        struct expr; 



        /// The abstract type of any node type in the expression tree.
        template <typename T>
        struct expr {

            /// The value of this expression node.
            T val{};

            /// Construct an Expr object with given value.
            explicit constexpr expr(const T& v) noexcept : 
                
                val(v) {}

            /// Destructor (to avoid warning)
            virtual constexpr ~expr() {}

            /// Bind a value pointer for writing the derivative during propagation
            virtual constexpr void bind_value(T*) {}

            /// Bind an expression pointer for writing the derivative expression during propagation
            virtual constexpr void bind_expr(expr_ptr<T>*) {}

            /// Update the contribution of this expression in the derivative of the root node of the expression tree.
            /// @param wprime The derivative of the root expression node w.r.t. the child expression of this expression node.
            virtual void constexpr propagate(const T& wprime) = 0;

            /// Update the contribution of this expression in the derivative of the root node of the expression tree.
            /// @param wprime The derivative of the root expression node w.r.t. the child expression of this expression node (as an expression).
            virtual void constexpr propagatex(const expr_ptr<T>& wprime) = 0;

            /// Update the value of this expression
            virtual void constexpr update() = 0;

        }; /// struct expr



        /// The node in the expression tree representing either an independent or dependent variable.
        template<typename T>
        struct variable_expr : expr<T> {

            /// The derivative value of the root expression node w.r.t. this variable.
            T* grad_ptr{};

            /// The derivative expression of the root expression node w.r.t. this variable (reusable for higher-order derivatives).
            expr_ptr<T>* gradx_ptr{};

            /// Construct a variable_expr object with given value.
            constexpr variable_expr(const T& v) noexcept : 
                
                Expr<T>(v) {}


            virtual constexpr void bind_value(T* grad) { 
                
                gradPtr = grad; 
                
            }

            virtual constexpr void bind_expr(ExprPtr<T>* gradx) { 
                
                gradxPtr = gradx; 
                
            }

        };

        /// The node in the expression tree representing an independent variable.
        template<typename T>
        struct independent_variable_expr : variable_expr<T>
        {
            using variable_expr<T>::gradPtr;
            using variable_expr<T>::gradxPtr;

            /// Construct an independent_variable_expr object with given value.
            independent_variable_expr(const T& v) : variable_expr<T>(v) {}

            constexpr void propagate(const T& wprime) override {
                if (gradPtr) { *gradPtr += wprime; }
            }

            void propagatex(const ExprPtr<T>& wprime) override
            {
                if (gradxPtr) { *gradxPtr = *gradxPtr + wprime; }
            }

            void update() override {}
        };

        /// The node in the expression tree representing a dependent variable.
        template<typename T>
        struct DependentVariableExpr : VariableExpr<T>
        {
            using VariableExpr<T>::gradPtr;
            using VariableExpr<T>::gradxPtr;

            /// The expression tree that defines how the dependent variable is calculated.
            ExprPtr<T> expr;

            /// Construct an DependentVariableExpr object with given value.
            DependentVariableExpr(const ExprPtr<T>& e) : VariableExpr<T>(e->val), expr(e) {}

            void propagate(const T& wprime) override
            {
                if(gradPtr) { *gradPtr += wprime; }
                expr->propagate(wprime);
            }

            void propagatex(const ExprPtr<T>& wprime) override
            {
                if(gradxPtr) { *gradxPtr = *gradxPtr + wprime; }
                expr->propagatex(wprime);
            }

            void update() override
            {
                expr->update();
                this->val = expr->val;
            }
        };

        template<typename T>
        struct ConstantExpr : Expr<T>
        {
            using Expr<T>::Expr;

            void propagate([[maybe_unused]] const T& wprime) override
            {}

            void propagatex([[maybe_unused]] const ExprPtr<T>& wprime) override
            {}

            void update() override {}
        };

        template<typename T> ExprPtr<T> constant(const T& val) { return std::make_shared<ConstantExpr<T>>(val); }



        template <typename T>
        struct variable {




        }; 
         

    } /// namespace differentials


} /// namespace scipp::math