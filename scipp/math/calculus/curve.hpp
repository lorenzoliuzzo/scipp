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
    struct curve : virtual nary_function<POINT_TYPE, POINT_TYPE::dim - 1, double> {


        using _t = curve<POINT_TYPE>;

        using point_t = POINT_TYPE;

        using args_t = std::array<double, POINT_TYPE::dim - 1>;


        inline static constexpr size_t dimension = POINT_TYPE::dim - 1;


        // template <typename... PARAMs>
        //     requires (sizeof...(PARAMs) == dimension  && are_numbers_v<PARAMs...>)
        // constexpr point_t f(const PARAMs&... params) const {

        //     return point_t{}; 

        // }


        // template <typename... PARAMs>
        //     requires (sizeof...(PARAMs) == dimension && are_numbers_v<PARAMs...>)
        // constexpr point_t operator()(PARAMs&&... params) const {

        //     for (auto t : {params...})
        //         if (t < 0.0 || t > 1.0) 
        //             throw std::out_of_range("All scalar parameters must be in the range [0, 1]");

        //     return meta::nary_function<POINT_TYPE, POINT_TYPE::dim - 1, double>::f(params...);

        // }


        // constexpr auto diff(const args_type& params, 
        //                     const args_type& increments) const {

        //     return (f(params + increments) - f(params)) / increments;

        // }


        // constexpr bool is_closed() const noexcept {

        //     return f(args_t::zero) == f(args_t::one);

        // }




    }; // struct curve 
        

    template <typename T>
    struct is_curve : std::false_type {};

    template <typename POINT_TYPE>
    struct is_curve<curve<POINT_TYPE>> : std::true_type {};

    template <typename T>
    inline static constexpr bool is_curve_v = is_curve<typename T::_t>::value;


    template <typename POINT_TYPE>
        requires (POINT_TYPE::dim == 2)
    struct circumference : curve<POINT_TYPE> {


        POINT_TYPE center;

        typename POINT_TYPE::measurement_t radius;

    
        constexpr circumference(const POINT_TYPE& center, const typename POINT_TYPE::measurement_t& radius) noexcept : 
            
            center{center}, radius{radius} {}


        // template <typename NUMBER_TYPE>
        //     requires (is_number_v<NUMBER_TYPE>)
        constexpr POINT_TYPE f(const double& t) const override {
            
            if (t < 0.0 || t > 1.0) 
                throw std::out_of_range("All scalar parameters must be in the range [0, 1]");

            return { center.x() + radius * op::cos(t * 2.0 * constants::pi), center.y() + radius * op::sin(t * 2.0 * constants::pi) };

        }

        
    };



} // namespace scipp::math