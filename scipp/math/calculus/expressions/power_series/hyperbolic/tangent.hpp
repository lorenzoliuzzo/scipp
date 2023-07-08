/**
 * @file    math/calculus/expressions/power_series/hyperbolic/tangent.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-03
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T>
        struct tangent_hyp_expr : unary_expr<T, T> {

            using unary_expr<T, T>::x;

            constexpr tangent_hyp_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                const auto aux = op::inv(op::cosh(x->val));
                auto x_v = wprime_v * op::square(aux); 
                x->propagate(std::make_shared<decltype(x_v)>(x_v));
            
            }

            // constexpr void propagatex(const expr_ptr<T>& wprime) override {

            //     const auto aux = op::inv(op::cosh(x));
            //     x->propagatex(wprime * op::square(aux));

            // }

            constexpr void update() override {

                x->update();
                this->val = op::tanh(x->val);

            }

        };


    } // namespace calculus


} // namespace scipp::math