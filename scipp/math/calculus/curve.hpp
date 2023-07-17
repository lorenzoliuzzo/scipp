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


        template <typename Y, typename X>
        struct curve {

            using curve_t = curve<Y, X>;
            using point_t = Y;
            // using value_t = 
            using parameter_t = X;
            using interval_t = interval<typename X::value_t>;


            std::function<point_t(parameter_t&)> parametrization;
            interval_t domain;


            template <typename FUNC>    
                requires (std::is_invocable_v<FUNC, parameter_t&> && 
                          std::is_same_v<point_t, std::invoke_result_t<FUNC, parameter_t&>>)
            constexpr curve(const FUNC& func, const interval_t& I) noexcept : 

                parametrization{func}, domain(I) {}


            constexpr auto operator()(parameter_t& x) const {

                if (!this->domain.contains(val(x))) {

                    std::cerr << "Trying to evaluate the curve in a point outside the domain of definition\n";
                    tools::print<std::femto>("Value: ", val(x)); 
                    tools::print("Interval: ", this->domain); 
                    throw std::runtime_error("The parametrization is not defined outside of the given interval");

                }

                return this->parametrization(x); 

            }

            
        }; // struct curve


        // template <typename FUNC, typename INTERVAL>
        // curve(FUNC, INTERVAL) -> curve<typename std::invoke_result_t<FUNC, variable<typename INTERVAL::value_t>&>::value_t, typename INTERVAL::value_t>;

        // template <typename RANGE>
        // curve(FUNC, interval<) -> curve<typename std::invoke_result_t<FUNC, variable<typename INTERVAL::value_t>&>::value_t, typename INTERVAL::value_t>;

    } // namespace calculus


} // namespace scipp::math


        // template <typename Y, typename X>
        // struct parametrization : unary_function<Y, X> {  

        //     using unary_function<Y, X>::f;
        //     using unary_function<Y, X>::var;
        //     using parametrization_t = parametrization<Y, X>;

        //     using result_t = variablevalue_tY>;
        //     using parameter_t = variable<X>;
        //     using interval_t = interval<X>;
            
        //     interval_t domain;


        //     constexpr parametrization(std::function<result_t(parameter_t&)>& func, X& variable, interval_t I) noexcept : 
                
        //         unary_function<Y, X>(func, variable), domain(I) {}

        //     constexpr parametrization(std::function<result_t(parameter_t&)>&& func, X& variable, interval_t I) noexcept :

        //         unary_function<Y, X>(func, variable), domain(I) {}


        //     constexpr parametrization(std::function<result_t(parameter_t&)>& func, parameter_t& variable, interval_t I) noexcept :

        //         unary_function<Y, X>(func, variable), domain(I) {}

        //     constexpr parametrization(std::function<result_t(parameter_t&)>&& func, parameter_t& variable, interval_t I) noexcept :

        //         unary_function<Y, X>(func, variable), domain(I) {}
            

        //     constexpr parametrization(unary_function<Y, X>& gamma, interval<X> I) noexcept :

        //         unary_function<Y, X>(gamma), domain(I) {}

        //     constexpr parametrization(unary_function<Y, X>&& gamma, interval<X> I) noexcept :

        //         unary_function<Y, X>(gamma), domain(I) {}


        //     constexpr parametrization(parametrization& gamma) noexcept :

        //         unary_function<Y, X>(gamma), domain(gamma.domain) {}


        //     constexpr parametrization(parametrization&& gamma) noexcept :

        //         unary_function<Y, X>(gamma), domain(std::move(gamma.domain)) {}


        //     constexpr auto operator()() {

        //         if (!this->domain.contains(val(this->var))) {
        //             std::cerr << "Trying to evaluate the curve in a point outside the domain of definition\n";
        //             std::cerr << "Value: " << val(this->var) << "\n";
        //             std::cerr << "Interval: [ " << domain.start << ", " << domain.end << " ]\n";
        //             throw std::runtime_error("The parametrization is not defined outside of the given interval");
        //         }

        //         return this->f(this->var);

            // }

            // template <size_t N>
            // constexpr auto length() const {
                
            //     return integrals::curvilinear<N>(*this);

            // }


            // constexpr auto at(ARGs&&... args) const {

            //     constexpr size_t N = sizeof...(ARGs);
            //     std::tuple<variable<ARGs>...> args_tuple{variable<ARGs>(args)...};

            //     meta::for_<N>([&](auto i) {
            //         if (!std::get<i>(this->intervals).contains(val(std::get<i>(args_tuple)))) {
            //             std::cerr << "Trying to evaluate the curve in a point outside the domain of definition\n";
            //             std::cerr << "Value: " << val(std::get<i>(args_tuple)) << "\n";
            //             auto I = std::get<i>(this->intervals);
            //             std::cerr << "Interval: [" << I.start << ", " << I.end << "]\n";
            //             throw std::runtime_error("The parametrization is not defined in the given interval");
            //         }
            //     });

            //     return std::apply(this->parametrization.f, args_tuple);

            // }


            // template <size_t N>
            // constexpr int index(variable<ARGs>&&... args) const {

            //     auto& x = std::get<0>(this->parametrization.variables); 
            //     return val(integrals::curvilinear<N>(*this, function<op::invert_t<T>, ARGs...>([&](variable<ARGs>&... args) {
            //         return op::inv(x - args)...;
            //     }, std::forward<variable<ARGs>>(args)...)));

            // }

        // }; // struct curve 


        // template <size_t N, typename Y, typename... PARAMs>
        //     requires (typename PARAMs::result_t == variablevalue_tY> && ...)
        // struct curve {

        //     using curve_t = curve<N, Y, Xs...>;
        //     using parametrization_t = parametrization<Y, Xs...>;
        //     using point_t = std::array<variablevalue_tY>, N>;

        //     std::tuple<PARAMs...> parametrizations;
        //     std::tuple<typename PARAMs::interval_t...> intervals;
        //     std::tuple<typename PARAMs::parameter_t...> parameters;


        //     constexpr curve(PARAMs&&... params) noexcept : 

        //         parametrizations{std::forward<PARAMs>(params)...}, 
        //         intervals{params.domain...}, 
        //         parameters{params.var...} {}


        // };


