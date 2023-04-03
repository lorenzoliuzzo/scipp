/**
 * @file    geometry/linspace.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-01
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::geometry {


    /// @brief Create a linearly spaced vector
    /// @param start The starting value of the sequence
    /// @param stop The end value of the sequence
    /// @param num The number of samples to generate
    template <std::size_t DIM, typename MEAS_TYPE>
        requires physics::is_measurement_v<MEAS_TYPE>
    static constexpr vector<MEAS_TYPE, DIM> linspace(const MEAS_TYPE& start, const MEAS_TYPE& stop) noexcept {

        const MEAS_TYPE step = (stop - start) / (DIM - 1.);
        vector<MEAS_TYPE, DIM> result;

        for (std::size_t i{}; i < DIM; ++i)
            result[i] = start + i * step;

        return result;

    };
    

    // template <typename MEAS_TYPE>
    //     requires physics::is_measurement_v<MEAS_TYPE>
    // static constexpr vector<MEAS_TYPE, DIM> linspace(const MEAS_TYPE& start, const MEAS_TYPE& stop, std::size_t dim) noexcept {

    //     const MEAS_TYPE step = (stop - start) / (dim - 1.);
    //     vector<MEAS_TYPE, dim> result;

    //     for (std::size_t i{}; i < dim; ++i)
    //         result[i] = start + i * step;

    //     return result;

    // };


}