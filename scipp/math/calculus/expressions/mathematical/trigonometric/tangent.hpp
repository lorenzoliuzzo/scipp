/**
 * @file    scipp/math/calculus/expressions/mathematical/trigonometric/tangent.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the tangent expression
 * @date    2023-07-15 
 *  
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T>
        struct tangent_expr : unary_expr<T, T> {

            using unary_expr<T, T>::x;

            constexpr tangent_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto x_v = wprime_v * op::square(op::sec(x->val)); 
                x->propagate(std::make_shared<decltype(x_v)>(x_v));

            }


            constexpr void update() override {

                x->update();
                this->val = op::tan(x->val);

            }
            
        };


    } // namespace calculus


} // namespace scipp::math