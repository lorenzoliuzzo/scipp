/**
 * @file    math/calculus/ode/solver.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation
 * @date    2023-06-25
 *
 * @copyright Copyright (c) 2023
 */

namespace scipp::math {


    namespace calculus {


        namespace ode {


            /// @brief Solve an ODE with the Euler method
            constexpr auto euler(const auto& init, const auto& f, const variable<auto>& x, const auto& incr) {

                auto [dfdx] = derivatives(f(x), wrt(x));
                return init + dfdx * incr;

            }

            
            // /**
            //  * @brief Solve an ODE with the Runge-Kutta method
            //  * 
            //  * @tparam ODE: type of the ODE
            //  * @tparam T: type of the solution
            //  * @tparam Args: arguments of the ODE
            //  * @tparam U: type of the step size
            //  * 
            //  * @param ode: ODE to be solved as l-value const reference
            //  * @param init: initial value of the ODE as l-value const reference
            //  * @param param: parameters of the ODE as l-value const reference
            //  * @param incr: time step of the ODE as l-value const reference
            //  * 
            //  * @return constexpr T 
            //  */
            // template <template <typename T, typename... Args> class ODE, typename T,  typename U, typename... Args>
            // constexpr T RK4(const ODE<T, Args...>& ode, const T& init, const U& incr, const Args&... param) const noexcept {

            //     T k1(ode(init, param...));
            //     T k2(ode(init + k1 * (incr / 2.), param...)); 
            //     T k3(ode(init + k2 * (incr / 2.), param...));
            //     T k4(ode(init + k3 * incr, param...)); 

            //     return init + (k1 + k2 * 2. + k3 * 2. + k4) * (incr / 6.); 

            // }


        } // namespace ode


    } // namespace calculus


} // namespace scipp::math