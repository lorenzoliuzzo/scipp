/**
 * @file    physics/lagrangian.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-25
 * 
 * @copyright Copyright (c) 2023
 */
 


namespace scipp::physics {


    template <typename... VArgs>
    struct lagrangian {

        calculus::variable<measurement<units::metre>>& x;
        calculus::variable<measurement<units::metre_per_second>>& x_dot;
        // calculus::variable<measurement<units::second>>& t; 

        const measurement<units::kilogram>& mass; 
        std::tuple<std::decay_t<VArgs>...> pot_args; 

        std::function<calculus::variable<measurement<units::joule>>()> T = [&]() { return 0.5 * mass * x_dot * x_dot; };  
        std::function<calculus::variable<measurement<units::joule>>()> V = potential_energy(x, pot_args);
        
        // calculus::variable<measurement<units::joule>> T = 0.5 * mass * x_dot * x_dot; 
        // calculus::variable<measurement<units::joule>> V; 
        

        lagrangian(calculus::variable<measurement<units::metre>>& position, 
                   calculus::variable<measurement<units::metre_per_second>>& velocity, 
                   const measurement<units::kilogram>& m, const VArgs&... args) noexcept 
                
            : x{position}, x_dot{velocity}, 
              mass{m}, pot_args{std::forward_as_tuple(args...)} {}


        lagrangian(calculus::variable<measurement<units::metre>>& position, 
                   calculus::variable<measurement<units::metre_per_second>>& velocity, 
                   const measurement<units::kilogram>& m, const std::tuple<VArgs...>& args) noexcept 
                
            : x{position}, x_dot{velocity}, 
              mass{m}, pot_args{args} {}


        // lagrangian(calculus::variable<measurement<units::metre>>& position, 
        //            calculus::variable<measurement<units::kilogram_metre_per_second>>& momentum, 
        //            const measurement<units::kilogram>& m, const VArgs&... args) noexcept : mass{m}, x{position}, x_dot{momentum / mass} {

        //     T = kinetic_energy(momentum, mass); 
        //     V = potential_energy(x, args...);
            
        // }


        inline calculus::variable<measurement<units::joule>> operator()() noexcept {
            
            return T() - V(); 

        }


    }; // class lagrangian


} // namespace scipp::physics