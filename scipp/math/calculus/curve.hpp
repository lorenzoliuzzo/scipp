/**
 * @file    math/calculus/curve.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-04-26
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    

    template <typename POINT_TYPE>      
        requires (geometry::is_vector_v<POINT_TYPE> || physics::is_cmeasurement_v<POINT_TYPE>)
    struct curve : meta::nary_function<POINT_TYPE, POINT_TYPE::dim - 1, double> {


        using _t = curve<POINT_TYPE>;

        using point_t = POINT_TYPE;

        using args_t = std::array<double, POINT_TYPE::dim - 1>;


        inline static constexpr std::size_t dimension = POINT_TYPE::dim - 1;


        std::function<point_t(args_t)> f;


        constexpr curve(std::function<point_t(args_t)>&& f) noexcept : 
            
            f(f) {}


        template <typename... PARAMs>
            requires (sizeof...(PARAMs) == dimension)
        constexpr point_t operator()(const PARAMs&... params) const {

            for (auto t : {params...})
                if (t < 0.0 || t > 1.0) {
                    std::cerr << "Cannot evaluate curve at t = " << t << '\n';
                    throw std::out_of_range("All scalar parameters must be in the range [0, 1]");
                }

            return f({params...});

        }


        // constexpr auto diff(const args_type& params, 
        //                     const args_type& increments) const {

        //     return (f(params + increments) - f(params)) / increments;

        // }


        // constexpr bool is_closed() const noexcept {

        //     return f(args_t::zero) == f(args_t::one);

        // }


    }; // struct curve 
        

} // namespace scipp::math