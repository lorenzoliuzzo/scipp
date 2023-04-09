/**
 * @file    math/function/mathematical.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-31
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {


    namespace functions {



        struct abs : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::abs(x);

            }

        };


        struct invert : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::invert(x);

            }

        };


        struct sin : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::sin(x);

            }

        }; 


        struct cos : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::cos(x);

            }

        };


        struct tan : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::tan(x);

            }

        };


        struct asin : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::asin(x);

            }

        };


        struct acos : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::acos(x);

            }

        };


        struct atan : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::atan(x);

            }

        };


        struct sinh : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::sinh(x);

            }

        };


        struct cosh : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::cosh(x);

            }

        };


        struct tanh : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::tanh(x);

            }

        };


        struct asinh : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::asinh(x);

            }

        };


        struct acosh : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::acosh(x);

            }

        };


        struct atanh : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::atanh(x);

            }

        };


        struct exp : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::exp(x);

            }

        };


        struct log : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::log(x);

            }

        };


        struct log10 : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::log10(x);

            }

        };


        struct sqrt : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::sqrt(x);

            }

        };


        struct cbrt : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::cbrt(x);

            }

        };


        // struct ceil : unary_function<physics::scalar_m, physics::scalar_m> {

        //     constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

        //         return op::ceil(x);

        //     }

        // };






        template <std::size_t N>
        struct factorial : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                if constexpr (N == 0) 
                    return 1;
                else
                    return N * factorial<N - 1>(x);

            }

        };




    } // namespace functions
    

} // namespace scipp::math