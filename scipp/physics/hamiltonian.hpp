/**
 * @file    physics/hamiltonian.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-25
 * 
 * @copyright Copyright (c) 2023
 */
 


namespace scipp::physics {


    template <typename... VArgs>
    struct hamiltonian {

        calculus::variable<measurement<units::metre>>& x; 
        calculus::variable<measurement<op::divide_t<units::joule, units::metre_per_second>>> p;
        
        const measurement<units::kilogram>& mass;

        std::function<calculus::variable<measurement<units::joule>>()> T = [&]() { return 0.5 * p * p / mass; };  
        std::function<calculus::variable<measurement<units::joule>>()> V;
        

        hamiltonian(lagrangian<VArgs...>& L) noexcept 
            
            : x{L.x}, mass{L.mass}, V{L.V}  {

            p = std::get<0>(calculus::derivatives(L(), calculus::wrt(L.x_dot)));

        }


        inline calculus::variable<measurement<units::joule>> operator()() noexcept {
             
            return T() + V(); 

        }


        void euler(const measurement<units::second>& dt) noexcept {

            auto [dHdx, dHdp] = calculus::derivatives(this->operator()(), calculus::wrt(x, p));
            x += dt * dHdp;
            p -= dt * dHdx; 

        }

        void rk2(const measurement<units::second>& dt) noexcept {

            // Compute the initial derivatives
            auto [dHdx_initial, dHdp_initial] = calculus::derivatives(this->operator()(), calculus::wrt(x, p));

            // Compute the intermediate values
            auto x_intermediate = x + 0.5 * dt * dHdp_initial;
            auto p_intermediate = p - 0.5 * dt * dHdx_initial;

            auto temp_x = x;
            auto temp_p = p;
            x = x_intermediate;
            p = p_intermediate;

            // Compute the derivatives at the intermediate values
            auto [dHdx_intermediate, dHdp_intermediate] = calculus::derivatives(this->operator()(), calculus::wrt(x, p));

            // Update the variables using the RK2 method
            x = temp_x + dt * dHdp_intermediate;
            p = temp_p - dt * dHdx_intermediate;

        }

void rk4(const measurement<units::second>& dt) noexcept {
    // Compute the initial derivatives
    auto [dHdx_initial, dHdp_initial] = calculus::derivatives(this->operator()(), calculus::wrt(x, p));

    // Compute the intermediate values
    auto x_intermediate1 = x + 0.5 * dt * dHdp_initial;
    auto p_intermediate1 = p - 0.5 * dt * dHdx_initial;

    // Store the original values
    auto temp_x = x;
    auto temp_p = p;

    // Update the variables
    x = x_intermediate1;
    p = p_intermediate1;

    // Compute the derivatives at the intermediate values
    auto [dHdx_intermediate1, dHdp_intermediate1] = calculus::derivatives(this->operator()(), calculus::wrt(x, p));

    auto x_intermediate2 = temp_x + 0.5 * dt * dHdp_intermediate1;
    auto p_intermediate2 = temp_p - 0.5 * dt * dHdx_intermediate1;

    // Update the variables
    x = x_intermediate2;
    p = p_intermediate2;

    // Compute the derivatives at the intermediate values
    auto [dHdx_intermediate2, dHdp_intermediate2] = calculus::derivatives(this->operator()(), calculus::wrt(x, p));

    // Restore the original values
    x = temp_x;
    p = temp_p;

    auto x_intermediate3 = temp_x + dt * dHdp_intermediate2;
    auto p_intermediate3 = temp_p - dt * dHdx_intermediate2;

    // Update the variables
    x = x_intermediate3;
    p = p_intermediate3;

    // Compute the derivatives at the intermediate values
    auto [dHdx_final, dHdp_final] = calculus::derivatives(this->operator()(), calculus::wrt(x, p));

    // Update the variables using the RK4 method
    x = temp_x + (dt / 6.0) * (dHdp_initial + 2.0 * dHdp_intermediate1 + 2.0 * dHdp_intermediate2 + dHdp_final);
    p = temp_p - (dt / 6.0) * (dHdx_initial + 2.0 * dHdx_intermediate1 + 2.0 * dHdx_intermediate2 + dHdx_final);
}
      

    }; // class hamiltonian


} // namespace scipp::physics