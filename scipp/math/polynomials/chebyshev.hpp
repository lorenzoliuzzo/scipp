/**
 * @file    math/polynomials/chebyshev.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace polynomials {


        template <uint type, uint order>
        struct chebyshev : meta::unary_function<double, double> {


            inline static constexpr double chebyshev_next(const double& x, const double& T_n_minus_1, const double& T_n_minus_2) noexcept {


                return 2.0 * x * T_n_minus_1 - T_n_minus_2;

            }


            constexpr double f(const double& x) const noexcept override {

                double p0 = 1.0;
                double p1 = x;

                if constexpr (type == 2)    
                    p1 *= 2.0; 

                if constexpr (order == 0)
                    return p0;

                else if constexpr (order == 1)
                    return p1;

                else {

                    for (std::size_t index = 2; index <= order; ++index) {

                        std::swap(p0, p1); 
                        p1 = chebyshev_next(x, p0, p1); 

                    }

                    return p1;

                }

            }


        };


    } // namespace polynomials


} // namespace scipp::math