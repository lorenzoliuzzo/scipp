/**
 * @file    math/polynomials/laguerre.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace polynomials {

        template <size_t order>
        struct laguerre : meta::unary_function<double, double> {


            inline static constexpr double laguerre_next(uint N, const double& x, const double& T_n_minus_1, const double& T_n_minus_2) noexcept {


                return - 2.0 * x * T_n_minus_1 + T_n_minus_2;

            }


            constexpr double f(const double& x) const noexcept override {


                double p0 = 1.0;
                double p1 = 1.0 - x;

                if constexpr (order == 0)
                    return p0;

                else if constexpr (order == 1)
                    return p1;

                else {

                    for (size_t index = 2; index <= order; ++index) {

                        std::swap(p0, p1); 
                        p1 = laguerre_next(index, x, p0, p1); 

                    }

                    return p1;

                }

            }


        };


    } // namespace polynomials


} // namespace scipp::math