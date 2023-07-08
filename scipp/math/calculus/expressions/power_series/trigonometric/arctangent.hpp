/**
 * @file    math/calculus/expressions/power_series/trigonometric/arctangent.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-03
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T>
        struct arctangent_expr : unary_expr<T, T> {

            using unary_expr<T, T>::x;

            constexpr arctangent_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto x_v = wprime_v / op::sqrt(1.0 + op::square(x->val)); 
                x->propagate(std::make_shared<decltype(x_v)>(x_v));

            }

            // constexpr void propagatex(const expr_ptr<T>& wprime) override {

            //     x->propagatex(wprime / (1.0 + op::square(x)));

            // }

            constexpr void update() override {

                x->update();
                this->val = op::atan(x->val);

            }

        };



        // template <typename T1, typename T2>
        // struct arctangent2_expr : binary_expr<T1, T2> {

        //     using binary_expr<T>::val;
        //     using binary_expr<T>::l;
        //     using binary_expr<T>::r;


        //     constexpr arctangent2_expr(const T& v, const expr_ptr<T>& ll, const expr_ptr<T>& rr) noexcept : binary_expr<T>(v, ll, rr) {}


        //     constexpr void propagate(const T& wprime) override {

        //         const auto aux = wprime / (l->val * l->val + r->val * r->val);
        //         l->propagate(r->val * aux);
        //         r->propagate(-l->val * aux);

        //     }

        //     // constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //     //     const auto aux = wprime / (l * l + r * r);
        //     //     l->propagatex(r * aux);
        //     //     r->propagatex(-l * aux);

        //     // }

        //     constexpr void update() override {

        //         l->update();
        //         r->update();
        //         this->val = op::atan(l->val, r->val);

        //     }

        // };


    } // namespace calculus


} // namespace scipp::math