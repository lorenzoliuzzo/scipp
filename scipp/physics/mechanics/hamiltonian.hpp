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

        measurement<base::mass>& m;
        calculus::variable<measurement<base::length>>& x; 
        calculus::variable<measurement<base::momentum>> p;
        calculus::variable<measurement<base::time>>& t; 
        
        potential_energy<VArgs...>& potential;
        calculus::variable<measurement<base::energy>> V{}, T{}; 

        hamiltonian(lagrangian<VArgs...>& L) noexcept 
            
            : m{L.m}, x{L.x}, t{L.t}, potential{L.potential}  {

            p = std::get<0>(calculus::derivatives(L(), calculus::wrt(L.x_dot)));

        }

        inline void update_kinetic() noexcept {

            this->T = kinetic_energy(this->m, this->p);

        }

        inline void update_potential() noexcept {

            this->V = this->potential(this->x);

        }

        inline calculus::variable<measurement<base::energy>> operator()() noexcept {
            
            update_kinetic();
            update_potential();
            return this->T + this->V; 

        }

        inline auto derivatives() noexcept {
            
            return calculus::derivatives(this->operator()(), calculus::wrt(this->x, this->p, this->t));

        }


        template <size_t N>
        void evolve(const measurement<base::time>& tmax) noexcept {

            const auto dt = tmax / N;
            for (size_t i = 0; i < N; ++i) 
                rk4(dt);

        }


        void euler(const measurement<base::time>& dt) noexcept {

            auto [dHdx, dHdp] = calculus::derivatives(this->operator()(), calculus::wrt(this->x, this->p));
            this->x += dt * dHdp;
            this->p -= dt * dHdx; 
            this->t += dt;

        }

        void rk2(const measurement<base::time>& dt) noexcept {

            // Store the original values
            auto temp_x = this->x;
            auto temp_p = this->p;

            // Compute the initial derivatives
            auto [dHdx_initial, dHdp_initial] = calculus::derivatives(this->operator()(), calculus::wrt(this->x, this->p));

            // Compute the intermediate values
            auto x_intermediate = this->x + 0.5 * dt * dHdp_initial;
            auto p_intermediate = this->p - 0.5 * dt * dHdx_initial;

            // Update the variables
            this->x = x_intermediate;
            this->p = p_intermediate;

            // Compute the derivatives at the intermediate values
            auto [dHdx_intermediate, dHdp_intermediate] = calculus::derivatives(this->operator()(), calculus::wrt(this->x, this->p));

            // Update the variables using the RK2 method
            this->x = temp_x + dt * dHdp_intermediate;
            this->p = temp_p - dt * dHdx_intermediate;
            this->t += dt;

        }

        void rk4(const measurement<base::time>& dt) noexcept {

            // Store the original values
            auto temp_x = this->x;
            auto temp_p = this->p;
            
            // Compute the initial derivatives
            auto [dHdx_initial, dHdp_initial] = calculus::derivatives(this->operator()(), calculus::wrt(this->x, this->p));

            // Compute the intermediate values
            auto x_intermediate1 = this->x + 0.5 * dt * dHdp_initial;
            auto p_intermediate1 = this->p - 0.5 * dt * dHdx_initial;

            // Update the variables
            this->x = x_intermediate1;
            this->p = p_intermediate1;

            // Compute the derivatives at the intermediate values
            auto [dHdx_intermediate1, dHdp_intermediate1] = calculus::derivatives(this->operator()(), calculus::wrt(this->x, this->p));

            // Compute the intermediate values
            auto x_intermediate2 = temp_x + 0.5 * dt * dHdp_intermediate1;
            auto p_intermediate2 = temp_p - 0.5 * dt * dHdx_intermediate1;

            // Update the variables
            this->x = x_intermediate2;
            this->p = p_intermediate2;

            // Compute the derivatives at the intermediate values
            auto [dHdx_intermediate2, dHdp_intermediate2] = calculus::derivatives(this->operator()(), calculus::wrt(this->x, this->p));

            // Restore the original values
            this->x = temp_x;
            this->p = temp_p;

            auto x_intermediate3 = temp_x + dt * dHdp_intermediate2;
            auto p_intermediate3 = temp_p - dt * dHdx_intermediate2;

            // Update the variables
            this->x = x_intermediate3;
            this->p = p_intermediate3;

            // Compute the derivatives at the intermediate values
            auto [dHdx_final, dHdp_final] = calculus::derivatives(this->operator()(), calculus::wrt(this->x, this->p));

            // Update the variables using the RK4 method
            this->x = temp_x + (dt / 6.0) * (dHdp_initial + 2.0 * dHdp_intermediate1 + 2.0 * dHdp_intermediate2 + dHdp_final);
            this->p = temp_p - (dt / 6.0) * (dHdx_initial + 2.0 * dHdx_intermediate1 + 2.0 * dHdx_intermediate2 + dHdx_final);
            this->t += dt;

        }
      

        // template <size_t N>
        // void plot_evolution(const measurement<base::time>& tmax) noexcept {

        //     std::vector<double> x_i(N), p_i(N), E_i(N), t_i(N);             /// value containers for plotting
        //     const auto dt = tmax / N;                                       /// time step

        //     meta::for_<N>([&](auto i) constexpr {

        //         this->rk4(dt);                                              /// evolving the system with rk4
        //         t_i[i] = val(this->t).value; 
        //         x_i[i] = val(this->x).value;                                /// extracting the variable value and then extracting the measurement value
        //         p_i[i] = val(this->p).value; 
        //         E_i[i] = val(this->operator()()).value;

        //     }); 

        //     plt::figure(); 
        //     plt::title("phase space p-x");                          
        //     plt::plot(x_i, p_i); 
        //     // plt::xlabel(std::string("x [", units::m::to_string(), "]"));
        //     // // plt::ylabel(std::string("p [", units::m_s::to_string(), "]"));
        //     plt::grid(true);
        //     plt::tight_layout(); 

        //     plt::figure(); 
        //     plt::title("Energy - time"); 
        //     plt::plot(t_i, E_i);
        //     plt::grid(true);
        //     plt::tight_layout(); 
            
        //     plt::show(); 

        // }



    }; // class hamiltonian


} // namespace scipp::physics