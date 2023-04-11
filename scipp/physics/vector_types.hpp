/**
 * @file    physics/vector_types.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date    2023-02-05
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::physics {


    template <std::size_t DIM> 
    using position = geometry::vector<length_m, DIM>; 

    using position2 = position<2>;
    using position3 = position<3>;

    template <std::size_t DIM>
    using uposition = geometry::vector<length_um, DIM>;

    using uposition2 = uposition<2>;
    using uposition3 = uposition<3>;


    template <std::size_t DIM> 
    using lin_velocity = geometry::vector<math::op::measurements_div_t<length_m, time_m>, DIM>; 

    using lin_velocity2 = lin_velocity<2>;
    using lin_velocity3 = lin_velocity<3>;

    template <std::size_t DIM> 
    using ulin_velocity = geometry::vector<math::op::measurements_div_t<length_um, time_um>, DIM>; 

    using ulin_velocity2 = ulin_velocity<2>;
    using ulin_velocity3 = ulin_velocity<3>;


} // namespace scipp::physics