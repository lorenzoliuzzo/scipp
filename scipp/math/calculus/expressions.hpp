/**
 * @file    math/calculus/functions/expressions.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-06-24
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
            explicit constexpr expr(const T& v) noexcept 
                : val(v) {}

            /// Destructor 
            virtual constexpr ~expr() {}


            /// Bind a value pointer for writing the derivative during propagation
            // template <typename U> 
            virtual constexpr void bind_value(std::shared_ptr<void>) {}

            /// Bind an expression pointer for writing the derivative expression during propagation
            // template <typename U> 
            virtual constexpr void bind_expr(void*) {}


            /// Update the contribution of this expression in the derivative of the root node of the expression tree.
            /// @param wprime The derivative of the root expression node w.r.t. the child expression of this expression node.
            virtual constexpr void propagate(std::shared_ptr<void>) = 0;

            // /// Update the contribution of this expression in the derivative of the root node of the expression tree.
            // /// @param wprime The derivative of the root expression node w.r.t. the child expression of this expression node (as an expression).
            // virtual constexpr void propagatex(std::shared_ptr<std::shared_ptr<void>>) = 0;


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


        /// The node in the expression tree representing a constant expression.
        template <typename T>
        struct constant_expr : expr<T> {

            using expr<T>::expr;

            constexpr void propagate([[maybe_unused]] std::shared_ptr<void> wprime) override {}

            // constexpr void propagatex([[maybe_unused]] const ExprPtr<T>& wprime) override {}

            constexpr void update() override {}

        };

        template <typename T> 
        inline constexpr expr_ptr<T> constant(const T& val) { 
            
            return std::make_shared<constant_expr<T>>(val); 
            
        }


        template <typename T>
        struct variable_expr : expr<T> {

            std::shared_ptr<void> grad_ptr;
            std::shared_ptr<std::shared_ptr<void>> gradx_ptr;


            constexpr variable_expr(const T& v) noexcept 
                : expr<T>(v) {}


            virtual constexpr void bind_value(std::shared_ptr<void> grad) {   

                grad_ptr = grad;

            }

            virtual constexpr void bind_expr(std::shared_ptr<std::shared_ptr<void>> gradx) {

                gradx_ptr = gradx;

            }

        };

        template <typename T>
        struct independent_variable_expr : variable_expr<T> {

            using variable_expr<T>::grad_ptr;
            using variable_expr<T>::gradx_ptr;


            constexpr independent_variable_expr(const T& v) noexcept 
                : variable_expr<T>(v) {}


            virtual constexpr void propagate(std::shared_ptr<void> wprime) {

                if (grad_ptr.get()) {

                    auto derivative = std::static_pointer_cast<T>(wprime);
                    auto value = std::static_pointer_cast<T>(grad_ptr);

                    *value += *derivative;
                    
                }

            }

            // virtual constexpr void propagatex(std::shared_ptr<std::shared_ptr<void>> wprime) {
                
            //     // if (gradx_ptr) 
            //         // *static_cast<decltype(wprime)*>(gradx_ptr) += wprime; 

            // }


            virtual constexpr void update() override {}

        };

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


            // constexpr void propagatex(std::shared_ptr<std::shared_ptr<void>> wprime) override {

            //     // if (gradx_ptr) 
            //         // *static_cast<decltype(wprime)*>(gradx_ptr) += wprime; 

            // }



            virtual constexpr void update() override {

                expr->update();
                this->val = expr->val;

            }
            
        };



        template <typename T>
        struct neg_expr : unary_expr<T, T> {

            // Using declarations for data members of base class
            using unary_expr<T, T>::x;
            using unary_expr<T, T>::unary_expr;


            template <typename U>
            constexpr void propagate(const U& wprime) {

                x->propagate(-wprime);

            }

            template <typename U>
            constexpr void propagatex(const expr_ptr<U>& wprime) {

                x->propagatex(-wprime);

            }

            virtual constexpr void update() override {

                x->update();
                this->val = -x->val;

            }

        };


        template <typename T, typename T1, typename T2>
        struct add_expr : binary_expr<T, T1, T2> {

            // Using declarations for data members of base class
            using binary_expr<T, T1, T2>::l;
            using binary_expr<T, T1, T2>::r;
            using binary_expr<T, T1, T2>::binary_expr;


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                l->propagate(wprime);
                r->propagate(wprime);

            }

            // constexpr void propagatex(std::shared_ptr<std::shared_ptr<void>> wprime) override {

            //     l->propagatex(wprime);
            //     r->propagatex(wprime);

            // }

            constexpr void update() override {

                l->update();
                r->update();
                this->val = l->val + r->val;

            }

        };


        template <typename T, typename T1, typename T2>
        struct mult_expr : binary_expr<T, T1, T2> {

            // Using declarations for data members of base class
            using binary_expr<T, T1, T2>::l;
            using binary_expr<T, T1, T2>::r;
            using binary_expr<T, T1, T2>::binary_expr;


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto rval = wprime_v * r->val;
                auto lval = wprime_v * l->val;
                l->propagate(std::make_shared<decltype(rval)>(rval)); // (l * r)'l = w' * r
                r->propagate(std::make_shared<decltype(lval)>(lval)); // (l * r)'r = l * w'

            }


                // constexpr void propagatex(std::shared_ptr<std::shared_ptr<void>> wprime) {

                //     // l->propagatex(op::multiply(wprime, r));
                //     // r->propagatex(op::multiply(wprime, l));

                // }

            constexpr void update() override {

                l->update();
                r->update();
                this->val = l->val * r->val;

            }

        };


        template <typename T>
        struct inv_expr : unary_expr<op::invert_t<T>, T> {

            // Using declarations for data members of base class
            using unary_expr<op::invert_t<T>, T>::x;
            using unary_expr<op::invert_t<T>, T>::unary_expr;


            constexpr void propagate(std::shared_ptr<void> wprime) override {
                
                auto wprime_p = std::static_pointer_cast<T>(wprime);
                auto wprime_v = *wprime_p;
                auto aux = - wprime_v / op::square(x->val);
                x->propagate(std::make_shared<decltype(aux)>(aux));

            }

            // template <typename U>
            // constexpr void propagatex(const expr_ptr<U>& wprime) {

            //     x->propagatex(-wprime);

            // }

            virtual constexpr void update() override {

                x->update();
                this->val = 1.0 / x->val;

            }        
            
        };


        template <typename T>
        struct sine_expr : unary_expr<T, T> {

            // Using declarations for data members of base class
            using unary_expr<T, T>::x;


            constexpr sine_expr(const T& v, auto e) noexcept 
                : unary_expr<T, T>(v, e) {}


            virtual constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto x_v = wprime_v * op::cos(x->val); 
                x->propagate(std::make_shared<decltype(x_v)>(x_v));

            }

            // virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

            //     x->propagatex(wprime * cos(x));

            // }

            constexpr void update() override {

                x->update();
                this->val = op::sin(x->val);

            }

        };


        template <typename T>
        struct cosine_expr : unary_expr<T, T> {

            // Using declarations for data members of base class
            using unary_expr<T, T>::x;


            constexpr cosine_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


            virtual constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto x_v = - wprime_v * op::sin(x->val); 
                x->propagate(std::make_shared<decltype(x_v)>(x_v));

            }

            // virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

            //     x->propagatex(-wprime * sin(x));

            // }

            constexpr void update() override {

                x->update();
                this->val = op::cos(x->val);

            }

        };



        template <typename T>
        struct tangent_expr : unary_expr<T, T> {

            // Using declarations for data members of base class
            using unary_expr<T, T>::x;


            constexpr tangent_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}



            virtual constexpr void propagate(const T& wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto x_v = wprime_v / op::square(op::cos(x->val)); 
                x->propagate(std::make_shared<decltype(x_v)>(x_v));

            }

            // virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

            //     const auto aux = 1.0 / cos(x);
            //     x->propagatex(wprime * aux * aux);

            // }

            constexpr void update() override {

                x->update();
                this->val = op::tan(x->val);

            }
            
        };


    } // namespace calculus


} // namespace scipp::math