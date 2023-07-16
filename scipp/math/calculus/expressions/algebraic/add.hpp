/**
 * @file    scipp/math/calculus/expressions/algebraic/add.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the add expression
 * @date    2023-07-14
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T, typename T1, typename T2>
        struct add_expr : binary_expr<T, T1, T2> {

            using binary_expr<T, T1, T2>::l;
            using binary_expr<T, T1, T2>::r;
            using binary_expr<T, T1, T2>::binary_expr;


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                l->propagate(wprime);
                r->propagate(wprime);

            }


            constexpr void update() override {

                l->update();
                r->update();
                this->val = l->val + r->val;

            }

        };


    } // namespace calculus


} // namespace scipp::math