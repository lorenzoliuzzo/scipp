/**
 * @file    math/calculus/curves/interval.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-06-09
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {
    
    
    namespace curves {


        template <typename T>
        struct interval {


            using arg_t = T;

            using param_t = double; 

            arg_t start, end;


            constexpr interval(const arg_t& A, const arg_t& B) noexcept {

                if (A > B) {  

                    this->start = std::forward<arg_t>(B); 
                    this->end = std::forward<arg_t>(A); 

                } else {

                    this->start = std::forward<arg_t>(A); 
                    this->end = std::forward<arg_t>(B); 

                }

            }


            constexpr interval(const interval& other) noexcept : 

                start(other.start), 
                end(other.end) {}

            
            constexpr interval(interval&& other) noexcept : 

                start(std::move(other.start)), 
                end(std::move(other.end)) {}


            constexpr arg_t operator()(param_t&& t) const {

                if (t < 0.0 || t > 1.0) {

                    std::cerr << "Cannot evaluate interval at t = " << t << '\n';
                    throw std::out_of_range("t must be in the range [0, 1]");

                }

                return this->start + t * (this->end - this->start);

            }


            constexpr arg_t step(size_t N) const noexcept {
                    
                return (this->end - this->start) / static_cast<double>(N);
        
            }


            constexpr arg_t length() const noexcept {

                return this->end - this->start; 

            }


        }; // struct interval


        template <typename T>
            requires (is_number_v<T> || physics::is_generic_measurement_v<T>)
        struct interval<T> : curve<T, 1> {


            using _t = interval<T>;

            using arg_t = T;

            using param_t = double; 

            arg_t start, end;


            constexpr interval(arg_t A, arg_t B) noexcept {

                if (A > B) {  

                    this->start = std::forward<arg_t>(B); 
                    this->end = std::forward<arg_t>(A); 

                } else {

                    this->start = std::forward<arg_t>(A); 
                    this->end = std::forward<arg_t>(B); 

                }

            }


            constexpr interval(const interval& other) noexcept : 

                start(other.start), 
                end(other.end) {}

            
            constexpr interval(interval&& other) noexcept : 

                start(std::move(other.start)), 
                end(std::move(other.end)) {}


            constexpr arg_t operator()(param_t&& t) const {

                if (t < 0.0 || t > 1.0) {

                    std::cerr << "Cannot evaluate interval at t = " << t << '\n';
                    throw std::out_of_range("t must be in the range [0, 1]");

                }

                return this->start + t * (this->end - this->start);

            }


            constexpr arg_t step(size_t N) const noexcept {
                    
                return (this->end - this->start) / static_cast<double>(N);
        
            }


            constexpr arg_t length() const noexcept {

                return this->end - this->start; 

            }


        }; // struct interval


    } // namespace curves

    
} // namespace scipp::math