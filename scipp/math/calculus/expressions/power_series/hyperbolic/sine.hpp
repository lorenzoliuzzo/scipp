/**
 * @file    math/calculus/expressions/power_series/hyperbolic/cosine.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-03
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T>
        struct sine_hyp_expr : unary_expr<T, T> {

            using unary_expr<T, T>::x;

            constexpr sine_hyp_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto x_v = wprime_v * op::cosh(x->val); 
                x->propagate(std::make_shared<decltype(x_v)>(x_v));
            
            }

            // constexpr void propagatex(const expr_ptr<T>& wprime) override {

            //     x->propagatex(wprime * cosh(x));

            // }

            constexpr void update() override {

                x->update();
                this->val = op::sinh(x->val);
            }

        };


    } // namespace calculus


} // namespace scipp::math