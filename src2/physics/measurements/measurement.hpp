/**
 * @file    base.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    /// @brief        The measurement class is a template class that represents a measurement of a physical quantity
    /// @tparam BASE: The base of the measurement
    /// @see          units::unit_base 
    template <typename BASE> 
        requires (units::is_base_v<BASE>)
    struct measurement {


        // ==============================================
        // aliases
        // ==============================================

            using type = measurement<BASE>; ///< The type of the measurement

            using base = BASE; ///< The base of the measurement


        // ==============================================
        // members
        // ==============================================

            scalar value; ///< The value of the measurement


        // ==============================================
        // constructors
        // ==============================================

            /// @brief Default constructor
            constexpr 
                measurement() 
            noexcept : 
                value{0.0} {}


            /// @brief Construct a measurement from a scalar value
            /// @param val: The value of the measurement
            constexpr 
                measurement(const scalar& val) 
            noexcept 
                : value{val} {}


            /// @brief Construct a measurement from a scalar value
            /// @param val: The value of the measurement
            constexpr 
                measurement(scalar&& val)
            noexcept 
                : value{std::move(val)} {}


            /// @brief Construct a measurement from a scalar value and an unit
            /// @param val: The value of the measurement
            /// @param UNITS: The unit of the measurement
            /// @note The unit must be of the same base of the measurement
            template <typename UNITS> 
                requires (units::is_same_base_v<BASE, typename UNITS::base>)
            constexpr 
                measurement(const scalar& val, const UNITS&) 
            noexcept 
                : value{val * UNITS::mult} {}


            /// @brief Construct a measurement from a scalar value and an unit
            /// @param val: The value of the measurement
            /// @param UNITS: The unit of the measurement
            /// @note The unit must be of the same base of the measurement
            template <typename UNITS> 
                requires (units::is_same_base_v<BASE, typename UNITS::base>)
            constexpr 
                measurement(scalar&& val, const UNITS&) 
            noexcept 
                : value{std::move(val * UNITS::mult)} {}


        // ==============================================
        // operators
        // ==============================================

            /// @brief Check if this measurement is equal to another measurement
            constexpr 
                bool operator==(const measurement& meas) 
            const noexcept 
            {

                return this->value == meas.value; 

            }
            
            
            /// @brief Check if this measurement is equal to another measurement
            constexpr 
                bool operator!=(const measurement& meas) 
            const noexcept {

                return this->value != meas.value; 

            }


            /// @brief Check if this measurement is greater than another measurement
            constexpr 
                bool operator>(const measurement& meas) 
            const noexcept 
            {

                return this->value > meas.value; 

            }


            /// @brief Check if this measurement is less than another measurement
            constexpr 
                bool operator<(const measurement& meas) 
            const noexcept 
            {

                return this->value < meas.value; 

            }


            /// @brief Check if this measurement is greater or equal to another measurement
            constexpr 
                bool operator>=(const measurement& meas) 
            const noexcept 
            {

                return this->value >= meas.value; 

            }


            /// @brief Check if this measurement is less or equal to another measurement
            constexpr 
                bool operator<=(const measurement& meas) 
            const noexcept 
            {

                return this->value <= meas.value; 

            }
            

            /// @brief Add a measurement to the current measurement
            constexpr 
                measurement& operator+=(const measurement& rhs) 
            noexcept 
            { 
                
                this->value += rhs.value;
                return *this;  
                
            }


            /// @brief Subtract a measurement to the current measurement
            constexpr 
                measurement& operator-=(const measurement& rhs) 
            noexcept 
            { 
                
                this->value -= rhs.value;
                return *this;  

            }

            
            /// @brief Add two measurements
            constexpr 
                measurement operator+(const measurement& rhs) 
            const noexcept 
            { 
                
                return this->value + rhs.value; 
                
            }


            /// @brief Subtract two measurements
            constexpr 
                measurement operator-(const measurement& rhs) 
            const noexcept 
            { 
                
                return this->value - rhs.value; 
                
            }


            /// @brief Negate a measurement
            constexpr 
                measurement operator-() 
            const noexcept 
            { 

                return -this->value; 

            }


            /// @brief Multiply two measurements
            template <typename BASE2> 
                requires (units::is_base_v<BASE2>)
            constexpr 
                auto operator*(const measurement<BASE2>& other) 
            const noexcept 
                -> measurement<units::base_prod_t<BASE, BASE2>>
            { 
                
                return this->value * other.value; 
                
            }


            /// @brief Divide two measurements
            template <typename BASE2> 
                requires (units::is_base_v<BASE2>)
            constexpr 
                auto operator/(const measurement<BASE2>& other) 
            const 
                -> measurement<units::base_div_t<BASE, BASE2>> 
            { 

                if (other.value == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by a zero measurement");
                return this->value / other.value; 
                
            }
        

            constexpr 
                measurement operator*(const scalar& val) 
            const noexcept 
            {

                return this->value * val; 

            }


            constexpr 
                measurement operator/(const scalar& val) 
            const 
            {

                if (val == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by zero");

                return this->value / val; 

            }


            friend 
            constexpr 
                measurement operator*(const scalar& val, const measurement& meas) 
            noexcept 
            {

                return val * meas.value; 
                
            }


            /// @brief Divide a scalar by a measurement
            /// @param val: The scalar value as lvalue const reference
            /// @param meas: The measurement as lvalue const reference
            /// @return measurement<units::base_inv_t<BASE>>
            friend 
            constexpr 
                auto operator/(const scalar& val, const measurement& meas)
                -> measurement<units::base_inv_t<BASE>>
            {

                if (val == 0.0) 
                    throw std::runtime_error("Cannot divide a scalar by a zero measurement");

                return val / meas.value; 
                
            }


            /// @brief Print a measurement to an output stream
            friend 
            constexpr 
                std::ostream& operator<<(std::ostream& os, const measurement& meas) 
            noexcept 
            { 
                
                return os << meas.value << ' ' << BASE::to_string();
                
            }
            
        
        // ==============================================
        // methods
        // ==============================================

            /// @brief  Get the value of the measurement in the specified unit
            /// @param  UNITS: The unit in which the value is returned
            /// @note   The unit must be of the same base of the measurement
            /// @return scalar 
            template <typename UNITS> 
                requires (units::is_same_base_v<BASE, typename UNITS::base>)
            constexpr 
                scalar value_as(const UNITS&) 
            const noexcept 
            { 
                
                return this->value / UNITS::mult; 
                
            }

            
            // /// @brief Convert a value from one unit to another 
            // template <typename UNITS> 
                // requires (units::is_same_base_v<BASE, typename UNITS::base>)
            // constexpr 
            // measurement convert(const UNITS&) const noexcept {

            //     return *this / UNITS::mult; 

            // }
                
            
            /// @brief Print the measurement to the standard output
            /// @param newline: If true (default case), a newline character is printed at the end of the measurement
            constexpr 
                void print(const bool& newline = true) 
            const noexcept 
            {

                std::cout << this->value << ' ' << BASE::to_string() << (newline ? '\n' : ' '); 

            }
            

            /// @brief Print the measurement to the standard output
            /// @param units: The unit in which the value is printed
            /// @param newline: If true (default case), a newline character is printed at the end of the measurement
            /// @note The unit must be of the same base of the measurement

            template <typename UNITS> 
                requires (units::is_unit_v<UNITS> && units::is_same_base_v<BASE, typename UNITS::base>)
            constexpr 
                void print(const UNITS& units, const bool& newline = true) 
            const noexcept 
            {

                std::cout << this->value_as(units) << ' ' << UNITS::to_string() << (newline ? '\n' : ' '); 

            }
            

    }; // struct measurement


    template <typename UNITS> 
        requires (units::is_unit_v<UNITS>)
    measurement(const scalar&, const UNITS&) 
        -> measurement<typename UNITS::base>;


    /// @brief Multiply a scalar with an unit to get a measurement
    template <typename UNITS> 
        requires (units::is_unit_v<UNITS>)
    constexpr
        auto operator*(const scalar& val, const UNITS&) 
    noexcept
        -> measurement<typename UNITS::base> 
    { 
        
        return val * UNITS::mult; 
        
    }


    template <typename T>
    struct is_measurement : std::false_type {};

    template <typename BASE>
    struct is_measurement<measurement<BASE>> : std::true_type {};

    template <typename T>
    constexpr 
    bool is_measurement_v = is_measurement<T>::value;


    template <typename... Ts>
    struct are_measurements : std::conjunction<is_measurement<Ts>...> {};

    template <typename... Ts>
    constexpr 
    bool are_measurements_v = are_measurements<Ts...>::value;
  

    template <typename T, typename... Ts>
        requires (are_measurements_v<T, Ts...>)
    struct measurements_prod : measurements_prod<measurements_prod<T, Ts...>> {};

    template <typename... MEAS_LIST>
        requires (are_measurements_v<MEAS_LIST...>)
    using measurements_prod_t = typename measurements_prod<MEAS_LIST...>::type;


    // template<typename T, typename... Args>
    // struct multiply_pack {

    //     using type = decltype(std::declval<T>() * std::declval<typename multiply_pack<Args...>::type>());

    // };

    // template<typename T>
    // struct multiply_pack<T> {

    //     using type = T;
        
    // };

    // template<typename T, typename... Args>
    // using multiply_pack_t = typename multiply_pack<T, Args...>::type;

// template<typename T, typename U, typename... Args>
// struct multiply_pack {

//     using type = decltype(std::declval<T>() * std::declval<typename multiply_pack<U, Args...>::type>());

// };

// template<typename T, typename U>
// struct multiply_pack<T, U> {

//     using type = decltype(std::declval<T>() * std::declval<U>());

// };

// template<typename T, typename U, typename... Args>
// using multiply_pack_t = typename multiply_pack<T, U, Args...>::type;


// template <typename T, typename... Args>
// struct multiply_each {
// private:
//     template <typename U>
//     struct impl {
//         using type = multiply_pack_t<T, U>;
//     };

// public:
//     using type = typename impl<typename multiply_each<Args...>::type>::type;
// };

// template <typename T>
// struct multiply_each<T> {
//     using type = T;
// };

// template<typename ExternalType, typename T, typename... Args>
// struct multiply_each<ExternalType, T, Args...> {
//     using type = typename measurements_prod<multiply_each<ExternalType, Args...>, ExternalType>;
// };

// template<typename ExternalType, typename T>
// struct multiply_each<ExternalType, T> {
//     using type = measurements_prod_t<T, ExternalType>;
// };

// template<typename ExternalType, typename... Args>
// using multiply_each_t = typename multiply_each<ExternalType, Args...>::type;

    // template <typename MEAS1, typename MEAS2> 
    //     requires (are_measurements_v<MEAS1, MEAS2>)
    // struct measurement_div : measurement<units::base_div_t<typename MEAS1::base, typename MEAS2::base>> {};


    // template <typename... MEAS_LIST>
    //     requires (are_measurements_v<MEAS_LIST...>)
    // struct measurement_div {
    //     template <typename MEAS1, typename MEAS2>
    //         requires (are_measurements_v<MEAS1, MEAS2>)
    //     using type = measurement<units::base_div_t<typename MEAS1::base, typename MEAS2::base>>;
    // };


    // template <typename... MEAS_LIST>
    //     requires (are_measurements_v<MEAS_LIST...>)
    // using measurement_div_t = typename measurement_div::template type<MEAS_LIST...>;


    // struct measurement_div {
    //     template <typename MEAS1, typename MEAS2>
    //         requires (are_measurements_v<MEAS1, MEAS2>)
    //     using type = measurement<units::base_div_t<typename MEAS1::base, typename MEAS2::base>>;
    // };


    // template <typename... MEAS_LIST>
    //     requires (are_measurements_v<MEAS_LIST...>)
    // using measurement_prod_t = typename measurement_prod::template type<MEAS_LIST...>;


    // template <typename... MEAS_LIST>
    //     requires (are_measurements_v<MEAS_LIST...>)
    // using measurement_div_t = typename measurement_div::template type<MEAS_LIST...>;


    // template <typename... MEAS_LIST>
    //     requires (are_measurements_v<MEAS_LIST...>)
    // inline constexpr
    //     auto operator*(const MEAS_LIST&... meas_list)
    // {
            
    //     return std::apply([](const auto&... meas) { return (meas * ...); }, std::make_tuple(meas_list...));

    // }


    // /// @brief measurement_prod is a type alias for the product of two measurements
    // template <typename MEAS1, typename MEAS2> 
    //     requires (are_measurements_v<MEAS1, MEAS2>)
    // using measurement_prod = measurement<units::base_prod_t<typename MEAS1::base, typename MEAS2::base>>;


    // /// @brief measurement_div is a type alias for the division of two measurements
    // template <typename MEAS1, typename MEAS2> 
    //     requires (are_measurements_v<MEAS1, MEAS2>)
    // using measurement_div = measurement<units::base_div_t<typename MEAS1::base, typename MEAS2::base>>;


    /// @brief multiply a measurement list with a measurement
    template <typename MEAS, typename... MEAS_LIST>
        requires (are_measurements_v<MEAS, MEAS_LIST...>)
    inline constexpr
        auto operator*(const measurement<MEAS>& meas, const MEAS_LIST&... meas_list) 
    noexcept {

        return meas * (meas_list * ...);

    }


        template <typename T, typename... Ts>
        struct common_base;

        template <typename T>
        struct common_base<T> {

            using type = typename T::base;

        };      

        template <typename T, typename U, typename... Ts>
        struct common_base<T, U, Ts...> {

            using type = std::conditional_t<units::is_same_base_v<typename T::base, typename U::base>, typename T::base, void>;
        
        };

        template <typename T, typename U>
        struct common_base<T, U> {

            using type = std::conditional_t<units::is_same_base_v<typename T::base, typename U::base>, typename T::base, void>;
        
        };

        template <typename... Ts>
        using common_base_t = typename common_base<Ts...>::type;



} // namespace scipp::physics