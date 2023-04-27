/**
 * @file    math/polynomials/hermite.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    template <typename T1, typename T2, typename T3>
        // requires (physics::are_same_measurements_v<math::op::measurements_prod_t<T1, T2>, T3>)
    inline static constexpr T3 hermite_next(const std::size_t& N, const T1& x, const T2& H_n_minus_1, const T3& H_n_minus_2) noexcept {
        
        return 2.0 * x * H_n_minus_1 - 2.0 * (N - 1.0) * H_n_minus_2;

    }

    
    template <std::size_t N, typename T>
    static constexpr T hermite(const T& x) noexcept {
        

        T p0 = 1.0;
        T p1 = 2.0 * x;

        if constexpr (N == 0)
            return p0;

        else if constexpr (N == 1)
            return p1;

        else {


            for (std::size_t index = 2; index <= N; ++index) {

                std::swap(p0, p1); 
                p1 = hermite_next(index, x, p0, p1); 

            }

            return p1;

        }

    }


    template <typename T>
    static constexpr T hermite(std::size_t N, const T& x) noexcept {
        

        T p0 = 1.0;
        T p1 = 2.0 * x;

        if (N == 0)
            return p0;

        else if (N == 1)
            return p1;

        else {


            for (std::size_t index = 2; index <= N; ++index) {

                std::swap(p0, p1); 
                p1 = hermite_next(index, x, p0, p1); 

            }

            return p1;

        }

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