/**
 * @file    physics/lagrangian.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-28
 * 
 * @copyright Copyright (c) 2023
 */
 


namespace scipp::physics {


    template <typename... PotArgs>
    struct lagrangian {

        measurement<units::kilogram>& m; 
        calculus::variable<measurement<units::metre>>& x;
        calculus::variable<measurement<units::metre_per_second>>& x_dot;
        calculus::variable<measurement<units::second>>& t; 

        potential_energy<PotArgs...>& potential;
        calculus::variable<measurement<units::joule>> V{}, T{}; 


        lagrangian(measurement<units::kilogram>& mass,
                   calculus::variable<measurement<units::metre>>& position, 
                   calculus::variable<measurement<units::metre_per_second>>& velocity, 
                   calculus::variable<measurement<units::second>>& time,
                   potential_energy<PotArgs...>& potential) noexcept 
                
            : m{mass}, x{position}, x_dot{velocity}, t{time}, potential{potential} {}


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

        inline auto derivatives() noexcept {
            
            return calculus::derivatives(this->operator()(), calculus::wrt(this->x, this->x_dot, this->t));

        }

    };


    template <size_t DIM, typename... Vars>
    struct lagrangian_multidim {

        // inline static constexpr dim = sizeof...(Vars);

        measurement<units::kilogram>& m; 

        std::array<calculus::variable<measurement<units::metre>>, DIM>& x;
        std::array<calculus::variable<measurement<units::metre_per_second>>, DIM>& x_dot;
        calculus::variable<measurement<units::second>>& t; 

        // potential_energy<VArgs...>& potential;
        calculus::variable<measurement<units::joule>> V{}, T{}; 

        lagrangian_multidim(measurement<units::kilogram>& mass,
                            std::array<calculus::variable<measurement<units::metre>>, DIM>& variables,
                            std::array<calculus::variable<measurement<units::metre_per_second>>, DIM>& tangents,
                            calculus::variable<measurement<units::second>>& time) noexcept
            
            : m{mass}, x{variables}, x_dot{tangents}, t{time} {}


        inline void update_kinetic() noexcept {

            this->T = kinetic_energy(this->m, this->x_dot);
        
        }

        // inline void update_potential() noexcept {

        //     this->V = this->potential(this->params);
        
        // }


        inline calculus::variable<measurement<units::joule>> operator()() noexcept {

            update_kinetic();
            // update_potential();
            return this->T - this->V;

        }

        // inline auto derivatives() noexcept {

        //     return calculus::derivatives(this->operator()(), calculus::wrt(this->params, this->x_dot, this->t));
            
        // }

    };


    template <typename... Vars>
    struct lagrangian_multi {

        inline static constexpr size_t dim = sizeof...(Vars);

        measurement<units::kilogram>& m; 
        // calculus::variable<measurement<units::second>>& t; 

        std::tuple<Vars...> variables;
        std::function<std::array<calculus::variable<measurement<units::metre>>, dim>(Vars...)>& parametrization;
        // std::array<calculus::variable<measurement<units::metre_per_second>>, dim>& x_dot;

        // potential_energy<VArgs...>& potential;
        calculus::variable<measurement<units::joule>> V{}, T{}; 

        lagrangian_multi(measurement<units::kilogram>& mass,
                        //  calculus::variable<measurement<units::second>>& time, 
                         std::function<std::array<calculus::variable<measurement<units::metre>>, dim>(Vars...)>& gamma,
                         Vars... variables
                        //  std::array<calculus::variable<measurement<units::metre_per_second>>, dim>& tangents
                         ) noexcept
            
            : m{mass}, variables{std::forward_as_tuple(variables...)} {} //, parametrization{gamma} {}


        inline void update_kinetic() noexcept {

            // this->T = kinetic_energy(this->m, this->x_dot);
        
        }

        // inline void update_potential() noexcept {

        //     this->V = this->potential(this->params);
        
        // }


        inline calculus::variable<measurement<units::joule>> operator()() noexcept {

            update_kinetic();
            // update_potential();
            return this->T - this->V;

        }

        // inline auto derivatives() noexcept {

        //     return calculus::derivatives(this->operator()(), calculus::wrt(this->params, this->x_dot, this->t));
            
        // }

    };


} // namespace scipp::physics