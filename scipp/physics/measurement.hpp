/**
 * @file    physics/measurements/measurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the measurement struct.
 * @date    2023-05-28
 *
 * @copyright Copyright (c) 2023
 */



/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    /// @brief Struct measurement represents a physical measurement as a double and a dimentional template meta-structure
    /// @tparam BASE_TYPE: base_quantity of the measurement
    /// @see in physics: base_quantity, prefix, unit1
    template <typename BASE_TYPE, typename VALUE_TYPE = double>
        requires (is_base_v<BASE_TYPE> && math::is_number_v<VALUE_TYPE>)
    struct measurement {


        // ==============================================
        // aliases
        // ==============================================

            using base_t = BASE_TYPE; ///< The base of the measurement

            using value_t = VALUE_TYPE; ///< The type of the value of the measurement

            using _t = measurement<base_t, value_t>; ///< The type of the measurement


        // ==============================================
        // members
        // ==============================================

            value_t value; ///< The value of the measurement


        // ==============================================
        // static members
        // ==============================================

            inline static constexpr measurement zero{value_t{}}; ///< The zero measurement

            inline static constexpr measurement one{value_t{1.0}}; ///< The one measurement


        // ==============================================
        // constructors
        // ==============================================

            /// @brief Default constructor
            constexpr measurement() noexcept :

                value{value_t{}} {}


            /// @brief Construct a measurement from a scalar value
            constexpr measurement(const value_t& val) noexcept :

                value{val} {}

            /// @brief Construct a measurement from a scalar value
            constexpr measurement(value_t&& val) noexcept :

                value{std::move(val)} {}


            /// @brief Construct a measurement from a scalar value and an unit
            /// @note The unit must be of the same base of the measurement
            /// @note The value is immediatly converted to the base unit
            template <typename UNIT_TYPE>
                requires (is_unit_v<UNIT_TYPE> && is_same_base_v<base_t, typename UNIT_TYPE::base_t>)
            constexpr measurement(value_t&& val, const UNIT_TYPE&) noexcept {

                using prefix_t = typename UNIT_TYPE::prefix_t;
                constexpr auto factor = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den);
                this->value = std::forward<value_t>(val * factor);

            }


            /// @brief Construct a measurement from another measurement
            constexpr measurement(const measurement& other) noexcept :

                value{other.value} {}


            /// @brief Construct a measurement from another measurement
            constexpr measurement(measurement&& other) noexcept :

                value{std::move(other.value)} {}


            template <typename OTHER_VALUE_T>
                requires math::is_number_v<OTHER_VALUE_T>
            constexpr measurement(const measurement<BASE_TYPE, OTHER_VALUE_T>& other) noexcept :

                value{static_cast<value_t>(other.value)} {}


            template <typename PointerType>
                requires std::is_pointer_v<PointerType>
            constexpr measurement(PointerType ptr) noexcept :

                value(static_cast<measurement<base_t, value_t>>(*ptr)) {}


        // ==============================================
        // operators
        // ==============================================

            /// @brief Copy assignment operator
            constexpr measurement& operator=(const measurement& other) noexcept {

                this->value = other.value;
                return *this;

            }

            /// @brief Move assignment operator
            constexpr measurement& operator=(measurement&& other) noexcept {

                this->value = std::move(other.value);
                return *this;

            }

            /// @brief Copy assignment operator
            template <typename T>
            constexpr measurement& operator=(const measurement<base_t, T>& other) noexcept {

                this->value = static_cast<value_t>(other.value);
                return *this;

            }

            /// @brief Move assignment operator
            template <typename T>
            constexpr measurement& operator=(measurement<base_t, T>&& other) noexcept {

                this->value = std::move(static_cast<value_t>(other.value));
                return *this;

            }


            /// @brief Implicitly convert the measurement to a scalar value if it is a scalar base measurement
            constexpr operator value_t() const noexcept
                requires is_scalar_base_v<base_t> {

                return this->value;

            }


            /// @brief Extract the value of this measurement converted to a specific unit
            /// @note The unit must be of the same base of the measurement
            template <typename T>
            constexpr auto value_as(const unit<base_t, T>&) const noexcept {

                return this->value / static_cast<double>(T::num) * static_cast<double>(T::den);

            }


            /// @brief Print a measurement to an output stream
            friend constexpr std::ostream& operator<<(std::ostream& os, const measurement& other) noexcept {

                os << other.value;
                if constexpr (!is_scalar_base_v<base_t>)
                    os << ' ' << base_t::to_string();
                return os;

            }

            /// @brief Read a measurement from an input stream
            friend constexpr std::istream& operator>>(std::istream& is, measurement& other) {

                std::string unit;

                if (!(is >> other.value >> unit))
                    return is;

                if (!unit.empty()) {

                    std::istringstream unit_stream(unit);
                    char prefix_char;
                    if (unit_stream.get() == '[' && unit_stream.get(prefix_char) && unit_stream.get() == ']') {

                        auto prefix_it = std::find_if(prefix_map.begin(), prefix_map.end(),
                            [prefix_char](const auto& pair) {
                                return pair.second == prefix_char;
                            }
                        );

                        if (prefix_it != prefix_map.end())
                            other.value *= prefix_it->first;

                    }

                    std::string expected_unit = base_t::to_string();
                    if (unit != expected_unit)
                        throw std::runtime_error("Unit mismatch: expected " + expected_unit + ", got " + unit);

                }

                return is;

            }


    }; // struct measurement


    // =============================================
    // measurement template guidelines
    // =============================================

        template <typename VALUE_TYPE, typename UNIT_TYPE>
            requires (math::is_number_v<VALUE_TYPE> && is_unit_v<UNIT_TYPE>)
        measurement(const VALUE_TYPE&, const UNIT_TYPE&)
            -> measurement<typename UNIT_TYPE::base_t, VALUE_TYPE>;

        template <typename VALUE_TYPE, typename UNIT_TYPE>
            requires (math::is_number_v<VALUE_TYPE> && is_unit_v<UNIT_TYPE>)
        measurement(VALUE_TYPE&&, const UNIT_TYPE&)
            -> measurement<typename UNIT_TYPE::base_t, VALUE_TYPE>;


} // namespace physics