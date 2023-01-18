/**
 * @file    constants.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-01
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp {


    namespace physics {


        namespace constants {


            constexpr measurement G(6.67430e-17, N * km.square() / kg.square()); ///< gravitational constant
            
            constexpr measurement c(299792458, m / s); ///< speed of light in vacuum

            constexpr measurement h(6.62607015e-34, J * s); ///< Planck constant

            constexpr measurement hbar(1.054571817e-34, J * s); ///< reduced Planck constant

            constexpr measurement mu0(1.25663706212e-6, N / A.square()); ///< magnetic permeability of vacuum

            constexpr measurement eps0 = 1 / (mu0 * square(c)); ///< electric permittivity of vacuum

            constexpr measurement e(1.602176634e-19, C); ///< elementary charge

            constexpr measurement m_e(9.1093837015e-31, kg); ///< electron mass

            constexpr measurement m_p(1.67262192369e-27, kg); ///< proton mass

            constexpr measurement m_n(1.67492749804e-27, kg); ///< neutron mass

            constexpr measurement k_B(1.380649e-23, J / K); ///< Boltzmann constant

            constexpr measurement N_A(6.02214076e23, mol.inv()); ///< Avogadro constant

            constexpr measurement R = N_A * k_B; ///< ideal gas constant


        } // namespace constants


    } // namespace physics


} // namespace scipp::measurements