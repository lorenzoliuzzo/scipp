/**
 * @file    integral.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-22
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {



    /// @brief Class for evaluating integrals
    class integral2 {


        public:


            static scalar midpoint(const std::function<scalar(scalar)>& f, 
                                             const scalar& from_a,
                                             const scalar& to_b,
                                             const size_t& steps = 1000) {

                scalar increment = std::fabs(to_b - from_a) / steps;
                scalar total_sum = 0.0;

                #pragma omp parallel for
                for (std::size_t i = 0; i < steps; ++i)
                    #pragma omp critical
                    total_sum += f(from_a + (i + 0.5) * increment); 

                return (from_a < to_b) ? total_sum * increment : -total_sum * increment;

            }


            template <class measurement_t>
            static constexpr auto midpoint(const std::function<auto(measurement_t)>& f, 
                                           const measurement_t& from_a,
                                           const measurement_t& to_b,
                                           const size_t& steps = 1000) {

                measurement_t increment = op::abs(to_b - from_a) / steps;
                auto total_sum = f(from_a);

                #pragma omp parallel for
                for (std::size_t i = 1; i < steps; ++i)
                    #pragma omp critical
                    total_sum += f(from_a + (i + 0.5) * increment); 

                return (from_a < to_b) ? total_sum * increment : -total_sum * increment;

            }


            template <unit_base UB, unit_base UB2>
            static constexpr measurement<UB * UB2> midpoint_fixed(const std::function<measurement<UB2>(measurement<UB>)>& f, 
                                                                  const measurement<UB>& from_a,
                                                                  const measurement<UB>& to_b,
                                                                  const scalar& prec = 1.e-6) { 

                                                        
                measurement<UB * UB2> integral, old_integral_1, old_integral_2, old_integral_3, error;
                std::size_t steps = 1;

                #pragma omp parallel 
                {
                    while (true) {
                        
                        #pragma omp single
                        {
                            old_integral_3 = old_integral_2;
                            old_integral_2 = old_integral_1;
                            old_integral_1 = integral;
                            integral = midpoint(f, from_a, to_b, steps * 2);
                            error = 64. * math::op::abs(64. * integral - 84. * old_integral_1 + 21. * old_integral_2 - old_integral_3) / 2835.; // errore al sesto ordine
                            steps *= 2; 
                        }

                        #pragma omp barrier
                        if (error < prec) 
                            break;

                    }

                }

                integral = (4096. * integral - 1344. * old_integral_1 + 84. * old_integral_2 - old_integral_3) / 2835.; // integrale all'ottavo ordine

                return (from_a < to_b) ? integral : -integral;
            
            }



            // }


    }; // class integral2



    /// @brief Class for evaluating integrals
    class integral {


        public: 

        // =============================================
        // constructors
        // =============================================

            /// @brief Default constructor
            constexpr integral() noexcept {}

            /// @brief Default destructor
            ~integral() = default; 

        
        // =============================================
        // get methods
        // =============================================

            /**
                * @brief Get the first integral limit
                * 
                * @return constexpr scalar 
                */
            constexpr scalar a() const { 
                
                return a_; 
                
            }


            /**
                * @brief Get the second integral limit
                * 
                * @return constexpr scalar 
                */
            constexpr scalar b() const { 
                
                return b_; 
                
            }


            /**
                * @brief Get the sign of the integral
                * 
                * @return constexpr int 
                */
            constexpr int sign() const { 
                
                return sign_; 
                
            }


            /**
                * @brief Get the number of points used to evaluate the integral
                * 
                * @return constexpr size_t 
                */
            constexpr size_t steps() const { 
                
                return steps_; 
                
            }


            /**
                * @brief Get the number of blocks used to evaluate the integral
                * 
                * @return constexpr scalar 
                */
            constexpr scalar h() const { 
                
                return h_; 
                
            }


            /**
                * @brief Get the sum of the function values
                * 
                * @return constexpr scalar 
                */
            constexpr scalar sum() const { 
                
                return sum_; 
                
            }


            /**
                * @brief Get the result of the integral
                * 
                * @return constexpr scalar 
                */
            constexpr scalar result() const { 
                
                return integral_; 
                
            }


            /**
                * @brief Get the error of the integral
                * 
                * @return constexpr scalar 
                */
            constexpr scalar error() const { 
                
                return error_; 
                
            }



        // =============================================
        // print methods
        // =============================================

            void print_result(const scalar& precision = 1.e-6) {

                std::cout << "integral of f(x) in [" << a_ << ", " << b_ << "] = " << std::setprecision(precision) << integral_ << "\n";

            }

            void print_error(const scalar& precision = 1.e-6) {

                std::cout << "error = " << std::setprecision(precision) << error_ << "\n";

            }        

            void print_integral(const scalar& precision = 1.e-6) {

                print_result(precision); 
                print_error(precision); 

            }
            
            
        // =============================================
        // integration methods
        // =============================================

            constexpr void midpoint(const scalar& a, 
                                    const scalar& b, 
                                    const std::function<scalar(scalar)>& f, 
                                    const size_t& n = 1000) {

                begin_integration(a, b, n); 
                for (size_t i{}; i < steps_; i++)
                    sum_ += f(a_ + (i + 0.5) * h_); 

                integral_ = sum_ * h_; 

            }


            constexpr void midpoint_fixed(const scalar& a, 
                                                 const scalar& b, 
                                                 const std::function<scalar(scalar)>& f, 
                                                 const scalar& prec = 1.e-6) {

                scalar old_integral_2{}, old_integral_3{};

                begin_integration(a, b, 1); 
                while (true) {

                    old_integral_3 = old_integral_2;
                    old_integral_2 = old_integral_;
                    old_integral_ = integral_; 

                    midpoint(a_, b_, f, steps_ * 2);
                    error_ = 64 * std::fabs(64 * integral_ - 84 * old_integral_ + 21 * old_integral_2 - old_integral_3) / 2835; // errore al sesto ordine
                    
                    if (error_ < prec) 
                        break;

                }  

                integral_ = (4096 * integral_ - 1344 * old_integral_ + 84 * old_integral_2 - old_integral_3) / 2835; // integrale all'ottavo ordine

            }

            
            void trapexoid(const scalar& a, 
                            const scalar& b, 
                            const std::function<scalar(scalar)>& f, 
                            const size_t& n = 1000) {

                begin_integration(a, b, n, (f(a) + f(b)) / 2.);
                for (size_t i{1}; i < steps_; i++) 
                    sum_ += f(a_ + i * h_); 

                integral_ = sum_ * h_; 

            } 


            void trapexoid_fixed(const scalar& a, 
                                    const scalar& b, 
                                    const std::function<scalar(scalar)>& f, 
                                    const scalar& prec = 1.e-6) {

                scalar old_integral_2{}, old_integral_3{};

                begin_integration(a, b, 2, f(a) + f(b) / 2. + f((a + b) / 2.)); 
                while (true) {

                    old_integral_3 = old_integral_2;
                    old_integral_2 = old_integral_;
                    old_integral_ = integral_; 

                    trapexoid(a_, b_, f, steps_ * 2);
                    error_ = 64 * std::fabs(64 * integral_ - 84 * old_integral_ + 21 * old_integral_2 - old_integral_3) / 2835; // errore al sesto ordine

                    if (error_ < prec) 
                        break;

                }

                integral_ = (4096 * integral_ - 1344 * old_integral_ + 84 * old_integral_2 - old_integral_3) / 2835; // integrale all'ottavo ordine

            }


            void simpson(const scalar& a, 
                            const scalar& b, 
                            const std::function<scalar(scalar)>& f, 
                            const size_t& n = 1000) {

                if (n % 2 == 0) 
                    begin_integration(a, b, n, (f(a) + f(b)) / 3.);
                else 
                    begin_integration(a, b, n + 1);  

                for (size_t i{1}; i < steps_; i++) 
                    sum_ += 2 * (1 + i % 2) * (f(a_ + i * h_)) / 3.; 

                integral_ = sum_ * h_; 

            }


            void simpson_fixed(const scalar& a, 
                                const scalar& b, 
                                const std::function<scalar(scalar)>& f, 
                                const scalar& prec = 1.e-6) {

                scalar old_integral_2{}, old_integral_3{};
                
                begin_integration(a, b, 2, (f(a) + f(b)) / 3.); 
                while (true) {
                    old_integral_3 = old_integral_2;
                    old_integral_2 = old_integral_;
                    old_integral_ = integral_; 

                    simpson(a_, b_, f, steps_ * 2);
                    error_ = 256 * op::abs(1024 * integral_ - 1104 * old_integral_ + 81 * old_integral_2 - old_integral_3) / 240975;
                    
                    if (error_ < prec) 
                        break; 

                }

                integral_ = (1024 * integral_ - 80 * old_integral_ + old_integral_2) / 945; 
                
            }


            // void mean(const scalar& a, 
            //             const scalar& b, 
            //             const std::function<scalar(scalar)>& f, 
            //             const size_t& n = 1000) {

            //     begin_integration(a, b, n); 
            //     for (size_t i{}; i < n; i ++) 
            //         sum_ += f(rg_.unif(a, b)); 

            //     integral_ = (b_ - a_) * sum_ / steps_; 

            // }


            // void mean_fixed(const scalar& a, 
            //                 const scalar& b, 
            //                 const std::function<scalar(scalar)>& f, 
            //                 const scalar& prec = 1.e-6) {

            //     std::vector<scalar> k{};
            //     for (unsigned i{}; i < 10000; i++) {
            //         mean(a, b, f);
            //         k.emplace_back(integral_); 
            //     }
            //     scalar k_mean = sqrt(100) * statistics::sd(k); 
                
            //     mean(a, b, f, static_cast<uint>(std::pow(k_mean / prec, 2))); 

            // }

    
            // constexpr void hit_or_miss(const scalar& a, 
            //                             const scalar& b, 
            //                             const std::function<scalar(scalar)>& f, 
            //                             const scalar& fmax, 
            //                             const size_t& n = 1000) {

            //     scalar x{}, y{}; 
            //     size_t hits{};

            //     begin_integration(a, b, n); 
            //     for (size_t i{}; i < n; i ++) {

            //         x = rg_.unif(a, b); 
            //         y = rg_.unif(0., fmax);  

            //         if (y <= f(x)) 
            //             hits++; 
            //     }
            //     integral_ = (b_ - a_) * fmax * hits / n; 

            // }


            // void hit_or_miss_fixed(const scalar& a, 
            //                         const scalar& b, 
            //                         const std::function<scalar(scalar)>& f, 
            //                         const scalar& fmax, 
            //                         const scalar& prec = 1.e-6) {

            //     std::vector<scalar> k{};
            //     for (unsigned i{}; i < 10000; i++) {
            //         hit_or_miss(a, b, f, fmax);
            //         k.emplace_back(integral_); 
            //     }
            //     scalar k_mean = sqrt(100) * statistics::sd(k); 
            //     size_t N = static_cast<size_t>(std::pow(k_mean / prec, 2)); 
            //     hit_or_miss(a, b, f, fmax, N); 

            // }


        private: 

        // =============================================
        // private methods
        // =============================================

            constexpr void steps(const size_t& n) { 

                steps_ = n; 
                h_ = std::fabs(b_ - a_) / steps_;

            }        

            
            constexpr void check_range() { 
                
                sign_ = (a_ == b_ ? 0. : (b_ > a_ ? 1. : -1)); 
                
            }
            
            
            constexpr void sum(const scalar& sum) { 
                
                sum_ = sum; 
            
            }

            
            constexpr void reset_integral() { 
                
                integral_ = 0; 
            
            }    

            
            constexpr void begin_integration(const scalar& a, 
                                                const scalar& b, 
                                                const size_t& n = 1000, 
                                                const scalar& sum0 = 0) {

                a_ = a; 
                b_ = b; 
                check_range(); 
                steps(n);
                reset_integral(); 
                sum(sum0); 

            }


        // =============================================
        // class members
        // =============================================

            scalar a_{}, b_{}; ///< integration limits
            
            scalar h_{}; ///< step size
            
            size_t steps_{}; /// number of steps

            int32_t sign_{}; /// sign of the integral

            scalar sum_{}, integral_{}, old_integral_{}, error_{}; ///< integral and error

            // random_generator rg_; ///< random number generator


    }; // class integral


} // namespace scipp::math