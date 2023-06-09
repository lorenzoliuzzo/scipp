/**
 * @file    math/calculus/curves/
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-06-09
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    



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


} // namespace scipp::math