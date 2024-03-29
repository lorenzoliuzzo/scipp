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


    /// @brief Print a number
    template <bool NEWLINE = true, typename T>
        requires (std::is_arithmetic_v<T>)
    inline static void print(const T& x) noexcept {

        std::cout << x; 
        if constexpr (NEWLINE) 
            std::cout << '\n';
        else 
            std::cout << ' '; 

    }
    

    /// @brief Print a number with a description
    template <bool NEWLINE = true, typename T>
        requires (std::is_arithmetic_v<T>)
    inline static void print(const std::string& description, const T& x) noexcept {

        std::cout << description << x; 
        if constexpr (NEWLINE) 
            std::cout << '\n';
        else 
            std::cout << ' '; 

    }


    /// @brief Print a number with a description
    template <bool NEWLINE = true, typename T>
        requires (std::is_arithmetic_v<T>)
    inline static void print(const T& x, const std::string& description) noexcept {

        std::cout << x << description; 
        if constexpr (NEWLINE) 
            std::cout << '\n';
        else 
            std::cout << ' '; 

    }


    /// @brief Print a measurement 
    template <bool NEWLINE = true, typename MEAS_TYPE>
        requires physics::is_measurement_v<MEAS_TYPE>
    inline static constexpr void print(const MEAS_TYPE& other) noexcept {

        std::cout << other.value << MEAS_TYPE::base_t::to_string(); 
        if constexpr (NEWLINE) 
            std::cout << '\n';
        else 
            std::cout << ' '; 

    }
    

    /// @brief Print a measurement with a description
    template <bool NEWLINE = true, typename MEAS_TYPE>
        requires physics::is_generic_measurement_v<MEAS_TYPE>
    inline static constexpr void print(const std::string& description, const MEAS_TYPE& other) noexcept {

        std::cout << description << other.value << MEAS_TYPE::base_t::to_string(); 
        if constexpr (NEWLINE) 
            std::cout << '\n';
        else 
            std::cout << ' '; 

    }


    // /// @brief Print a measurement with a fixed number of digits and a description
    // template <typename PREFIX_TYPE, typename MEAS_TYPE, bool NEWLINE = true>
    //     requires (physics::is_prefix_v<PREFIX_TYPE> && (physics::is_generic_measurement_v<MEAS_TYPE> || math::is_number_v<MEAS_TYPE>))
    // inline static constexpr void print(const std::string& message, const MEAS_TYPE& other) noexcept {

    //     double fixed_precision;

    //     if constexpr (PREFIX_TYPE::num < PREFIX_TYPE::den)
    //         fixed_precision = std::log10(static_cast<double>(PREFIX_TYPE::den) / static_cast<double>(PREFIX_TYPE::num));
    //     else
    //         fixed_precision = std::log10(static_cast<double>(PREFIX_TYPE::num) / static_cast<double>(PREFIX_TYPE::den));

    //     std::cout << message; 
    //     std::cout.precision(fixed_precision);
    //     std::cout << std::fixed << other << std::defaultfloat; 
    //     std::cout.precision(6);
    //     if constexpr (NEWLINE) 
    //         std::cout << '\n';
    //     else 
    //         std::cout << ' '; 

    // }

    // /// @brief Print a measurement with a fixed number of digits
    // template <typename PREFIX_TYPE, typename MEAS_TYPE, bool NEWLINE = true>
    //     requires (physics::is_prefix_v<PREFIX_TYPE> && (physics::is_generic_measurement_v<MEAS_TYPE> || math::is_number_v<MEAS_TYPE>))
    // inline static constexpr void print(const MEAS_TYPE& other) noexcept {

    //     double fixed_precision;

    //     if constexpr (PREFIX_TYPE::num < PREFIX_TYPE::den)
    //         fixed_precision = std::log10(static_cast<double>(PREFIX_TYPE::den) / static_cast<double>(PREFIX_TYPE::num));
    //     else
    //         fixed_precision = std::log10(static_cast<double>(PREFIX_TYPE::num) / static_cast<double>(PREFIX_TYPE::den));

    //     std::cout.precision(fixed_precision);
    //     std::cout << std::fixed << other << std::defaultfloat; 
    //     std::cout.precision(6);
    //     if constexpr (NEWLINE) 
    //         std::cout << '\n';
    //     else 
    //         std::cout << ' '; 

    // }


    /// @brief Print the measurement with a specific number of digits
    template <typename PREFIX_TYPE, bool NEWLINE = true, typename MEAS_TYPE>
        requires (physics::is_prefix_v<PREFIX_TYPE> && physics::is_measurement_v<MEAS_TYPE>)
    inline static constexpr void print(const MEAS_TYPE& other) noexcept {

        constexpr int digits = std::log10(static_cast<double>(PREFIX_TYPE::den) / static_cast<double>(PREFIX_TYPE::num));
        const auto rounded_value = std::round(other.value * std::pow(10.0, digits)) / std::pow(10.0, digits);
        std::cout << rounded_value << MEAS_TYPE::base_t::to_string(); 
        if constexpr (NEWLINE)
            std::cout << '\n'; 
        
    }


    /// @brief Print the measurement with a specific number of digits and a description
    template <typename PREFIX_TYPE, bool NEWLINE = true, typename MEAS_TYPE>
        requires (physics::is_prefix_v<PREFIX_TYPE> && physics::is_measurement_v<MEAS_TYPE>)
    inline static constexpr void print(const std::string& description, const MEAS_TYPE& other) noexcept {

        constexpr int digits = std::log10(static_cast<double>(PREFIX_TYPE::den) / static_cast<double>(PREFIX_TYPE::num));
        const auto rounded_value = std::round(other.value * std::pow(10.0, digits)) / std::pow(10.0, digits);
        std::cout << description << rounded_value << MEAS_TYPE::base_t::to_string(); 
        if constexpr (NEWLINE)
            std::cout << '\n'; 

    }

    /// @brief Print the measurement with a specific number of digits
    template <typename PREFIX_TYPE, bool NEWLINE = true, typename T>
        requires physics::is_prefix_v<PREFIX_TYPE>
    inline static constexpr void print(const math::calculus::variable<T>& other) noexcept {

        print<PREFIX_TYPE>(math::calculus::val(other));

    }


    /// @brief Print the measurement with a specific number of digits and a description
    template <typename PREFIX_TYPE, bool NEWLINE = true, typename T>
        requires physics::is_prefix_v<PREFIX_TYPE>
    inline static constexpr void print(const std::string& description, const math::calculus::variable<T>& other) noexcept {

        print<PREFIX_TYPE>(description, math::calculus::val(other));

    }

    
    /// @brief Print the measurement with a specific unit of measure 
    /// @note The unit must be of the same base of the measurement
    template <typename UNIT_TYPE, bool NEWLINE = true, typename MEAS_TYPE>
        requires (physics::is_unit_v<UNIT_TYPE> && physics::is_measurement_v<MEAS_TYPE> && 
                  physics::is_same_base_v<typename MEAS_TYPE::base_t, typename UNIT_TYPE::base_t>)
    inline static constexpr void print(const MEAS_TYPE& other) noexcept {

        using prefix_t = typename UNIT_TYPE::prefix_t;
        constexpr auto factor = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den);
        std::cout << other.value / factor << UNIT_TYPE::to_string(); 
        if constexpr (NEWLINE)
            std::cout << '\n'; 

    }


    /// @brief Print the measurement with a specific unit of measure and a description
    /// @note The unit must be of the same base of the measurement
    template <bool NEWLINE = true, typename UNIT_TYPE, typename MEAS_TYPE>
        requires (physics::is_unit_v<UNIT_TYPE> && physics::is_measurement_v<MEAS_TYPE> && 
                  physics::is_same_base_v<typename MEAS_TYPE::base_t, typename UNIT_TYPE::base_t>)
    inline static constexpr void print(const std::string& description, const MEAS_TYPE& other) noexcept {

        using prefix_t = typename UNIT_TYPE::prefix_t;
        constexpr auto factor = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den);
        std::cout << description << other.value / factor << UNIT_TYPE::to_string(); 
        if constexpr (NEWLINE)
            std::cout << '\n'; 

    }

    
    /// @brief Print the measurement with a specific unit of measure 
    /// @note The unit must be of the same base of the measurement
    template <bool NEWLINE = true, typename MEAS_TYPE, typename UNIT_TYPE>
        requires (physics::is_measurement_v<MEAS_TYPE> && physics::is_unit_v<UNIT_TYPE> && 
                  physics::is_same_base_v<typename MEAS_TYPE::base_t, typename UNIT_TYPE::base_t>)
    inline static constexpr void print(const MEAS_TYPE& other, const UNIT_TYPE&) noexcept {

        using prefix_t = typename UNIT_TYPE::prefix_t;
        constexpr auto factor = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den);
        std::cout << other.value / factor << UNIT_TYPE::to_string(); 
        if constexpr (NEWLINE)
            std::cout << '\n'; 

    }


    /// @brief Print the measurement with a specific unit of measure and a description
    /// @note The unit must be of the same base of the measurement
    template <bool NEWLINE = true, typename MEAS_TYPE, typename UNIT_TYPE>
        requires (physics::is_measurement_v<MEAS_TYPE> && physics::is_unit_v<UNIT_TYPE> && 
                  physics::is_same_base_v<typename MEAS_TYPE::base_t, typename UNIT_TYPE::base_t>)
    inline static constexpr void print(const std::string& description, const MEAS_TYPE& other, const UNIT_TYPE&) noexcept {

        using prefix_t = typename UNIT_TYPE::prefix_t;
        constexpr auto factor = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den);
        std::cout << description << other.value / factor << UNIT_TYPE::to_string(); 
        if constexpr (NEWLINE)
            std::cout << '\n'; 

    }

    // /// @brief Print the umeasurement with a specific unit of measure and a description
    // /// @note The unit must be of the same base of the measurement
    // template <bool NEWLINE = true, typename MEAS_TYPE, typename UNIT_TYPE>
    //     requires (physics::is_umeasurement_v<MEAS_TYPE> && 
    //               physics::is_unit_v<UNIT_TYPE> && 
    //               physics::is_same_base_v<typename MEAS_TYPE::base_t, typename UNIT_TYPE::base_t>)
    // static constexpr void print(const MEAS_TYPE& other, const UNIT_TYPE&) noexcept {

    //     const double abs_value = std::fabs(other.value);

    //     // determine number of digits before decimal point in value
    //     const int n_val = (abs_value >= 1.0) ? 
    //                         std::ceil(std::log10(abs_value)) : 
    //                         ((abs_value == 0.0) ? 
    //                             1 : 
    //                             std::floor(std::log10(std::fabs(abs_value))) + 1); 

    //     // determine number of digits before decimal point in uncertainty
    //     int n_unc = (other.uncertainty >= 1.0) ? 
    //                         std::ceil(std::log10(other.uncertainty)) : 
    //                         ((other.uncertainty == 0.0) ? 
    //                             1 : 
    //                             std::floor(std::log10(std::fabs(other.uncertainty))) + 1); 

    //     // determine the number of decimal places to show in the uncertainty
    //     const int prec = std::max(0, std::min(6, -n_unc)) + 1; /// @todo

    //     // determine whether scientific notation is needed
    //     const bool scientific_notation_needed = abs_value >= 1e4 || abs_value <= 1e-4 || 
    //                                             other.uncertainty >= 1e4 || other.uncertainty <= 1e-4;

    //     // set the formatting of the output stream
    //     if (other.uncertainty == 0.0) {

    //         std::cout << std::fixed; 
    //         std::cout.precision(n_val); 
    //         std::cout << other.value << UNIT_TYPE::to_string();

    //     } else if (scientific_notation_needed) {

    //         std::cout << std::scientific; 
    //         std::cout.precision(prec - 1); 
    //         std::cout << other.value << " ± ";
    //         std::cout.precision(0); 
    //         std::cout << other.uncertainty << UNIT_TYPE::to_string();

    //     } else {

    //         std::cout << std::fixed;
    //         if (other.uncertainty >= 1.0) 
    //             std::cout.precision(0);
    //         else 
    //             std::cout.precision(std::max(0, std::min(6, -n_unc)) + 1);
            
    //         std::cout << other.value << " ± " << other.uncertainty << UNIT_TYPE::to_string();
            
    //     }

    //     if constexpr (NEWLINE)
    //         std::cout << '\n'; 
    
    // }

    // /// @brief Print the umeasurement with a specific unit of measure and a description
    // /// @note The unit must be of the same base of the measurement
    // template <bool NEWLINE = true, typename MEAS_TYPE, typename UNIT_TYPE>
    //     requires (physics::is_umeasurement_v<MEAS_TYPE> && 
    //               physics::is_unit_v<UNIT_TYPE> && 
    //               physics::is_same_base_v<typename MEAS_TYPE::base_t, typename UNIT_TYPE::base_t>)
    // static constexpr void print(const std::string& description, const MEAS_TYPE& other, const UNIT_TYPE&) noexcept {

    //     std::cout << description; 
    //     using prefix_t = typename UNIT_TYPE::prefix_t;
    //     constexpr auto factor = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den);

    //     const MEAS_TYPE meas = other / factor;
    //     const double abs_value = std::fabs(meas.value);

    //     // determine number of digits before decimal point in value
    //     const int n_val = (abs_value >= 1.0) ? 
    //                         std::ceil(std::log10(abs_value)) : 
    //                         ((abs_value == 0.0) ? 
    //                             1 : 
    //                             std::floor(std::log10(std::fabs(abs_value))) + 1); 

    //     // determine number of digits before decimal point in uncertainty
    //     int n_unc = (meas.uncertainty >= 1.0) ? 
    //                         std::ceil(std::log10(meas.uncertainty)) : 
    //                         ((meas.uncertainty == 0.0) ? 
    //                             1 : 
    //                             std::floor(std::log10(std::fabs(meas.uncertainty))) + 1); 

    //     // determine the number of decimal places to show in the uncertainty
    //     const int prec = (std::fabs(n_unc) < std::fabs(n_val)) ? 1 : n_val - n_unc; 

    //     // determine whether scientific notation is needed
    //     const bool scientific_notation_needed = abs_value >= 1e4 || abs_value <= 1e-4 || 
    //                                             meas.uncertainty >= 1e4 || meas.uncertainty <= 1e-4;

    //     // set the formatting of the output stream
    //     if (meas.uncertainty == 0.0) {

    //         std::cout << std::fixed; 
    //         std::cout.precision(n_val); 
    //         std::cout << meas.value << UNIT_TYPE::to_string();

    //     } else if (scientific_notation_needed) {

    //         std::cout << std::scientific; 
    //         std::cout.precision(prec - 1); 
    //         std::cout << meas.value << " ± ";
    //         std::cout.precision(0); 
    //         std::cout << meas.uncertainty << UNIT_TYPE::to_string();

    //     } else {

    //         std::cout << std::fixed;
    //         if (meas.uncertainty >= 1.0) 
    //             std::cout.precision(0);
    //         else 
    //             std::cout.precision(std::max(0, std::min(6, -n_unc)) + 1);
            
    //         std::cout << meas.value << " ± " << meas.uncertainty << UNIT_TYPE::to_string();
            
    //     }

    //     if constexpr (NEWLINE)
    //         std::cout << '\n'; 
    
    // }



    template <typename MEAS_TYPE>
        requires (math::is_complex_v<MEAS_TYPE>)
    static constexpr void print(const MEAS_TYPE& other) noexcept {

        std::cout << other.real << " + i(" << other.imag << ")\n";

    }
    
    template <typename MEAS_TYPE>
        requires (math::is_dual_v<MEAS_TYPE>)
    static constexpr void print(const MEAS_TYPE& other) noexcept {

        std::cout << other.real << " + ε(" << other.imag << ")\n";

    }
    

    // template <typename MEAS_TYPE>
    //     requires (math::is_dual_measurement_v<MEAS_TYPE>)
    // static constexpr void print(const MEAS_TYPE& other) noexcept {

    //     std::cout << other.real << " + ε(" << other.imag << ")\n";

    // }


    /// @brief Print a geometry::vector
    template <bool NEWLINE = true, typename VECTOR_TYPE>
        requires geometry::is_vector_v<VECTOR_TYPE>
    inline static constexpr void print(const VECTOR_TYPE& other) noexcept {

        std::cout << "[ "; 
        meta::for_<VECTOR_TYPE::dim>([&](auto i) constexpr {

            print<false>(other.data[i]);

            if constexpr (i.index == VECTOR_TYPE::dim - 1) {
                std::cout << ']';
                if constexpr (NEWLINE)
                    std::cout << '\n';
            }

            else 
                std::cout << ", ";      

        }); 

    }

    /// @brief Print a geometry::vector with a description
    template <bool NEWLINE = true, typename VECTOR_TYPE>
        requires geometry::is_vector_v<VECTOR_TYPE>
    inline static constexpr void print(const std::string& description, const VECTOR_TYPE& other) noexcept {

        std::cout << description << "[ "; 
        meta::for_<VECTOR_TYPE::dim>([&](auto i) constexpr {

            print<false>(other.data[i]);

            if constexpr (i.index == VECTOR_TYPE::dim - 1) {
                std::cout << ']';
                if constexpr (NEWLINE)
                    std::cout << '\n';
            }

            else 
                std::cout << ", ";           

        }); 

    }


    /// @brief Print a geometry::vector in a specific unit of measure
    /// @note The unit must be of the same base of the measurement of the vector
    template <bool NEWLINE = true, typename VECTOR_TYPE, typename UNIT_TYPE>
        requires (geometry::is_vector_v<VECTOR_TYPE> && 
                  physics::is_unit_v<UNIT_TYPE> && 
                  physics::is_same_base_v<typename VECTOR_TYPE::measurement_t::base, typename UNIT_TYPE::base_t>)
    inline static constexpr void print(const VECTOR_TYPE& other, const UNIT_TYPE& units) noexcept {

        std::cout << "[ "; 
        for (size_t i{}; i < VECTOR_TYPE::dim; ++i) {
            print<false>(other.data[i], units); 
            std::cout << ((i < VECTOR_TYPE::dim - 1) ? ", " : " ]\n"); 
        }

    }

    /// @brief Print a geometry::vector in a specific unit of measure with a description
    /// @note The unit must be of the same base of the measurement of the vector
    template <typename VECTOR_TYPE, typename UNIT_TYPE>
        requires (geometry::is_vector_v<VECTOR_TYPE> && 
                  physics::is_unit_v<UNIT_TYPE> && 
                  physics::is_same_base_v<typename VECTOR_TYPE::measurement_t::base, typename UNIT_TYPE::base_t>)
    inline static constexpr void print(const std::string& description, const VECTOR_TYPE& other, const UNIT_TYPE& units) noexcept {

        std::cout << description << "[ "; 
        for (size_t i{}; i < VECTOR_TYPE::dim; ++i) {
            print<false>(other.data[i], units); 
            std::cout << ((i < VECTOR_TYPE::dim - 1) ? ", " : " ]\n"); 
        }

    }


    /// @brief Print a geometry::matrix
    template <typename MATRIX_TYPE>
        requires (geometry::is_matrix_v<MATRIX_TYPE>)
    inline static constexpr void print(const MATRIX_TYPE& other) noexcept {

        for (size_t i{}; i < MATRIX_TYPE::columns; ++i)
            print(other.data[i]); 

    }


    /// @brief Print a geometry::matrix
    template <typename MATRIX_TYPE>
        requires (geometry::is_matrix_v<MATRIX_TYPE>)
    inline static constexpr void print(const std::string& description, const MATRIX_TYPE& other) noexcept {

        std::cout << description << ":\n"; 
        for (size_t i{}; i < MATRIX_TYPE::columns; ++i)
            print(other.data[i]); 

    }


    template <typename T>
        requires math::calculus::is_interval_v<T>
    inline static constexpr void print(const T& other) noexcept {

        std::cout << "[ " << other.start << ", " << other.end << " ]\n"; 

    }
    

    template <typename T>
        requires math::calculus::is_interval_v<T>
    inline static constexpr void print(const std::string& message, const T& other) noexcept {

        std::cout << message << "[ " << other.start << ", " << other.end << " ]\n"; 

    }


    template <bool NEWLINE = true, typename T>
    inline static constexpr void print(const math::calculus::expr_ptr<T>& other) noexcept {

        print<NEWLINE>(math::calculus::val(other));

    }

    template <bool NEWLINE = true, typename T>
    inline static constexpr void print(const std::string& description, const math::calculus::expr_ptr<T>& other) noexcept {

        print<NEWLINE>(description, math::calculus::val(other));

    }


    template <bool NEWLINE = true, typename T>
    inline static constexpr void print(const math::calculus::expr_ptr<T>& other, const std::string& description) noexcept {

        print<NEWLINE>(math::calculus::val(other), description);

    }


    /// @brief Print a variable
    template <bool NEWLINE = true, typename T>
    inline static void print(const math::calculus::variable<T>& x) noexcept {

        print<NEWLINE>(math::calculus::val(x));

    }
    

    /// @brief Print a variable with a description
    template <bool NEWLINE = true, typename T>
    inline static void print(const std::string& description, const math::calculus::variable<T>& x) noexcept {

        print<NEWLINE>(description, math::calculus::val(x));

    }


    /// @brief Print a variable with a description
    template <bool NEWLINE = true, typename T>
    inline static void print(const math::calculus::variable<T>& x, const std::string& description) noexcept {

        print<NEWLINE>(math::calculus::val(x), description);

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
    //     for (size_t i{}; i < MATRIX_TYPE::dim; ++i)
    //         std::cout << other.data[i] << ((i < MATRIX_TYPE::dim - 1) ? ", " : " ]\n"); 

    // }


    template <typename... Ts>
    static constexpr void print(const std::tuple<Ts...>& other) noexcept {

        std::cout << "[ "; 
        std::apply([](auto&&... args) { (print<false>(args), ...); }, other);
        std::cout << "]\n"; 

    }

    template <typename... Ts>
    static constexpr void print(std::string message, const std::tuple<Ts...>& other) noexcept {

        std::cout << message << "[ "; 
        std::apply([](auto&&... args) { (print<false>(args), ...); }, other);
        std::cout << "]\n"; 

    }

    // template <typename PRINTABLE_TYPE>
    // inline static void print(const PRINTABLE_TYPE& printable) noexcept {

    //     std::cout << printable << '\n';

    // }


    // template <typename PRINTABLE_TYPE>
    // inline static void print(const std::vector<PRINTABLE_TYPE>& printable) noexcept {

    //     for (const auto& element : printable)
    //         std::cout << element << '\n';

    // }


    // template <typename PRINTABLE_TYPE>
    // inline static void print(const std::string& description, const PRINTABLE_TYPE& printable) noexcept {

    //     std::cout << description << printable << '\n';

    // }


    // template <typename PRINTABLE_TYPE>
    // inline static void print(const std::string& description, const std::vector<PRINTABLE_TYPE>& printable) noexcept {

    //     std::cout << description << '\n';
    //     for (const auto& element : printable)
    //         std::cout << element << '\n';

    // }


    template <typename MEAS_TYPE, size_t DIM>
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    geometry::column_vector<MEAS_TYPE, DIM> read_measurements(const std::string& file) {

        geometry::column_vector<MEAS_TYPE, DIM> vector; 

        std::ifstream infile(file);
        if (infile.fail())  
            throw std::runtime_error("Error! Cannot read file: " + file); 

        else for (size_t i{}; i < DIM; ++i) 
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