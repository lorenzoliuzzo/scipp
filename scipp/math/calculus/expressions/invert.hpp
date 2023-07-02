/**
 * @file    math/calculus/expressions/invert.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-02
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T>
        struct inv_expr : unary_expr<op::invert_t<T>, T> {

            // Using declarations for data members of base class
            using unary_expr<op::invert_t<T>, T>::x;
            using unary_expr<op::invert_t<T>, T>::unary_expr;


            constexpr void propagate(std::shared_ptr<void> wprime) override {
                
                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto aux = - wprime_v / op::square(x->val);
                x->propagate(std::make_shared<decltype(aux)>(aux));

            }

            // constexpr void propagatex(std::shared_ptr<std::shared_ptr<void>> wprime) override {
                
            //     auto wprime_v = *std::static_pointer_cast<expr_ptr<T>>(wprime);
            //     auto aux = - wprime_v / op::square(x->expr);
            //     x->propagatex(std::make_shared<decltype(aux)>(aux));

            // }

            virtual constexpr void update() override {

                x->update();
                this->val = 1.0 / x->val;

            }        
            
        };


    } // namespace calculus


} // namespace scipp::math