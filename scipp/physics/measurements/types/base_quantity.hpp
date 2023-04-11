/**
 * @file    physics/measurements/types/base_quantity.hpp
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


        using scalar = base_quantity<0, 0, 0, 0, 0, 0, 0>; ///< scalar base_quantity 

        using metre = base_quantity<1, 0, 0, 0, 0, 0, 0>; ///< metre base_quantity 
        using metre2 = base_quantity<2, 0, 0, 0, 0, 0, 0>; ///< metre2 base_quantity 
        using metre3 = base_quantity<3, 0, 0, 0, 0, 0, 0>; ///< metre3 base_quantity 

        using second = base_quantity<0, 1, 0, 0, 0, 0, 0>; ///< second base_quantity
        using second2 = base_quantity<0, 2, 0, 0, 0, 0, 0>; ///< second base_quantity
        using second3 = base_quantity<0, 3, 0, 0, 0, 0, 0>; ///< second base_quantity

        using kilogram = base_quantity<0, 0, 1, 0, 0, 0, 0>; ///< kilogram base_quantity
        using kilogram2 = base_quantity<0, 0, 2, 0, 0, 0, 0>; ///< kilogram base_quantity
        using kilogram3 = base_quantity<0, 0, 3, 0, 0, 0, 0>; ///< kilogram base_quantity

        using kelvin = base_quantity<0, 0, 0, 1, 0, 0, 0>; ///< kelvin base_quantity
        using kelvin2 = base_quantity<0, 0, 0, 2, 0, 0, 0>; ///< kelvin base_quantity
        using kelvin3 = base_quantity<0, 0, 0, 3, 0, 0, 0>; ///< kelvin base_quantity
                
        using ampere = base_quantity<0, 0, 0, 0, 1, 0, 0>; ///< ampere base_quantity
        using ampere2 = base_quantity<0, 0, 0, 0, 2, 0, 0>; ///< ampere base_quantity
        using ampere3 = base_quantity<0, 0, 0, 0, 3, 0, 0>; ///< ampere base_quantity

        using mole = base_quantity<0, 0, 0, 0, 0, 1, 0>; ///< mole base_quantity
        using mole2 = base_quantity<0, 0, 0, 0, 0, 2, 0>; ///< mole base_quantity

        using candela = base_quantity<0, 0, 0, 0, 0, 0, 1>; ///< candela base_quantity
        using candela2 = base_quantity<0, 0, 0, 0, 0, 0, 2>; ///< candela base_quantity

        using radian = base_quantity<0, 0, 0, 0, 0, 0, 0>; ///< radian base_quantity
        using radian2 = base_quantity<0, 0, 0, 0, 0, 0, 0>; ///< radian base_quantity


        using steradian = base_quantity<0, 0, 0, 0, 0, 0, 0>; ///< steradian base_quantity    
        using steradian2 = base_quantity<0, 0, 0, 0, 0, 0, 0>; ///< steradian base_quantity

        using metre_per_second = base_quantity<1, -1, 0, 0, 0, 0, 0>; ///< metre_per_second base_quantity 

        using metre_per_second2 = base_quantity<1, -2, 0, 0, 0, 0, 0>; ///< metre_per_second2 base_quantity 

        using metre_per_second3 = base_quantity<1, -3, 0, 0, 0, 0, 0>; ///< metre_per_second3 base_quantity 

        using metre2_per_second = base_quantity<2, -1, 0, 0, 0, 0, 0>; ///< metre2_per_second base_quantity 

        using metre2_per_second2 = base_quantity<2, -2, 0, 0, 0, 0, 0>; ///< metre2_per_second2 base_quantity 

        using metre2_per_second3 = base_quantity<2, -3, 0, 0, 0, 0, 0>; ///< metre2_per_second3 base_quantity 

        using metre3_per_second = base_quantity<3, -1, 0, 0, 0, 0, 0>; ///< metre3_per_second base_quantity 

        using metre3_per_second2 = base_quantity<3, -2, 0, 0, 0, 0, 0>; ///< metre3_per_second2 base_quantity 

        using metre3_per_second3 = base_quantity<3, -3, 0, 0, 0, 0, 0>; ///< metre3_per_second3 base_quantity 

        using metre_per_kilogram = base_quantity<1, 0, -1, 0, 0, 0, 0>; ///< metre_per_kilogram base_quantity 

        using metre_per_kilogram2 = base_quantity<1, 0, -2, 0, 0, 0, 0>; ///< metre_per_kilogram2 base_quantity 

        using metre_per_kilogram3 = base_quantity<1, 0, -3, 0, 0, 0, 0>; ///< metre_per_kilogram3 base_quantity 

        using metre2_per_kilogram = base_quantity<2, 0, -1, 0, 0, 0, 0>; ///< metre2_per_kilogram base_quantity 

        using metre2_per_kilogram2 = base_quantity<2, 0, -2, 0, 0, 0, 0>; ///< metre2_per_kilogram2 base_quantity 

        using metre2_per_kilogram3 = base_quantity<2, 0, -3, 0, 0, 0, 0>; ///< metre2_per_kilogram3 base_quantity 

        using metre3_per_kilogram = base_quantity<3, 0, -1, 0, 0, 0, 0>; ///< metre3_per_kilogram base_quantity 

        using metre3_per_kilogram2 = base_quantity<3, 0, -2, 0, 0, 0, 0>; ///< metre3_per_kilogram2 base_quantity 

        using metre3_per_kilogram3 = base_quantity<3, 0, -3, 0, 0, 0, 0>; ///< metre3_per_kilogram3 base_quantity 

        using metre_per_ampere = base_quantity<1, 0, 0, -1, 0, 0, 0>; ///< metre_per_ampere base_quantity 

        using metre_per_ampere2 = base_quantity<1, 0, 0, -2, 0, 0, 0>; ///< metre_per_ampere2 base_quantity 

        using metre_per_ampere3 = base_quantity<1, 0, 0, -3, 0, 0, 0>; ///< metre_per_ampere3 base_quantity 

        using metre2_per_ampere = base_quantity<2, 0, 0, -1, 0, 0, 0>; ///< metre2_per_ampere base_quantity 

        using metre2_per_ampere2 = base_quantity<2, 0, 0, -2, 0, 0, 0>; ///< metre2_per_ampere2 base_quantity 

        using metre2_per_ampere3 = base_quantity<2, 0, 0, -3, 0, 0, 0>; ///< metre2_per_ampere3 base_quantity 

        using metre3_per_ampere = base_quantity<3, 0, 0, -1, 0, 0, 0>; ///< metre3_per_ampere base_quantity 

        using metre3_per_ampere2 = base_quantity<3, 0, 0, -2, 0, 0, 0>; ///< metre3_per_ampere2 base_quantity 

        using metre3_per_ampere3 = base_quantity<3, 0, 0, -3, 0, 0, 0>; ///< metre3_per_ampere3 base_quantity 

        using metre_per_kelvin = base_quantity<1, 0, 0, 0, -1, 0, 0>; ///< metre_per_kelvin base_quantity 

        using metre_per_kelvin2 = base_quantity<1, 0, 0, 0, -2, 0, 0>; ///< metre_per_kelvin2 base_quantity 

        using metre_per_kelvin3 = base_quantity<1, 0, 0, 0, -3, 0, 0>; ///< metre_per_kelvin3 base_quantity 

        using metre2_per_kelvin = base_quantity<2, 0, 0, 0, -1, 0, 0>; ///< metre2_per_kelvin base_quantity 

        using metre2_per_kelvin2 = base_quantity<2, 0, 0, 0, -2, 0, 0>; ///< metre2_per_kelvin2 base_quantity 

        using metre2_per_kelvin3 = base_quantity<2, 0, 0, 0, -3, 0, 0>; ///< metre2_per_kelvin3 base_quantity 

        using metre3_per_kelvin = base_quantity<3, 0, 0, 0, -1, 0, 0>; ///< metre3_per_kelvin base_quantity 

        using metre3_per_kelvin2 = base_quantity<3, 0, 0, 0, -2, 0, 0>; ///< metre3_per_kelvin2 base_quantity 

        using metre3_per_kelvin3 = base_quantity<3, 0, 0, 0, -3, 0, 0>; ///< metre3_per_kelvin3 base_quantity 


        using kilogram_metre_per_second2 = base_quantity<1, -2, 1, 0, 0, 0, 0>; ///< kilogram_metre_per_second2 base_quantity  

        using kilogram_metre2_per_second2 = base_quantity<2, -2, 1, 0, 0, 0, 0>; ///< kilogram_metre2_per_second2 base_quantity  

        using radian_per_second = base_quantity<0, -1, 0, 0, 0, 0, 0>; ///< radian_per_second base_quantity

        using radian_per_second2 = base_quantity<0, -2, 0, 0, 0, 0, 0>; ///< radian_per_second2 base_quantity


    /// =================================================
    /// Composed base_quantity
    /// =================================================

        using hertz = base_quantity<0, -1, 0, 0, 0, 0, 0>; ///< hertz base_quantity  

        using newton = base_quantity<1, -2, 1, 0, 0, 0, 0>; ///< newton base_quantity

        using pascal = base_quantity<-1, -2, 1, 0, 0, 0, 0>; ///< pascal base_quantity

        using joule = base_quantity<2, -2, 1, 0, 0, 0, 0>; ///< joule base_quantity

        using watt = base_quantity<2, -3, 1, 0, 0, 0, 0>; ///< watt base_quantity

        using coulomb = base_quantity<0, 0, 1, 1, 0, 0, 0>; ///< coulomb base_quantity

        using volt = base_quantity<2, -3, 1, -1, 0, 0, 0>; ///< volt base_quantity

        using farad = base_quantity<-2, -2, -1, 2, 0, 0, 0>; ///< farad base_quantity

        using ohm = base_quantity<2, -3, 1, -2, 0, 0, 0>; ///< ohm base_quantity

        using siemens = base_quantity<-2, -3, -1, 2, 0, 0, 0>; ///< siemens base_quantity

        using weber = base_quantity<2, -2, 1, -1, 0, 0, 0>; ///< weber base_quantity

        using tesla = base_quantity<0, -2, 1, -1, 0, 0, 0>; ///< tesla base_quantity

        using henry = base_quantity<2, -2, 1, -2, 0, 0, 0>; ///< henry base_quantity


    } // namespace units


} // namespace scipp::physics