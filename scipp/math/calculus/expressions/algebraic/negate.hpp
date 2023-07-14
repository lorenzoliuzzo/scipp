/**
 * @file    scipp/math/calculus/expressions/algebraic/negate.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-14
 *
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T>
        struct negate_expr : unary_expr<T, T> {

            // Using declarations for data members of base class
            using unary_expr<T, T>::x;
            using unary_expr<T, T>::unary_expr;


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                x->propagate(std::make_shared<T>(-wprime_v));

            }


            constexpr void update() override {

                x->update();
                this->val = -x->val;

            }

        };


    } // namespace calculus


} // namespace scipp::math