/**
 * @file    physics/lagrangian.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-28
 * 
 * @copyright Copyright (c) 2023
 */
 


namespace scipp::physics {


    template <typename... VArgs>
    struct lagrangian {


        calculus::variable<measurement<units::metre>>& x;
        calculus::variable<measurement<units::metre_per_second>>& x_dot;
        calculus::variable<measurement<units::second>>& t; 

        measurement<units::kilogram>& mass; 
        std::tuple<std::decay_t<VArgs>...> pot_args; 

        std::function<calculus::variable<measurement<units::joule>>()> T = kinetic_energy(x_dot, mass);  
        std::function<calculus::variable<measurement<units::joule>>()> V = potential_energy(x, pot_args);
        

        lagrangian(calculus::variable<measurement<units::metre>>& position, 
                   calculus::variable<measurement<units::metre_per_second>>& velocity, 
                   calculus::variable<measurement<units::second>>& time,
                   measurement<units::kilogram>& m, const VArgs&... args) noexcept 
                
            : x{position}, x_dot{velocity}, t{time}, mass{m}, pot_args{std::forward_as_tuple(std::decay_t<VArgs>(args)...)} {}


        lagrangian(calculus::variable<measurement<units::metre>>& position, 
                   calculus::variable<measurement<units::metre_per_second>>& velocity, 
                   measurement<units::kilogram>& m, const std::tuple<VArgs...>& args) noexcept 
                
            : x{position}, x_dot{velocity}, mass{m}, pot_args{args} {}



        lagrangian(calculus::variable<measurement<units::metre>>& position, 
                   calculus::variable<measurement<units::kilogram_metre_per_second>>& momentum, 
                   calculus::variable<measurement<units::second>>& time,
                   measurement<units::kilogram>& m, const VArgs&... args) noexcept 
                
            : x{position}, t{time}, mass{m}, pot_args{std::forward_as_tuple(std::decay_t<VArgs>(args)...)} {

            x_dot = momentum / mass;
        
        }


        lagrangian(calculus::variable<measurement<units::metre>>& position, 
                   calculus::variable<measurement<units::kilogram_metre_per_second>>& momentum, 
                   measurement<units::kilogram>& m, const std::tuple<VArgs...>& args) noexcept 
                
            : x{position}, mass{m}, pot_args{args} {

            x_dot = momentum / mass;
        
        }


        inline calculus::variable<measurement<units::joule>> operator()() noexcept {
            
            return T() - V(); 

        }


    }; // class lagrangian


    template <typename... VArgs>
    struct Lagrangian {

        measurement<units::kilogram>& m; 
        calculus::variable<measurement<units::metre>>& x;
        calculus::variable<measurement<units::metre_per_second>>& x_dot;
        // calculus::variable<measurement<units::second>>& t; 

        potential_energy<VArgs...>& potential;
        calculus::variable<measurement<units::joule>> V{}, T{}; 


        Lagrangian(measurement<units::kilogram>& mass,
                   calculus::variable<measurement<units::metre>>& position, 
                   calculus::variable<measurement<units::metre_per_second>>& velocity, 
                //    calculus::variable<measurement<units::second>>& time,
                   potential_energy<VArgs...>& potential) noexcept 
                
            : m{mass}, x{position}, x_dot{velocity}, potential{potential} {}


        // Lagrangian(measurement<units::kilogram>& mass,
        //            calculus::variable<measurement<units::metre>>& position, 
        //            calculus::variable<measurement<units::kilogram_metre_per_second>>& momentum, 
        //         //    calculus::variable<measurement<units::second>>& time,
        //            potential_energy<VArgs...>& potential) noexcept 
                
        //     : m{mass}, x{position}, x_dot{calculus::variable<measurement<units::metre_per_second>>(momentum / mass)}, potential{potential} {
            
        //     update_kinetic();
        //     update_potential(); 

        // }

        inline void update_kinetic() noexcept {

            this->T = kinetic_energy(this->m, this->x_dot);

        }

        inline void update_potential() noexcept {

            this->V = this->potential(this->x);

        }

        inline calculus::variable<measurement<units::joule>> operator()() noexcept {
            
            update_kinetic();
            update_potential();
            return this->T - this->V; 

        }

    };


} // namespace scipp::physics