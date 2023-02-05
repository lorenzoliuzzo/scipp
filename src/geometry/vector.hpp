/**
 * @file vector.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2023-02-03
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::geometry {


    template <typename T, std::size_t DIM>
    struct vector {

        
        // ===========================================================
        // aliases
        // ===========================================================

            using type = vector<T, DIM>;

            using value_type = T;


        // ===========================================================
        // constructors
        // ===========================================================

            /**
             * @brief Construct a new vector specifying the unit_base of the vector
             * 
             * @param unit: unit_base (default = unit_base())
             */
            explicit constexpr vector() noexcept {

                this->data_.fill(T());

            }


            /**
             * @brief Construct a new vector from a pack of measurements
             * 
             * @param vec: list of all the vector components
             * 
             * @note The number of components must be the same as the dimesion of the vector
             */
            template <typename... MEAS>
            constexpr vector(const MEAS&... measurements) noexcept requires (physics::are_measurements_v<MEAS...> && (sizeof...(measurements) == DIM)) : 
                
                data_{(measurements)...} {}


        // ===========================================================
        // operators
        // ===========================================================

            /**
             * @brief Add two vectors
             * 
             * @param vec: vector to add
             * 
             * @return vector&: reference to the vector
             */
            inline constexpr vector& operator+=(const vector& vec) noexcept {

                for (std::size_t i{}; i < DIM; ++i) {

                    this->data_[i] += vec.data_[i];

                }

                return *this;

            }


        // ===========================================================
        // methods
        // ===========================================================

            /**
             * @brief Get the vector components
             * 
             * @return const std::array<T, DIM>&: vector components
             */
            inline constexpr const std::array<T, DIM>& data() const noexcept {

                return this->data_;

            }


            /// @brief Print the vector components
            inline constexpr void print() const noexcept {
                
                std::cout << "( ";
                for (std::size_t i{}; i < DIM; ++i) {

                    std::cout << this->data_[i] << ((i < DIM - 1) ? ", " : " )\n"); 

                }

            }


            template <typename UNITS, typename = std::enable_if_t<physics::units::is_unit_v<UNITS>>>
            inline constexpr void print(const UNITS& units) const noexcept {
                
                std::cout << "( ";
                for (std::size_t i{}; i < DIM; ++i) {

                    this->data_[i].print(units, false); 
                    std::cout << ((i < DIM - 1) ? ", " : " )\n"); 

                }

            }
            

        // ===========================================================
        // members
        // ===========================================================

            std::array<T, DIM> data_;

            inline static constexpr std::size_t dimension = DIM;


    }; // struct vector


    template <typename T, typename... MEAS>
    vector(const MEAS&... measurements) -> vector<T, sizeof...(measurements)>; 

    template <typename T, typename... MEAS>
    vector(MEAS&&... measurements) -> vector<T, sizeof...(measurements)>; 


    // template <template <unit_base UB> class... measurements_type, unit_base UB>
    // vector(measurements_type<UB>&&... measurements) -> vector<UB, sizeof...(measurements)>; 


} // namespace scipp::geometry