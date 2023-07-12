/**
 * @file    physics/kinetic_energy.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-28
 * 
 * @copyright Copyright (c) 2023
 */
 


namespace scipp::physics {


    inline calculus::variable<measurement<base::energy>> kinetic_energy(const measurement<base::mass>& mass, const calculus::variable<measurement<base::velocity>>& v) {
        
        return 0.5 * mass * math::op::square(v); 

    } 

    inline calculus::variable<measurement<base::energy>> kinetic_energy(const calculus::variable<measurement<base::velocity>>& v, const measurement<base::mass>& mass) {
        
        return 0.5 * mass * math::op::square(v); 

    } 

    inline calculus::variable<measurement<base::energy>> kinetic_energy(const measurement<base::mass>& mass, const calculus::variable<measurement<base::momentum>>& p) {
        
        return 0.5 * math::op::square(p) / mass; 

    } 

    inline calculus::variable<measurement<base::energy>> kinetic_energy(const calculus::variable<measurement<base::momentum>>& p, const measurement<base::mass>& mass) {
        
        return 0.5 * math::op::square(p) / mass; 

    } 


    template <size_t N> 
    inline calculus::variable<measurement<base::energy>> kinetic_energy(const measurement<base::mass>& mass, const std::array<calculus::variable<measurement<base::velocity>>, N>& velocity) {

        calculus::variable<measurement<base::energy>> T;
        meta::for_<N>([&](auto i) constexpr {
            T += 0.5 * mass * math::op::square(velocity[i]); 
        });    
        return T; 

    } 

    template <size_t N> 
    inline calculus::variable<measurement<base::energy>> kinetic_energy(const std::array<calculus::variable<measurement<base::velocity>>, N>& velocity, const measurement<base::mass>& mass) {

        calculus::variable<measurement<base::energy>> T;
        meta::for_<N>([&](auto i) constexpr {
            T += 0.5 * mass * math::op::square(velocity[i]); 
        });    
        return T; 

    } 

    template <size_t N> 
    inline calculus::variable<measurement<base::energy>> kinetic_energy(const measurement<base::mass>& mass, const std::array<calculus::variable<measurement<base::momentum>>, N>& p) {

        calculus::variable<measurement<base::energy>> T;
        meta::for_<N>([&](auto i) constexpr {
            T += 0.5 * math::op::square(p[i]) / mass; 
        });    
        return T; 

    } 

    template <size_t N> 
    inline calculus::variable<measurement<base::energy>> kinetic_energy(const std::array<calculus::variable<measurement<base::momentum>>, N>& p, const measurement<base::mass>& mass) {

        calculus::variable<measurement<base::energy>> T;
        meta::for_<N>([&](auto i) constexpr {
            T += 0.5 * math::op::square(p[i]) / mass; 
        });    
        return T; 

    } 


} // namespace scipp::physics