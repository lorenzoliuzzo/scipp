/**
 * @file    tools/io.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */





/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::tools {


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
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    inline static constexpr void print(const std::string& description, const MEAS_TYPE& other) noexcept {

        std::cout << description << ": " << other << '\n'; 

    }

    
    /// @brief Print the measurement with a specific unit of measure 
    /// @note The unit must be of the same base of the measurement
    template <typename MEAS_TYPE, typename UNIT_TYPE>
        requires (physics::is_measurement_v<MEAS_TYPE> && 
                  physics::is_unit_v<UNIT_TYPE> && 
                  physics::is_same_base_v<typename MEAS_TYPE::base, typename UNIT_TYPE::base>)
    inline static constexpr void print(const MEAS_TYPE& other, const UNIT_TYPE&, bool newline = true) noexcept {

        std::cout << other.value / static_cast<physics::scalar_m>(UNIT_TYPE::mult) << ' ' << UNIT_TYPE::to_string(); 
        if (newline)
            std::cout << '\n'; 

    }


    /// @brief Print the measurement with a specific unit of measure and a description
    /// @note The unit must be of the same base of the measurement
    template <typename MEAS_TYPE, typename UNIT_TYPE>
        requires (physics::is_measurement_v<MEAS_TYPE> && 
                  physics::is_unit_v<UNIT_TYPE> && 
                  physics::is_same_base_v<typename MEAS_TYPE::base, typename UNIT_TYPE::base>)
    inline static constexpr void print(const std::string& description, const MEAS_TYPE& other, const UNIT_TYPE&, bool newline = true) noexcept {

        std::cout << description << ": " << other / static_cast<physics::scalar_m>(UNIT_TYPE::mult); 
        if (newline)
            std::cout << '\n'; 

    }

    /// @brief Print the umeasurement with a specific unit of measure and a description
    /// @note The unit must be of the same base of the measurement
    template <typename MEAS_TYPE, typename UNIT_TYPE>
        requires (physics::is_umeasurement_v<MEAS_TYPE> && 
                  physics::is_unit_v<UNIT_TYPE> && 
                  physics::is_same_base_v<typename MEAS_TYPE::base, typename UNIT_TYPE::base>)
    static constexpr void print(const MEAS_TYPE& other, const UNIT_TYPE&, bool newline = true) noexcept {

        const double abs_value = std::fabs(other.value);

        // determine number of digits before decimal point in value
        const int n_val = (abs_value >= 1.0) ? 
                            std::ceil(std::log10(abs_value)) : 
                            ((abs_value == 0.0) ? 
                                1 : 
                                std::floor(std::log10(std::fabs(abs_value))) + 1); 

        // determine number of digits before decimal point in uncertainty
        int n_unc = (other.uncertainty >= 1.0) ? 
                            std::ceil(std::log10(other.uncertainty)) : 
                            ((other.uncertainty == 0.0) ? 
                                1 : 
                                std::floor(std::log10(std::fabs(other.uncertainty))) + 1); 

        // determine the number of decimal places to show in the uncertainty
        const int prec = std::max(0, std::min(6, -n_unc)) + 1; /// @todo

        // determine whether scientific notation is needed
        const bool scientific_notation_needed = abs_value >= 1e4 || abs_value <= 1e-4 || 
                                                other.uncertainty >= 1e4 || other.uncertainty <= 1e-4;

        // set the formatting of the output stream
        if (other.uncertainty == 0.0) {

            std::cout << std::fixed; 
            std::cout.precision(n_val); 
            std::cout << other.value << ' ' << UNIT_TYPE::to_string();

        } else if (scientific_notation_needed) {

            std::cout << std::scientific; 
            std::cout.precision(prec - 1); 
            std::cout << other.value << " ± ";
            std::cout.precision(0); 
            std::cout << other.uncertainty << ' ' << UNIT_TYPE::to_string();

        } else {

            std::cout << std::fixed;
            if (other.uncertainty >= 1.0) 
                std::cout.precision(0);
            else 
                std::cout.precision(std::max(0, std::min(6, -n_unc)) + 1);
            
            std::cout << other.value << " ± " << other.uncertainty << ' ' << UNIT_TYPE::to_string();
            
        }

        if (newline)
            std::cout << '\n';
    
    }

    /// @brief Print the umeasurement with a specific unit of measure and a description
    /// @note The unit must be of the same base of the measurement
    template <typename MEAS_TYPE, typename UNIT_TYPE>
        requires (physics::is_umeasurement_v<MEAS_TYPE> && 
                  physics::is_unit_v<UNIT_TYPE> && 
                  physics::is_same_base_v<typename MEAS_TYPE::base, typename UNIT_TYPE::base>)
    static constexpr void print(const std::string& description, const MEAS_TYPE& other, const UNIT_TYPE&, bool newline = true) noexcept {

        std::cout << description << ": "; 

        const MEAS_TYPE meas = other / UNIT_TYPE::mult;
        const double abs_value = std::fabs(meas.value);

        // determine number of digits before decimal point in value
        const int n_val = (abs_value >= 1.0) ? 
                            std::ceil(std::log10(abs_value)) : 
                            ((abs_value == 0.0) ? 
                                1 : 
                                std::floor(std::log10(std::fabs(abs_value))) + 1); 

        // determine number of digits before decimal point in uncertainty
        int n_unc = (meas.uncertainty >= 1.0) ? 
                            std::ceil(std::log10(meas.uncertainty)) : 
                            ((meas.uncertainty == 0.0) ? 
                                1 : 
                                std::floor(std::log10(std::fabs(meas.uncertainty))) + 1); 

        // determine the number of decimal places to show in the uncertainty
        const int prec = (std::fabs(n_unc) < std::fabs(n_val)) ? 1 : n_val - n_unc; 

        // determine whether scientific notation is needed
        const bool scientific_notation_needed = abs_value >= 1e4 || abs_value <= 1e-4 || 
                                                meas.uncertainty >= 1e4 || meas.uncertainty <= 1e-4;

        // set the formatting of the output stream
        if (meas.uncertainty == 0.0) {

            std::cout << std::fixed; 
            std::cout.precision(n_val); 
            std::cout << meas.value << ' ' << UNIT_TYPE::to_string();

        } else if (scientific_notation_needed) {

            std::cout << std::scientific; 
            std::cout.precision(prec - 1); 
            std::cout << meas.value << " ± ";
            std::cout.precision(0); 
            std::cout << meas.uncertainty << ' ' << UNIT_TYPE::to_string();

        } else {

            std::cout << std::fixed;
            if (meas.uncertainty >= 1.0) 
                std::cout.precision(0);
            else 
                std::cout.precision(std::max(0, std::min(6, -n_unc)) + 1);
            
            std::cout << meas.value << " ± " << meas.uncertainty << ' ' << UNIT_TYPE::to_string();
            
        }

        if (newline)
            std::cout << '\n';
    
    }



    template <typename MEAS_TYPE>
        requires (math::is_complex_measurement_v<MEAS_TYPE>)
    static constexpr void print(const MEAS_TYPE& other) noexcept {

        std::cout << other.real << " + i(" << other.imag << ")\n";

    }
    

    template <typename MEAS_TYPE>
        requires (math::is_dual_measurement_v<MEAS_TYPE>)
    static constexpr void print(const MEAS_TYPE& other) noexcept {

        std::cout << other.real << " + ε(" << other.imag << ")\n";

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
                  physics::is_same_base_v<typename VECTOR_TYPE::measurement_t::base, typename UNIT_TYPE::base>)
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
                  physics::is_same_base_v<typename VECTOR_TYPE::measurement_t::base, typename UNIT_TYPE::base>)
    inline static constexpr void print(const std::string& description, const VECTOR_TYPE& other, const UNIT_TYPE& units) noexcept {

        std::cout << description << ": [ "; 
        for (std::size_t i{}; i < VECTOR_TYPE::dim; ++i) {
            print(other.data[i], units, false); 
            std::cout << ((i < VECTOR_TYPE::dim - 1) ? ", " : " ]\n"); 
        }

    }


    /// @brief Print a geometry::matrix
    template <typename MATRIX_TYPE>
        requires (geometry::is_matrix_v<MATRIX_TYPE>)
    inline static constexpr void print(const MATRIX_TYPE& other) noexcept {

        for (std::size_t i{}; i < MATRIX_TYPE::columns; ++i)
            print(other.data[i]); 

    }


    /// @brief Print a geometry::matrix
    template <typename MATRIX_TYPE>
        requires (geometry::is_matrix_v<MATRIX_TYPE>)
    inline static constexpr void print(const std::string& description, const MATRIX_TYPE& other) noexcept {

        std::cout << description << ":\n"; 
        for (std::size_t i{}; i < MATRIX_TYPE::columns; ++i)
            print(other.data[i]); 

    }



    // /// @brief Print a geometry::MATRIX
    // template <typename MATRIX_TYPE>
    //     requires (geometry::is_matrix_v<MATRIX_TYPE>)
    // inline static constexpr void print(const MATRIX_TYPE& other) noexcept {

    //     std::cout << "[ "; 
        

    // }

    // /// @brief Print a geometry::MATRIX with a description
    // template <typename MATRIX_TYPE>
    //     requires (geometry::is_matrix_v<MATRIX_TYPE>)
    // inline static constexpr void print(const std::string& description, const MATRIX_TYPE& other) noexcept {

    //     std::cout << description << ": [ "; 
    //     for (std::size_t i{}; i < MATRIX_TYPE::dim; ++i)
    //         std::cout << other.data[i] << ((i < MATRIX_TYPE::dim - 1) ? ", " : " ]\n"); 

    // }


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