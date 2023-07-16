/**
 * @file    scipp/math/calculus/interval.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the interval struct.
 * @date    2023-07-07
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {
    
    
    namespace calculus {


        template <typename T>
        struct interval {

            using value_t = T;

            value_t start, end;


            constexpr interval(const value_t& A, const value_t& B) noexcept {

                if (A > B) {  

                    this->start = B; 
                    this->end = A; 

                } else {

                    this->start = A; 
                    this->end = B; 

                }

            }

            constexpr interval(value_t&& A, value_t&& B) noexcept {

                if (A > B) {  

                    this->start = std::move(B); 
                    this->end = std::move(A); 

                } else {

                    this->start = std::move(A); 
                    this->end = std::move(B); 

                }

            }


            constexpr interval(const interval& other) noexcept : 

                start(other.start), 
                end(other.end) {}

            
            constexpr interval(interval&& other) noexcept : 

                start(std::move(other.start)), 
                end(std::move(other.end)) {}


            constexpr value_t operator()(double t) const {

                if (t < 0.0 || t > 1.0) {

                    std::cerr << "Cannot evaluate interval at t = " << t << '\n';
                    throw std::out_of_range("t must be in the range [0, 1]");

                }

                return this->start + t * (this->end - this->start);

            }


            constexpr value_t step(size_t N) const noexcept {
                    
                return (this->end - this->start) / static_cast<double>(N);
        
            }

            constexpr size_t steps(const value_t& step) const noexcept {
                    
                return op::abs((this->end - this->start) / step); 
        
            }


            constexpr value_t length() const noexcept {

                return op::abs(this->end - this->start);

            }


            constexpr bool contains(const value_t& x) const noexcept {

                return x >= this->start && x <= this->end;

            }
            

        }; // struct interval


    } // namespace calculus


} // namespace math