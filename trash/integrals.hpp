/**
 * @file    math/calculus/integrals.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-23
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace integrals {


        enum integration_method {

            rectangle = 0,
            trapexoid = 1, 
            midpoint = 2, 
            simpson = 3,
            // MC = 4
            
        }; 


        template <size_t steps, typename FUNCTION_TYPE> 
            // requires (is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto rectangle_integration(const FUNCTION_TYPE& f,
                                                    const interval<typename FUNCTION_TYPE::arg_t>& I) noexcept
            -> multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            typename FUNCTION_TYPE::result_t total_sum;
            constexpr auto N = static_cast<double>(steps); 

            for (size_t i{0}; i < steps; ++i) 
                total_sum += f(I(static_cast<double>(i) / N));

            return total_sum * (I.end - I.start) / N;

        }


        template <size_t steps, typename FUNCTION_TYPE> 
            requires (is_unary_function_v<typename FUNCTION_TYPE::function_t>)
        static constexpr auto trapexoid_integration(const FUNCTION_TYPE& f,
                                                    const interval<typename FUNCTION_TYPE::arg_t>& I) noexcept
            -> multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            typename FUNCTION_TYPE::result_t total_sum = (f(I(0.0)) + f(I(1.0))) / 2.;
            constexpr auto N = static_cast<double>(steps); 

            for (size_t i{1}; i < steps; ++i) 
                total_sum += f(I(static_cast<double>(i) / N)); 

            return total_sum * (I.end - I.start) / N; 

        }




        // template <typename FUNCTION_TYPE> 
        //     requires (is_unary_function_v<typename FUNCTION_TYPE::_t>)
        // static constexpr auto rectangle_integration(const FUNCTION_TYPE& f,
        //                                             const interval<typename FUNCTION_TYPE::arg_t>& I,
        //                                             const double& relative_error) noexcept
        //     -> multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

        //     typename FUNCTION_TYPE::result_t total_sum;

        //     for (size_t i{0}; i < steps; ++i) 
        //         total_sum += f(I(static_cast<double>(i) / steps));

        //     return total_sum * (I.end - I.start) / static_cast<double>(steps);

        // }


        // template <typename FUNCTION_TYPE> 
        //     requires (is_unary_function_v<typename FUNCTION_TYPE::_t>)
        // static constexpr auto trapexoid_integration(const FUNCTION_TYPE& f,
        //                                             const interval<typename FUNCTION_TYPE::arg_t>& I,
        //                                             const double& relative_error) noexcept
        //     -> multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

        //     typename FUNCTION_TYPE::result_t total_sum = (f(I(0.0)) + f(I(1.0))) / 2.;

        //     for (size_t i{1}; i < steps; ++i) 
        //         total_sum += f(I(static_cast<double>(i) / static_cast<double>(steps))); 

        //     return total_sum * (I.end - I.start) / static_cast<double>(steps); 

        // }


        // template <typename FUNCTION_TYPE> 
        //     requires (is_unary_function_v<typename FUNCTION_TYPE::_t>)
        // static constexpr auto midpoint_integration(const FUNCTION_TYPE& f, 
        //                                            const interval<typename FUNCTION_TYPE::arg_t>& I,
        //                                            const double& relative_error) noexcept
        //     -> multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

        //     typename FUNCTION_TYPE::result_t total_sum = f(I(0.0));

        //     for (size_t i{1}; i < steps; ++i)
        //         total_sum += f(I((static_cast<double>(i) + 0.5) / static_cast<double>(steps))); 

        //     return total_sum * (I.end - I.start) / static_cast<double>(steps); 

        // }
                

        template <typename FUNCTION_TYPE> 
            requires (is_unary_function_v<typename FUNCTION_TYPE::function_t>)
        static constexpr auto simpson_integration(const FUNCTION_TYPE& f, 
                                                  const interval<typename FUNCTION_TYPE::arg_t>& I,
                                                  const double& relative_error) noexcept
            -> multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            double steps = 2;
            multiply_t<typename FUNCTION_TYPE::result_t, 
                             typename FUNCTION_TYPE::arg_t> result{}, old_sum1{}, old_sum2{}, old_sum3{}, err{};

            while (true) {

                typename FUNCTION_TYPE::arg_t increment = (I.end - I.start) / steps;    
                old_sum3 = old_sum2;
                old_sum2 = old_sum1;
                old_sum1 = result;
                result = (f(I(0.0)) + f(I(1.0))) * increment / 3.;
                for (size_t i = 1; i < steps; ++i)
                    result += 2. * (1. + i % 2) * increment * f(I(static_cast<double>(i) / steps)) / 3.;
                
                err = 256. * op::abs(1024. * result - 1104. * old_sum1 + 81. * old_sum2 - old_sum3) / 240975.0; 
                
                if (err < relative_error * op::abs(result))
                    break;

                result = (1024. * result - 80. * old_sum1 + old_sum2) / 945.;
                steps *= 2;

            }

            std::cout << "steps needed for a precision of " << relative_error << ": " << steps << '\n'; 

            return result; 
                
        }


        template <integration_method method, size_t steps = 1000, typename FUNCTION_TYPE> 
            requires (is_unary_function_v<typename FUNCTION_TYPE::function_t>)
        inline static constexpr auto riemann(const FUNCTION_TYPE& f, 
                                      const typename FUNCTION_TYPE::arg_t& from_a,
                                      const typename FUNCTION_TYPE::arg_t& to_b)                                        
            -> multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            interval I(from_a, to_b); 

            if constexpr (method == integration_method::rectangle)
                return rectangle_integration<steps>(f, I);

            else if constexpr (method == integration_method::trapexoid)
                return trapexoid_integration<steps>(f, I);

            else if constexpr (method == integration_method::midpoint)
                return midpoint_integration<steps>(f, I);

            else if constexpr (method == integration_method::simpson)   
                return simpson_integration<steps>(f, I);
            
            else 
                throw std::runtime_error("The selected integration method is not implemented."); 

        }


        template <integration_method method, size_t steps = 1000, typename FUNCTION_TYPE> 
            requires (is_unary_function_v<typename FUNCTION_TYPE::function_t>)
        inline static constexpr auto riemann(const FUNCTION_TYPE& f, 
                                             const interval<typename FUNCTION_TYPE::arg_t>& I)
            -> multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            if constexpr (method == integration_method::rectangle)
                return rectangle_integration<steps>(f, I);

            else if constexpr (method == integration_method::trapexoid)
                return trapexoid_integration<steps>(f, I);

            else if constexpr (method == integration_method::midpoint)
                return midpoint_integration<steps>(f, I);

            else if constexpr (method == integration_method::simpson)   
                return simpson_integration<steps>(f, I);
            
            else 
                throw std::runtime_error("The selected integration method is not implemented."); 
        }


        template <integration_method method, typename FUNCTION_TYPE> 
            requires (is_unary_function_v<typename FUNCTION_TYPE::function_t>)
        inline static constexpr auto riemann(const FUNCTION_TYPE& f, 
                                             const typename FUNCTION_TYPE::arg_t& from_a,
                                             const typename FUNCTION_TYPE::arg_t& to_b,
                                             double relative_error = 1.e-6)                                        
            -> multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {
            
            if (relative_error <= 0.0)
                throw std::runtime_error("The relative error must be positive.");

            interval I(from_a, to_b); 

            if constexpr (method == integration_method::rectangle)
                return rectangle_integration(f, I, relative_error);

            else if constexpr (method == integration_method::trapexoid)
                return trapexoid_integration(f, I, relative_error);

            else if constexpr (method == integration_method::midpoint)
                return midpoint_integration(f, I, relative_error);

            else if constexpr (method == integration_method::simpson)   
                return simpson_integration(f, I, relative_error);
            
            else 
                throw std::runtime_error("The selected integration method is not implemented."); 

        }


        template <integration_method method, typename FUNCTION_TYPE> 
            requires (is_unary_function_v<typename FUNCTION_TYPE::function_t>)
        static constexpr auto riemann(const FUNCTION_TYPE& f, 
                                      const interval<typename FUNCTION_TYPE::arg_t>& I, 
                                      double relative_error = 1.e-6)
            -> multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            if (relative_error <= 0.0)
                throw std::runtime_error("The relative error must be positive.");

            if constexpr (method == integration_method::rectangle)
                return rectangle_integration(f, I, relative_error);

            else if constexpr (method == integration_method::trapexoid)
                return trapexoid_integration(f, I, relative_error);

            else if constexpr (method == integration_method::midpoint)
                return midpoint_integration(f, I, relative_error);

            else if constexpr (method == integration_method::simpson)   
                return simpson_integration(f, I, relative_error);
            
            else 
                throw std::runtime_error("The selected integration method is not implemented."); 
        }





        template <typename CURVE_TYPE>
            requires (is_curve_v<CURVE_TYPE>)
        inline static constexpr auto length(const CURVE_TYPE& curve, double der_incr = 1.e-6) noexcept {

            return curvilinear(functions::one<typename CURVE_TYPE::point_t>(), curve, der_incr);

        }


    } // namespace integrals
    

} // namespace scipp::math




    //         // template <typename MEAS1, typename MEAS2> 
    //         //     requires (physics::are_measurements_v<MEAS1, MEAS2>)
    //         // static constexpr auto midpoint_fixed(std::function<MEAS2(MEAS1)>& f, 
    //         //                                      const MEAS1 from_a,
    //         //                                      const MEAS1 to_b,
    //         //                                      const MEAS2& prec = MEAS2(1.e-6)) noexcept -> multiply_t<MEAS1, MEAS2> {
                
    //         //     size_t steps = 1;
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
    //         //                               const size_t& steps = 1000) noexcept -> multiply_t<MEAS1, MEAS2> {
                                                
    //         //     bool is_even = (steps % 2 == 0);
    //         //     const MEAS1 increment = op::abs(to_b - from_a) / static_cast<double>(steps);
    //         //     MEAS2 total_sum = (is_even ? (f(from_a) + f(to_b)) / 3. : 0.0);

    //         //     for (size_t i{1}; i < ((is_even) ? steps : steps + 1); ++i) 
    //         //         total_sum += 2. * (1 + i % 2) * (f(from_a + i * increment)) / 3.; 

    //         //     return (from_a < to_b) ? total_sum * increment : -total_sum * increment; 

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
