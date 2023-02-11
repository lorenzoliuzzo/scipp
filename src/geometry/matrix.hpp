/**
 * @file    geometry/matrix.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-02-11
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::geometry {


template <typename... Args>
struct custom_tuple : std::tuple<Args...>
{
    template <typename... Vectors>
    custom_tuple(Vectors&&... vectors) :
        std::tuple<Args...>(std::forward<Vectors>(vectors)...)
    {}
};

} // namespace scipp::geometry

namespace std {

    template <typename... Args>
    struct tuple_size<scipp::geometry::custom_tuple<Args...>>
        : public std::tuple_size<std::tuple<Args...>>
    {};

} // namespace std


namespace scipp::geometry {

template <size_t N, size_t M, typename... TYPES>
class matrix {

private: 

    custom_tuple<TYPES...> data_;

    static_assert((N > 0) && (M > 0), "matrix dimensions must be greater than zero.");
    static_assert(are_vectors_v<TYPES...>, "matrix must contain vectors as elements.");


public:
    using type = matrix<N, M, TYPES...>;

    static inline constexpr size_t rows = N;

    static inline constexpr size_t columns = M;

    static inline constexpr size_t size = N * M;

    

    constexpr matrix() noexcept : 
        data_{} {}

    template <typename... VECTORS>
    constexpr matrix(VECTORS&&... vectors) noexcept : 
        data_{std::forward<VECTORS>(vectors)...} {}


    // constexpr auto operator[](size_t i) {
        
    //     if (i < N)
    //         throw std::runtime_error("matrix index out of range.");

    //     return std::get<i>(this->data_);

    // }

    // constexpr auto operator[](size_t i) const {
        
    //     if (i < N)
    //         throw std::runtime_error("matrix index out of range.");

    //     return std::get<i>(this->data_);

    // }


    void print() const noexcept {

        std::apply([](const auto&... args) {
            ((std::cout << args), ...);
        }, this->data_);

    }

}; 

template <size_t N, size_t M, typename... VECTORS>
matrix<N, M, VECTORS...> make_matrix(VECTORS&&... vectors)
{
    static_assert(are_vectors_v<VECTORS...>, "make_matrix must take vectors as arguments.");
    static_assert(sizeof...(VECTORS) == M, "number of vectors must match matrix column count.");
    return matrix<N, M, VECTORS...>(std::forward<VECTORS>(vectors)...);
}


            // constexpr matrix& operator=(const matrix& other) noexcept {
            //     m_vectors = other.m_vectors;
            //     return *this;
            // }


            // constexpr matrix& operator=(matrix&& other) noexcept {
            //     m_vectors = std::move(other.m_vectors);
            //     return *this;
            // }


            // constexpr auto operator[](const size_t index) const noexcept {
            //     return m_vectors[index];
            // }


            // constexpr auto operator[](const size_t index) noexcept {
            //     return m_vectors[index];
            // }


            // constexpr auto operator()(const size_t row, const size_t column) const noexcept {
            //     return m_vectors[column][row];
            // }


            // constexpr auto operator()(const size_t row, const size_t column) noexcept {
            //     return m_vectors[column][row];
            // }


            // constexpr auto operator==(const matrix& other) const noexcept {
            //     return m_vectors == other.m_vectors;
            // }


            // constexpr auto operator!=(const matrix& other) const noexcept {
            //     return m_vectors != other.m_vectors;
            // }


            // constexpr auto operator+(const matrix& other) const noexcept {
            //     return matrix{m_vectors + other.m_vectors};
            // }


            // constexpr auto operator-(const matrix& other) const noexcept {
            //     return matrix{m_vectors - other.m_vectors};
            // }


            // constexpr auto operator*(const matrix& other) const noexcept {
            //     return matrix{m_vectors * other.m_vectors};
            // }


            // constexpr auto operator/(const matrix& other) const noexcept {
            //     return matrix{m_vectors / other.m_vectors};
            // }


            // constexpr auto operator+=(const matrix& other) noexcept {
            //     m_vectors += other.m_vectors;
            //     return *this;
            // }


            // constexpr auto operator-=(const matrix& other) noexcept {
            //     m_vectors -= other.m_vectors;
            //     return *this;
            // }


            // constexpr auto operator*=(const matrix& other) noexcept {
            //     m_vectors *= other.m_vectors;
            //     return *this;
            // }


            // constexpr auto operator/=(const matrix& other) noexcept {
            //     m_vectors /= other.m_vectors;
            //     return *this;
            // }


            // constexpr auto operator+(const value_type& value) const noexcept {
            //     return matrix{m_vectors + value};
            // }



            // constexpr auto operator-(const value_type& value) const noexcept {
            //     return matrix{m_vectors - value};
            // }


            // constexpr auto operator*(const value_type& value) const noexcept {
            //     return matrix{m_vectors * value};
            // }


            // constexpr auto operator/(const value_type& value) const noexcept {
            //     return matrix{m_vectors / value};
            // }


            // constexpr auto operator+=(const value_type& value) noexcept {
            //     m_vectors += value;
            //     return *this;
            // }


            // constexpr auto operator-=(const value_type& value) noexcept {
            //     m_vectors -= value;
            //     return *this;
            // }


            // constexpr auto operator*=(const value_type& value) noexcept {
            //     m_vectors *= value;
            //     return *this;
            // }



            







} // namespace scipp::geometry