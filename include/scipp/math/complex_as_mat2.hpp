#pragma once


namespace scipp::math {
    

    template <typename MEAS_TYPE>
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    struct complex_as_mat2 {


        using type = complex<MEAS_TYPE>;
        using data_type = geometry::matrix<geometry::vector<MEAS_TYPE, 2>, 2>;
        using value_type = MEAS_TYPE; 


        data_type data; 


        constexpr complex_as_mat2() noexcept : 
            
            data{} {}


        constexpr complex_as_mat2(const complex_as_mat2& other) noexcept :

            data{other.data} {}


        constexpr complex_as_mat2(type&& other) noexcept :

            data{std::move(other.data)} {}


        constexpr complex_as_mat2(const value_type& real, const value_type& imag) noexcept :

            data{data_type(geometry::make_vector<value_type>(real, imag), geometry::make_vector<value_type>(-imag, real))} {}


    }; 


} // namespace scipp::math