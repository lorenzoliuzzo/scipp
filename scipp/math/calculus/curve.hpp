/**
 * @file    math/calculus/curve.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-06-29
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {    


        template <typename T, size_t DIM>
            requires is_variable_v<T>  
        struct curve {

            std::array<T, DIM> point{};
            // std::tuple<VARS&...> variables;

            inline constexpr static size_t dim = DIM;

            template <typename CONSTRAIN, typename... VARS>
            inline constexpr curve(CONSTRAIN f, VARS&... variables) :

                point(f(variables...)) {}


            inline constexpr std::array<T, DIM> operator()() {

                return point; 

            }; // operator()


        }; // struct curve 


        namespace curves {


            template <typename T>
            struct line : curve<T, 2> {

                inline constexpr line(auto m, auto q, T& x) : 

                    curve<T, 2>(
                        [&](T& x) -> std::array<T, 2> { 
                            return {x, m * x + q}; 
                        }, x) {};

            };


            template <typename T>
            struct parabola : curve<T, 2> {

                inline constexpr parabola(auto a, auto b, auto c, T& x) : 

                    curve<T, 2>(
                        [&](T& x) -> std::array<T, 2> { 
                            return {x, a * x * x + b * x + c}; 
                        }, x) {};

            };


            template <typename T, bool UP_OR_DOWN = true>
            struct circle : curve<T, 2> {

                inline constexpr circle(auto center, auto r, T& x) : 

                    curve<T, 2>(
                        [&](T& x) -> std::array<T, 2> { 

                            T y = center[1];
                            if constexpr (UP_OR_DOWN) 
                                y += math::op::root<2>(r * r - (x - center[0]) * (x - center[0]));
                            else
                                y -= math::op::root<2>(r * r - (x - center[0]) * (x - center[0]));
                            
                            return {x, y};

                        }, x) {};

            }; 


        } // namespace curves


    } // namespace calculus


} // namespace scipp::math