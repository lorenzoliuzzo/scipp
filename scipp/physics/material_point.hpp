/**
 * @file    scipp/physics/material_point.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-07-08
 * 
 * @copyright Copyright (c) 2023
 */
 


namespace scipp::physics {


    template <size_t DIM>
    struct material_point {

        measurement<base::mass> m;
        std::array<measurement<base::length>, DIM> x;
        std::array<measurement<base::velocity>, DIM> v;

        constexpr material_point() noexcept : m{0.0}, x{0.0}, v{0.0} {}

        constexpr material_point(measurement<base::mass> m, 
                                 measurement<base::length> x[DIM], 
                                 measurement<base::velocity> v[DIM]) noexcept : m{m}, x{x}, v{v} {}

        constexpr material_point(measurement<base::mass> m, 
                                 std::array<measurement<base::length>, DIM> x, 
                                 std::array<measurement<base::velocity>, DIM> v) noexcept : m{m}, x{x.data()}, v{v.data()} {}

        constexpr material_point(measurement<base::mass> m, 
                                 std::array<measurement<base::length>, DIM> x) noexcept : m{m}, x{x}, v{} {}


        constexpr material_point(measurement<base::mass> m,
                                 measurement<base::length> x[DIM]) noexcept : m{m}, x{x}, v{} {}                               

    }; 


} // namespace scipp::physics