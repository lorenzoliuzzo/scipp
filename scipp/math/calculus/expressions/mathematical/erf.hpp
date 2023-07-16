/**
 * @file    scipp/math/calculus/expressions/mathematical/erf.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the erf expression
 * @date    2023-07-16
 *  
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T>
        struct erf_expr : unary_expr<T, T> {

            using unary_expr<T, T>::unary_expr;
            using unary_expr<T, T>::val;
            using unary_expr<T, T>::x;


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto x_v = 2.0 / std::sqrt(std::numbers::pi) * wprime_v * op::exp(-op::square(x->val));
                x->propagate(std::make_shared<decltype(x_v)>(x_v));

            }

            constexpr void update() override {

                x->update();
                this->val = op::erf(x->val);
            
            }

        };


    } // namespace calculus


} // namespace scipp::math