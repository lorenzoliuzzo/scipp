/**
 * @file linear_velocity.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2022-12-21
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::physics {


    /**
     * @brief Class expressing the linear_velocity of a generic object as a vector of measurements
     * @see template <size_t DIM> vector 
     * 
     * @note The linear_velocity unit_base must be metre / second
     * @note The linear_velocity is expressed in a cartesian coordinate system
     * @todo Add more coordinate system (e.g. polar, spherical, cylindrical)
     * 
     * @tparam DIM: size_t dimesions of the space
     */
    template <size_t DIM> 
    class linear_velocity : public vector<DIM> {


        public: 

        // =============================================
        // constructors & destructor
        // =============================================

            /**
             * @brief Construct a new default linear_velocity object
             * 
             * @note The linear_velocity is set to zero metre / second
             */
            explicit constexpr linear_velocity() noexcept : 
            
                vector<DIM>(basis::metre / basis::second) {}


            /**
             * @brief Construct a new linear_velocity from a pack of coordinates
             * 
             * @param coord: list of all the coordinates
             * 
             * @note The number of components must be the same as the dimesion of the vector
             */
            template <typename... coord>
            constexpr linear_velocity(const coord&... coords) requires (sizeof...(coords) == DIM) {
                    
                for (const measurement& x : {coords...}) 
                    if (x.units().base() != basis::metre / basis::second) 
                        throw std::invalid_argument("Wrong linear_velocity unit, the unit_base must be metre / second"); 

                this->data_ = {coords...};

            }


            /**
             * @brief Construct a new linear_velocity object from an std::array of speed measurements
             * 
             * @param vel: std::array of speed measurements as l-value const reference
             */
            constexpr linear_velocity(const std::array<speed_measurement, DIM>& vel) : 
                
                vector<DIM>(vel) {}


            /**
             * @brief Construct a new linear_velocity object from an std::array of speed measurements
             * 
             * @param vel: std::array of speed measurements as r-value reference
             */
            constexpr linear_velocity(std::array<speed_measurement, DIM>&& vel) :
                
                vector<DIM>(std::move(vel)) {}


            /**
             * @brief Construct a new linear_velocity object from a vector of measurements
             * 
             * @param vel: vector of measurements as l-value const reference
             */
            constexpr linear_velocity(const vector<DIM>& vel) : 
                
                vector<DIM>(vel) {

                    for (size_t i{}; i < DIM; ++i) {

                        if (vel[i].units().base() != basis::metre / basis::second) 
                            throw std::invalid_argument("Wrong linear_velocity unit, the unit_base must be metre / second");
                    
                    }
                
                }


            /**
             * @brief Construct a new linear_velocity object from a vector of measurements
             * 
             * @param vel: vector of measurements as r-value reference
             */
            constexpr linear_velocity(vector<DIM>&& vel) : 
                
                vector<DIM>(std::move(vel)) {

                    for (size_t i{}; i < DIM; ++i) {

                        if (vel[i].units().base() != basis::metre / basis::second) 
                            throw std::invalid_argument("Wrong linear_velocity unit, the unit_base must be metre / second");
                    
                    }
                
                }

            
            /// @brief Default destructor
            ~linear_velocity() = default; 


        // =============================================
        // operators
        // =============================================

            /**
             * @brief Output stream operator
             * 
             * @param os: std::ostream&
             * @param vel: linear_velocity to be printed as l-value const reference
             * 
             * @return constexpr std::ostream& 
             */
            friend constexpr std::ostream& operator<<(std::ostream& os, const linear_velocity& vel) noexcept { 

                os << "linear_velocity = " << vel.as_vector(); 

                return os;

            }


            /**
             * @brief Output stream operator
             * 
             * @param file: std::ofstream&
             * @param vel: linear_velocity to be printed as l-value const reference
             * 
             * @return constexpr std::ofstream& 
             */
            friend constexpr std::ofstream& operator<<(std::ofstream& file, const linear_velocity& vel) noexcept { 

                file << "linear_velocity = " << vel.as_vector(); 

                return file;

            }


            /**
             * @brief Print the linear_velocity to the standard output
             * 
             * @param newline: if true, print a newline character at the end of the output
             * 
             * @return void
             */
            constexpr void print() const noexcept {

                std::cout << "linear_velocity = ";
                this->vector<DIM>::print(); 

            }   


    }; // class linear_velocity


    /// @brief Template deduction guide for a list of coordinates
    template <typename... coord>
    linear_velocity(const coord&...) -> linear_velocity<sizeof...(coord)>;


} // namespace scipp::physics {