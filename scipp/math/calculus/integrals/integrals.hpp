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


        template <std::size_t steps, typename FUNCTION_TYPE> 
            // requires (meta::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto rectangle_integration(const FUNCTION_TYPE& f,
                                                    const interval<typename FUNCTION_TYPE::arg_t>& I) noexcept
            -> meta::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            typename FUNCTION_TYPE::result_t total_sum;
            constexpr auto N = static_cast<double>(steps); 

            for (size_t i{0}; i < steps; ++i) 
                total_sum += f(I(static_cast<double>(i) / N));

            return total_sum * (I.end - I.start) / N;

        }


        template <std::size_t steps, typename FUNCTION_TYPE> 
            requires (meta::is_unary_function_v<FUNCTION_TYPE>)
        static constexpr auto trapexoid_integration(const FUNCTION_TYPE& f,
                                                    const interval<typename FUNCTION_TYPE::arg_t>& I) noexcept
            -> meta::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            typename FUNCTION_TYPE::result_t total_sum = (f(I(0.0)) + f(I(1.0))) / 2.;
            constexpr auto N = static_cast<double>(steps); 

            for (size_t i{1}; i < steps; ++i) 
                total_sum += f(I(static_cast<double>(i) / N)); 

            return total_sum * (I.end - I.start) / N; 

        }


        template <std::size_t steps, typename FUNCTION_TYPE> 
            requires (meta::is_unary_function_v<FUNCTION_TYPE>)
        static constexpr auto midpoint_integration(const FUNCTION_TYPE& f, 
                                                   const interval<typename FUNCTION_TYPE::arg_t>& I) noexcept
            -> meta::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            typename FUNCTION_TYPE::result_t total_sum = f(I(0.0));
            constexpr auto N = static_cast<double>(steps); 

            for (std::size_t i{1}; i < steps; ++i)
                total_sum += f(I((static_cast<double>(i) + 0.5) / N)); 

            return total_sum * (I.end - I.start) / N; 

        }
                

        template <std::size_t steps, typename FUNCTION_TYPE> 
            requires (meta::is_unary_function_v<FUNCTION_TYPE>)
        static constexpr auto simpson_integration(const FUNCTION_TYPE& f, 
                                                  const interval<typename FUNCTION_TYPE::arg_t>& I) noexcept
            -> meta::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            typename FUNCTION_TYPE::result_t total_sum;
            constexpr auto N = static_cast<double>(steps); 

            if constexpr (steps % 2 == 0) 
                total_sum = (f(I(0.0)) + f(I(1.0))) / 3.;

            for (std::size_t i = 1; i < steps; ++i) 
                total_sum += 2. * (1. + i % 2) * f(I(static_cast<double>(i) / N)) / 3.;

            return total_sum * (I.end - I.start) / N; 

        }


        // template <typename FUNCTION_TYPE> 
        //     requires (meta::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        // static constexpr auto rectangle_integration(const FUNCTION_TYPE& f,
        //                                             const interval<typename FUNCTION_TYPE::arg_t>& I,
        //                                             const double& relative_error) noexcept
        //     -> meta::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

        //     typename FUNCTION_TYPE::result_t total_sum;

        //     for (size_t i{0}; i < steps; ++i) 
        //         total_sum += f(I(static_cast<double>(i) / steps));

        //     return total_sum * (I.end - I.start) / static_cast<double>(steps);

        // }


        // template <typename FUNCTION_TYPE> 
        //     requires (meta::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        // static constexpr auto trapexoid_integration(const FUNCTION_TYPE& f,
        //                                             const interval<typename FUNCTION_TYPE::arg_t>& I,
        //                                             const double& relative_error) noexcept
        //     -> meta::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

        //     typename FUNCTION_TYPE::result_t total_sum = (f(I(0.0)) + f(I(1.0))) / 2.;

        //     for (size_t i{1}; i < steps; ++i) 
        //         total_sum += f(I(static_cast<double>(i) / static_cast<double>(steps))); 

        //     return total_sum * (I.end - I.start) / static_cast<double>(steps); 

        // }


        // template <typename FUNCTION_TYPE> 
        //     requires (meta::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        // static constexpr auto midpoint_integration(const FUNCTION_TYPE& f, 
        //                                            const interval<typename FUNCTION_TYPE::arg_t>& I,
        //                                            const double& relative_error) noexcept
        //     -> meta::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

        //     typename FUNCTION_TYPE::result_t total_sum = f(I(0.0));

        //     for (std::size_t i{1}; i < steps; ++i)
        //         total_sum += f(I((static_cast<double>(i) + 0.5) / static_cast<double>(steps))); 

        //     return total_sum * (I.end - I.start) / static_cast<double>(steps); 

        // }
                

        template <typename FUNCTION_TYPE> 
            requires (meta::is_unary_function_v<FUNCTION_TYPE>)
        static constexpr auto simpson_integration(const FUNCTION_TYPE& f, 
                                                  const interval<typename FUNCTION_TYPE::arg_t>& I,
                                                  const double& relative_error) noexcept
            -> meta::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

            double steps = 2;
            meta::multiply_t<typename FUNCTION_TYPE::result_t, 
                             typename FUNCTION_TYPE::arg_t> result, old_sum1, old_sum2, old_sum3, err;

            while (true) {

                typename FUNCTION_TYPE::arg_t increment = (I.end - I.start) / steps;    
                old_sum3 = old_sum2;
                old_sum2 = old_sum1;
                old_sum1 = result;
                result = (f(I(0.0)) + f(I(1.0))) * increment / 3.;
                for (std::size_t i = 1; i < steps; ++i)
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


        template <integration_method method, std::size_t steps = 1000, typename FUNCTION_TYPE> 
            requires (meta::is_unary_function_v<FUNCTION_TYPE>)
        inline static constexpr auto riemann(const FUNCTION_TYPE& f, 
                                      const typename FUNCTION_TYPE::arg_t& from_a,
                                      const typename FUNCTION_TYPE::arg_t& to_b)                                        
            -> meta::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

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


        template <integration_method method, std::size_t steps = 1000, typename FUNCTION_TYPE> 
            requires (meta::is_unary_function_v<FUNCTION_TYPE>)
        inline static constexpr auto riemann(const FUNCTION_TYPE& f, 
                                             const interval<typename FUNCTION_TYPE::arg_t>& I)
            -> meta::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

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
            requires (meta::is_unary_function_v<FUNCTION_TYPE>)
        inline static constexpr auto riemann(const FUNCTION_TYPE& f, 
                                             const typename FUNCTION_TYPE::arg_t& from_a,
                                             const typename FUNCTION_TYPE::arg_t& to_b,
                                             double relative_error = 1.e-6)                                        
            -> meta::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {
            
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
            requires (meta::is_unary_function_v<FUNCTION_TYPE>)
        static constexpr auto riemann(const FUNCTION_TYPE& f, 
                                      const interval<typename FUNCTION_TYPE::arg_t>& I, 
                                      double relative_error = 1.e-6)
            -> meta::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {

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


        template <typename FUNCTION_TYPE, std::size_t steps = 1000> 
            requires (meta::is_unary_function_v<FUNCTION_TYPE>)
        static constexpr auto curvilinear(const FUNCTION_TYPE& func, 
                                          const curve<typename FUNCTION_TYPE::arg_t>& curve,
                                          double incr_der = 1.e-6) 

            -> meta::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t::measurement_t> {

            meta::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t::measurement_t> total_sum; 
                // auto d_curve = total_derivative(curve); // @todo
            for (std::size_t i{}; i < steps; ++i) {

                double t = static_cast<double>(i) / static_cast<double>(steps);
                auto x = curve(t);
                total_sum += func(x) * op::norm((curve(t + incr_der) - x) / incr_der);

            }

            return total_sum / static_cast<double>(steps); 

        }


        template <typename CURVE_TYPE>
            requires (is_curve_v<CURVE_TYPE>)
        inline static constexpr auto length(const CURVE_TYPE& curve, double der_incr = 1.e-6) noexcept {

            return curvilinear(meta::one<typename CURVE_TYPE::point_t>(), curve, der_incr);

        }




// # compute the n smallest eigenvalues of the symmetric tridiagonal matrix H
// # (defined from b as in eigpoly) using a Newton iteration
// # on det(H - lambda I).  Unlike eig, handles BigFloat.
// function eignewt(b,m,n)
//     # get initial guess from eig on Float64 matrix
//     H = SymTridiagonal(zeros(m), Float64[ b[i] for i in 1:m-1 ])
//     lambda0 = sort(eigvals(H))

//     lambda = Array{eltype(b)}(undef, n)
//     for i = 1:n
//         lambda[i] = lambda0[i]
//         for k = 1:1000
//             (p,pderiv) = eigpoly(b,lambda[i],m)
//             δλ = p / pderiv # may be NaN or Inf if pderiv underflows to 0.0
//             if isfinite(δλ)
//                 lambda[i] -= δλ
//                 if abs(δλ) ≤ 10 * eps(lambda[i])
//                     # do one final Newton iteration for luck and profit:
//                     δλ = (/)(eigpoly(b,lambda[i],m)...) # = p / pderiv
//                     isfinite(δλ) && (lambda[i] -= δλ)
//                 end
//             else
//                 break
//             end
//         end
//     end
//     return lambda

// # given an eigenvalue z and the matrix H(b) from above, return
// # the corresponding eigenvector, normalized to 1.
// function eigvec1(b,z::Number,m=length(b)+1)
//     # "cheat" and use the fact that our eigenvector v must have a
//     # nonzero first entries (since it is a quadrature weight), so we
//     # can set v[1] = 1 to solve for the rest of the components:.
//     v = Array{eltype(b)}(undef, m)
//     v[1] = 1
//     if m > 1
//         s = v[1]
//         v[2] = z * v[1] / b[1]
//         s += v[2]^2
//         for i = 3:m
//             v[i] = - (b[i-2]*v[i-2] - z*v[i-1]) / b[i-1]
//             s += v[i]^2
//         end
//         rmul!(v, 1 / sqrt(s))
//     end
//     return v



//         template <std::size_t N, typename FUNCTION_TYPE>
//             requires (is_function_v<FUNCTION_TYPE>)
//         inline static constexpr auto gauss_points(const FUNCTION_TYPE& func) noexcept {

//             using result_t = std::pair<geometry::vector<typename FUNCTION_TYPE::result_t, N>, 
//                                        geometry::vector<typename FUNCTION_TYPE::arg_t, N>; 

//             result_t result;
            
//             for (std::size_t i{}; i < N - 1; ++i)
//                 result[0][i] = static_cast<double>(i) / op::sqrt(4.0 * op::square(i) - 1.0); 

//             auto x = eigen_newton(b, N, N); 
            
//             for (std::size_t i{}; i < N; ++i)
//                 result[1][i] = 2.0 * op::square(eigein_vec1(b, x[i])[1]); 

//             return result; 

//         }
        

//         template <std::size_t N, typename FUNCTION_TYPE>
//             requires (is_function_v<FUNCTION_TYPE>)
//         inline static constexpr auto gauss_points(const FUNCTION_TYPE& func, 
//                                                   const interval<typename FUNCTION_TYPE::arg_t>& I) noexcept {

//             using result_t = std::pair<geometry::vector<typename FUNCTION_TYPE::result_t, N>, 
//                                        geometry::vector<typename FUNCTION_TYPE::arg_t, N>; 

//             typename FUNCTION_TYPE::arg_t h = (I.end - I.start) / 2.;
//             result_t gauss_mat = gauss_points<N>(func); 
//             gauss_mat[0] = result_t(I.start) + (gauss_mat[0] + result_t::one) * h;
//             gauss_mat[1] *= op::abs(h)
            
//             return gauss_mat;

//         }


//         template <std::size_t N, typename FUNCTION_TYPE>
//             requires (is_function_v<FUNCTION_TYPE>)
//         inline static constexpr auto gauss(const FUNCTION_TYPE& func, 
//                                            const interval<typename FUNCTION_TYPE::arg_t>& I) noexcept {

//             auto gauss_mat = gauss_points<N>(func, I);
//             return op::dot(gauss_mat[0], gauss_mat[1]);

//         }
                                        



    } // namespace integrals
    

} // namespace scipp::math




    //         // template <typename MEAS1, typename MEAS2> 
    //         //     requires (physics::are_measurements_v<MEAS1, MEAS2>)
    //         // static constexpr auto midpoint_fixed(std::function<MEAS2(MEAS1)>& f, 
    //         //                                      const MEAS1 from_a,
    //         //                                      const MEAS1 to_b,
    //         //                                      const MEAS2& prec = MEAS2(1.e-6)) noexcept -> meta::multiply_t<MEAS1, MEAS2> {
                
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
    //         //                               const std::size_t& steps = 1000) noexcept -> meta::multiply_t<MEAS1, MEAS2> {
                                                
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
