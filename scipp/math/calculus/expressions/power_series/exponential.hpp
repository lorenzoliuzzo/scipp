/**
 * @file    math/calculus/expressions/power_series/exponential.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-03
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T>
        struct exponential_expr : unary_expr<T, T> {

            using unary_expr<T, T>::unary_expr;
            using unary_expr<T, T>::val;
            using unary_expr<T, T>::x;


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto xval = wprime_v * val;
                x->propagate(std::make_shared<decltype(xval)>(xval)); // exp(x)' = exp(x) * x'
            
            }

            // constexpr void propagatex(const expr_ptr<T>& wprime) override {

            //     x->propagatex(wprime * exp(x));
            
            // }

            constexpr void update() override {

                x->update();
                this->val = op::exp(x->val);
            
            }

        };


    } // namespace calculus


} // namespace scipp::math