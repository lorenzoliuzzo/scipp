/**
 * @file    math/constants.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-04
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace constants {


        inline static constexpr physics::scalar_m nan = std::numeric_limits<double>::signaling_NaN(); /// scalar Not a Number

        inline static constexpr physics::scalar_m zero = 0.0; /// scalar Zero

        inline static constexpr physics::scalar_m infinity = std::numeric_limits<double>::infinity(); /// scalar Infinity
        
        inline static constexpr physics::scalar_m pi = 3.14159265358979323846; /// scalar Pi
        
        inline static constexpr physics::scalar_m e = 2.7182818284590452353603; /// scalar Euler's number

        inline static constexpr math::complex<physics::scalar_m> i(0.0, 1.0); /// scalar imaginary unit
        
        inline static constexpr math::dual<physics::scalar_m> epsilon(0.0, 1.0); /// scalar dual unit
        

    } // namespace constants


} // namespace scipp::math