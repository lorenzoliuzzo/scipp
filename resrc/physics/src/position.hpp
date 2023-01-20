/**
 * @file position.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2022-12-21
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::physics {


    template <std::size_t DIM> 
    using position = vector<basis::metre, DIM>; 

    using position2 = position<2>;
    using position3 = position<3>;


    // /**
    //  * @brief Class expressing the position of a generic object as a vector of measurements
    //  * @see template <size_t DIM> vector 
    //  * 
    //  * @note The position unit_base must be metre
    //  * @note The position is expressed in a cartesian coordinate system
    //  * @todo Add more coordinate system (e.g. polar, spherical, cylindrical)
    //  * 
    //  * @tparam DIM: size_t dimesions of the space
    //  */
    // template <size_t DIM> 
    // class position : public vector<basis::metre, DIM> {


    //     public: 

    //     // =============================================
    //     // constructors & destructor
    //     // =============================================

    //         /**
    //          * @brief Construct a new default position object
    //          * 
    //          * @note The position is set to zero metre
    //          */
    //         explicit constexpr position() noexcept : 
            
    //             vector<DIM>(basis::metre) {}


    //         /**
    //          * @brief Construct a new position from a pack of coordinates
    //          * 
    //          * @param coords: list of all the coordinates
    //          * 
    //          * @note The number of components must be the same as the dimesion of the vector
    //          */
    //         template <typename... coord>
    //         constexpr position(const coord&... coords) requires (sizeof...(coords) == DIM) {
                    
    //             for (const measurement& x : {coords...}) 
    //                 if (x.units().base() != basis::metre) 
    //                     throw std::invalid_argument("Wrong position unit, the unit_base must be metre"); 

    //             this->data_ = {coords...};

    //         }


    //         /**
    //          * @brief Construct a new position object from an std::array of length measurements
    //          * 
    //          * @param pos: std::array of length measurements as l-value const reference
    //          */
    //         constexpr position(const std::array<length_measurement, DIM>& pos) : 
                
    //             vector<DIM>(pos) {}


    //         /**
    //          * @brief Construct a new position object from an std::array of length measurements
    //          * 
    //          * @param pos: std::array of length measurements as r-value reference
    //          */
    //         constexpr position(std::array<length_measurement, DIM>&& pos) :
                
    //             vector<DIM>(std::move(pos)) {}


    //         /**
    //          * @brief Construct a new position object from a vector of measurements
    //          * 
    //          * @param pos: vector of measurements as l-value const reference
    //          */
    //         constexpr position(const vector<DIM>& pos) : 
                
    //             vector<DIM>(pos) {

    //                 for (size_t i{}; i < DIM; ++i) {

    //                     if (pos[i].units().base() != basis::metre) 
    //                         throw std::invalid_argument("Wrong position unit, the unit_base must be metre");
                    
    //                 }
                
    //             }


    //         /**
    //          * @brief Construct a new position object from a vector of measurements
    //          * 
    //          * @param pos: vector of measurements as r-value reference
    //          */
    //         constexpr position(vector<DIM>&& pos) : 
                
    //             vector<DIM>(std::move(pos)) {

    //                 for (size_t i{}; i < DIM; ++i) {

    //                     if (pos[i].units().base() != basis::metre) 
    //                         throw std::invalid_argument("Wrong position unit, the unit_base must be metre");
                    
    //                 }
                
    //             }

            
    //         /// @brief Default destructor
    //         ~position() = default; 


    //     // =============================================
    //     // operators
    //     // =============================================

    //         /**
    //          * @brief Output stream operator
    //          * 
    //          * @param os: std::ostream&
    //          * @param pos: position to be printed as l-value const reference
    //          * 
    //          * @return constexpr std::ostream& 
    //          */
    //         friend constexpr std::ostream& operator<<(std::ostream& os, const position& pos) noexcept { 

    //             os << "position = " << pos.as_vector(); 

    //             return os;

    //         }


    //         /**
    //          * @brief Output stream operator
    //          * 
    //          * @param file: std::ofstream&
    //          * @param pos: position to be printed as l-value const reference
    //          * 
    //          * @return constexpr std::ofstream& 
    //          */
    //         friend constexpr std::ofstream& operator<<(std::ofstream& file, const position& pos) noexcept { 

    //             file << "position = " << pos.as_vector(); 

    //             return file;

    //         }


    //     // =============================================
    //     // get methods
    //     // =============================================

    //         /**
    //          * @brief Get the distance between this position and another position
    //          * 
    //          * @param other: position to be compared as l-value const reference
    //          * 
    //          * @return constexpr length_measurement 
    //          */
    //         constexpr length_measurement distance(const position& other) const noexcept {    
                
    //             return (other - *this).norm();
                
    //         }       


    //         /**
    //          * @brief Get the square distance between this position and another position
    //          * 
    //          * @param other: position to be compared as l-value const reference
    //          * 
    //          * @return constexpr measurement 
    //          */
    //         constexpr measurement distance2(const position& other) const noexcept {    
                
    //             return (other - *this).norm2();
                
    //         }       


    //         /**
    //          * @brief Get the polar angle of this position
    //          * 
    //          * @return constexpr measurement 
    //          */
    //         constexpr measurement phi() const noexcept {

    //             return vector<DIM>::phi();

    //         }

                
    //         /**
    //          * @brief Get the polar angle between this position and another position
    //          * 
    //          * @param other: position to be compared as l-value const reference
    //          * 
    //          * @return constexpr measurement 
    //          */
    //         constexpr measurement phi(const position& other) const noexcept requires (DIM >= 2) { 

    //             if (other != *this) 
    //                 return (other - *this).phi();
    //             else 
    //                 return 0.0 * rad;
                                    
    //         }


    //         /**
    //          * @brief Get the azimuthal angle of this position
    //          * 
    //          * @return constexpr measurement 
    //          */
    //         constexpr measurement theta() const noexcept {

    //             return vector<DIM>::theta();

    //         }


    //         /**
    //          * @brief Get the azimuthal angle between this position and another position
    //          * 
    //          * @param other: position to be compared as l-value const reference
    //          * 
    //          * @return constexpr measurement 
    //          */
    //         constexpr measurement theta(const position& other) const noexcept requires (DIM >= 3) {

    //             if (other.pos_[2] != this->operator[](2)) 
    //                 return (other - *this).theta(); 
    //             else 
    //                 return 0.0 * rad;
            
    //         }


    //         /**
    //          * @brief Get the versor between this position and another position
    //          * 
    //          * @param other: position to be compared as l-value const reference
    //          * 
    //          * @return constexpr verctor
    //          */
    //         constexpr vector<DIM> direction(const position& other) const noexcept requires (DIM >= 2) {

    //             if (other != *this)
    //                 return vector<DIM>((other - *this) / this->distance(other));
    //             else 
    //                 return vector<DIM>();

    //         } 


    //         /**
    //          * @brief Print the position to the standard output
    //          * 
    //          * @param newline: if true, print a newline character at the end of the output
    //          * 
    //          * @return void
    //          */
    //         constexpr void print() const noexcept {

    //             std::cout << "position = ";
    //             this->vector<DIM>::print(); 

    //         }   


    // }; // class position


    // /// @brief Template deduction guide for a list of coordinates
    // template <typename... coord>
    // position(const coord&...) -> position<sizeof...(coord)>;


} // namespace scipp::physics {