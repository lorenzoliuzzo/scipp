/**
 * @file    math/calculus/expressions/algebraic/root.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-03
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <size_t N, typename T>
        struct root_expr : unary_expr<op::root_t<N, T>, T> {

            using unary_expr<op::root_t<N, T>, T>::x;
            using unary_expr<op::root_t<N, T>, T>::unary_expr;


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto aux = (1.0 / (N * op::root<N - 1>(x->val))) * wprime_v;
                x->propagate(std::make_shared<decltype(aux)>(aux));

            }

            constexpr void propagatex(std::shared_ptr<void> ) override {

            //     l->propagatex(wprime);
            //     r->propagatex(wprime);

            }

            constexpr void update() override {

                x->update();
                this->val = op::root<N>(x->val);

            }

        };


    } // namespace calculus


} // namespace scipp::math