/**
 * @file    scipp/math/calculus/expressions/mathematical/trigonometric/hyperbolic/sine.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the hyperbolic cosine function
 * @date    2023-07-15 
 *  
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T>
        struct hyperbolic_sine_expr : unary_expr<T, T> {

            using unary_expr<T, T>::x;

            constexpr hyperbolic_sine_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto x_v = wprime_v * op::cosh(x->val); 
                x->propagate(std::make_shared<decltype(x_v)>(x_v));

            }


            constexpr void update() override {

                x->update();
                this->val = op::sinh(x->val);

            }

        };


    } // namespace calculus


} // namespace scipp::math