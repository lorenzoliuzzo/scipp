/**
 * @file    math/hermite_polinomial.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-31
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    template <size_t N>
    struct bessel_integral_function1 : public binary_function<physics::scalar_m, physics::scalar_m> {


        constexpr physics::scalar_m operator()(const physics::scalar_m& x, const physics::scalar_m& t) const noexcept override {
            
            return op::cos(static_cast<physics::scalar_m>(N) * t - x * op::sin(t));

        }


    };
    

    template <size_t N, typename T1, typename T2, typename T3 = T2>
    struct bessel_integral_function2 : public binary_function<T1, T2, T3> {


        constexpr T1 operator()(const T2& x, const T3& t) const noexcept override {
            
            return op::exp(math::constants::i * (x * op::sin(t) - static_cast<physics::scalar_m>(N) * t)).real;

        }


    };
    

    template <size_t N>
    inline static constexpr physics::scalar_m J_n(const physics::scalar_m& x) noexcept {

        return integrals::riemann(bessel_integral_function1<N>(), x, 0, constants::pi, 10000) / constants::pi;

        // return integral::simpson(bessel_integral_function2<N, physics::scalar_m, physics::scalar_m>(), x,
        //                           -constants::pi, constants::pi, 10000) / (2.0 * constants::pi);

    }

    
    // requires (physics::are_same_measurements_v<math::op::measurements_prod_t<T1, T2>, T3>)
    inline static constexpr physics::scalar_m bessel_next(const size_t& N, 
                                                          const physics::angle_m& x, 
                                                          const physics::scalar_m& J_n_minus_1, 
                                                          const physics::scalar_m& J_n_minus_2) noexcept {
        
        return J_n_minus_1 - J_n_minus_2 * x / static_cast<physics::scalar_m>(2.0 * N);

    }

    
    template <size_t N>
    constexpr auto bessel(const physics::angle_m& x) noexcept {

        physics::scalar_m p0 = J_n<0>(x); 
        physics::scalar_m p1 = J_n<1>(x); 

        if constexpr (N == 0)
            return p0; 

        else if constexpr (N == 1)
            return p1; 

        else for (size_t index = 2; index < N; ++index) {

            std::swap(p0, p1); 
            p1 = bessel_next(index, x, p0, p1); 

        }

        return p1; 

    }


    constexpr physics::scalar_m bessel(size_t N, const physics::angle_m& x) noexcept {
        

        physics::scalar_m p0 = J_n<0>(x); 
        physics::scalar_m p1 = J_n<1>(x); 

        if (N == 0)
            return p0; 

        else if (N == 1)
            return p1; 
        
        else for (size_t index = 2; index < N; ++index) {

            std::swap(p0, p1); 
            p1 = bessel_next(index, x, p0, p1); 

        }

        return p1;

    }


    // template <size_t N>
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