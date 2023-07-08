/**
 * @file    math/calculus/expressions/power_series/trigonometric/sine.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-03
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T>
        struct sine_expr : unary_expr<T, T> {

            using unary_expr<T, T>::x;

            constexpr sine_expr(const T& v, auto e) noexcept : unary_expr<T, T>(v, e) {}


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto x_v = wprime_v * op::cos(x->val); 
                x->propagate(std::make_shared<decltype(x_v)>(x_v));

            }

            constexpr void propagatex(std::shared_ptr<void> ) override {

            //     x->propagatex(wprime * cos(x));

            }

            constexpr void update() override {

                x->update();
                this->val = op::sin(x->val);

            }

        };


    } // namespace calculus


} // namespace scipp::math