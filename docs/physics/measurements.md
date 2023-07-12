---
title: Measurements
layout: default
permalink: /physics/measurements/
parent: Physics namespace
author_profile: true
---

{:toc}

# Measurements and units of measure
Brief description of the measurement structure. 
Please note that all the tools that are here presented are defined inside the scipp::physics namespace.

## Base quantity
The base_quantity struct represents a physical quantity by storing the powers of the seven base quantities of the International System of Units (SI) - length, time, mass, temperature, electric current, substance amount, and luminous intensity, as template parameters:
```cpp
template <int LENGTH, int TIME, int MASS, int TEMPERATURE, 
          int ELETTRIC_CURRENT, int SUBSTANCE_AMOUNT, int LUMINOUS_INTENSITY>
struct base_quantity {

    // Implementation details...

};
```

The powers of the base quantities can be accessed using the corresponding aliases.
It is possible to define custom base_quantities using the constuctor providing the powers, or just by combining existing types using the basic operations, defined inside the scipp::math::op namespace, such as multiplication, division, and exponentiation.
However, the principal base quantities are defined in the scipp::physics::base namespace and should be used whenever possible.
The base quantities are not meant to be used directly, but rather as template parameters for the unit and measurement structs.

```cpp
namespace base {

    using length = base_quantity<1, 0, 0, 0, 0, 0, 0>;
    using time = base_quantity<0, 1, 0, 0, 0, 0, 0>;
    using mass = base_quantity<0, 0, 1, 0, 0, 0, 0>;
    using temperature = base_quantity<0, 0, 0, 1, 0, 0, 0>;
    using electric_current = base_quantity<0, 0, 0, 0, 1, 0, 0>;
    using substance_amount = base_quantity<0, 0, 0, 0, 0, 1, 0>;
    using luminous_intensity = base_quantity<0, 0, 0, 0, 0, 0, 1>;

}
```

Some other useful derived base_quantity aliases are defined in the scipp::physics::base namespace:
```cpp
namespace base {

    using angle = math::op::divide_t<length, length>;                        ///< radian base_quantity
    using area = math::op::multiply_t<length, length>;                       ///< square_metre base_quantity
    using volume = math::op::multiply_t<length, area>;                       ///< cubic_metre base_quantity
    using velocity = math::op::divide_t<length, time>;                       ///< metre_per_second base_quantity
    using acceleration = math::op::divide_t<velocity, time>;                 ///< metre_per_second_squared base_quantity
    using angular_velocity = math::op::divide_t<angle, time>;                ///< radian_per_second base_quantity
    using angular_acceleration = math::op::divide_t<angular_velocity, time>; ///< radian_per_second2 base_quantity
    using momentum = math::op::multiply_t<mass, velocity>;                   ///< kilogram_metre_per_second base_quantity
    using impulse = math::op::multiply_t<momentum, time>;                    ///< kilogram_metre_per_second base_quantity
    using angular_momentum = math::op::multiply_t<momentum, length>;         ///< kilogram_metre_squared_per_second base_quantity
    using force = math::op::multiply_t<mass, acceleration>;                  ///< newton base_quantity
    using torque = math::op::multiply_t<force, length>;                      ///< newton_metre base_quantity
    using energy = math::op::multiply_t<force, length>;                      ///< joule base_quantity
    using action = math::op::multiply_t<energy, time>;                       ///< joule_second base_quantity
    using power = math::op::divide_t<energy, time>;                          ///< watt base_quantity
    using pressure = math::op::divide_t<force, area>;                        ///< pascal base_quantity
    using density = math::op::divide_t<mass, volume>;                        ///< kilogram_per_cubic_metre base_quantity
    using frequency = math::op::invert_t<time>;                              ///< hertz base_quantity

    [...]

}
```

## Unit of measure
The unit struct represents a unit of measurement by combining a base_quantity with an std::ratio prefix. 
```cpp
template <typename BASE_T, typename PREFIX_T = std::ratio<1>> 
    requires (is_base_v<BASE_T> && is_prefix_v<PREFIX_T>)  
struct unit {

    using base_t = BASE_T;      ///< base_quantity type
    using prefix_t = PREFIX_T;  ///< prefix type

    /// @brief Return a string representation of the unit
    static constexpr std::string to_string() noexcept {

        std::stringstream ss;
        auto factor = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den); 
        constexpr auto prefix = std::lower_bound(prefix_map.begin(), prefix_map.end(), factor,
            [](const auto& p, const auto& value) { return p.first < value; });
        
        if constexpr (prefix == prefix_map.end())
            ss << base_t::to_string();
        else
            ss << "[" << prefix->second << "]" << base_t::to_string();

        return ss.str();

    }

};
```

