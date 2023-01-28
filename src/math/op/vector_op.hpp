/**
 * @file    geometry::vector_op.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-21
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp::math {


    namespace op {


        /**
         * @brief Invert the geometry::vector
         *
         * @param other: geometry::vector<UB, DIM> as l-value const reference
         *
         * @return constexpr geometry::vector<op::inv(UB), DIM>
         */
        template <unit_base UB, std::size_t DIM>
        constexpr geometry::vector<op::inv(UB), DIM> inv(const geometry::vector<UB, DIM>& other) {

            std::array<measurement<op::inv(UB)>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i)
                result[i] = op::inv(other[i]); 
            
            return result;

        }


        /**
         * @brief Invert the geometry::vector
         *
         * @param other: geometry::vector<UB, DIM> as r-value reference
         *
         * @return constexpr geometry::vector<op::inv(UB), DIM>
         */
        template <unit_base UB, std::size_t DIM>
        constexpr geometry::vector<op::inv(UB), DIM> inv(geometry::vector<UB, DIM>&& other) {

            std::array<measurement<op::inv(UB)>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i)
                result[i] = op::inv(other[i]); 
            
            return result;

        }


        /**
         * @brief Take the power of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as l-value const reference
         * @param power: int
         *  
         * @return constexpr geometry::vector<op::pow(UB, power), DIM>
         */
        template <unit_base UB, std::size_t DIM>
        constexpr auto pow(const geometry::vector<UB, DIM>& other, const int& power) noexcept {

            std::array<measurement<op::pow(UB, power)>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i)
                result[i] = op::pow(other[i], power);
            
            return result;

        }


        /**
         * @brief Take the power of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as r-value reference
         * @param power: int
         *  
         * @return constexpr geometry::vector<op::pow(UB, power), DIM>
         */
        template <unit_base UB, std::size_t DIM>
        constexpr auto pow(geometry::vector<UB, DIM>&& other, const int& power) noexcept {

            std::array<measurement<op::pow(UB, power)>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i)
                result[i] = op::pow(other[i], power);
            
            return result;

        }


        /**
         * @brief Take the square power of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as l-value const reference
         *  
         * @return constexpr geometry::vector<op::square(UB), DIM>
         */
        template <unit_base UB, std::size_t DIM>
        constexpr geometry::vector<op::square(UB), DIM> square(const geometry::vector<UB, DIM>& other) noexcept {

            std::array<measurement<op::square(UB)>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i)
                result[i] = op::square(other[i]);
            
            return result;

        }


        /**
         * @brief Take the square power of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as r-value reference
         *  
         * @return constexpr geometry::vector<op::square(UB), DIM>
         */
        template <unit_base UB, std::size_t DIM>
        constexpr geometry::vector<op::square(UB), DIM> square(geometry::vector<UB, DIM>&& other) noexcept {

            std::array<measurement<op::square(UB)>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i)
                result[i] = op::square(other[i]);
            
            return result;

        }


        /**
         * @brief Take the cube power of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as l-value const reference
         *  
         * @return constexpr geometry::vector<op::cube(UB), DIM>
         */
        template <unit_base UB, std::size_t DIM>
        constexpr geometry::vector<op::cube(UB), DIM> cube(const geometry::vector<UB, DIM>& other) noexcept {

            std::array<measurement<op::cube(UB)>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i)
                result[i] = op::cube(other[i]);
            
            return result;

        }


        /**
         * @brief Take the cube power of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as r-value reference
         *  
         * @return constexpr geometry::vector<op::cube(UB), DIM>
         */
        template <unit_base UB, std::size_t DIM>
        constexpr geometry::vector<op::cube(UB), DIM> cube(geometry::vector<UB, DIM>&& other) noexcept {

            std::array<measurement<op::cube(UB)>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i)
                result[i] = op::cube(other[i]);
            
            return result;

        }


        /**
         * @brief Take the root of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as l-value const reference
         * @param power: int
         * 
         * @return constexpr geometry::vector<op::root(UB, power), DIM>
         */
        template <unit_base UB, std::size_t DIM>
        constexpr auto root(const geometry::vector<UB, DIM>& other, const int& power) {

            std::array<measurement<op::root(UB, power)>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i)
                result[i] = op::root(other[i], power);
            
            return result;

        }


        /**
         * @brief Take the root of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as r-value reference
         * @param power: int
         * 
         * @return constexpr geometry::vector<op::root(UB, power), DIM>
         */
        template <unit_base UB, std::size_t DIM>
        constexpr auto root(geometry::vector<UB, DIM>&& other, const int& power) {

            std::array<measurement<op::root(UB, power)>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i)
                result[i] = op::root(other[i], power);
            
            return result;

        }


        /**
         * @brief Take the square root of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as l-value const reference
         *  
         * @return constexpr geometry::vector<op::sqrt(UB), DIM>
         */
        template <unit_base UB, std::size_t DIM>
        constexpr geometry::vector<op::sqrt(UB), DIM> sqrt(const geometry::vector<UB, DIM>& other) noexcept {

            std::array<measurement<op::sqrt(UB)>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i)
                result[i] = op::sqrt(other[i]);
            
            return result;

        }


        /**
         * @brief Take the square root of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as r-value reference
         *  
         * @return constexpr geometry::vector<op::sqrt(UB), DIM>
         */
        template <unit_base UB, std::size_t DIM>
        constexpr geometry::vector<op::sqrt(UB), DIM> sqrt(geometry::vector<UB, DIM>&& other) noexcept {

            std::array<measurement<op::sqrt(UB)>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i)
                result[i] = op::sqrt(other[i]);
            
            return result;

        }


        /**
         * @brief Take the cubic root of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as l-value const reference
         *  
         * @return constexpr geometry::vector<op::cbrt(UB), DIM>
         */
        template <unit_base UB, std::size_t DIM>
        constexpr geometry::vector<op::cbrt(UB), DIM> cbrt(const geometry::vector<UB, DIM>& other) noexcept {

            std::array<measurement<op::cbrt(UB)>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i)
                result[i] = op::cbrt(other[i]);
            
            return result;

        }


        /**
         * @brief Take the cubic root of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as r-value reference
         *  
         * @return constexpr geometry::vector<op::cbrt(UB), DIM>
         */
        template <unit_base UB, std::size_t DIM>
        constexpr geometry::vector<op::cbrt(UB), DIM> cbrt(geometry::vector<UB, DIM>&& other) noexcept {

            std::array<measurement<op::cbrt(UB)>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i)
                result[i] = op::cbrt(other[i]);
            
            return result;

        }


        /**
         * @brief Get the norm of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as l-value const reference
         *
         * @return constexpr measurement 
         */
        template <unit_base UB, std::size_t DIM>
        constexpr measurement<UB> norm(const geometry::vector<UB, DIM>& other) noexcept { 

            if constexpr (DIM == 1) 
                return other[0];

            geometry::vector<op::square(UB), DIM> squared = op::square(other);

            return op::sqrt(std::accumulate(squared.data().begin(), squared.data().end(), measurement<op::square(UB)>()));

        }


        /**
         * @brief Get the norm of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as r-value reference
         *
         * @return constexpr measurement 
         */
        template <unit_base UB, std::size_t DIM>
        constexpr measurement<UB> norm(geometry::vector<UB, DIM>&& other) noexcept { 

            if constexpr (DIM == 1) 
                return other[0];

            geometry::vector<op::square(UB), DIM> squared = op::square(other);

            return op::sqrt(std::accumulate(squared.data().begin(), squared.data().end(), measurement<op::square(UB)>()));

        }


        /**
         * @brief Get the norm squared of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as l-value const reference
         *
         * @return constexpr measurement 
         */
        template <unit_base UB, std::size_t DIM>
        constexpr measurement<op::square(UB)> norm2(const geometry::vector<UB, DIM>& other) noexcept { 

            if constexpr (DIM == 1) 
                return other[0];

            geometry::vector<op::square(UB), DIM> squared = op::square(other);

            return std::accumulate(squared.data().begin(), squared.data().end(), measurement<op::square(UB)>());

        }


        /**
         * @brief Get the norm squared of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as r-value reference
         *
         * @return constexpr measurement 
         */
        template <unit_base UB, std::size_t DIM>
        constexpr measurement<op::square(UB)> norm2(geometry::vector<UB, DIM>&& other) noexcept { 

            if constexpr (DIM == 1) 
                return other[0];

            geometry::vector<op::square(UB), DIM> squared = op::square(other);

            return std::accumulate(squared.data().begin(), squared.data().end(), measurement<op::square(UB)>());

        }


        /**
         * @brief Compute the cross product between two geometry::vectors
         * 
         * @param v1: geometry::vector<UB1, DIM> as l-value const reference
         * @param v2: geometry::vector<UB2, DIM> as l-value const reference
         * 
         * @return constexpr geometry::vector<UB1 * UB2, DIM>
         */
        template <unit_base UB1, unit_base UB2, std::size_t DIM>
        constexpr geometry::vector<UB1 * UB2, DIM> cross(const geometry::vector<UB1, DIM>& v1, 
                                                         const geometry::vector<UB2, DIM>& v2) {

            std::array<measurement<UB1 * UB2>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i) 
                result[i] = v1[(i + 1) % v1.size()] * v2[(i + 2) % v1.size()] - v1[(i + 2) % v1.size()] * v2[(i + 1) % v1.size()]; 

            return result;
        
        }

        
        /**
         * @brief Compute the cross product between two geometry::vectors
         * 
         * @param v1: geometry::vector<UB1, DIM> as r-value reference
         * @param v2: geometry::vector<UB2, DIM> as r-value reference
         * 
         * @return constexpr geometry::vector<UB1 * UB2, DIM>
         */
        template <unit_base UB1, unit_base UB2, std::size_t DIM>
        constexpr geometry::vector<UB1 * UB2, DIM> cross(geometry::vector<UB1, DIM>&& v1, 
                                                         geometry::vector<UB2, DIM>&& v2) {

            std::array<measurement<UB1 * UB2>, DIM> result;
            for (std::size_t i{}; i < DIM; ++i) 
                result[i] = v1[(i + 1) % v1.size()] * v2[(i + 2) % v1.size()] - v1[(i + 2) % v1.size()] * v2[(i + 1) % v1.size()]; 

            return result;
        
        }


        /**
         * @brief Compute the dot product between two geometry::vectors
         * 
         * @param v1: geometry::vector<UB1, DIM> as l-value const reference
         * @param v2: geometry::vector<UB2, DIM> as l-value const reference
         * 
         * @return constexpr measurement<UB1 * UB2>
         */
        template <unit_base UB1, unit_base UB2, std::size_t DIM>
        constexpr measurement<UB1 * UB2> dot(const geometry::vector<UB1, DIM>& v1, 
                                             const geometry::vector<UB2, DIM>& v2) {

            measurement<UB1 * UB2> result;
            for (std::size_t i{}; i < DIM; ++i)
                result += v1[i] * v2[i]; 
            
            return result;
        
        }


        /**
         * @brief Compute the dot product between two geometry::vectors
         * 
         * @param v1: geometry::vector<UB1, DIM> as r-value reference
         * @param v2: geometry::vector<UB2, DIM> as r-value reference
         * 
         * @return constexpr measurement<UB1 * UB2>
         */
        template <unit_base UB1, unit_base UB2, std::size_t DIM>
        constexpr measurement<UB1 * UB2> dot(geometry::vector<UB1, DIM>&& v1,   
                                             geometry::vector<UB2, DIM>&& v2) {

            measurement<UB1 * UB2> result;
            for (std::size_t i{}; i < DIM; ++i)
                result += v1[i] * v2[i]; 
            
            return result;
        
        }


        /**
         * @brief Get the normalization of the geometry::vector
         *
         * @param other: geometry::vector<UB, DIM> as l-value const reference
         *
         * @return constexpr geometry::vector 
         */
        template <unit_base UB, std::size_t DIM>
        constexpr geometry::vector<basis::scalar, DIM> normalize(const geometry::vector<UB, DIM>& other) {

            return other / op::norm(other); 

        } 


        /**
         * @brief Get the normalization of the geometry::vector
         * 
         * @param other: geometry::vector<UB, DIM> as r-value reference
         *
         * @return constexpr geometry::vector 
         */
        template <unit_base UB, std::size_t DIM>
        constexpr geometry::vector<basis::scalar, DIM> normalize(geometry::vector<UB, DIM>&& other) {

            return other / op::norm(other); 

        }     
        
        
    } // namespace op


} // namespace scipp::math