/**
 * @file    math/calculus/integrals.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace integrals {


        enum method {

            rectangle = 0,
            trapexoid = 1, 
            midpoint = 2, 
            simpson = 3,
            // MC = 4
            
        }; 


        template <typename FUNCTION_TYPE> 
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto rectangle_integration(const FUNCTION_TYPE& f, 
                                                   const typename FUNCTION_TYPE::arg_t& from_a,
                                                   const typename FUNCTION_TYPE::arg_t& to_b,
                                                   std::size_t steps) noexcept
            -> op::measurements_prod_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            const typename FUNCTION_TYPE::arg_t increment = op::abs(to_b - from_a) / static_cast<physics::scalar_m>(steps);
            typename FUNCTION_TYPE::result_t total_sum;

            for (size_t i{0}; i < steps; ++i) 
                total_sum += f(from_a + static_cast<physics::scalar_m>(i) * increment);

            return (from_a < to_b) ? total_sum * increment : -total_sum * increment;

        }


        template <typename FUNCTION_TYPE> 
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto trapexoid_integration(const FUNCTION_TYPE& f, 
                                                   const typename FUNCTION_TYPE::arg_t& from_a,
                                                   const typename FUNCTION_TYPE::arg_t& to_b,
                                                   std::size_t steps) noexcept
            -> op::measurements_prod_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            const typename FUNCTION_TYPE::arg_t increment = op::abs(to_b - from_a) / static_cast<physics::scalar_m>(steps);
            typename FUNCTION_TYPE::result_t total_sum = (f(from_a) + f(to_b)) / 2.;

            for (size_t i{1}; i < steps; ++i) 
                total_sum += f(from_a + static_cast<physics::scalar_m>(i) * increment); 

            return (from_a < to_b) ? total_sum * increment : -total_sum * increment; 

        }


        template <typename FUNCTION_TYPE> 
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto midpoint_integration(const FUNCTION_TYPE& f, 
                                                   const typename FUNCTION_TYPE::arg_t& from_a,
                                                   const typename FUNCTION_TYPE::arg_t& to_b,
                                                   std::size_t steps) noexcept
            -> op::measurements_prod_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            const typename FUNCTION_TYPE::arg_t increment = op::abs(to_b - from_a) / static_cast<physics::scalar_m>(steps);
            typename FUNCTION_TYPE::result_t total_sum = f(from_a);

            for (std::size_t i{1}; i < steps; ++i)
                total_sum += f(from_a + static_cast<physics::scalar_m>(static_cast<double>(i) + 0.5) * increment); 

            return (from_a < to_b) ? total_sum * increment : -total_sum * increment; 

        }


        template <typename FUNCTION_TYPE> 
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto simpson_integration(const FUNCTION_TYPE& f, 
                                                  const typename FUNCTION_TYPE::arg_t& from_a,
                                                  const typename FUNCTION_TYPE::arg_t& to_b,
                                                  std::size_t steps) noexcept
            -> op::measurements_prod_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            const typename FUNCTION_TYPE::arg_t increment = op::abs(to_b - from_a) / static_cast<physics::scalar_m>(steps);
            typename FUNCTION_TYPE::result_t total_sum = ((steps % 2 == 0) ? (f(from_a) + f(to_b)) / 3.0 : 0.0);

            for (std::size_t i = 1; i < steps; ++i) 
                total_sum += 2.0 * (1.0 + i % 2) * f(from_a + static_cast<physics::scalar_m>(i) * increment) / 3.0;

            return (from_a < to_b) ? total_sum * increment : -total_sum * increment; 

        }


        template <typename FUNCTION_TYPE> 
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto riemann(const FUNCTION_TYPE& f, 
                                      const typename FUNCTION_TYPE::arg_t& from_a,
                                      const typename FUNCTION_TYPE::arg_t& to_b,
                                      method integration_method,
                                      std::size_t steps = 1000)                                        
            -> op::measurements_prod_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            switch (integration_method) {

                case rectangle:
                    return rectangle_integration(f, from_a, to_b, steps);
                    break; 

                case trapexoid:
                    return trapexoid_integration(f, from_a, to_b, steps);
                    break;

                case midpoint:
                    return midpoint_integration(f, from_a, to_b, steps);
                    break;

                case simpson:   
                    return simpson_integration(f, from_a, to_b, steps);
                    break;
            
                default:
                    break;
            }

            throw std::runtime_error("The selected integration method is not implemented."); 

        }



        template <typename FUNCTION_TYPE> 
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto midpoint_integration(const FUNCTION_TYPE& f, 
                                                   const interval<typename FUNCTION_TYPE::arg_t>& I,
                                                   std::size_t steps) noexcept
            -> op::measurements_prod_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            const typename FUNCTION_TYPE::arg_t increment = I.step(steps);
            typename FUNCTION_TYPE::result_t total_sum = f(I(0));

            for (std::size_t i{1}; i < steps; ++i)
                total_sum += f(I(0) + static_cast<physics::scalar_m>(static_cast<double>(i) + 0.5) * increment); 

            return total_sum * increment; 

        }
                

        template <typename FUNCTION_TYPE> 
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto simpson_integration(const FUNCTION_TYPE& f, 
                                                  const interval<typename FUNCTION_TYPE::arg_t>& I,
                                                  std::size_t steps) noexcept
            -> op::measurements_prod_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            const typename FUNCTION_TYPE::arg_t increment = I.step(steps);
            typename FUNCTION_TYPE::result_t total_sum = ((steps % 2 == 0) ? (f(I(0)) + f(I(1))) / 3. : 0.0);

            for (std::size_t i = 1; i < steps; ++i) 
                total_sum += 2. * (1. + i % 2) * f(I(0) + static_cast<physics::scalar_m>(i) * increment) / 3.;

            return total_sum * increment; 

        }


        template <typename FUNCTION_TYPE> 
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto riemann(const FUNCTION_TYPE& f, 
                                        const interval<typename FUNCTION_TYPE::arg_t>& interval,
                                        method integration_method,
                                        std::size_t steps = 1000)
            -> op::measurements_prod_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            switch (integration_method) {

                case midpoint:
                    return midpoint_integration(f, interval, steps);
                    break;

                case rectangle:
                    break; 

                case trapexoid:
                {
                    const typename FUNCTION_TYPE::arg_t increment = op::abs(interval(1) - interval(0)) / static_cast<double>(steps);
                    typename FUNCTION_TYPE::result_t total_sum = (f(interval(0)) + f(interval(1))) / 2.;

                    for (size_t i{1}; i < steps; ++i) 
                        total_sum += f(interval(0) + static_cast<physics::scalar_m>(i) * increment); 

                    return total_sum * increment;  
                    break;

                }

                case simpson:  
                    return simpson_integration(f, interval, steps); 
                    break;
            
                default:
                    break;
            }

            throw std::runtime_error("The selected integration method is not implemented."); 

        }


        template <typename FUNCTION_TYPE> 
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto curvilinear(const FUNCTION_TYPE& f, 
                                          const curve<typename FUNCTION_TYPE::arg_t>& curve,
                                          std::size_t steps = 1000, 
                                          physics::scalar_m incr_der = 1.e-6) 

            -> op::measurements_prod_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t::measurement_type> {

            op::measurements_prod_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t::measurement_type> total_sum; 

            // auto d_curve = total_derivative(curve); // @todo
            for (std::size_t i{}; i < steps; ++i) {

                physics::scalar_m t = static_cast<double>(i) / static_cast<double>(steps);

                total_sum += f(curve(t)) * op::norm((curve(t + incr_der) - curve(t)) / incr_der);

            }

            return total_sum / static_cast<physics::scalar_m>(steps); 

        }


        template <typename CURVE_TYPE> 
            requires (math::is_curve_v<CURVE_TYPE>)
        static constexpr auto length(const CURVE_TYPE& curve, std::size_t steps = 1000, physics::scalar_m incr_der = 1.e-6) noexcept 
            -> typename CURVE_TYPE::point_type::measurement_type {

            typename CURVE_TYPE::point_type::measurement_type total_sum; 

            // auto d_curve = total_derivative(curve); // @todo
            for (std::size_t i{}; i < steps; ++i) {

                physics::scalar_m t = static_cast<double>(i) / static_cast<double>(steps);

                total_sum += op::norm((curve(t + incr_der) - curve(t)) / incr_der);

            }

            return total_sum / static_cast<physics::scalar_m>(steps);        

        }


        // template <typename FUNCTION_TYPE> 
        //     requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        // static constexpr auto volumetric(const FUNCTION_TYPE& f, 
        //                                  const curve<typename FUNCTION_TYPE::arg_t>& curve,
        //                                  std::size_t steps = 1000, 
        //                                  physics::scalar_m incr_der = 1.e-6) 

        //     -> op::measurements_prod_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t::measurement_type> {

        //     op::measurements_prod_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t::measurement_type> total_sum; 



        // }



    } // namespace integrals
    

} // namespace scipp::math




    //         // template <typename MEAS1, typename MEAS2> 
    //         //     requires (physics::are_measurements_v<MEAS1, MEAS2>)
    //         // static constexpr auto midpoint_fixed(std::function<MEAS2(MEAS1)>& f, 
    //         //                                      const MEAS1 from_a,
    //         //                                      const MEAS1 to_b,
    //         //                                      const MEAS2& prec = MEAS2(1.e-6)) noexcept -> op::measurements_prod_t<MEAS1, MEAS2> {
                
    //         //     std::size_t steps = 1;
    //         //     auto integral = midpoint(f, from_a, to_b, steps);

    //         //     decltype(integral) old_integral_1, old_integral_2, old_integral_3, error;
    //         //     bool loop = true;

    //         //     // #pragma omp parallel 
    //         //     {
    //         //         do {
                        
    //         //             // #pragma omp single
    //         //             {
    //         //                 steps *= 2; 
    //         //                 old_integral_3 = old_integral_2;
    //         //                 old_integral_2 = old_integral_1;
    //         //                 old_integral_1 = integral;
    //         //                 integral = midpoint(f, from_a, to_b, steps);
    //         //                 error = 64. * math::op::abs(64. * integral - 84. * old_integral_1 + 21. * old_integral_2 - old_integral_3) / 2835.; // errore al sesto ordine
                            
    //         //                 // #pragma omp critical 
    //         //                 {
    //         //                     if (error < prec) 
    //         //                         loop = false;
    //         //                 }
    //         //             }

    //         //         } while (loop);

    //         //     }

    //         //     integral = (4096. * integral - 1344. * old_integral_1 + 84. * old_integral_2 - old_integral_3) / 2835.; // integrale all'ottavo ordine

    //         //     return (from_a < to_b) ? integral : -integral;
            
    //         // }




    //         // template <typename MEAS1, typename MEAS2> 
    //         //     requires (physics::are_measurements_v<MEAS1, MEAS2>)
    //         // static constexpr auto simpson(std::function<MEAS2(MEAS1)>& f, 
    //         //                               const MEAS1 from_a,
    //         //                               const MEAS1 to_b,
    //         //                               const std::size_t& steps = 1000) noexcept -> op::measurements_prod_t<MEAS1, MEAS2> {
                                                
    //         //     bool is_even = (steps % 2 == 0);
    //         //     const MEAS1 increment = op::abs(to_b - from_a) / static_cast<physics::scalar_m>(steps);
    //         //     MEAS2 total_sum = (is_even ? (f(from_a) + f(to_b)) / 3. : 0.0);

    //         //     for (size_t i{1}; i < ((is_even) ? steps : steps + 1); ++i) 
    //         //         total_sum += 2. * (1 + i % 2) * (f(from_a + i * increment)) / 3.; 

    //         //     return (from_a < to_b) ? total_sum * increment : -total_sum * increment; 

    //         // }



    //         // template <typename FUNCTION_TYPE> 
    //         //     requires (math::is_binary_function_v<typename FUNCTION_TYPE::_t>)
    //         // static constexpr auto simpson(FUNCTION_TYPE&& f, 
    //         //                                typename FUNCTION_TYPE::first_arg_t fixed_arg,
    //         //                                typename FUNCTION_TYPE::second_arg_t from_a,
    //         //                                typename FUNCTION_TYPE::second_arg_t to_b,
    //         //                                typename FUNCTION_TYPE::result_t prec) noexcept
                
    //         //     -> op::measurements_prod_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::second_arg_t> {

    //         // }



    //         // void trapexoid_fixed(const double& a, 
    //         //                         const double& b, 
    //         //                         const std::function<double(double)>& f, 
    //         //                         const MEAS2& prec = MEAS2(1.e-6)) {

    //         //     double old_integral_2{}, old_integral_3{};

    //         //     begin_integration(a, b, 2, f(a) + f(b) / 2. + f((a + b) / 2.)); 
    //         //     while (true) {

    //         //         old_integral_3 = old_integral_2;
    //         //         old_integral_2 = old_integral_;
    //         //         old_integral_ = integral_; 

    //         //         trapexoid(a_, b_, f, steps_ * 2);
    //         //         error_ = 64 * std::fabs(64 * integral_ - 84 * old_integral_ + 21 * old_integral_2 - old_integral_3) / 2835; // errore al sesto ordine

    //         //         if (error_ < prec) 
    //         //             break;

    //         //     }

    //         //     integral_ = (4096 * integral_ - 1344 * old_integral_ + 84 * old_integral_2 - old_integral_3) / 2835; // integrale all'ottavo ordine

    //         // }




    // }; // class integral
