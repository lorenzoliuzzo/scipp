/**
 * @file    scipp/math/calculus/expressions/mathematical/absolute.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the absolute expression
 * @date    2023-07-16
 *  
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T>
        struct absolute_expr : unary_expr<T, T> {

            using unary_expr<T, T>::unary_expr;
            using unary_expr<T, T>::val;
            using unary_expr<T, T>::x;


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);

                if (x->val < T{0.0}) 
                    x->propagate(std::make_shared<decltype(wprime_v)>(-wprime_v));

                else if (x->val > T{0.0}) 
                    x->propagate(std::make_shared<decltype(wprime_v)>(wprime_v));

                else 
                    x->propagate(std::make_shared<decltype(wprime_v)>(0));
                    
            }

            constexpr void update() override {

                x->update();
                this->val = op::abs(x->val);
            
            }

        };


    } // namespace calculus


} // namespace scipp::math