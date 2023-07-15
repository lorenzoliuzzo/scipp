---
title: Units and measurements
layout: default
permalink: /physics/units-and-measurements/
parent: Physics namespace
author_profile: true
---

# Units and measurements
Please note that all the tools that are here presented are defined inside the `scipp::physics` namespace.

## Base quantity
The `base_quantity` struct represents a physical quantity by storing the powers of the seven base quantities of the International System of Units ([SI](https://en.wikipedia.org/wiki/International_System_of_Units)) - `length`, `time`, `mass`, `temperature`, `electric_current`, `substance_amount`, and `luminous_intensity`, as template parameters:
```cpp
template <int LENGTH, int TIME, int MASS, int TEMPERATURE, 
          int ELETTRIC_CURRENT, int SUBSTANCE_AMOUNT, int LUMINOUS_INTENSITY>
struct base_quantity {

    static constexpr std::array<int, 7> powers = {LENGTH, TIME, MASS, TEMPERATURE, ELETTRIC_CURRENT, SUBSTANCE_AMOUNT, LUMINOUS_INTENSITY}; ///< array of the powers of the base quantities

    static constexpr std::array<std::string_view, 7> base_literals = {"m", "s", "kg", "K", "A", "mol", "cd"}; //< array of the literals of the base quantities

    /// @brief Returns the string representation of the base_quantity
    static constexpr std::string_view to_string() noexcept {

        std::stringstream ss;

        // Iterate over the base quantities and their powers
        meta::for_<7>([&](auto i) constexpr {

            if constexpr (powers[i] != 0) {

                if constexpr (powers[i] == 1) // Append the base quantity to the string builder
                    ss << base_literals[i]; 

                else // Append the base quantity and its power to the string builder
                    ss << base_literals[i] << '^' << powers[i]; 

            }
            
        });

        return ss.str();

    }

};
```

The powers of the base quantities can be accessed using the corresponding aliases.
It is possible to define custom base_quantities using the constuctor providing the powers, or just by combining existing types using the basic operations, defined inside the `scipp::math::op` namespace, such as multiplication, division, and exponentiation.
However, the principal base quantities are defined in the `scipp::physics::base` namespace and should be used whenever possible.
The base quantities are not meant to be used directly, but rather as template parameters for the unit and measurement structs.

Some other useful base_quantity aliases are defined in the `scipp::physics::base` namespace:
```cpp
namespace base {

    using length = base_quantity<1, 0, 0, 0, 0, 0, 0>;                      ///< metre base_quantity
    using time = base_quantity<0, 1, 0, 0, 0, 0, 0>;                        ///< second base_quantity                   
    using mass = base_quantity<0, 0, 1, 0, 0, 0, 0>;                        ///< kilogram base_quantity
    using temperature = base_quantity<0, 0, 0, 1, 0, 0, 0>;                 ///< kelvin base_quantity
    using electric_current = base_quantity<0, 0, 0, 0, 1, 0, 0>;            ///< ampere base_quantity
    using substance_amount = base_quantity<0, 0, 0, 0, 0, 1, 0>;            ///< mole base_quantity
    using luminous_intensity = base_quantity<0, 0, 0, 0, 0, 0, 1>;          ///< candela base_quantity

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
The `unit` struct represents a unit of measurement by combining a `base_quantity` with an `std::ratio` prefix. 
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

In the `units` namespace are defined the most common units of measure: 
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
The `measurement` struct represents a physical measurement as a value with a `dimensional-aware template meta-structure`. 
The value type is defaulted to double, but it can be changed to any type that supports the basic arithmetic operations. 
Operations between measurements with different units are allowed and respect the dimensional analysis rules.
Using the measurement struct, it is possible to perform dimensional analysis `at compile-time without loss of precision` and overhead. Writing physical accurate code is now possible and easy!
```cpp
template <typename BASE_T, typename VALUE_TYPE = double>
    requires (is_base_v<BASE_TYPE> && math::is_number_v<VALUE_TYPE>)
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
    /// @note The unit must be of the same base of the measurement 
    /// @note The value is immediatly converted to the base unit
    template <typename UNIT_TYPE> 
        requires (is_unit_v<UNIT_TYPE> && is_same_base_v<base_t, typename UNIT_TYPE::base_t>)
    constexpr measurement(value_t&& val, const UNIT_TYPE&) noexcept {

        using prefix_t = typename UNIT_TYPE::prefix_t;
        constexpr auto factor = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den);
        this->value = std::forward<value_t>(val * factor);
        
    }

    /// @brief Convert the measurement to a scalar value if it is a scalar base measurement
    constexpr operator value_t() const requires is_scalar_base_v<base_t> { 
        
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

Consider this basic example, where the physical meaning of a variable it is completely given by its name rather than its type.

```cpp
int main() {

  // This code will compile, but it will produce physical incorrect results.
  double length{1.0};
  double mass{60.0};
  double force{length + mass};

}
```
We assume that all the code that we write is always physically correct, but this is not true... We do make mistakes of this kind all the time, and to find these bugs we don't just need to read the code, we need to understand the physical meaning of the code.
Who has never written a code like this? And we are alone in doing this crazy search between values and value types, because the compiler does not help us in any way. In fact, the compiler does not know the physical meaning of the code, it only knows the type of the variables, and the type of the variables is not enough to understand the physical meaning of the code.
The solution is to use a type that encodes the physical meaning of the variable, so that the compiler can understand the physical meaning of the code.
The scipp `measurement` comes in handy here, because it is a type that encodes the physical meaning of the variable, and it is also a type that can be used in arithmetic operations. So we can write the previous code in this way:

```cpp
int main() {
  measurement<base::length, double> length{1.0};
  measurement<base::mass, double> mass{60.0};
  measurement<base::force, double> force{length * mass};
}
```

This code will not compile yet because it contains incorrect physical operations, but at least the physical error in the code is now clear to the compiler, which will give us an error message that will help us understand the problem.
```cpp
error: conversion from ‘measurement<base_quantity<[...],0,[...],[...],[...],[...],[...]>,[...]>’ to non-scalar type ‘measurement<base_quantity<[...],-2,[...],[...],[...],[...],[...]>,[...]>’ requested here:
    measurement<base::force, double> force = length * mass;
```

We are indeed trying to assign a value obtained from the multiplication of a length and a mass, which does not correspond to the physical meaning of the force, to a variable of type `measurement<base::force, double>`.
Please note that this is all done at compile time, so we don't have to run the code and maybe, if we are lucky, to find a little suspicius numerical result that will make us think that something is wrong in the code and then manually debug the code to find the error, if we ever find it.

Maybe you are thinking that this is all very nice, but that it is not worth the effort to write code in this way, because it is too complicated and it is not worth the effort to write code in this way. But this is not true. In fact, the code is not more complicated, it is just different. And it is not more complicated because the compiler does all the work for us, we just have to write the code in a different way. And it is worth the effort because we can write physically correct code without any effort, and we can be sure that the code is physically correct, because the compiler will tell us if it is not.

Remembering Newton second law, we can rewrite the previous code in the correct way:
```cpp
int main() {
  measurement<base::acceleration, double> a{1.0};
  measurement<base::mass, double> m{60.0};
  measurement<base::force, double> F = m * a;
}
```

In the units namespace there is also defined a macro for costructing measurements from units using literal operators:
```cpp
namespace units::literals {


    /// @brief Define a literal operator for the given unit
    #define UNIT_LITERALS(unit)                                                    \
        inline constexpr auto operator"" unit(long double value) noexcept {        \
            return static_cast<double>(value) * units::unit;                       \
        }                                                                           


}
```

### Usage
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