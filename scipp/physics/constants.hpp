/**
 * @file    physics/constants.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-28
 * 
 * @copyright Copyright (c) 2023
 */
 


namespace scipp::physics {


    namespace constants {


        using namespace units; ///< import units namespace


        inline static constexpr measurement G(6.67430e-23, N * m2 / kg2); ///< gravitational constant
        
        inline static constexpr velocity_m c(299792458, m / s); ///< speed of light in vacuum

        inline static constexpr measurement h(6.62607015e-34, J * s); ///< Planck constant

        inline static constexpr measurement hbar(1.054571817e-34, J * s); ///< reduced Planck constant

        inline static constexpr measurement mu0(1.25663706212e-6, N / A2); ///< magnetic permeability of vacuum

        // inline static constexpr measurement eps0(math::op::inv(mu0 * c * c)); ///< electric permittivity of vacuum

        // inline static constexpr charge_m e(1.602176634e-19, C); ///< elementary charge

        inline static constexpr mass_m m_e(9.1093837015e-31, kg); ///< electron mass

        inline static constexpr mass_m m_p(1.67262192369e-27, kg); ///< proton mass

        inline static constexpr mass_m m_n(1.67492749804e-27, kg); ///< neutron mass

        inline static constexpr measurement k_B(1.380649e-23, J / K); ///< Boltzmann constant

        inline static constexpr measurement N_A(6.02214076e23 / mol); ///< Avogadro constant

        inline static constexpr auto R = N_A * k_B; ///< ideal gas constant


    } // namespace constants


} // namespace scipp::physics