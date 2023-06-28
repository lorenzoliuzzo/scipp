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


} // namespace scipp::physics