In the namespace units are defined the most common units of measure: 
```cpp
namespace units {

    using metre = unit<base::length, std::ratio<1>>;    ///< metre unit
    inline static constexpr metre m;                    ///< m unit

    using kilometre = unit<base::length, std::kilo>;    ///< kilometre unit
    inline static constexpr kilometre km;               ///< Km unit

    using decimetre = unit<base::length, std::deci>;    ///< decimetre unit
    inline static constexpr decimetre dm;               ///< dm unit

    using centimetre = unit<base::length, std::centi>;  ///< centimetre unit
    inline static constexpr centimetre cm;              ///< cm unit

    [...]

    using second = unit<base::time, std::ratio<1>>;     ///< second unit
    inline static constexpr second s;                   ///< s unit

    using minute = unit<base::time, std::ratio<60>>;    ///< minute unit
    inline static constexpr minute min;                 ///< min unit

    using hour = unit<base::time, std::ratio<3600>>;    ///< hour unit
    inline static constexpr hour h;                     ///< h unit
    
    [...]

    using kilogram = unit<base::mass>;                  ///< kilogram unit
    inline static constexpr kilogram kg;                ///< kg unit

    using gram = unit<base::mass, std::milli>;          ///< gram unit
    inline static constexpr gram g;                     ///< g unit

    [...]


    using litre = cubic_decimetre;                      ///< litre unit
    inline static constexpr litre L;                    ///< L unit

    using joule = unit<base::energy>;                   ///< Joule unit
    inline static constexpr joule J;                    ///< J unit

    using newton = unit<base::force>;                   ///< Newton unit
    inline static constexpr newton N;                   ///< N unit

    using pascal = unit<base::pressure>;                ///< Pascal unit
    inline static constexpr pascal Pa;                  ///< Pa unit

    [...]

}
```

## Measurement
The measurement struct represents a physical measurement as a value with a dimensional-aware template meta-structure. 
The value type is defaulted to double, but it can be changed to any type that supports the basic arithmetic operations without loss of precision and overhead. 
```cpp
template <typename BASE_T, typename VALUE_TYPE = double>
struct measurement {

    using base_t = BASE_TYPE;   ///< The base of the measurement
    using value_t = VALUE_TYPE; ///< The type of the value of the measurement

    value_t value;              ///< The value of the measurement


    static constexpr measurement zero{value_t{}};   ///< The zero measurement

    static constexpr measurement one{value_t{1.0}}; ///< The one measurement


    /// @brief Default constructor
    constexpr measurement() noexcept : value{value_t{}} {}

    /// @brief Construct a measurement from a scalar value
    constexpr measurement(const value_t& val) noexcept : value{val} {}

    /// @brief Construct a measurement from a scalar value
    constexpr measurement(value_t&& val) noexcept : value{std::move(val)} {}

    /// @brief Construct a measurement from a scalar value and an unit
    template <typename UNIT_TYPE> 
        requires (is_unit_v<UNIT_TYPE> && is_same_base_v<base_t, typename UNIT_TYPE::base_t>)
    constexpr measurement(value_t&& val, const UNIT_TYPE&) noexcept {

        using prefix_t = typename UNIT_TYPE::prefix_t;
        constexpr auto mult = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den);
        this->value = std::forward<value_t>(val * mult);
        
    }

    /// @brief Convert the measurement to a scalar value if it is a scalar base measurement
    constexpr operator value_t() const requires (is_scalar_base_v<base_t>) { 
        return this->value; 
    }

    /// @brief Print a measurement to an output stream
    friend constexpr std::ostream& operator<<(std::ostream& os, const measurement& other) noexcept { 
        
        os << other.value; 
        if constexpr (!is_scalar_base_v<base_t>) 
            os << ' ' << base_t::to_string();
        return os;
        
    }

};
```

## Usage
In the following example we show how to create measurements and how to use them.
```cpp
    // Creating measurements with explicit value_type and base_quantity
    measurement<base::length, int> l0(1, units::m);     

    print(sizeof(l0));                                  ///< '4' (bytes)

    // Creating measurements by multiplying a number by a unit 
    measurement<base::length> l1 = 2.0 * units::m;      
    // @note the value_type is deduced from the number
    // @note the unit base_quantity must be compatible with the base_quantity of the measurement

    print(sizeof(l1));                                  ///< '8' (bytes)

    // Creating measurements with implicit deduction of base quantity and value type
    measurement l2 = 3.0 * units::m;    
    print(l2);                                          ///< '3.0 m'

    // Creating measurements with a prefixed unit
    auto l3 = 4.0 * units::cm;                          
    
    print(l3);                                          ///< '0.04 m'
    // @note The prefix is automatically applied to the value by multiplying it by the prefix factor

    // Printing a measurement with a specific unit type
    print<units::centimetre>(l3);                       ///< '4.0 [c]m'
    print(l3, units::cm);                               ///< '4.0 [c]m'
    // @note the unit base_quantity must be compatible with the base_quantity of the measurement


    // Using literal operators for units
    using namespace units::literals;
    auto l4 = 5.0m;                                     
    auto l5 = 6.0mm;                                    

    print(l4);                                          ///< '5.0 m'
    print(l5);                                          ///< '0.006 m'


    // Creating measurements by combining other measurements
    auto l6 = l1 + l2;                                  
    
    print(l6);                                          ///< '5.0 m'
    print(l1 * l2);                                     ///< '6 m^2'
    print("l1 / l2 = ", l1 / l2);                       ///< 'l1 / l2 = 0.666667'
    print<std::centi>("l1 / l2 = ", l1 / l2);           ///< 'l1 / l2 = 0.67'
    print<std::milli>("l1 / l2 = ", l1 / l2);           ///< 'l1 / l2 = 0.667'

```