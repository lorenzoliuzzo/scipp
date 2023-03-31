/**
 * @file    tools/io.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-30
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once
#include <experimental/array>


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::tools {


    template <typename PRINTABLE_TYPE>
    inline static void print(const PRINTABLE_TYPE& printable) noexcept {

        std::cout << printable << '\n';

    }


    template <typename PRINTABLE_TYPE>
    inline static void print(const std::vector<PRINTABLE_TYPE>& printable) noexcept {

        for (const auto& element : printable)
            std::cout << element << '\n';

    }


    template <typename PRINTABLE_TYPE, std::size_t DIM>
    inline static void print(const geometry::vector<PRINTABLE_TYPE, DIM>& printable) noexcept {

        for (const auto& element : printable)
            std::cout << element << '\n';

    }


    template <typename PRINTABLE_TYPE>
    inline static void print(const std::string& description, const PRINTABLE_TYPE& printable) noexcept {

        std::cout << description << ": " << printable << '\n';

    }


    template <typename PRINTABLE_TYPE>
    inline static void print(const std::string& description, const std::vector<PRINTABLE_TYPE>& printable) noexcept {

        std::cout << description << ":\n";
        for (const auto& element : printable)
            std::cout << element << '\n';

    }


    template <typename MEAS_TYPE, std::size_t DIM>
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    geometry::vector<MEAS_TYPE, DIM> read_measurements(const std::string& file) {

        geometry::vector<MEAS_TYPE, DIM> vector; 

        std::ifstream infile(file);
        if (infile.fail())  
            throw std::runtime_error("Error! Cannot read file: " + file); 

        else for (std::size_t i{}; i < DIM; ++i) 
            infile >> vector[i];

        return vector;      

    }


    template <typename MEAS_TYPE>
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    auto read_measurements(const std::string& file) {


        MEAS_TYPE measurement; 
        std::vector<MEAS_TYPE> measurements;

        std::ifstream infile(file);
        if (infile.fail())  
            throw std::runtime_error("Error! Cannot read file: " + file); 

        else while (infile >> measurement)
            measurements.emplace_back(measurement);
        
        return measurements; 

    }

    
} // namespace scipp::tools