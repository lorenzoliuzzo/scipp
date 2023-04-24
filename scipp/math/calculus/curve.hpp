/**
 * @file    math/calculus/curve.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    

    template <typename POINT_TYPE>      
        requires (geometry::is_vector_v<POINT_TYPE> || is_complex_v<POINT_TYPE>)
    struct curve : functions::nary_function<POINT_TYPE, physics::scalar_m, POINT_TYPE::dim - 1> {


        using type = curve<POINT_TYPE>;

        using point_t = POINT_TYPE;

        using args_t = geometry::vector<physics::scalar_m, POINT_TYPE::dim - 1>;


        inline static constexpr std::size_t dimension = POINT_TYPE::dim - 1;


        std::function<point_t(args_t)> f;


        constexpr curve(std::function<point_t(args_t)>&& f) noexcept : 
            
            f(f) {}


        constexpr point_t operator()(const args_t& params) const {

            for (auto t : params.data)
                if (t < physics::scalar_m::zero || t > physics::scalar_m::one) {
                    std::cerr << "Cannot evaluate curve at t = " << t << '\n';
                    throw std::out_of_range("All scalar parameters must be in the range [0, 1]");
                }

            return f(params);

        }


        // constexpr auto diff(const args_type& params, 
        //                     const args_type& increments) const {

        //     return (f(params + increments) - f(params)) / increments;

        // }


        constexpr bool is_closed() const noexcept {

            return f(args_t::zero) == f(args_t::one);

        }


    }; // struct curve 


    template <typename T>
    struct is_curve : std::false_type {};

    template <typename POINT_TYPE>
        requires (geometry::is_vector_v<POINT_TYPE>)
    struct is_curve<curve<POINT_TYPE>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_curve_v = is_curve<T>::value;
        

} // namespace scipp::math