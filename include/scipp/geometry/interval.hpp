/**
 * @file    geometry/interval.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-04-04
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief geometry namespace contains all the classes and functions of the geometry library
namespace scipp::geometry {
    

    template <typename T>
    struct is_ordinable : std::true_type {}; /// @todo

    template <typename T>
    inline static constexpr bool is_ordinable_v = is_ordinable<T>::value; 


    template <typename ARG_TYPE>
        requires (is_ordinable_v<ARG_TYPE>)
    struct interval : math::unary_function<ARG_TYPE, double> {


        using type = interval<ARG_TYPE>;

        using arg_type = ARG_TYPE;


        arg_type start, end;


        constexpr interval(const arg_type& A, const arg_type& B) noexcept {

            if (start > end) {  
                this->start = B; 
                this->end = A; 
            } else {
                this->start = A; 
                this->end = B; 
            }

        }
            

        constexpr interval(arg_type&& A, arg_type&& B) noexcept {

            if (start > end) {  
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


        constexpr arg_type operator()(const double& t) const override {

            if (t < 0.0 || t > 1.0) {

                std::cerr << "Cannot evaluate interval at t = " << t << '\n';
                throw std::out_of_range("t must be in the range [0, 1]");

            }

            return start + static_cast<physics::scalar_m>(t) * (end - start);

        }


    };


    template <typename T>
    struct is_interval : std::false_type {};

    template <typename ARG_TYPE>
    struct is_interval<interval<ARG_TYPE>> : std::true_type {};

    template <typename T>
    concept is_interval_v = is_interval<T>::value;

    
} // namespace scipp::geometry