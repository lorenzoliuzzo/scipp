/**
 * @file    scipp/math/calculus/expressions/algebraic/multiply.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the multiply expression
 * @date    2023-07-14
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T, typename T1, typename T2>
        struct multiply_expr : binary_expr<T, T1, T2> {

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


            constexpr void update() override {

                l->update();
                r->update();
                this->val = l->val * r->val;

            }

        };


    } // namespace calculus


} // namespace scipp::math