/**
 * @file    integral.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-02-05
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {


    /// @brief Class for evaluating integrals
    class integral {


        public:


            template <typename MEAS1, typename MEAS2> 
                requires (physics::are_measurements_v<MEAS1, MEAS2>)
            static constexpr auto midpoint(std::function<MEAS2(MEAS1)>& f, 
                                           const MEAS1 from_a,
                                           const MEAS1 to_b,
                                           const size_t& steps = 1000) noexcept -> physics::measurement<op::base_product_t<typename MEAS1::base, typename MEAS2::base>> {

                const MEAS1 increment = op::abs(to_b - from_a) / static_cast<double>(steps);
                MEAS2 total_sum = f(from_a);

                for (std::size_t i{1}; i < steps; ++i)
                    total_sum += f(from_a + (i + 0.5) * increment); 

                return (from_a < to_b) ? total_sum * increment : -total_sum * increment; 

            }


            template <typename MEAS1, typename MEAS2> 
                requires (physics::are_measurements_v<MEAS1, MEAS2>)
            static constexpr auto midpoint_fixed(std::function<MEAS2(MEAS1)>& f, 
                                                 const MEAS1 from_a,
                                                 const MEAS1 to_b,
                                                 const MEAS2& prec = MEAS2(1.e-6)) noexcept -> physics::measurement<op::base_product_t<typename MEAS1::base, typename MEAS2::base>> {
                
                std::size_t steps = 1;
                auto integral = midpoint(f, from_a, to_b, steps);

                decltype(integral) old_integral_1, old_integral_2, old_integral_3, error;
                bool loop = true;

                // #pragma omp parallel 
                {
                    do {
                        
                        // #pragma omp single
                        {
                            steps *= 2; 
                            old_integral_3 = old_integral_2;
                            old_integral_2 = old_integral_1;
                            old_integral_1 = integral;
                            integral = midpoint(f, from_a, to_b, steps);
                            error = 64. * math::op::abs(64. * integral - 84. * old_integral_1 + 21. * old_integral_2 - old_integral_3) / 2835.; // errore al sesto ordine
                            
                            // #pragma omp critical 
                            {
                                if (error < prec) 
                                    loop = false;
                            }
                        }

                    } while (loop);

                }

                integral = (4096. * integral - 1344. * old_integral_1 + 84. * old_integral_2 - old_integral_3) / 2835.; // integrale all'ottavo ordine

                return (from_a < to_b) ? integral : -integral;
            
            }


            template <typename MEAS1, typename MEAS2> 
                requires (physics::are_measurements_v<MEAS1, MEAS2>)
            static constexpr auto trapexoid(std::function<MEAS2(MEAS1)>& f, 
                                            const MEAS1 from_a,
                                            const MEAS1 to_b,
                                            const size_t& steps = 1000) noexcept -> physics::measurement<op::base_product_t<typename MEAS1::base, typename MEAS2::base>> {

                const MEAS1 increment = op::abs(to_b - from_a) / static_cast<double>(steps);
                MEAS2 total_sum = (f(from_a) + f(to_b)) / 2.;

                for (size_t i{1}; i < steps; ++i) 
                    total_sum += f(from_a + i * increment); 

                return (from_a < to_b) ? total_sum * increment : -total_sum * increment; 

            } 


            template <typename MEAS1, typename MEAS2> 
                requires (physics::are_measurements_v<MEAS1, MEAS2>)
            static constexpr auto simpson(std::function<MEAS2(MEAS1)>& f, 
                                          const MEAS1 from_a,
                                          const MEAS1 to_b,
                                          const size_t& steps = 1000) noexcept -> physics::measurement<op::base_product_t<typename MEAS1::base, typename MEAS2::base>> {
                                                
                bool is_even = (steps % 2 == 0);
                const MEAS1 increment = op::abs(to_b - from_a) / static_cast<double>(steps);
                MEAS2 total_sum = (is_even ? (f(from_a) + f(to_b)) / 3. : 0.0);

                for (size_t i{1}; i < ((is_even) ? steps : steps + 1); ++i) 
                    total_sum += 2. * (1 + i % 2) * (f(from_a + i * increment)) / 3.; 

                return (from_a < to_b) ? total_sum * increment : -total_sum * increment; 

            }


            // void trapexoid_fixed(const double& a, 
            //                         const double& b, 
            //                         const std::function<double(double)>& f, 
            //                         const MEAS2& prec = MEAS2(1.e-6)) {

            //     double old_integral_2{}, old_integral_3{};

            //     begin_integration(a, b, 2, f(a) + f(b) / 2. + f((a + b) / 2.)); 
            //     while (true) {

            //         old_integral_3 = old_integral_2;
            //         old_integral_2 = old_integral_;
            //         old_integral_ = integral_; 

            //         trapexoid(a_, b_, f, steps_ * 2);
            //         error_ = 64 * std::fabs(64 * integral_ - 84 * old_integral_ + 21 * old_integral_2 - old_integral_3) / 2835; // errore al sesto ordine

            //         if (error_ < prec) 
            //             break;

            //     }

            //     integral_ = (4096 * integral_ - 1344 * old_integral_ + 84 * old_integral_2 - old_integral_3) / 2835; // integrale all'ottavo ordine

            // }


            // void simpson_fixed(const double& a, 
            //                     const double& b, 
            //                     const std::function<double(double)>& f, 
            //                     const MEAS2& prec = MEAS2(1.e-6)) {

            //     double old_integral_2{}, old_integral_3{};
                
            //     begin_integration(a, b, 2, (f(a) + f(b)) / 3.); 
            //     while (true) {
            //         old_integral_3 = old_integral_2;
            //         old_integral_2 = old_integral_;
            //         old_integral_ = integral_; 

            //         simpson(a_, b_, f, steps_ * 2);
            //         error_ = 256 * std::fabs(1024 * integral_ - 1104 * old_integral_ + 81 * old_integral_2 - old_integral_3) / 240975;
                    
            //         if (error_ < prec) 
            //             break; 

            //     }

            //     integral_ = (1024 * integral_ - 80 * old_integral_ + old_integral_2) / 945; 
                
            // }


    }; // class integral


} // namespace scipp::math