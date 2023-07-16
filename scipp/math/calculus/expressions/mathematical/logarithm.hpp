/**
 * @file    scipp/math/calculus/expressions/mathematical/logarithm.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-15 
 *  
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T>
        struct logarithm_expr : unary_expr<T, T> {

            using unary_expr<T, T>::unary_expr;
            using unary_expr<T, T>::val;
            using unary_expr<T, T>::x;


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto xval = wprime_v / val;
                x->propagate(std::make_shared<decltype(xval)>(xval));
            
            }


            constexpr void update() override {

                x->update();
                this->val = op::log(x->val);
            
            }

        };


    } // namespace calculus


} // namespace scipp::math