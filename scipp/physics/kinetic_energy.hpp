/**
 * @file    physics/kinetic_energy.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-28
 * 
 * @copyright Copyright (c) 2023
 */
 


namespace scipp::physics {


    inline calculus::variable<measurement<units::joule>> kinetic_energy(const measurement<units::kilogram>& mass, const calculus::variable<measurement<units::metre_per_second>>& velocity) {
        
        return 0.5 * mass * velocity * velocity; 

    } 

    inline calculus::variable<measurement<units::joule>> kinetic_energy(const calculus::variable<measurement<units::metre_per_second>>& velocity, const measurement<units::kilogram>& mass) {
        
        return 0.5 * mass * velocity * velocity; 

    } 

    inline calculus::variable<measurement<units::joule>> kinetic_energy(const measurement<units::kilogram>& mass, const calculus::variable<measurement<units::kilogram_metre_per_second>>& momentum) {
        
        return 0.5 * momentum * momentum / mass; 

    } 

    inline calculus::variable<measurement<units::joule>> kinetic_energy(const calculus::variable<measurement<units::kilogram_metre_per_second>>& momentum, const measurement<units::kilogram>& mass) {
        
        return 0.5 * momentum * momentum / mass; 

    } 


    template <size_t N> 
    inline calculus::variable<measurement<units::joule>> kinetic_energy(const measurement<units::kilogram>& mass, const std::array<calculus::variable<measurement<units::metre_per_second>>, N>& velocity) {

        calculus::variable<measurement<units::joule>> T;
        meta::for_<N>([&](auto i) constexpr {
            T += 0.5 * mass * velocity[i] * velocity[i]; 
        });    
        return T; 

    } 

    template <size_t N> 
    inline calculus::variable<measurement<units::joule>> kinetic_energy(const std::array<calculus::variable<measurement<units::metre_per_second>>, N>& velocity, const measurement<units::kilogram>& mass) {

        calculus::variable<measurement<units::joule>> T;
        meta::for_<N>([&](auto i) constexpr {
            T += 0.5 * mass * velocity[i] * velocity[i]; 
        });    
        return T; 

    } 

    template <size_t N> 
    inline calculus::variable<measurement<units::joule>> kinetic_energy(const measurement<units::kilogram>& mass, const std::array<calculus::variable<measurement<units::kilogram_metre_per_second>>, N>& momentum) {

        calculus::variable<measurement<units::joule>> T;
        meta::for_<N>([&](auto i) constexpr {
            T += 0.5 * momentum[i] * momentum[i] / mass; 
        });    
        return T; 

    } 

    template <size_t N> 
    inline calculus::variable<measurement<units::joule>> kinetic_energy(const std::array<calculus::variable<measurement<units::kilogram_metre_per_second>>, N>& momentum, const measurement<units::kilogram>& mass) {

        calculus::variable<measurement<units::joule>> T;
        meta::for_<N>([&](auto i) constexpr {
            T += 0.5 * momentum[i] * momentum[i] / mass; 
        });    
        return T; 

    } 


} // namespace scipp::physics