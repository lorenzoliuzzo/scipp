/**
 * @file    math/calculus/curve.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-07
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {    


        template <typename T, typename... ARGs>
        struct curve {  

            using curve_t = curve<T, ARGs...>;
            using parametrization_t = function<T, ARGs...>;
            using value_t = T;
            
            function<T, ARGs...> parametrization;
            std::tuple<interval<ARGs>...> intervals;

            
            constexpr curve(function<T, ARGs...>&& gamma, interval<ARGs>... args_I) noexcept :

                parametrization{gamma}, intervals{args_I...} {}


            constexpr curve(std::function<variable<T>(variable<ARGs>&...)>&& gamma, ARGs&... vars, interval<ARGs>... Is) noexcept :

                parametrization{gamma, vars...}, intervals{Is...} {}


            constexpr curve(std::function<variable<T>(variable<ARGs>&...)>&& gamma, variable<ARGs>&... vars, interval<ARGs>... Is) noexcept :

                parametrization{gamma, vars...}, intervals{Is...} {}


            constexpr auto operator()() {

                meta::for_<sizeof...(ARGs)>([&](auto i) {
                    if (!std::get<i>(this->intervals).contains(val(std::get<i>(this->parametrization.variables)))) {
                        std::cerr << "Trying to evaluate the curve in a point outside the domain of definition\n";
                        std::cerr << "Value: " << val(std::get<i>(this->parametrization.variables)) << "\n";
                        auto I = std::get<i>(this->intervals);
                        std::cerr << "Interval: [ " << I.start << ", " << I.end << " ]\n";
                        throw std::runtime_error("The parametrization is not defined in the given interval");
                    }
                });

                return std::tuple_cat(this->parametrization.variables, std::make_tuple(this->parametrization())); 

            }


            constexpr auto gradient() {

                auto dvars = meta::make_tuple_repeated<int, sizeof...(ARGs)>(1);
                return std::tuple_cat(dvars, this->parametrization.gradient());

            }

            constexpr auto at(ARGs&&... args) const {

                constexpr size_t N = sizeof...(ARGs);
                std::tuple<variable<ARGs>...> args_tuple{variable<ARGs>(args)...};

                meta::for_<N>([&](auto i) {
                    if (!std::get<i>(this->intervals).contains(val(std::get<i>(args_tuple)))) {
                        std::cerr << "Trying to evaluate the curve in a point outside the domain of definition\n";
                        std::cerr << "Value: " << val(std::get<i>(args_tuple)) << "\n";
                        auto I = std::get<i>(this->intervals);
                        std::cerr << "Interval: [" << I.start << ", " << I.end << "]\n";
                        throw std::runtime_error("The parametrization is not defined in the given interval");
                    }
                });

                return std::apply(this->parametrization.f, args_tuple);

            }

            template <size_t N>
            constexpr auto length() const {
                
                return integrals::curvilinear<N>(*this);

            }

            // template <size_t N>
            // constexpr int index(variable<ARGs>&&... args) const {

            //     auto& x = std::get<0>(this->parametrization.variables); 
            //     return val(integrals::curvilinear<N>(*this, function<op::invert_t<T>, ARGs...>([&](variable<ARGs>&... args) {
            //         return op::inv(x - args)...;
            //     }, std::forward<variable<ARGs>>(args)...)));

            // }

        }; // struct curve 


        namespace curves {


            template <typename Y, typename X>
            struct line : curve<Y, X> {

                op::divide_t<Y, X> slope;
                Y height;
                variable<X> x;


                constexpr line(const op::divide_t<Y, X>& m, const Y& q) noexcept : 

                    curve<Y, X>(function<Y, X>([m, q](variable<X>& t) -> variable<Y> { 
                        
                            return q + t * m; 

                        }, x), interval<X>(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max())), 
                    slope{m}, height{q} {}


                constexpr line(const op::divide_t<Y, X>& m, const Y& q, variable<X>& var) noexcept : 

                    curve<Y, X>(function<Y, X>([m, q](variable<X>& t) -> variable<Y> { 
                        
                            return q + t * m; 

                        }, var), interval<X>(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max())), 
                    slope{m}, height{q}, x{var} {}

            };


            template <typename Y, typename X>
            struct segment : curve<Y, X> {

                op::divide_t<Y, X> slope;
                Y height;
                variable<X> x;


                constexpr segment(const op::divide_t<Y, X>& m, const Y& q, const interval<X>& I) noexcept : 

                    curve<Y, X>(function<Y, X>([m, q](variable<X>& t) -> variable<Y> { 
                        
                            return q + t * m; 

                        }, x), I), 
                    slope{m}, height{q} {}


                constexpr segment(const op::divide_t<Y, X>& m, const Y& q, variable<X>& var, const interval<X>& I) noexcept : 

                    curve<Y, X>(function<Y, X>([m, q](variable<X>& t) -> variable<Y> { 
                        
                            return q + t * m; 

                        }, var), I), 
                    slope{m}, height{q}, x{var} {}

            };


            template <typename Y, typename X>
            struct parabola : curve<Y, X> {

                op::divide_t<Y, op::power_t<2, X>> a;
                op::divide_t<Y, X> b;
                Y c;

                variable<X> x;


                constexpr parabola(const op::divide_t<Y, op::power_t<2, X>>& a_, 
                                   const op::divide_t<Y, X>& b_, 
                                   const Y& c_, 
                                   const interval<X>& I = interval<X>(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max())) noexcept : 
                    
                    curve<Y, X>(function<Y, X>([a_, b_, c_](variable<X>& t) -> variable<Y> {

                            return a_ * op::square(t) + b_ * t + c_;

                        }, x), I),
                    a{a_}, b{b_}, c{c_} {}


                constexpr parabola(const op::divide_t<Y, op::power_t<2, X>>& a_, 
                                   const op::divide_t<Y, X>& b_, 
                                   const Y& c_, 
                                   variable<X>& var,
                                   const interval<X>& I = interval<X>(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max())) noexcept : 
                    
                    curve<Y, X>(function<Y, X>([a_, b_, c_](variable<X>& t) -> variable<Y> {

                            return a_ * op::square(t) + b_ * t + c_;

                        }, var), I),
                    a{a_}, b{b_}, c{c_}, x{var} {}

            };


            // template <typename Y, typename X>
            //     requires (Y::dim == 2)
            // struct circle : curve<Y, X> {

            //     Y center;
            //     typename Y::value_t radius;
            //     variable<X> theta;

            //     constexpr circle(const Y& C, const typename Y::value_t& r) noexcept :

            //         curve<Y, X>(function<Y, X>([C, r](variable<X>& t) -> variable<Y> {
            //                 variable<double> x = C[0] + r * op::cos(t);
            //                 variable<double> y = C[1] + r * op::sin(t);
            //                 return variable<Y>(x, y);
            //             }, theta), interval<X>(0.0, 2.0 * std::numbers::pi)), 
            //         center(C), radius(r) {}                

            // }; 


            // template <typename Y, typename X>
            //     requires (Y::dim == 3)
            // struct sphere : curve<Y, X, X> {

            //     Y center;
            //     typename Y::value_t radius;
            //     variable<X> theta;
            //     variable<X> phi;

            //     constexpr sphere(const Y& C, const typename Y::value_t& r) noexcept :

            //         curve<Y, X, X>(function<Y, X, X>([C, r](variable<X>& theta, variable<X>& phi) -> variable<Y> {
            //                 return {C[0] + r * op::sin(phi) * op::cos(theta), 
            //                         C[1] + r * op::sin(phi) * op::sin(theta),
            //                         C[2] + r * op::cos(phi)};
            //             }, theta, phi), interval<X>(0.0, 2.0 * std::numbers::pi), interval<X>(0.0, std::numbers::pi)),
            //         center(C), radius(r) {}

            // };
            


// template <typename T>
// struct ellipse : curve<T, T> {
//     T center_x;
//     T center_y;
//     T radius_x;
//     T radius_y;

//     inline constexpr ellipse(const T& cx, const T& cy, const T& rx, const T& ry) noexcept
//         : curve<T, T>(function<T, T>([cx, cy, rx, ry](variable<T> t) -> variable<T> {
//             return cx + rx * op::cos(t) + cy + ry * op::sin(t);
//         }, variable<T>{}), interval<T>(0.0, 2.0 * pi<T>)),
//           center_x(cx), center_y(cy), radius_x(rx), radius_y(ry) {}
// };


        } // namespace curves


    } // namespace calculus


} // namespace scipp::math