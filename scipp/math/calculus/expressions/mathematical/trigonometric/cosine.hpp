/**
 * @file    scipp/math/calculus/expressions/mathematical/trigonometric/cosine.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-15 
 *  
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <typename T>
        struct cosine_expr : unary_expr<T, T> {

            using unary_expr<T, T>::x;

            constexpr cosine_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                auto wprime_v = *std::static_pointer_cast<T>(wprime);
                auto x_v = - wprime_v * op::sin(x->val); 
                x->propagate(std::make_shared<decltype(x_v)>(x_v));

            }


            constexpr void update() override {

                x->update();
                this->val = op::cos(x->val);

            }

        };


    } // namespace calculus


} // namespace scipp::math