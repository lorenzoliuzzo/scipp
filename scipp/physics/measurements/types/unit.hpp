/**
 * @file    physics/measurements/types/unit.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the aliases and declarations of units
 * @note    
 * @date    2023-04-02
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::physics {


    /// @brief units namespace contains the implementation of units of measurements
    namespace units {


        inline static constexpr unit<metre> m; ///< m; unit

        using kilometre = unit<metre, std::kilo>; ///< kilometre unit
        inline static constexpr kilometre km; ///< Km unit

        using hectometre = unit<metre, std::hecto>; ///< hectometre unit
        inline static constexpr hectometre hm; ///< hm unit

        using decametre = unit<metre, std::deca>; ///< decametre unit
        inline static constexpr decametre dam; ///< dam unit

        using centimetre = unit<metre, std::centi>; 
        inline static constexpr centimetre cm; ///< cm unit

        using millimetre = unit<metre, std::milli>; ///< millimetre unit
        inline static constexpr millimetre mm; ///< mm unit

        using micrometre = unit<metre, std::micro>; ///< micrometre unit
        inline static constexpr micrometre um; ///< um unit

        using nanometre = unit<metre, std::nano>; ///< nanometre unit
        inline static constexpr nanometre nm; ///< nm unit

        using picometre = unit<metre, std::pico>; ///< picometre unit
        inline static constexpr picometre pm; ///< pm unit

        using inch = unit<metre, std::ratio<254, 10000>>; ///< inch unit
        inline static constexpr inch in; ///< in unit

        using foot = unit<metre, std::ratio<3048, 10000>>; ///< foot unit
        inline static constexpr foot ft; ///< ft unit

        using yard = unit<metre, std::ratio<9144, 10000>>; ///< yard unit
        inline static constexpr yard yd; ///< yd unit

        using mile = unit<metre, std::ratio<1609344, 10000>>; ///< mile unit
        inline static constexpr mile mi; ///< mi unit

        using nautical_mile = unit<metre, std::ratio<1852000, 10000>>; ///< nautical_mile unit
        inline static constexpr nautical_mile nmi; ///< nmi unit

        using kilometre2 = unit<metre2, std::kilo>; ///< kilometre2 unit
        inline static constexpr kilometre2 km2; ///< km2 unit

        using hectometre2 = unit<metre2, std::hecto>; ///< hectometre2 unit
        inline static constexpr hectometre2 hm2; ///< hm2 unit

        using decametre2 = unit<metre2, std::deca>; ///< decametre2 unit
        inline static constexpr decametre2 dam2; ///< dam2 unit

        using centimetre2 = unit<metre2, std::centi>; ///< centimetre2 unit
        inline static constexpr centimetre2 cm2; ///< cm2 unit

        using millimetre2 = unit<metre2, std::milli>; ///< millimetre2 unit
        inline static constexpr millimetre2 mm2; ///< mm2 unit

        using micrometre2 = unit<metre2, std::micro>; ///< micrometre2 unit
        inline static constexpr micrometre2 um2; ///< um2 unit

        using nanometre2 = unit<metre2, std::nano>; ///< nanometre2 unit
        inline static constexpr nanometre2 nm2; ///< nm2 unit

        using picometre2 = unit<metre2, std::pico>; ///< picometre2 unit
        inline static constexpr picometre2 pm2; ///< pm2 unit

        inline static constexpr unit<metre2_per_second> m2_s; ///< m2_s unit


        inline static constexpr unit<second> s; ///< s unit
        inline static constexpr unit<kilogram> kg; ///< kg unit
        inline static constexpr unit<ampere> A; ///< A unit
        inline static constexpr unit<kelvin> K; ///< K unit
        inline static constexpr unit<mole> mol; ///< mol unit
        inline static constexpr unit<candela> cd; ///< cd unit
        inline static constexpr unit<radian> rad; ///< rad unit


        inline static constexpr unit<metre_per_second> m_s; ///< m_s unit
        inline static constexpr unit<metre_per_second2> m_ss; ///< m_s unit

        inline static constexpr unit<metre2, std::kilo> Km2; ///< Km2 unit

        inline static constexpr unit<second, std::nano> ns; ///< ns unit 

        inline static constexpr unit<second, std::ratio<60, 1>> min; ///< min unit 

        inline static constexpr unit<hertz, std::giga> GHz; ///< GHz unit

        inline static constexpr unit<kilogram2> kg2; ///< kg2 unit
        inline static constexpr unit<metre2> m2; ///< m2 unit
        inline static constexpr unit<second2> s2; ///< s2 unit
        inline static constexpr unit<ampere2> A2; ///< A2 unit

        inline static constexpr auto N = kg * m / s2; ///< s2 unit
        inline static constexpr auto Pa = N / m2; ///< m2 unit
        inline static constexpr auto J = N * m; ///< J unit
        inline static constexpr auto W = J / s; ///< W unit
        inline static constexpr auto C = A * s; ///< C unit
        inline static constexpr auto V = W / A; ///< V unit


    } // namespace units


} // namespace scipp::physics