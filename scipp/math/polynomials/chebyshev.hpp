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


        template <size_t TYPE, size_t ORDER>
            requires (TYPE != 0 && TYPE < 5)
        struct chebyshev : meta::unary_function<double, double> {

            
            inline static constexpr size_t type = TYPE;

            inline static constexpr size_t order = ORDER;


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

                    for (size_t index = 2; index <= order; ++index) {

                        std::swap(p0, p1); 
                        p1 = chebyshev_next(x, p0, p1); 

                    }

                    return p1;

                }

            }


            static constexpr auto weighted_nodes() noexcept 
                -> std::pair<geometry::vector<double, order>, geometry::vector<double, order>> {
                
                std::array<double, order> weights, nodes;

                if constexpr (type == 1) {

                    weights.fill(constants::pi / static_cast<double>(order));
                    for (size_t i{}; i < order; ++i)
                        nodes[i] = op::cos((2. * i - 1.) * constants::pi / (2. * order)); 

                } else if constexpr (type == 2) {

                    for (size_t i{}; i < order; ++i) {

                        const double x = constants::pi / (order + 1);
                        nodes[i] = op::cos(i * x); 
                        weights[i] = x * op::square(op::sin(i * x));

                    }

                } else if constexpr (type == 3) {

                    for (size_t i{}; i < order; ++i) {

                        const double x = constants::pi / (order + 0.5);
                        nodes[i] = op::cos((i - 0.5) * x);
                        weights[i] = 2.0 * x * op::square(op::cos(0.5 * (i - 0.5) * x));

                    }


                } else {

                    for (size_t i{}; i < order; ++i) {

                        const double x = constants::pi / (order + 0.5);
                        nodes[i] = op::cos(i * x);
                        weights[i] = 2.0 * x * op::square(0.5 * op::sin((i * x)));

                    }

                } 

                return std::make_pair(nodes, weights);

            }


            static constexpr double weight_f(const double& x) noexcept {

                if constexpr (type == 1)
                    return 1.0 / std::sqrt(1.0 - op::square(x));

                else if constexpr (type == 2)
                    return std::sqrt(1.0 - op::square(x));

                else if constexpr (type == 3)
                    return std::sqrt((1. + x) / (1. - x));

                else
                    return std::sqrt((1. - x) / (1. + x));

            }


        };


    } // namespace polynomials


} // namespace scipp::math