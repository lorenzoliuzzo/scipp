/**
 * @file    math/calculus/interval.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-04-26
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {
    

    // template <typename T>
    // concept ordinable { T x, y; x > y; y < x; }; /// @todo

    // template <typename T>
    // inline static constexpr bool is_ordinable_v = is_ordinable<T>::value; 


    template <typename ARG_TYPE>
        // requires (is_ordinable_v<ARG_TYPE>)
    struct interval {


        using _t = interval<ARG_TYPE>;

        using arg_t = ARG_TYPE;


        arg_t start, end;


        constexpr interval(const arg_t& A, const arg_t& B) noexcept {

            if (A > B) {  

                this->start = B; 
                this->end = A; 

            } else {

                this->start = A; 
                this->end = B; 

            }

        }
            
        constexpr interval(arg_t&& A, arg_t&& B) noexcept {

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


        constexpr arg_t operator()(const double& t) const {

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


    };


} // namespace scipp::math