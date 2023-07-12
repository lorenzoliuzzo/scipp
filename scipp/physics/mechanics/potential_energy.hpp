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


        virtual inline calculus::variable<measurement<base::energy>> operator()(const calculus::variable<measurement<base::length>>&) = 0; 


        inline calculus::variable<measurement<base::force>> force(const calculus::variable<measurement<base::length>>& x) {

            return -std::get<0>(calculus::derivatives(this->operator()(x), calculus::wrt(x))); 

        } 

    };


    template <typename... Potentials>
    struct potential_energy : potential<Potentials...> {

        calculus::variable<measurement<base::energy>> energy;

        potential_energy(const Potentials&... params) noexcept : potential<Potentials...>(params...) {}

        inline calculus::variable<measurement<base::energy>> operator()(const calculus::variable<measurement<base::length>>& x) override {

            this->energy = 0.0;
            std::apply([&](auto&&... args) {
                ((this->energy += args(x)), ...);
            }, this->params);

            return this->energy;

        }

    };


    namespace potentials {


        struct elastic : potential<measurement<math::op::divide_t<base::force, base::length>>, measurement<base::length>> {

            elastic(const measurement<math::op::divide_t<base::force, base::length>>& k, const measurement<base::length>& l0) noexcept 
                            
                : potential<measurement<math::op::divide_t<base::force, base::length>>, measurement<base::length>>(k, l0) {}


            inline calculus::variable<measurement<base::energy>> operator()(const calculus::variable<measurement<base::length>>& x) override {
                
                const auto& [k, l0] = this->params; 
                return 0.5 * k * math::op::square(x - l0); 

            }

        };


        struct gravitational : potential<measurement<base::mass>, measurement<base::mass>> {

            gravitational(const measurement<base::mass>& m1, const measurement<base::mass>& m2) noexcept 
                            
                : potential<measurement<base::mass>, measurement<base::mass>>(m1, m2) {}


            inline calculus::variable<measurement<base::energy>> operator()(const calculus::variable<measurement<base::length>>& x) override {

                const auto& [m1, m2] = this->params; 
                return -physics::constants::G * m1 * m2 / x; 

            }

        };


    } // namespace potentials


} // namespace scipp::physics