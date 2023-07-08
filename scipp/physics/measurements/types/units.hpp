/**
 * @file    physics/measurements/types/unit.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the aliases and declarations of units
 * @note    
 * @date    2023-07-08
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::physics {


    /// @brief units namespace contains the implementation of units of measurements
    namespace units {


        using metre = unit<base::length, std::ratio<1>>; ///< metre unit
        inline static constexpr metre m; ///< m; unit

        using kilometre = unit<base::length, std::kilo>; ///< kilometre unit
        inline static constexpr kilometre km; ///< Km unit

        using hectometre = unit<base::length, std::hecto>; ///< hectometre unit
        inline static constexpr hectometre hm; ///< hm unit

        using decametre = unit<base::length, std::deca>; ///< decametre unit
        inline static constexpr decametre dam; ///< dam unit

        using decimetre = unit<base::length, std::deci>; ///< decimetre unit
        inline static constexpr decimetre dm; ///< dm unit

        using centimetre = unit<base::length, std::centi>; 
        inline static constexpr centimetre cm; ///< cm unit

        using millimetre = unit<base::length, std::milli>; ///< millimetre unit
        inline static constexpr millimetre mm; ///< mm unit

        using micrometre = unit<base::length, std::micro>; ///< micrometre unit
        inline static constexpr micrometre um; ///< um unit

        using nanometre = unit<base::length, std::nano>; ///< nanometre unit
        inline static constexpr nanometre nm; ///< nm unit

        using picometre = unit<base::length, std::pico>; ///< picometre unit
        inline static constexpr picometre pm; ///< pm unit

        using inch = unit<base::length, std::ratio<254, 10000>>; ///< inch unit
        inline static constexpr inch in; ///< in unit

        using foot = unit<base::length, std::ratio<3048, 10000>>; ///< foot unit
        inline static constexpr foot ft; ///< ft unit

        using yard = unit<base::length, std::ratio<9144, 10000>>; ///< yard unit
        inline static constexpr yard yd; ///< yd unit

        using mile = unit<base::length, std::ratio<1609344, 10000>>; ///< mile unit
        inline static constexpr mile mi; ///< mi unit

        using nautical_mile = unit<base::length, std::ratio<1852000, 10000>>; ///< nautical_mile unit
        inline static constexpr nautical_mile nmi; ///< nmi unit


        using square_metre = unit<base::area>; ///< square metre unit
        inline static constexpr square_metre sq_m; ///< sq_m unit

        using square_kilometre = unit<base::area, std::kilo>; ///< square kilometre unit
        inline static constexpr square_kilometre sq_km; ///< sq_km unit

        using square_hectometre = unit<base::area, std::hecto>; ///< square hectometre unit
        inline static constexpr square_hectometre sq_hm; ///< sq_hm unit

        using square_centimetre = unit<base::area, std::centi>; ///< square centimetre unit
        inline static constexpr square_centimetre sq_cm; ///< sq_cm unit

        using square_millimetre = unit<base::area, std::milli>; ///< square millimetre unit
        inline static constexpr square_millimetre sq_mm; ///< sq_mm unit

        using square_micrometre = unit<base::area, std::micro>; ///< square micrometre unit
        inline static constexpr square_micrometre sq_um; ///< sq_um unit

        using square_nanometre = unit<base::area, std::nano>; ///< square nanometre unit
        inline static constexpr square_nanometre sq_nm; ///< sq_nm unit

        using hectare = unit<base::area, std::hecto>; ///< hectare unit
        inline static constexpr hectare ha; ///< ha unit

        using acre = unit<base::area, std::ratio<40468564224, 100000000>>; ///< acre unit
        inline static constexpr acre ac; ///< ac unit

        using square_mile = unit<base::area, std::ratio<16093440000, 1>>; ///< square mile unit
        inline static constexpr square_mile sq_mi; ///< sq_mi unit

        using square_yard = unit<base::area, std::ratio<83612736, 10000>>; ///< square yard unit
        inline static constexpr square_yard sq_yd; ///< sq_yd unit

        using square_foot = unit<base::area, std::ratio<9290304, 10000>>; ///< square foot unit
        inline static constexpr square_foot sq_ft; ///< sq_ft unit

        using square_inch = unit<base::area, std::ratio<64516, 10000>>; ///< square inch unit
        inline static constexpr square_inch sq_in; ///< sq_in unit


        using cubic_metre = unit<base::volume>; ///< cubic metre unit
        inline static constexpr cubic_metre cu_m; ///< cu_m unit

        using cubic_millimetre = unit<base::volume, std::milli>; ///< cubic millimetre unit
        inline static constexpr cubic_millimetre cu_mm; ///< cu_mm unit

        using cubic_centimetre = unit<base::volume, std::centi>; ///< cubic centimetre unit
        inline static constexpr cubic_centimetre cu_cm; ///< cu_cm unit

        using cubic_decimetre = unit<base::volume, std::deci>; ///< cubic decimetre unit
        inline static constexpr cubic_decimetre cu_dm; ///< cu_dm unit

        using cubic_kilometre = unit<base::volume, std::kilo>; ///< cubic kilometre unit
        inline static constexpr cubic_kilometre cu_km; ///< cu_km unit

        using litre = cubic_decimetre; 
        inline static constexpr litre L; ///< L unit

        using decilitre = math::op::multiply_t<std::deci, litre>; 
        inline static constexpr decilitre dL; 

        using centilitre = math::op::multiply_t<std::centi, litre>; 
        inline static constexpr centilitre cL; 

        using millilitre = math::op::multiply_t<std::milli, litre>; 
        inline static constexpr millilitre mL; 

        using decalitre = math::op::multiply_t<std::deca, litre>; 
        inline static constexpr decalitre daL; ///< daL unit

        using hectolitre = math::op::multiply_t<std::hecto, litre>; ///< hectolitre unit
        inline static constexpr hectolitre hL; ///< hL unit

        using kilolitre = math::op::multiply_t<std::kilo, litre>; ///< kilolitre unit
        inline static constexpr kilolitre kL; ///< kL unit


        using second = unit<base::time>; ///< second unit
        inline static constexpr second s; ///< s unit

        using decisecond = unit<base::time, std::deci>; ///< decisecond unit
        inline static constexpr decisecond ds; ///< ds unit

        using centisecond = unit<base::time, std::centi>; ///< centisecond unit
        inline static constexpr centisecond cs; ///< cs unit
        
        using millisecond = unit<base::time, std::milli>; ///< millisecond unit
        inline static constexpr millisecond ms; ///< ms unit

        using microsecond = unit<base::time, std::micro>; ///< microsecond unit
        inline static constexpr microsecond us; ///< us unit

        using nanosecond = unit<base::time, std::nano>; ///< nanosecond unit
        inline static constexpr nanosecond ns; ///< ns unit

        using picosecond = unit<base::time, std::pico>; ///< picosecond unit
        inline static constexpr picosecond ps; ///< ps unit

        using minute = unit<base::time, std::ratio<60>>; ///< minute unit
        inline static constexpr minute min; ///< min unit

        using hour = unit<base::time, std::ratio<3600>>; ///< hour unit
        inline static constexpr hour h; ///< h unit

        using day = unit<base::time, std::ratio<86400>>; ///< day unit
        inline static constexpr day d; ///< d unit

        using week = unit<base::time, std::ratio<604800>>; ///< week unit
        inline static constexpr week wk; ///< wk unit

        using year = unit<base::time, std::ratio<31557600>>; ///< year unit
        inline static constexpr year yr; ///< yr unit


        using kilogram = unit<base::mass>; ///< kilogram unit
        inline static constexpr kilogram kg; ///< kg unit

        using gram = unit<base::mass, std::milli>; ///< gram unit
        inline static constexpr gram g; ///< g unit

        using milligram = unit<base::mass, std::micro>; ///< milligram unit
        inline static constexpr milligram mg; ///< mg unit

        using microgram = unit<base::mass, std::nano>; ///< microgram unit
        inline static constexpr microgram ug; ///< ug unit

        using tonne = unit<base::mass, std::kilo>; ///< tonne unit
        inline static constexpr tonne t; ///< t unit

        using pound = unit<base::mass, std::ratio<45359237, 100000000>>; ///< pound unit
        inline static constexpr pound lb; ///< lb unit

        using ounce = unit<base::mass, std::ratio<28349523, 1000000000>>; ///< ounce unit
        inline static constexpr ounce oz; ///< oz unit


        using joule = unit<base::energy>; ///< joule unit
        inline static constexpr joule J; ///< J unit

        using millijoule = unit<base::energy, std::milli>; ///< millijoule unit
        inline static constexpr millijoule mJ; ///< mJ unit

        using microjoule = unit<base::energy, std::micro>; ///< microjoule unit
        inline static constexpr microjoule uJ; ///< uJ unit

        using nanojoule = unit<base::energy, std::nano>; ///< nanojoule unit
        inline static constexpr nanojoule nJ; ///< nJ unit

        using kilojoule = unit<base::energy, std::kilo>; ///< kilojoule unit
        inline static constexpr kilojoule kJ; ///< kJ unit

        using megajoule = unit<base::energy, std::mega>; ///< megajoule unit
        inline static constexpr megajoule MJ; ///< MJ unit

        using gigajoule = unit<base::energy, std::giga>; ///< gigajoule unit
        inline static constexpr gigajoule GJ; ///< GJ unit

        using electronvolt = unit<base::energy, std::pico>; ///< electronvolt unit
        inline static constexpr electronvolt eV; ///< eV unit

        using kiloelectronvolt = unit<base::energy, std::femto>; ///< kiloelectronvolt unit
        inline static constexpr kiloelectronvolt keV; ///< keV unit

        using megaelectronvolt = unit<base::energy, std::atto>; ///< megaelectronvolt unit
        inline static constexpr megaelectronvolt MeV; ///< MeV unit

        using calorie = unit<base::energy, std::ratio<4184, 1000>>; ///< calorie unit
        inline static constexpr calorie cal; ///< cal unit

        using kilocalorie = unit<base::energy, std::ratio<4184, 1>>; ///< kilocalorie unit
        inline static constexpr kilocalorie kcal; ///< kcal unit
        

        using newton = unit<base::force>; ///< newton unit
        inline static constexpr newton N; ///< N unit

        using kilonewton = unit<base::force, std::kilo>; ///< kilonewton unit
        inline static constexpr kilonewton kN; ///< kN unit

        // using pound_force = unit<base::force, std::ratio<4448222, 10000>>; ///< pound-force unit
        // inline static constexpr pound_force lbf; ///< lbf unit

        using pascal = unit<base::pressure>; ///< pascal unit
        inline static constexpr pascal Pa; ///< m2 unit

        using kilopascal = unit<base::pressure, std::kilo>; ///< kilopascal unit
        inline static constexpr kilopascal kPa; ///< kPa unit

        using megapascal = unit<base::pressure, std::mega>; ///< megapascal unit
        inline static constexpr megapascal MPa; ///< MPa unit

        using gigapascal = unit<base::pressure, std::giga>; ///< gigapascal unit
        inline static constexpr gigapascal GPa; ///< GPa unit

        using barometre = unit<base::pressure, std::ratio<100000, 1>>; ///< bar unit
        inline static constexpr barometre bar; ///< bar unit

        using millibar = unit<base::pressure, std::ratio<100, 1>>; ///< millibar unit
        inline static constexpr millibar mbar; ///< mbar unit

        using atmosphere = unit<base::pressure, std::ratio<101325, 1>>; ///< atmosphere unit
        inline static constexpr atmosphere atm; ///< atm unit

        using torricelli = unit<base::pressure, std::ratio<101325, 760>>; ///< torr unit
        inline static constexpr torricelli torr; ///< torr unit


        using kelvin = unit<base::temperature>;
        inline static constexpr kelvin K;


        using mole = unit<base::substance_amount>;
        inline static constexpr mole mol;


        namespace literals {


            #define UNIT_LITERALS(unit)                                                    \
                inline constexpr auto operator"" unit(long double value) noexcept {              \
                    return static_cast<double>(value) * units::unit;                                             \
                }                                                                           

            UNIT_LITERALS(m)
            UNIT_LITERALS(km)
            UNIT_LITERALS(cm)
            UNIT_LITERALS(mm)
            UNIT_LITERALS(um)
            UNIT_LITERALS(nm)
            
            UNIT_LITERALS(s)
            UNIT_LITERALS(ms)
            UNIT_LITERALS(us)
            UNIT_LITERALS(ns)
            UNIT_LITERALS(ps)
            UNIT_LITERALS(min)
            UNIT_LITERALS(h)


        } // namespace literals


    } // namespace units


} // namespace scipp::physics