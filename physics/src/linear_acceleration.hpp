/**
 * @file linear_acceleration.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2022-12-21
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::physics {


    /**
     * @brief Class expressing the linear_acceleration of a generic object as a vector of measurements
     * @see template <size_t DIM> vector 
     * 
     * @note The linear_acceleration unit_base must be metre / second^2
     * @note The linear_acceleration is expressed in a cartesian coordinate system
     * @todo Add more coordinate system (e.g. polar, spherical, cylindrical)
     * 
     * @tparam DIM: size_t dimesions of the space
     */
    template <size_t DIM> 
    class linear_acceleration : public vector<DIM> {


        public: 

        // =============================================
        // constructors & destructor
        // =============================================

            /**
             * @brief Construct a new default linear_acceleration object
             * 
             * @note The linear_acceleration is set to zero metre / second^2
             */
            explicit constexpr linear_acceleration() noexcept : 
            
                vector<DIM>(basis::metre / basis::second.square()) {}


            /**
             * @brief Construct a new linear_acceleration from a pack of coordinates
             * 
             * @param coord: list of all the coordinates
             * 
             * @note The number of components must be the same as the dimesion of the vector
             */
            template <typename... coord>
            constexpr linear_acceleration(const coord&... coords) requires (sizeof...(coords) == DIM) {
                    
                for (const measurement& x : {coords...}) 
                    if (x.units().base() != basis::metre / basis::second.square()) 
                        throw std::invalid_argument("Wrong linear_acceleration unit, the unit_base must be metre / second^2"); 

                this->data_ = {coords...};

            }


            /**
             * @brief Construct a new linear_acceleration object from an std::array of acceleration measurements
             * 
             * @param acc: std::array of acceleration measurements as l-value const reference
             */
            constexpr linear_acceleration(const std::array<acceleration_measurement, DIM>& acc) : 
                
                vector<DIM>(acc) {}


            /**
             * @brief Construct a new linear_acceleration object from an std::array of acceleration measurements
             * 
             * @param acc: std::array of acceleration measurements as r-value reference
             */
            constexpr linear_acceleration(std::array<acceleration_measurement, DIM>&& acc) :
                
                vector<DIM>(std::move(acc)) {}


            /**
             * @brief Construct a new linear_acceleration object from a vector of measurements
             * 
             * @param acc: vector of measurements as l-value const reference
             */
            constexpr linear_acceleration(const vector<DIM>& acc) : 
                
                vector<DIM>(acc) {

                    for (size_t i{}; i < DIM; ++i) {

                        if (acc[i].units().base() != basis::metre / basis::second.square()) 
                            throw std::invalid_argument("Wrong linear_acceleration unit, the unit_base must be metre / second^2");
                    
                    }
                
                }


            /**
             * @brief Construct a new linear_acceleration object from a vector of measurements
             * 
             * @param acc: vector of measurements as r-value reference
             */
            constexpr linear_acceleration(vector<DIM>&& acc) : 
                
                vector<DIM>(std::move(acc)) {

                    for (size_t i{}; i < DIM; ++i) {

                        if (acc[i].units().base() != basis::metre / basis::second.square()) 
                            throw std::invalid_argument("Wrong linear_acceleration unit, the unit_base must be metre / second^2");
                    
                    }
                
                }

            
            /// @brief Default destructor
            ~linear_acceleration() = default; 


        // =============================================
        // operators
        // =============================================

            /**
             * @brief Output stream operator
             * 
             * @param os: std::ostream&
             * @param acc: linear_acceleration to be printed as l-value const reference
             * 
             * @return constexpr std::ostream& 
             */
            friend constexpr std::ostream& operator<<(std::ostream& os, const linear_acceleration& acc) noexcept { 

                os << "linear_acceleration = " << acc.as_vector(); 

                return os;

            }


            /**
             * @brief Output stream operator
             * 
             * @param file: std::ofstream&
             * @param acc: linear_acceleration to be printed as l-value const reference
             * 
             * @return constexpr std::ofstream& 
             */
            friend constexpr std::ofstream& operator<<(std::ofstream& file, const linear_acceleration& acc) noexcept { 

                file << "linear_acceleration = " << acc.as_vector(); 

                return file;

            }


            /**
             * @brief Print the linear_acceleration to the standard output
             * 
             * @param newline: if true, print a newline character at the end of the output
             * 
             * @return void
             */
            constexpr void print() const noexcept {

                std::cout << "linear_acceleration = ";
                this->vector<DIM>::print(); 

            }   


    }; // class linear_acceleration


    /// @brief Template deduction guide for a list of coordinates
    template <typename... coord>
    linear_acceleration(const coord&...) -> linear_acceleration<sizeof...(coord)>;


} // namespace scipp::physics {