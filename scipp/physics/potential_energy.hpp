/**
 * @file    physics/potential_energy.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-28
 * 
 * @copyright Copyright (c) 2023
 */
 


namespace scipp::physics {


    template <typename... VArgs>
    struct potential { 

        std::tuple<std::decay_t<VArgs>...> params; 

        potential(const VArgs&... params) noexcept 
            
            : params{std::forward_as_tuple(std::decay_t<VArgs>(params)...)} {}


        virtual inline calculus::variable<measurement<units::joule>> operator()(const calculus::variable<measurement<units::metre>>&) = 0; 


        inline calculus::variable<measurement<units::newton>> force(const calculus::variable<measurement<units::metre>>& x) {

            return -std::get<0>(calculus::derivatives(this->operator()(x), calculus::wrt(x))); 

        } 

    };


    template <typename... Potentials>
    struct potential_energy : potential<Potentials...> {

        calculus::variable<measurement<units::joule>> energy;

        potential_energy(const Potentials&... params) noexcept : potential<Potentials...>(params...) {}

        inline calculus::variable<measurement<units::joule>> operator()(const calculus::variable<measurement<units::metre>>& x) override {

            this->energy = 0.0;
            std::apply([&](auto&&... args) {
                ((this->energy += args(x)), ...);
            }, this->params);

            return this->energy;

        }

    };


    namespace potentials {


        struct elastic : potential<measurement<units::newton_per_metre>, measurement<units::metre>> {

            elastic(const measurement<units::newton_per_metre>& k, const measurement<units::metre>& l0) noexcept 
                            
                : potential<measurement<units::newton_per_metre>, measurement<units::metre>>(k, l0) {}


            inline calculus::variable<measurement<units::joule>> operator()(const calculus::variable<measurement<units::metre>>& x) override {
                
                const auto& [k, l0] = this->params; 
                return 0.5 * k * (x - l0) * (x - l0);

            }

        };


        struct gravitational : potential<measurement<units::kilogram>, measurement<units::kilogram>> {

            gravitational(const measurement<units::kilogram>& m1, const measurement<units::kilogram>& m2) noexcept 
                            
                : potential<measurement<units::kilogram>, measurement<units::kilogram>>(m1, m2) {}


            inline calculus::variable<measurement<units::joule>> operator()(const calculus::variable<measurement<units::metre>>& x) override {

                const auto& [m1, m2] = this->params; 
                return -physics::constants::G * m1 * m2 / x; 

            }

        };


    } // namespace potentials


} // namespace scipp::physics