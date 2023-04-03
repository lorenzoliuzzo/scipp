/**
 * @file    math/hermite_polinomial.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-31
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {


    template <std::size_t N>
    struct bessel_integral_function1 : public binary_function<physics::scalar_m, physics::scalar_m> {


        using result_t = physics::scalar_m; 

        using first_argument_t = physics::scalar_m; 

        using second_argument_t = physics::scalar_m; 


        constexpr physics::scalar_m operator()(const physics::scalar_m& x, const physics::scalar_m& t) const noexcept override {
            
            return op::cos(static_cast<physics::scalar_m>(N) * t - x * op::sin(t));

        }


    };
    
    // template <std::size_t N>
    // struct bessel_integral_function2 : public binary_function<physics::scalar_m, physics::scalar_m> {


    //     using result_t = physics::scalar_m; 

    //     using first_argument_t = physics::scalar_m; 

    //     using second_argument_t = physics::scalar_m; 


    //     constexpr physics::scalar_m operator()(const physics::scalar_m& x, const physics::scalar_m& t) const noexcept override {
            
    //         // return op::exp(i * (- x * op::sinh(t) - static_cast<physics::scalar_m>(N) * t));

    //     }


    // };
    

    template <std::size_t N>
    inline static constexpr physics::scalar_m J_n(const physics::scalar_m& x) noexcept {

        return integral::simpson(bessel_integral_function1<N>(), x,
                                  0.0, constants::pi.value, 10000) / constants::pi;

    }

    
    // requires (physics::are_same_measurements_v<math::op::measurements_prod_t<T1, T2>, T3>)
    inline static constexpr physics::scalar_m bessel_next(const std::size_t& N, 
                                                          const physics::angle_m& x, 
                                                          const physics::scalar_m& J_n_minus_1, 
                                                          const physics::scalar_m& J_n_minus_2) noexcept {
        
        return J_n_minus_1 - J_n_minus_2 * x / static_cast<physics::scalar_m>(2.0 * N);

    }

    
    template <std::size_t N>
    constexpr auto bessel(const physics::angle_m& x) noexcept {

        physics::scalar_m p0 = J_n<0>(x); 
        physics::scalar_m p1 = J_n<1>(x); 

        if constexpr (N == 0)
            return p0; 

        else if constexpr (N == 1)
            return p1; 

        else for (std::size_t index = 2; index < N; ++index) {

            std::swap(p0, p1); 
            p1 = bessel_next(index, x, p0, p1); 

        }

        return p1; 

    }


    constexpr physics::scalar_m bessel(std::size_t N, const physics::angle_m& x) noexcept {
        

        physics::scalar_m p0 = J_n<0>(x); 
        physics::scalar_m p1 = J_n<1>(x); 

        if (N == 0)
            return p0; 

        else if (N == 1)
            return p1; 
        
        else for (std::size_t index = 2; index < N; ++index) {

            std::swap(p0, p1); 
            p1 = bessel_next(index, x, p0, p1); 

        }

        return p1;

    }


    // template <std::size_t N>
    // static std::pair<double, double> hermite_polynomial(const double& x) noexcept {
        

    //     if constexpr (N == 0)
    //         return {1.0, 0.0};
    //     else if constexpr (N == 1)
    //         return {x, 1.0};
    //     else {
            
    //         auto [H_n_minus_1, H_n_minus_1_prime] = hermite_polynomial<N - 1>(x);
    //         auto [H_n_minus_2, H_n_minus_2_prime] = hermite_polynomial<N - 2>(x);

    //         return {2.0 * x * H_n_minus_1 - 2.0 * (N - 1.0) * H_n_minus_2, 
    //                 2.0 * H_n_minus_1 + 2.0 * x * H_n_minus_1_prime - 2.0 * (N - 1.0) * H_n_minus_2_prime};

    //     }

    // }


} // namespace scipp::math