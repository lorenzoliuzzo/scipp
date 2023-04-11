/**
 * @file    geometry/linear_algebra/vectorial_base.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of 
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */





/// @brief geometry namespace contains all the classes and functions of the geometry library
namespace scipp::geometry {


    template <typename VEC_TYPE, std::size_t DIM>
        requires (is_vector_v<VEC_TYPE>)
    struct vectorial_base {


        using type = vectorial_base<VEC_TYPE, DIM>;

        using data_t = matrix<VEC_TYPE, DIM>;

        using vector_t = VEC_TYPE;

        using measurement_t = typename vector_t::measurement_type;


        static inline constexpr std::size_t dim = DIM;


        data_t data;


        constexpr vectorial_base() noexcept : 
            
            data{data_t::identity()} {}


        constexpr vectorial_base(const data_t& other) {

            if (other.determinant() != measurement_t::zero)
                this->data = other;
            else
                throw std::invalid_argument("Cannot initializate a vectorial base with matrix of linear dependent vectors");

        } 
            
        constexpr vectorial_base(data_t&& other) {

            if (other.determinant() != measurement_t::zero)
                this->data = std::move(other);
            else
                throw std::invalid_argument("Cannot initializate a vectorial base with matrix of linear dependent vectors");

        }


        constexpr vectorial_base(const vectorial_base& other) noexcept :

            data{other.data} {}

        constexpr vectorial_base(vectorial_base&& other) noexcept :

            data{std::move(other.data)} {}


        constexpr bool operator==(const vectorial_base& other) const noexcept {

            return data == other.data;

        }

        constexpr bool operator!=(const vectorial_base& other) const noexcept {

            return !(*this == other);

        }


        constexpr const vector_t& operator[](const std::size_t index) const noexcept {

            return data[index];

        }


        constexpr bool is_normalized() const noexcept {

            for (std::size_t i{}; i < dim; ++i) 
                if (math::op::norm(this->data.column(i)) != measurement_t::one)
                    return false;

            return true;

        }


        constexpr vectorial_base& normalize() noexcept {

            if (!this->is_normalized()) {

                data_t result; 
                for (std::size_t i{}; i < dim; ++i) 
                    result[i] = math::op::normalize(data[i]);

                return result;

            } else 
                return *this;

        }


        constexpr vector<physics::scalar_m, vector_t::dim> from_base(const vector_t& v) const noexcept {

            return this->data.solve(v);

        }


        constexpr vector_t to_base(const vector<physics::scalar_m, vector_t::dim>& v) const noexcept {

            return this->data * v;

        }


    }; // struct base


    // template <typename VEC_TYPE, std::size_t DIM>
    //     requires (is_vector_v<VEC_TYPE>)
    // struct onb : public vectorial_base<VEC_TYPE, DIM> {


    //     using type = onb<VEC_TYPE, DIM>;

    //     using base_t = vectorial_base<VEC_TYPE, DIM>;

    //     // using vector_t = VEC_TYPE;

    //     // using measurement_t = typename VEC_TYPE::measurement_type;


    //     // static inline constexpr std::size_t dim = DIM;

    //     // data_t data;

    //     constexpr onb(const base_t& other) {

    //         for (std::size_t i{}; i < DIM; ++i)
    //             if (math::op::norm(other.data.column(i)) != base_t::measurement_t::one)
    //                 throw std::invalid_argument("Cannot initializate an orthonormal basis with non normalized vectors");
        
    //         else
    //             this->data = other.data;

    //     } 

    //     constexpr onb(base_t&& other) {

    //         for (std::size_t i{}; i < DIM; ++i)
    //             if (math::op::norm(other.data.column(i)) != base_t::measurement_t::one)
    //                 throw std::invalid_argument("Cannot initializate an orthonormal basis with non normalized vectors");
            
    //         else
    //             this->data = std::move(other.data);

    //     }


    //     // constexpr onb(const base_t::data_t& other) {

    //     //     if (other.determinant() == base_t::measurement_t::zero)
    //     //         throw std::invalid_argument("Cannot initializate an vectorial base with matrix of linear dependent vectors");

    //     //     else
    //     //         for (std::size_t i{}; i < DIM; ++i)
    //     //             if (math::op::norm(other.column(i)) != base_t::measurement_t::one)
    //     //                 throw std::invalid_argument("Cannot initializate an orthonormal basis with non normalized vectors");
            
    //     //     else
    //     //         this->data = other;

    //     // } 

    //     // constexpr onb(base_t::data_t&& other) {

    //     //     if (other.determinant() == base_t::measurement_t::zero)
    //     //         throw std::invalid_argument("Cannot initializate an vectorial base with matrix of linear dependent vectors");

    //     //     else
    //     //         for (std::size_t i{}; i < DIM; ++i)
    //     //             if (math::op::norm(other.column(i)) != base_t::measurement_t::one)
    //     //                 throw std::invalid_argument("Cannot initializate an orthonormal basis with non normalized vectors");
            
    //     //     else
    //     //         this->data = std::move(other);

    //     // }


    //     constexpr bool is_normalized() const noexcept {

    //         return true;

    //     }


    // }; // struct onb


} // namespace scipp::geometry