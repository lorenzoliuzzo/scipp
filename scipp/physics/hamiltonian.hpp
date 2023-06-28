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
        calculus::variable<measurement<units::second>>& t; 
        
        measurement<units::kilogram>& mass;

        std::function<calculus::variable<measurement<units::joule>>()> T = kinetic_energy(p, mass);  
        std::function<calculus::variable<measurement<units::joule>>()> V;
        

        hamiltonian(lagrangian<VArgs...>& L) noexcept 
            
            : x{L.x}, t{L.t}, mass{L.mass}, V{L.V}  {

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

            // Store the original values
            auto temp_x = x;
            auto temp_p = p;

            // Compute the initial derivatives
            auto [dHdx_initial, dHdp_initial] = calculus::derivatives(this->operator()(), calculus::wrt(x, p));

            // Compute the intermediate values
            auto x_intermediate = x + 0.5 * dt * dHdp_initial;
            auto p_intermediate = p - 0.5 * dt * dHdx_initial;

            // Update the variables
            x = x_intermediate;
            p = p_intermediate;

            // Compute the derivatives at the intermediate values
            auto [dHdx_intermediate, dHdp_intermediate] = calculus::derivatives(this->operator()(), calculus::wrt(x, p));

            // Update the variables using the RK2 method
            x = temp_x + dt * dHdp_intermediate;
            p = temp_p - dt * dHdx_intermediate;

        }

        void rk4(const measurement<units::second>& dt) noexcept {

            // Store the original values
            auto temp_x = x;
            auto temp_p = p;
            
            // Compute the initial derivatives
            auto [dHdx_initial, dHdp_initial] = calculus::derivatives(this->operator()(), calculus::wrt(x, p));

            // Compute the intermediate values
            auto x_intermediate1 = x + 0.5 * dt * dHdp_initial;
            auto p_intermediate1 = p - 0.5 * dt * dHdx_initial;

            // Update the variables
            x = x_intermediate1;
            p = p_intermediate1;

            // Compute the derivatives at the intermediate values
            auto [dHdx_intermediate1, dHdp_intermediate1] = calculus::derivatives(this->operator()(), calculus::wrt(x, p));

            // Compute the intermediate values
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


    template <typename... VArgs>
    struct hamiltonian_legendre {

        lagrangian<VArgs...> L;
        
        calculus::variable<measurement<units::metre>>& x = L.x; 
        calculus::variable<measurement<op::divide_t<units::joule, units::metre_per_second>>> p;
        calculus::variable<measurement<units::second>>& t = L.t; 

        measurement<units::kilogram>& mass = L.mass;

        std::function<calculus::variable<measurement<units::joule>>()> T = kinetic_energy(p, mass);
        std::function<calculus::variable<measurement<units::joule>>()> V = L.V;

        hamiltonian_legendre(lagrangian<VArgs...>& L_) noexcept : L{L_} {

            p = std::get<0>(calculus::derivatives(L_(), calculus::wrt(L_.x_dot)));
            calculus::variable<measurement<units::metre_per_second>> x_dot = p / mass;
            L.x_dot = x_dot;
            if (std::get<0>(calculus::derivatives(L.x_dot, calculus::wrt(p))) != 1.0 / mass) {
                std::cout << "Error: the derivative of x_dot with respect to p is not 1/mass" << std::endl;
            }
            if (std::get<0>(calculus::derivatives(L(), calculus::wrt(p))) == 0.0) {
                std::cout << "Error: the derivative of L with respect to p is zero" << std::endl;
            }

        }

        inline calculus::variable<measurement<units::joule>> operator()() noexcept {
            
            calculus::variable<measurement<units::joule>> H = p * L.x_dot - L(); 
            auto [dH_dL] = calculus::derivatives(H, calculus::wrt(L()));
            std::cout << "dH_dL" << dH_dL << std::endl;
            return H; 

        }


        void euler(const measurement<units::second>& dt) noexcept {

            auto [dHdx, dHdp] = calculus::derivatives(this->operator()(), calculus::wrt(x, p));
            x += dt * dHdp;
            p -= dt * dHdx; 

        }


        void rk4(const measurement<units::second>& dt) noexcept {

            // Store the original values
            auto temp_x = x;
            auto temp_p = p;
            
            // Compute the initial derivatives
            auto [dHdx_initial, dHdp_initial] = calculus::derivatives(this->operator()(), calculus::wrt(x, p));

            // Compute the intermediate values
            auto x_intermediate1 = x + 0.5 * dt * dHdp_initial;
            auto p_intermediate1 = p - 0.5 * dt * dHdx_initial;

            // Update the variables
            x = x_intermediate1;
            p = p_intermediate1;

            // Compute the derivatives at the intermediate values
            auto [dHdx_intermediate1, dHdp_intermediate1] = calculus::derivatives(this->operator()(), calculus::wrt(x, p));

            // Compute the intermediate values
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
      

    };


} // namespace scipp::physics