//         namespace curves {


//             template <typename Y, typename X>
//             struct line : curve<Y, X> {

//                 op::divide_t<Y, X> slope;
//                 Y height;
//                 variable<X> x;


//                 constexpr line(const op::divide_t<Y, X>& m, const Y& q) noexcept : 

//                     curve<Y, X>(function<Y, X>([m, q](variable<X>& t) -> variablevalue_tY> { 
                        
//                             return q + t * m; 

//                         }, x), interval<X>(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max())), 
//                     slope{m}, height{q} {}


//                 constexpr line(const op::divide_t<Y, X>& m, const Y& q, variable<X>& var) noexcept : 

//                     curve<Y, X>(function<Y, X>([m, q](variable<X>& t) -> variablevalue_tY> { 
                        
//                             return q + t * m; 

//                         }, var), interval<X>(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max())), 
//                     slope{m}, height{q}, x{var} {}

//             };


//             template <typename Y, typename X>
//             struct segment : curve<Y, X> {

//                 op::divide_t<Y, X> slope;
//                 Y height;
//                 variable<X> x;


//                 constexpr segment(const op::divide_t<Y, X>& m, const Y& q, const interval<X>& I) noexcept : 

//                     curve<Y, X>(function<Y, X>([m, q](variable<X>& t) -> variable<Y> { 
                        
//                             return q + t * m; 

//                         }, x), I), 
//                     slope{m}, height{q} {}


//                 constexpr segment(const op::divide_t<Y, X>& m, const Y& q, variable<X>& var, const interval<X>& I) noexcept : 

