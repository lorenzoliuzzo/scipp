/**
 * @file    tools/io.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-01
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::tools {


    template <typename T, typename... Args>
    inline static constexpr bool is_one_of_v = (std::is_same_v<T, Args> || ...);


    /// @brief Print a message
    inline static void print(const std::string& message) noexcept {

        std::cout << message << '\n';

    }


    /// @brief Print a message with a description
    inline static void print(const std::string& description, const std::string& message) noexcept {

        std::cout << description << ": " << message << '\n';

    }


    /// @brief Print a number
    template <typename T>
        requires (std::is_arithmetic_v<T>)
    inline static constexpr void print(const T& number) noexcept {

        std::cout << number << '\n';

    }


    /// @brief Print a measurement 
    template <typename MEAS_TYPE>
        requires (physics::is_measurement_v<MEAS_TYPE>)
    inline static constexpr void print(const MEAS_TYPE& other) noexcept {

        std::cout << other.value << ' ' << MEAS_TYPE::base::to_string() << '\n'; 

    }
    

    /// @brief Print a measurement with a description
    template <typename MEAS_TYPE>
        requires (physics::is_measurement_v<MEAS_TYPE>)
    inline static constexpr void print(const std::string& description, const MEAS_TYPE& other) noexcept {

        std::cout << description << ": " << other.value << ' ' << MEAS_TYPE::base::to_string() << '\n'; 

    }

    
    /// @brief Print the measurement with a specific unit of measure 
    /// @note The unit must be of the same base of the measurement
    template <typename MEAS_TYPE, typename UNIT_TYPE>
        requires (physics::is_measurement_v<MEAS_TYPE> && 
                  physics::is_unit_v<UNIT_TYPE> && 
                  physics::is_same_base_v<typename MEAS_TYPE::base, typename UNIT_TYPE::base>)
    inline static constexpr void print(const MEAS_TYPE& other, const UNIT_TYPE& units, bool newline = true) noexcept {

        std::cout << other.value_as(units) << ' ' << UNIT_TYPE::to_string(); 
        if (newline)
            std::cout << '\n'; 

    }


    /// @brief Print the measurement with a specific unit of measure and a description
    /// @note The unit must be of the same base of the measurement
    template <typename MEAS_TYPE, typename UNIT_TYPE>
        requires (physics::is_measurement_v<MEAS_TYPE> && 
                  physics::is_unit_v<UNIT_TYPE> && 
                  physics::is_same_base_v<typename MEAS_TYPE::base, typename UNIT_TYPE::base>)
    inline static constexpr void print(const std::string& description, const MEAS_TYPE& other, const UNIT_TYPE& units, bool newline = true) noexcept {

        std::cout << description << ": " << other.value_as(units) << ' ' << UNIT_TYPE::to_string(); 
        if (newline)
            std::cout << '\n'; 

    }


    /// @brief Print a geometry::vector
    template <typename VECTOR_TYPE>
        requires (geometry::is_vector_v<VECTOR_TYPE>)
    inline static constexpr void print(const VECTOR_TYPE& other) noexcept {

        std::cout << "[ "; 
        for (std::size_t i{}; i < VECTOR_TYPE::dim; ++i)
            std::cout << other.data[i] << ((i < VECTOR_TYPE::dim - 1) ? ", " : " ]\n"); 

    }

    /// @brief Print a geometry::vector with a description
    template <typename VECTOR_TYPE>
        requires (geometry::is_vector_v<VECTOR_TYPE>)
    inline static constexpr void print(const std::string& description, const VECTOR_TYPE& other) noexcept {

        std::cout << description << ": [ "; 
        for (std::size_t i{}; i < VECTOR_TYPE::dim; ++i)
            std::cout << other.data[i] << ((i < VECTOR_TYPE::dim - 1) ? ", " : " ]\n"); 

    }


    /// @brief Print a geometry::vector in a specific unit of measure
    /// @note The unit must be of the same base of the measurement of the vector
    template <typename VECTOR_TYPE, typename UNIT_TYPE>
        requires (geometry::is_vector_v<VECTOR_TYPE> && 
                  physics::is_unit_v<UNIT_TYPE> && 
                  physics::is_same_base_v<typename VECTOR_TYPE::measurement_type::base, typename UNIT_TYPE::base>)
    inline static constexpr void print(const VECTOR_TYPE& other, const UNIT_TYPE& units) noexcept {

        std::cout << "[ "; 
        for (std::size_t i{}; i < VECTOR_TYPE::dim; ++i) {
            print(other.data[i], units, false); 
            std::cout << ((i < VECTOR_TYPE::dim - 1) ? ", " : " ]\n"); 
        }

    }

    /// @brief Print a geometry::vector in a specific unit of measure with a description
    /// @note The unit must be of the same base of the measurement of the vector
    template <typename VECTOR_TYPE, typename UNIT_TYPE>
        requires (geometry::is_vector_v<VECTOR_TYPE> && 
                  physics::is_unit_v<UNIT_TYPE> && 
                  physics::is_same_base_v<typename VECTOR_TYPE::measurement_type::base, typename UNIT_TYPE::base>)
    inline static constexpr void print(const std::string& description, const VECTOR_TYPE& other, const UNIT_TYPE& units) noexcept {

        std::cout << description << ": [ "; 
        for (std::size_t i{}; i < VECTOR_TYPE::dim; ++i) {
            print(other.data[i], units, false); 
            std::cout << ((i < VECTOR_TYPE::dim - 1) ? ", " : " ]\n"); 
        }

    }


    template <typename PRINTABLE_TYPE>
    inline static void print(const PRINTABLE_TYPE& printable) noexcept {

        std::cout << printable << '\n';

    }


    template <typename PRINTABLE_TYPE>
    inline static void print(const std::vector<PRINTABLE_TYPE>& printable) noexcept {

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