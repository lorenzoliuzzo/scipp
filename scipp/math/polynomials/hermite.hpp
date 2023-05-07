/**
 * @file    math/polynomials/hermite.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace polynomials {


        template <size_t order>
        struct hermite : meta::unary_function<double, double> {


            inline static constexpr double hermite_next(uint N, const double& x, const double& H_n_minus_1, const double& H_n_minus_2) noexcept {


                return 2.0 * x * H_n_minus_1 - 2.0 * (N - 1.0) * H_n_minus_2;

            }


            constexpr double f(const double& x) const noexcept override {


                double p0 = 1.0;
                double p1 = x;

                if constexpr (order == 0)
                    return p0;

                else if constexpr (order == 1)
                    return p1;

                else {

                    for (size_t index = 2; index <= order; ++index) {

                        std::swap(p0, p1); 
                        p1 = hermite_next(index, x, p0, p1); 

                    }

                    return p1;

                }

            }


            // constexpr double f(const double& z, const double& x) const override {

            //     return op::exp(-op::square(z) + 2.0 * x * z); 

            // }


        };


    } // namespace polynomials
    

} // namespace scipp::math