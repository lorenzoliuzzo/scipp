/**
 * @file    math/calculus/expressions/multiply.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-02
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


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

            //     auto wprime_v = *std::static_pointer_cast<expr_ptr<T>>(wprime);
            //     auto rval = wprime_v * r->val;
            //     auto lval = wprime_v * l->val;
            //     l->propagatex(std::make_shared<decltype(rval)>(rval)); // (l * r)'l = w' * r
            //     r->propagatex(std::make_shared<decltype(lval)>(lval)); // (l * r)'r = l * w'

            // }

            constexpr void update() override {

                l->update();
                r->update();
                this->val = l->val * r->val;

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