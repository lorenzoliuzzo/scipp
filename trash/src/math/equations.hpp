/**
 * @file    equations.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-22
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {


    /// @brief Namespace defining mathematical equations
    namespace equations {
        

        /**
         * @brief Class representing an equation 
         * 
         * @tparam T: type of the equation
         * @tparam Args: arguments of the equation
         */
        template <typename T, typename... Args>
        class equation {


            public: 

            // =============================================
            // constructors and destructor
            // =============================================   

                /**
                 * @brief Construct a new equation object
                 * 
                 * @param args: arguments of the equation
                 */
                constexpr equation(std::function<T(const T&, const Args&...)> func) : 

                    func_(func) {}


                /**
                 * @brief Copy construct a new equation object
                 * 
                 * @param other: equation to be copied as l-value const reference
                 */
                constexpr equation(const equation& other) = default;


                /**
                 * @brief Move construct a new equation object
                 * 
                 * @param other: equation to be moved as r-value reference
                 */
                constexpr equation(equation&& other) = default;


            // =============================================
            // solve methods
            // =============================================   

                /**
                 * @brief Evaluate the equation
                 * 
                 * @param init: T as l-value const reference
                 * @param param: parameters of the ODE as l-value const reference
                 * 
                 * @return constexpr T
                 */
                constexpr T solve(const T& init, const Args&... args) const {

                    return func_(init, args...);

                }


                /**
                 * @brief Evaluate the equation
                 * 
                 * @param init: T as l-value const reference
                 * @param args: parameters of the ODE as l-value const reference
                 * 
                 * @return constexpr T 
                 */
                constexpr T operator()(const T& init, const Args&... args) const {

                    return func_(init, args...);

                }


            private: 

            // =============================================
            // class member
            // =============================================     

                std::function<T(const T&, const Args&...)> func_; ///< function to evaluate the equation

            
        };  // class equation


        /**
         * @brief Class representing an ordinary differential equation (ODE) 
         * @see equation
         * 
         * @tparam DIM: type of the ODE
         * @tparam Args...: arguments of the ODE
         */
        template <typename T, typename... Args>
        class ode : public equation<T, Args...> {
            

            public: 

            // =============================================
            // constructor and destructor
            // =============================================

                /**
                 * @brief Construct a new ode object 
                 * 
                 * @param evaluate: std::function that evaluates the ODE for a specific vector
                 * @param differentiate: std::function that evaluates the derivative of the ODE for a specific vector
                 */
                constexpr ode(const std::function<T(const T&, const Args&...)>& evaluate, 
                              const std::function<T(const T&, const Args&...)>& differentiate) noexcept :

                    equation<T, Args...>(evaluate), 
                    diff_(differentiate) {}


                /// @brief Default destructor
                ~ode() = default;

            
            // =============================================
            // ode methods
            // =============================================

                /**
                 * @brief Evaluate the derivative of the ODE for a specific vector
                 * 
                 * @param init: initial vector as l-value const reference
                 * @param param: parameters of the ODE as l-value const reference
                 *  
                 * @return constexpr T 
                 */
                constexpr T diff(const T& init, const Args&... param) const noexcept {

                    return diff_(init, param...); 

                } 


                /**
                 * @brief Evaluate the derivative of the ODE for a specific vector
                 * 
                 * @param init: initial vector as l-value const reference
                 * @param param: parameters of the ODE as l-value const reference
                 * 
                 * @return constexpr T 
                 */
                constexpr T operator()(const T& init, const Args&... param) const noexcept {

                    return diff_(init, param...);

                }


            private: 

            // =============================================
            // class member
            // =============================================

                std::function<T(const T&, const Args&...)> diff_; ///< function to differentiate the ode


        }; // class ode


        /**
         * @brief Class representing a system of equations
         * 
         * @tparam T: type of the system
         * @tparam Args: arguments of the system
         */
        template <typename T, typename... Args>
        class system_of_equations {


            public: 

            // =============================================
            // constructors and destructor
            // =============================================   

                /**
                 * @brief Construct a new system_of_equations object
                 * 
                 * @param args: arguments of the system_of_equations
                 */
                constexpr system_of_equations(std::function<T(const T&, const Args&...)> func) noexcept : 

                    func_(func) {}


                /**
                 * @brief Copy construct a new system_of_equations object
                 * 
                 * @param other: system_of_equations to be copied as l-value const reference
                 */
                constexpr system_of_equations(const system_of_equations& other) noexcept : 

                    func_(other.func_) {}


                /**
                 * @brief Move construct a new system_of_equations object
                 * 
                 * @param other: system_of_equations to be moved as r-value reference
                 */
                constexpr system_of_equations(system_of_equations&& other) noexcept : 

                    func_(std::move(other.func_)) {}


            // =============================================
            // solve methods
            // =============================================

                /**
                 * @brief Evaluate the system_of_equations
                 * 
                 * @param init: T as l-value const reference
                 * @param param: parameters of the ODE as l-value const reference
                 * 
                 * @return constexpr T
                 */
                constexpr T solve(const T& init, const Args&... args) const {

                    return func_(init, args...);

                }


                /**
                 * @brief Evaluate the system_of_equations
                 * 
                 * @param init: T as l-value const reference
                 * @param param: parameters of the ODE as l-value const reference
                 * 
                 * @return constexpr T
                 */
                constexpr T operator()(const T& init, const Args&... args) const {

                    return func_(init, args...);

                }


            private: 

            // =============================================
            // class members
            // =============================================     

                std::function<T(const T&, const Args&...)> func_; ///< function to evaluate the equation


        }; // class system_of_equations


        /**
         * @brief Class representing a system of ordinary differential equations (ODE)
         * 
         * @tparam T: type of the system
         * @tparam Args: arguments of the system
         */
        template <typename T, typename... Args>
        class system_of_odes : public system_of_equations<T, Args...> {
            

            public: 

            // =============================================
            // constructor and destructor
            // =============================================

                /**
                 * @brief Construct a new system of ode object 
                 * 
                 * @param evaluate: std::function that evaluates the ODE system for a specific T
                 * @param differentiate: std::function that evaluates the derivative of the ODE system for a specific T
                 */
                constexpr system_of_odes(const std::function<T(const T&, const Args&...)>& evaluate, 
                                         const std::function<T(const T&, const Args&...)>& differentiate) noexcept :

                    system_of_equations<T, Args...>(evaluate), 
                    diff_(differentiate) {}


                /// @brief Default destructor
                ~system_of_odes() = default;

            
            // =============================================
            // ODE methods
            // =============================================

                /**
                 * @brief Evaluate the derivative of the ODE system for a specific T
                 * 
                 * @param init: initial T as l-value const reference
                 * @param param: parameters of the ODE as l-value const reference
                 *  
                 * @return constexpr T 
                 */
                constexpr T diff(const T& init, const Args&... param) const noexcept {

                    return diff_(init, param...); 

                } 


                /**
                 * @brief Evaluate the derivative of the ODE system for a specific T
                 * 
                 * @param init: initial T as l-value const reference
                 * @param param: parameters of the ODE as l-value const reference
                 * 
                 * @return constexpr T 
                 */
                constexpr T operator()(const T& init, const Args&... param) const noexcept {

                    return diff_(init, param...);

                }


            private: 

            // =============================================
            // class member
            // =============================================

                std::function<T(const T&, const Args&...)> diff_; ///< function to differentiate the ode system


        }; // class system_of_odes


        // template <size_t DIM, typename... Args>
        // class hamiltonian {

            
        //     private: 
            

        //         ode<vector<DIM>, Args...>* potential_;


        //         system_of_odes<matrix<DIM, 2>, Args...> system_;


        //         ode_solver solver_;


        //     public: 
                
                
        //         constexpr hamiltonian(ode<vector<DIM>, Args...>* potential) noexcept :

        //             potential_{potential}, 
        //             system_(

        //                 [this](const matrix<DIM, 2>& init, const Args&... param) -> matrix<DIM, 2> {

        //                     return matrix<DIM, 2>(); 

        //                 }, /// @todo
                    
        //                 [this](const matrix<DIM, 2>& init, const Args&... param) -> matrix<DIM, 2> { 
                        
        //                     return matrix<DIM, 2>({init[1], - potential_->diff(init[0], param...)}); 

        //                 }

        //             ) {}


        //         constexpr matrix<DIM, 2> solve(const measurement& mass, 
        //                                        const matrix<DIM, 2>& init, 
        //                                        const Args&... param, 
        //                                        const measurement& time_incr) const noexcept {
                    
        //             vector<2> incr({time_incr, time_incr / mass}); 
        //             return solver_.RK4(system_, init, incr, param...);

        //         }


        //         constexpr matrix<DIM, 2> operator()(const measurement& mass, 
        //                                             const matrix<DIM, 2>& init, 
        //                                             const Args&... param, 
        //                                             const measurement& time_incr) const noexcept {
                    
        //             return solve(mass, init, param..., time_incr);

        //         }


        // }; // class hamiltonian


    } // namespace equations 


} // namespace scipp::math