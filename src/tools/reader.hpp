/**
 * @file    tools/reader.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-22
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::tools {


    template <typename MEAS_TYPE, std::size_t DIM>
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    geometry::vector<MEAS_TYPE, DIM> read_measurements(const std::string& file) {

        std::ifstream infile(file);
        geometry::vector<MEAS_TYPE, DIM> vector; 

        for (std::size_t i{}; i < DIM; ++i) 
            infile >> vector[i];

        return vector;      

    }


    template <typename MEAS_TYPE>
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    std::vector<MEAS_TYPE> read_measurements(const std::string& file) {

        std::ifstream infile(file);
        MEAS_TYPE measurement; 
        std::vector<MEAS_TYPE> measurements;

        while (infile >> measurement)
            measurements.emplace_back(measurement);
        
        return measurements;

    }



} // namespace scipp::tools