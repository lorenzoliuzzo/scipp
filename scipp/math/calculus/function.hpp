/**
 * @file    math/calculus/function.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-07
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {    


        template <typename RANGE, typename... DOMAIN>
        struct function {

            using result_t = variable<RANGE>; 
            using variable_t = std::tuple<variable<DOMAIN>&...>; 

            std::function<result_t(variable<DOMAIN>&...)> f;
            variable_t variables; 

            constexpr function(std::function<variable<RANGE>(variable<DOMAIN>&...)>& func, DOMAIN&... args) noexcept : 
                
                f(func), variables(static_cast<variable<DOMAIN>>(args)...) {}


            constexpr function(std::function<variable<RANGE>(variable<DOMAIN>&...)>& func, variable<DOMAIN>&... args) noexcept : 
                
                f(func), variables(args...) {}


            constexpr function(std::function<variable<RANGE>(variable<DOMAIN>&...)>&& func, DOMAIN&... args) noexcept : 
                
                f(std::move(func)), variables(static_cast<variable<DOMAIN>>(args)...) {}


            constexpr function(std::function<variable<RANGE>(variable<DOMAIN>&...)>&& func, variable<DOMAIN>&... args) noexcept : 
                
                f(std::move(func)), variables(args...) {}


            constexpr auto operator()() {

                return std::apply(this->f, this->variables);

            }

            constexpr auto gradient() {

                return derivatives(this->operator()(), std::apply([](auto&... vars) { return wrt(vars...); }, this->variables));

            }


            // inline constexpr result_t operator()(DOMAIN&&... args) const {
            //     std::tuple<variable<std::decay_t<DOMAIN>>&...> argsTuple(args...);
            //     return std::apply(this->f, argsTuple);
            // }


            // inline constexpr result_t operator()(variable<DOMAIN>&&... args) const {

            //     return std::apply(this->f, std::forward_as_tuple(args...));

            // }

            // inline constexpr result_t operator()(std::tuple<variable<DOMAIN>&...>&& args) const {

            //     return std::apply(this->f, args);

            // }


            // inline constexpr auto gradient(DOMAIN&&... args) {

            //     return derivatives(this->operator()(args...), wrt(static_cast<variable<DOMAIN>>(args)...)); 

            // }

        }; // struct function


        namespace functions {
        

            template <typename T>
            inline static constexpr auto identity(T& x) {
                
                return function<T, T>([](T& x) { return x; }, x);

            }


            template <typename T>
            inline static constexpr auto subtract(T& x, T& y) {
                
                return function<T, T, T>([](T& x, T& y) { return x - y; }, x, y);

            } 


            template <typename T>
            inline static constexpr auto invert(T& x) {
                
                return function<op::invert_t<T>, T>([](T& x) { return 1 / x; }, x);

            }

        
        } // namespace functions


    } // namespace calculus


} // namespace scipp::math