//                     curve<Y, X>(function<Y, X>([m, q](variable<X>& t) -> variable<Y> { 
                        
//                             return q + t * m; 

//                         }, var), I), 
//                     slope{m}, height{q}, x{var} {}

//             };


//             template <typename Y, typename X>
//             struct parabola : curve<Y, X> {

//                 op::divide_t<Y, op::power_t<2, X>> a;
//                 op::divide_t<Y, X> b;
//                 Y c;

//                 variable<X> x;


//                 constexpr parabola(const op::divide_t<Y, op::power_t<2, X>>& a_, 
//                                    const op::divide_t<Y, X>& b_, 
//                                    const Y& c_, 
//                                    const interval<X>& I = interval<X>(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max())) noexcept : 
                    
//                     curve<Y, X>(function<Y, X>([a_, b_, c_](variable<X>& t) -> variable<Y> {

//                             return a_ * op::square(t) + b_ * t + c_;

//                         }, x), I),
//                     a{a_}, b{b_}, c{c_} {}


//                 constexpr parabola(const op::divide_t<Y, op::power_t<2, X>>& a_, 
//                                    const op::divide_t<Y, X>& b_, 
//                                    const Y& c_, 
//                                    variable<X>& var,
//                                    const interval<X>& I = interval<X>(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max())) noexcept : 
                    
//                     curve<Y, X>(function<Y, X>([a_, b_, c_](variable<X>& t) -> variable<Y> {

//                             return a_ * op::square(t) + b_ * t + c_;

//                         }, var), I),
//                     a{a_}, b{b_}, c{c_}, x{var} {}

//             };


//             // template <typename Y, typename X>
//             //     requires (Y::dim == 2)
//             // struct circle : curve<Y, X> {

//             //     Y center;
//             //     typename Y::value_t radius;
//             //     variable<X> theta;

//             //     constexpr circle(const Y& C, const typename Y::value_t& r) noexcept :

//             //         curve<Y, X>(function<Y, X>([C, r](variable<X>& t) -> variable<Y> {
//             //                 variable<double> x = C[0] + r * op::cos(t);
//             //                 variable<double> y = C[1] + r * op::sin(t);
//             //                 return variable<Y>(x, y);
//             //             }, theta), interval<X>(0.0, 2.0 * std::numbers::pi)), 
//             //         center(C), radius(r) {}                

//             // }; 


//             // template <typename Y, typename X>
//             //     requires (Y::dim == 3)
//             // struct sphere : curve<Y, X, X> {

//             //     Y center;
//             //     typename Y::value_t radius;
//             //     variable<X> theta;
//             //     variable<X> phi;

//             //     constexpr sphere(const Y& C, const typename Y::value_t& r) noexcept :

//             //         curve<Y, X, X>(function<Y, X, X>([C, r](variable<X>& theta, variable<X>& phi) -> variable<Y> {
//             //                 return {C[0] + r * op::sin(phi) * op::cos(theta), 
//             //                         C[1] + r * op::sin(phi) * op::sin(theta),
//             //                         C[2] + r * op::cos(phi)};
//             //             }, theta, phi), interval<X>(0.0, 2.0 * std::numbers::pi), interval<X>(0.0, std::numbers::pi)),
//             //         center(C), radius(r) {}

//             // };
            


// // template <typename T>
// // struct ellipse : curve<T, T> {
// //     T center_x;
// //     T center_y;
// //     T radius_x;
// //     T radius_y;

// //     inline constexpr ellipse(const T& cx, const T& cy, const T& rx, const T& ry) noexcept
// //         : curve<T, T>(function<T, T>([cx, cy, rx, ry](variable<T> t) -> variable<T> {
// //             return cx + rx * op::cos(t) + cy + ry * op::sin(t);
// //         }, variable<T>{}), interval<T>(0.0, 2.0 * pi<T>)),
// //           center_x(cx), center_y(cy), radius_x(rx), radius_y(ry) {}
// // };


//         } // namespace curves

