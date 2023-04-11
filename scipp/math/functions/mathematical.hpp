/**
 * @file    math/function/mathematical.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        template <typename ARG_TYPE>  
            requires (is_dual_measurement_v<ARG_TYPE>)
        struct abs : unary_function<ARG_TYPE, ARG_TYPE> {

            constexpr ARG_TYPE operator()(const ARG_TYPE& other) const noexcept override {

                return op::abs(other); 

            }

        };

        template <typename ARG_TYPE>  
            requires (is_dual_measurement_v<ARG_TYPE> && physics::is_scalar_v<typename ARG_TYPE::measurement_t>)
        struct sin : unary_function<ARG_TYPE, ARG_TYPE> {

            constexpr ARG_TYPE operator()(const ARG_TYPE& other) const noexcept override {

                return op::sin(other); 

            }

        };


        template <typename ARG_TYPE>  
            requires (is_dual_measurement_v<ARG_TYPE> && physics::is_scalar_v<typename ARG_TYPE::measurement_t>)
        struct cos : unary_function<ARG_TYPE, ARG_TYPE> {

            constexpr ARG_TYPE operator()(const ARG_TYPE& other) const noexcept override {

                return op::cos(other); 

            }

        };


        struct invert : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::invert(x);

            }

            constexpr auto backward(const physics::scalar_m& x, const physics::scalar_m& y) const noexcept {

                return -op::square(op::invert(x)) * y;

            }

        };


        // struct sin : unary_function<physics::scalar_m, physics::scalar_m> {

        //     constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

        //         return op::sin(x);

        //     }

        //     constexpr auto backward(const physics::scalar_m& x, const physics::scalar_m& y) const noexcept {

        //         return op::cos(x) * y;

        //     }

        // }; 


        // struct cos : unary_function<physics::scalar_m, physics::scalar_m> {

        //     constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

        //         return op::cos(x);

        //     }

        //     constexpr auto backward(const physics::scalar_m& x, const physics::scalar_m& y) const noexcept {

        //         return -op::sin(x) * y;

        //     }


        // };


        struct tan : unary_function<physics::scalar_m, physics::scalar_m> {

            constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

                return op::tan(x);

            }

            constexpr auto backward(const physics::scalar_m& x, const physics::scalar_m& y) const noexcept {

                return op::square(op::cos(x)) * y;

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


        template <typename T>
        struct sqrt : unary_function<op::measurement_sqrt_t<T>, T> {

            constexpr op::measurement_sqrt_t<T> operator()(const T& x) const noexcept override {

                return op::sqrt(x);

            }

        };


        template <typename T>
        struct cbrt : unary_function<op::measurement_cbrt_t<T>, T> {

            constexpr op::measurement_cbrt_t<T> operator()(const T& x) const noexcept override {

                return op::cbrt(x);

            }

        };


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