/**
 * @file    math/calculus/expressions/algebraic/power.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-03
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <size_t N, typename T>
        struct power_expr : unary_expr<op::power_t<N, T>, T> {

            using unary_expr<op::power_t<N, T>, T>::x;
            using unary_expr<op::power_t<N, T>, T>::unary_expr;


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto aux = N * wprime_v * op::pow<N - 1>(x->val);
                x->propagate(std::make_shared<decltype(aux)>(aux));

            }

            constexpr void propagatex(std::shared_ptr<void>) override {

                // auto wprime_v = *std::static_pointer_cast<expr_ptr<T>>(wprime);
                // auto aux = N * wprime_v * op::pow<N - 1>(x->expr);
                // x->propagate(std::make_shared<decltype(aux)>(aux));

            }

            constexpr void update() override {

                x->update();
                this->val = op::pow<N>(x->val);

            }

        };


    } // namespace calculus


} // namespace scipp::math