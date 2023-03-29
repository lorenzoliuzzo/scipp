/**
 * @file    physics/units_litterals.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the units litterals
 * @date    2023-03-24
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    namespace units {
    

        inline constexpr auto operator""m(long double value) noexcept -> length_m {

            return length_m(value);

        }

        inline constexpr auto operator""km(long double value) noexcept -> length_m {

            return length_m(value, units::km);

        }

        inline constexpr auto operator""cm(long double value) noexcept -> length_m {

            return length_m(value, units::cm);

        }

        inline constexpr auto operator""mm(long double value) noexcept -> length_m {

            return length_m(value, units::mm);

        }

        inline constexpr auto operator""um(long double value) noexcept -> length_m {

            return length_m(value, units::um);

        }

        inline constexpr auto operator""nm(long double value) noexcept -> length_m {

            return length_m(value, units::nm);

        }


    } // namespace units


} // namespace scipp::physics