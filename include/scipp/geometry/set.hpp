/**
 * @file    geometry/set.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-04-05
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief geometry namespace contains all the classes and functions of the geometry library
namespace scipp::geometry {
    
    
    template <typename T, std::size_t DIM>
    struct finite_set {


        using type = finite_set<T, DIM>;

        using data_type = std::array<T, DIM>; 

        using arg_type = T; 

        inline static constexpr std::size_t dimension = DIM;


        data_type data; 


        constexpr finite_set(const data_type& other) noexcept : 
            
            data(other) {}

        constexpr finite_set(data_type&& other) noexcept :

            data(std::move(other)) {}


        constexpr finite_set(const finite_set& other) noexcept : 
            
            data(other.data) {}

        constexpr finite_set(finite_set&& other) noexcept :

            data(std::move(other.data)) {}


        constexpr arg_type& operator[](const std::size_t& i) const noexcept {

            return data[i];

        }

        constexpr arg_type& operator[](const std::size_t& i) noexcept {

            return data[i];

        }


        // constexpr bool is_empty() const noexcept {

        //     return DIM == 0;

        // }


        // constexpr bool is_finite() const noexcept {

        //     return true;

        // }


        // constexpr bool is_infinite() const noexcept {

        //     return false;

        // }


        // constexpr bool is_bounded() const noexcept {

        //     return true;

        // }


        // constexpr bool is_unbounded() const noexcept {

        //     return false;

        // }


        // constexpr bool is_closed() const noexcept {

        //     return true;

        // }


        // constexpr bool is_open() const noexcept {

        //     return false;

        // }


        // constexpr bool is_connected() const noexcept {

        //     return true;

        // }


        // constexpr bool is_disconnected() const noexcept {

        //     return false;

        // }


        // constexpr bool is_compact() const noexcept {

        //     return true;

        // }


        // constexpr bool is_convex() const noexcept {

        //     return true;

        // }


        // constexpr bool is_simple() const noexcept {

        //     return true;

        // }



        

    }; 


    template <typename T, std::size_t DIM, typename PROPERTY>
    struct finite_set {

        using type = finite_set<T, DIM, PROPERTY>; 

        using arg_type = T; 


        inline static constexpr std::size_t dimension = DIM;


        data_type data;


        PROPERTY property;


        constexpr finite_set(const data_type& data, const PROPERTY& property) noexcept : 
            
            data(data), property(property) {}


        constexpr finite_set(data_type&& data, PROPERTY&& property) noexcept :

            data(std::move(data)), property(std::move(property)) {}


        constexpr T operator[](const std::size_t& i) const noexcept {

            return data[i];

        }


        constexpr T& operator[](const std::size_t& i) noexcept {

            return data[i];

        }


    }


    template <typename INTERVAL_TYPE, std::size_t N>    
        requires (is_interval_v<INTERVAL_TYPE>)
    constexpr finite_set<typename INTERVAL_TYPE::arg_type, N> linspace(const INTERVAL_TYPE& other) noexcept {

        const typename INTERVAL_TYPE::arg_type increment = math::op::abs(other.end - other.start) / static_cast<physics::scalar_m>(N); 
        std::array<typename INTERVAL_TYPE::arg_type, N> result; 
        for (std::size_t i{}; i < N; ++i)   
            result[i] = other.start + static_cast<physics::scalar_m>(i) * increment;

        return result;  

    }

    
} /// namespace scipp::geometry