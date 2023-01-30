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



        template <typename base>
        class meta_measurement {


            public:

                consteval meta_measurement() noexcept : 
                    
                    value_{0.} {}


                constexpr meta_measurement(const scalar& value) noexcept : 
                    
                    value_{value} {}


                template <typename units>
                constexpr meta_measurement(const scalar& value, const units& unit) noexcept 

                    requires (std::is_same_v<base, typename units::type>) :
                
                    value_{value * units::mult} {}


                // /**
                // * @brief Multiply this measurement by another measurement
                // * 
                // * @param other: measurement as r-value reference
                // * 
                // * @return constexpr measurement 
                // */
                // template <template <meta_unit_base UB2> class M>
                // constexpr auto operator*(const M& other) const noexcept { 
                    
                //     return meta_measurement<decltype(M::base_type() * base_type())>(this->value_ * other.value()); 
                
                // }


                constexpr scalar value() const noexcept { 
                    
                    return value_; 
                    
                }


            using type = base;

            scalar value_;


        }; // struct meta_measurement


        template <typename units>
        meta_measurement(const scalar&, const units&) -> meta_measurement<typename units::type>;


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