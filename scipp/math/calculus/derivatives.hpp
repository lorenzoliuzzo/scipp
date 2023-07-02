/**
 * @file    math/calculus/functions/derivatives.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-06-21
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {    


        template <typename... Vars>
        struct Wrt {

            std::tuple<Vars...> args;

        };

        /// The keyword used to denote the variables *with respect to* the derivative is calculated.
        template <typename... Args>
        constexpr auto wrt(Args&&... args) {

            return Wrt<Args&&...>{std::forward_as_tuple(std::forward<Args>(args)...)};

        }


        /// Return the derivatives of a dependent variable y with respect given independent variables.
        template <typename T, typename... Vars>
        constexpr auto derivatives(const variable<T>& y, const Wrt<Vars...>& wrt) {
            
            constexpr auto N = sizeof...(Vars);
            std::tuple<op::divide_t<T, typename std::decay_t<Vars>::value_t>...> values;
    
            meta::for_<N>([&](auto i) constexpr {
                using grad_t = std::tuple_element_t<i, decltype(values)>;
                std::shared_ptr<grad_t> sharedPtr(&std::get<i>(values), [](grad_t*){});
                std::get<i>(wrt.args).expr->bind_value(sharedPtr);
            });

            y.expr->propagate(std::make_shared<double>(1.0)); 

            meta::for_<N>([&](auto i) constexpr {

                std::get<i>(wrt.args).expr->bind_value(nullptr);

            });

            return values; 

        }


        // /// Return the derivatives expr of a dependent variable y with respect given independent variables.
        // template <typename T, typename... Vars>
        // constexpr auto derivativesx(const variable<T>& y, const Wrt<Vars...>& wrt) {
            
        //     constexpr auto N = sizeof...(Vars);
        //     std::tuple<variable<op::divide_t<T, typename std::decay_t<Vars>::value_t>>...> values;
    
        //     meta::for_<N>([&](auto i) constexpr {
        //         using grad_t = std::tuple_element_t<i, decltype(values)>;
        //         std::shared_ptr<grad_t> sharedPtr(&std::get<i>(values), [](grad_t*){});
        //         std::get<i>(wrt.args).expr->bind_expr(sharedPtr);
        //     });

        //     std::shared_ptr<grad_t> sharedPtr(&std::get<i>(values), [](grad_t*){});

        //     y.expr->propagatex(std::shared_ptr<std::shared_ptr<void>>(1.0)); 

        //     meta::for_<N>([&](auto i) constexpr {

        //         std::get<i>(wrt.args).expr->bind_expr(nullptr);

        //     });

        //     return values; 

        // }


    } // namespace calculus


} // namespace scipp::math