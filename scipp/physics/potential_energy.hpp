/**
 * @file    physics/potential_energy.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-25
 * 
 * @copyright Copyright (c) 2023
 */
 


namespace scipp::physics {


    // template <typename... VArgs>
    // struct potential {

    //     static std::function<calculus::variable<measurement<units::joule>>(calculus::variable<measurement<units::metre>>, VArgs...)> V_func; 

    //     inline static auto f(const calculus::variable<measurement<units::metre>>& x, const VArgs&... params)
    //         -> calculus::variable<measurement<units::joule>> {

    //         return V_func(x, params...); 

    //     }

    // }; // class potential


    template <typename... VArgs>
    struct potential {

        calculus::variable<measurement<units::metre>>& x;

        std::tuple<std::decay_t<VArgs>...> params; 

        potential(calculus::variable<measurement<units::metre>>& x, const VArgs&... params) noexcept 
            
            : x{x}, params{std::forward_as_tuple(std::decay_t<VArgs>(params)...)} {}


        potential(calculus::variable<measurement<units::metre>>& x, const std::tuple<VArgs...>& params) noexcept 
            
            : x{x}, params{params} {}


        virtual inline calculus::variable<measurement<units::joule>> operator()() = 0; 

    };


    struct spring_potential : potential<measurement<units::newton_per_metre>, measurement<units::metre>> {


        spring_potential(calculus::variable<measurement<units::metre>>& x, 
                         const measurement<units::newton_per_metre>& k, 
                         const measurement<units::metre>& l0) noexcept 
                         
            : potential<measurement<units::newton_per_metre>, measurement<units::metre>>(x, k, l0) {}


        spring_potential(calculus::variable<measurement<units::metre>>& x, 
                         const std::tuple<measurement<units::newton_per_metre>, measurement<units::metre>>& params) noexcept 
            
            : potential<measurement<units::newton_per_metre>, measurement<units::metre>>(x, params) {}
            

        inline calculus::variable<measurement<units::joule>> operator()() override {
            
            auto& [k, l0] = this->params; 
            return 0.5 * k * (x - l0) * (x - l0);

        }

    };


    template <typename... VArgs>
    inline auto potential_energy(const calculus::variable<measurement<units::metre>>& x, const VArgs&... args) {

        std::tuple<std::decay_t<VArgs>...> parameters = std::forward_as_tuple(args...); 
        
        if constexpr (is_same_measurement_v<std::tuple_element_t<0, decltype(parameters)>, measurement<units::newton_per_metre>>)
            return spring_potential(x, args...); 
        
        else 
            throw std::invalid_argument("Cannot instantiate a potential with the given parameters, please try again"); 

    }

    template <typename... VArgs>
    inline auto potential_energy(calculus::variable<measurement<units::metre>>& x, const std::tuple<VArgs...>& args) {
        
        if constexpr (is_same_measurement_v<std::tuple_element_t<0, std::tuple<VArgs...>>, measurement<units::newton_per_metre>>)
            return spring_potential(x, args); 
        
        else 
            throw std::invalid_argument("Cannot instantiate a potential with the given parameters, please try again"); 

    }


        // measurement<units::newton_per_metre> k; 
        // measurement<units::metre> l0{}; 


        // spring_potential(const measurement<units::newton_per_metre>& spring_constant, 
        //                  const measurement<units::metre>& position) noexcept 
            
        //     :  potential_energy(0.5 * spring_constant * (position - l0) * (position - l0)), k{spring_constant} {}

        // spring_potential(const measurement<units::newton_per_metre>& spring_constant, 
        //                  const calculus::variable<measurement<units::metre>>& position) noexcept 
            
        //     :  potential_energy(0.5 * spring_constant * position * position), k{spring_constant} {}



        // spring_potential(const measurement<units::newton_per_metre>& spring_constant,
        //                  const measurement<units::metre>& initial_lenght, 
        //                  const measurement<units::metre>& position) noexcept 
            
        //     : potential_energy(0.5 * spring_constant * (position - initial_lenght) * (position - initial_lenght)), k{spring_constant}, l0{initial_lenght} {}

        // spring_potential(const measurement<units::newton_per_metre>& spring_constant,
        //                  const measurement<units::metre>& initial_lenght, 
        //                  const calculus::variable<measurement<units::metre>>& position) noexcept 
            
        //     : potential_energy(0.5 * spring_constant * (position - initial_lenght) * (position - initial_lenght)), k{spring_constant}, l0{initial_lenght} {}

            
    // };


} // namespace scipp::physics