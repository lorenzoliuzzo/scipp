/**
 * @file    physics/kinetic_energy.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-25
 * 
 * @copyright Copyright (c) 2023
 */
 


namespace scipp::physics {



    // inline auto kinetic_energy(const measurement<units::kilogram>& mass, 
    //                            const measurement<units::metre_per_second>& velocity) noexcept 
    //     -> calculus::variable<measurement<units::joule>> {

            
    //         return 0.5 * mass * velocity * velocity;

    // } 

    inline auto kinetic_energy(const calculus::variable<measurement<units::metre_per_second>>& velocity,
                               const measurement<units::kilogram>& mass) noexcept 
        -> calculus::variable<measurement<units::joule>> {
        
        calculus::variable<measurement<units::joule>> T = 0.5 * mass * velocity * velocity;
        return T;

    } 


    // inline auto kinetic_energy(const measurement<units::kilogram>& mass, 
    //                            const measurement<units::kilogram_metre_per_second>& momentum) noexcept 
    //     -> calculus::variable<measurement<units::joule>> {
            
    //         return 0.5 * momentum * momentum / mass;

    // } 


    inline auto kinetic_energy(const calculus::variable<measurement<units::kilogram_metre_per_second>>& momentum, 
                               const measurement<units::kilogram>& mass) noexcept 
        -> calculus::variable<measurement<units::joule>> {
            
        return 0.5 * momentum * momentum / mass;
        
    } 


} // namespace scipp::physics