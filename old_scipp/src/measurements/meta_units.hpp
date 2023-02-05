/**
 * @file    unit_base.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-21
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief measurements namespace contains all the classes and functions of the measurements library
namespace scipp::measurements {

    
    /// @brief units namespace contains all the units of the measurements library
    namespace units {




        template <typename base, std::size_t DIM>
        class vector2 {


            public:

            constexpr vector2() noexcept : data_{meta_measurement<base>{}} {}

            constexpr vector2(const std::array<meta_measurement<base>, DIM>& data) noexcept : data_{data} {}



            using base_type = base::type;

            std::array<meta_measurement<base>, DIM> data_;


        }; // struct vector2


        template <typename base, std::size_t DIM>
        vector2(const std::array<meta_measurement<base>, DIM>&) -> vector2<base, DIM>;



    } // namespace units


} // namespace scipp::measurements