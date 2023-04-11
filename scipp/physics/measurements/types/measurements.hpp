/**
 * @file    physics/measurements/types/measurements.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-30
 * 
 * @copyright Copyright (c) 2023
 */





/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    using scalar_m = measurement<units::scalar>;                       ///< scalar_m
    using length_m = measurement<units::metre>;                        ///< length_m 
    using time_m = measurement<units::second>;                         ///< time_m 
    using mass_m = measurement<units::kilogram>;                       ///< mass_m 
    using angle_m = measurement<units::radian>;                        ///< angle_m 
    using temperature_m = measurement<units::kelvin>;                  ///< temperature_m
    using current_m = measurement<units::ampere>;                      ///< current_m
    using luminous_intensity_m = measurement<units::candela>;          ///< luminous_intensity_m
    using mole_m = measurement<units::mole>;                           ///< mole_m

    using velocity_m = measurement<units::metre_per_second>;           ///< velocity_m 
    using ang_velocity_m = measurement<units::radian_per_second>;      ///< ang_velocity_m
    using acceleration_m = measurement<units::metre_per_second2>;      ///< acceleration_m 
    using ang_acceleration_m = measurement<units::radian_per_second2>; ///< ang_acceleration_m
    using force_m = measurement<units::kilogram_metre_per_second2>;    ///< force_m 
    using energy_m = measurement<units::kilogram_metre2_per_second2>;  ///< energy_m 


    using scalar_um = umeasurement<units::scalar>;                       ///< scalar_m
    using length_um = umeasurement<units::metre>;                        ///< length_m 
    using time_um = umeasurement<units::second>;                         ///< time_m 
    using mass_um = umeasurement<units::kilogram>;                       ///< mass_m 
    using angle_um = umeasurement<units::radian>;                        ///< angle_m 
    using temperature_um = umeasurement<units::kelvin>;                  ///< temperature_m
    using current_um = umeasurement<units::ampere>;                      ///< current_m
    using luminous_intensity_um = umeasurement<units::candela>;          ///< luminous_intensity_m
    using mole_um = umeasurement<units::mole>;                           ///< mole_m

    using velocity_um = umeasurement<units::metre_per_second>;           ///< velocity_m 
    using ang_velocity_um = umeasurement<units::radian_per_second>;      ///< ang_velocity_m
    using acceleration_um = umeasurement<units::metre_per_second2>;      ///< acceleration_m 
    using ang_acceleration_um = umeasurement<units::radian_per_second2>; ///< ang_acceleration_m
    using force_um = umeasurement<units::kilogram_metre_per_second2>;    ///< force_m 
    using energy_um = umeasurement<units::kilogram_metre2_per_second2>;  ///< energy_m 





    template <typename T>
    struct is_angle : std::false_type {};

    template <>
    struct is_angle<measurement<units::radian>> : std::true_type {};

    template <>
    struct is_angle<umeasurement<units::radian>> : std::true_type {};

    template <typename T>
    constexpr bool is_angle_v = is_angle<T>::value;

    
    // using frequency_m = measurement<units::hertz>;                    ///< frequency_m
    // using power_m = measurement<units::watt>;                         ///< power_m
    using charge_m = measurement<units::coulomb>;                     ///< charge_m
    // using voltage_m = measurement<units::volt>;                       ///< voltage_m
    // using capacitance_m = measurement<units::farad>;                  ///< capacitance_m
    // using resistance_m = measurement<units::ohm>;                     ///< resistance_m
    // using conductance_m = measurement<units::siemens>;                ///< conductance_m
    // using magnetic_flux_m = measurement<units::weber>;                ///< magnetic_flux_m
    // using magnetic_field_m = measurement<units::tesla>;               ///< magnetic_field_m
    // using inductance_m = measurement<units::henry>;                   ///< inductance_m
    // using luminous_flux_m = measurement<units::lumen>;                ///< luminous_flux_m
    // using illuminance_m = measurement<units::lux>;                    ///< illuminance_m
    // using radioactivity_m = measurement<units::becquerel>;            ///< radioactivity_m
    // using absorbed_dose_m = measurement<units::gray>;                 ///< absorbed_dose_m
    // using dose_equivalent_m = measurement<units::sievert>;            ///< dose_equivalent_m
    // using catalytic_activity_m = measurement<units::katal>;           ///< catalytic_activity_m


        inline constexpr auto operator""m(long double value) noexcept -> length_m {

            return length_m(value);

        }

        inline constexpr auto operator""km(long double value) noexcept -> length_m {

            return length_m(value, units::km);

        }

        inline constexpr auto operator""cm(long double value) noexcept -> length_m {

            return length_m(value, units::cm);

        }

        inline constexpr auto operator""mm(long double value) noexcept -> length_m {

            return length_m(value, units::mm);

        }

        inline constexpr auto operator""um(long double value) noexcept -> length_m {

            return length_m(value, units::um);

        }

        inline constexpr auto operator""nm(long double value) noexcept -> length_m {

            return length_m(value, units::nm);

        }


} // namespace scipp::physics