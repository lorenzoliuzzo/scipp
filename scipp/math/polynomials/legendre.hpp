/**
 * @file    math/polynomials/legendre.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace polynomials {


        template <std::size_t order>
        struct legendre : meta::unary_function<double, double> {


            inline static constexpr double legendre_next(uint n, const double& x, const double& P_n_minus_1, const double& P_n_minus_2) noexcept {

                return ((2.0 * n + 1.0) * x * P_n_minus_1 - n * P_n_minus_2) / (n + 1.0);

            }


            constexpr double f(const double& x) const noexcept override {

                double p0 = 1.0;
                double p1 = x;

                if constexpr (order == 0)
                    return p0;

                else if constexpr (order == 1)
                    return p1;

                else {

                    for (std::size_t index = 2; index <= order; ++index) {

                        std::swap(p0, p1); 
                        p1 = legendre_next(index, x, p0, p1); 

                    }

                    return p1;

                }

            }


        };


    } // namespace polynomials
    

} // namespace scipp::math