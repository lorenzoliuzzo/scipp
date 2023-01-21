/**
 * @file mass.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2023-01-21
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::physics {


    /**
     * @brief Class for a generic mass_point
     * 
     * @tparam DIM: dimension of the space
     */
    template <size_t DIM>
    class mass {


        public: 

        // =============================================
        // constructors and destructor 
        // =============================================

            /**
             * @brief Construct a new mass object
             * 
             * @param m: mass_m of mass
             * @param pos: position<DIM> vector
             * @param vel: lin_velocity vector
             * @param acc: lin_acceleration vector
             * 
             */
            mass(mass_m&& mass_meas, 
                           position<DIM>&& pos = position<DIM>(), 
                           lin_velocity<DIM>&& vel = lin_velocity<DIM>(), 
                           lin_acceleration<DIM>&& acc = lin_acceleration<DIM>()) {

                this->mass_ = std::move(mass_meas);
                this->position_ = std::move(pos);
                this->lin_velocity_ = std::move(vel);
                this->lin_acceleration_ = std::move(acc);

            }


            /**
             * @brief Copy construct a new mass object
             * 
             * @param other: mass object to copy from as l-result const reference
             */
            constexpr mass(const mass& other) noexcept : 
            
                mass_(other.mass_),
                position_(other.position_), 
                lin_velocity_(other.lin_velocity_), 
                lin_acceleration_(other.lin_acceleration_) {} 


            /**
             * @brief Move construct a new mass object
             * 
             * @param other: mass object to move from as r-value reference
             */
            constexpr mass(mass&& other) noexcept : 
            
                mass_(std::move(other.mass_)),
                position_(std::move(other.position_)), 
                lin_velocity_(std::move(other.lin_velocity_)), 
                lin_acceleration_(std::move(other.lin_acceleration_)) {} 


            /// @brief Default destructor
            ~mass() noexcept = default;


        // =============================================
        // operators
        // =============================================

            /**
             * @brief Copy assignment operator
             * 
             * @param other: mass object to copy from as l-value const reference
             * 
             * @return constexpr mass& 
             */
            constexpr mass& operator=(const mass& other) noexcept {

                if (*this != other) {

                    mass_ = other.mass_; 
                    position_ = other.position_;
                    lin_velocity_ = other.lin_velocity_;
                    lin_acceleration_ = other.lin_acceleration_;

                }

                return *this;

            }


            /**
             * @brief Move assignment operator
             * 
             * @param other: mass object to move from as r-value reference
             * 
             * @return constexpr mass& 
             */
            constexpr mass& operator=(mass&& other) noexcept {

                if (!(*this == other)) {

                    mass_ = std::move(other.mass_); 
                    position_ = std::move(other.position_);
                    lin_velocity_ = std::move(other.lin_velocity_);
                    lin_acceleration_ = std::move(other.lin_acceleration_);

                }

                return *this;

            }


            /**
             * @brief Equality operator
             * 
             * @param other: mass object to compare with as l-value const reference
             * 
             * @return bool
             */
            constexpr bool operator==(const mass& other) const noexcept {

                return (mass_ == other.mass_ &&
                        position_ == other.position_ && 
                        lin_velocity_ == other.lin_velocity_ && 
                        lin_acceleration_ == other.lin_acceleration_);

            }


            /**
             * @brief Inequality operator
             * 
             * @param other: mass object to !compare with as l-value const reference
             * 
             * @return bool
             */
            constexpr bool operator!=(const mass& other) const noexcept {

                return !(*this == other);

            }


        // =============================================
        // get methods
        // =============================================

            /**
             * @brief Get the mass measurement 
             * 
             * @return constexpr mass_measurement 
             */
            constexpr mass_m as_mass_measurement() const noexcept { 
                
                return mass_; 
                
            }


            /**
             * @brief Get the mass measurement
             * 
             * @return constexpr measurement& 
             */
            constexpr mass_m& as_mass_measurement() noexcept {

                return mass_; 

            }


            /**
             * @brief Get the position vector 
             * 
             * @return constexpr position<DIM> 
             */
            constexpr position<DIM> as_position() const noexcept { 
                
                return position_; 
            
            }


            /**
             * @brief Get the position vector
             * 
             * @return constexpr position<DIM>& 
             */
            constexpr position<DIM>& as_position() noexcept { 
                
                return position_; 
            
            }


            /**
             * @brief Get the linear velocity vector 
             * 
             * @return constexpr lin_velocity<DIM> 
             */
            constexpr lin_velocity<DIM> as_lin_velocity() const noexcept { 
                
                return lin_velocity_; 
            
            }


            /**
             * @brief Get the linear velocity vector
             * 
             * @return constexpr lin_velocity<DIM>& 
             */
            constexpr lin_velocity<DIM>& as_lin_velocity() noexcept { 
                
                return lin_velocity_; 
            
            }


            /**
             * @brief Get the linear acceleration vector 
             * 
             * @return constexpr lin_acceleration<DIM> 
             */
            constexpr lin_acceleration<DIM> as_lin_acceleration() const noexcept { 
                
                return lin_acceleration_; 
            
            }


            /**
             * @brief Get the linear acceleration vector
             * 
             * @return constexpr lin_acceleration<DIM>& 
             */
            constexpr lin_acceleration<DIM>& as_lin_acceleration() noexcept { 
                
                return lin_acceleration_; 
            
            }

      
            /**
             * @brief Get the dimesion of the space
             * 
             * @return constexpr size_t 
             */
            constexpr size_t dim() const noexcept {

                return DIM; 

            }


            /**
             * @brief Get the mass object
             * 
             * @return constexpr object<DIM> 
             */
            constexpr mass<DIM> as_mass_object() const noexcept { 
                
                return *this; 
                
            }


            /**
             * @brief Get the mass object
             * 
             * @return constexpr object<DIM>& 
             */
            constexpr mass<DIM>& as_mass_object() noexcept { 
                
                return *this; 
                
            }


            // /**
            //  * @brief Get the matrix of the state (position, lin_velocity)
            //  * 
            //  * @return constexpr matrix<DIM, 2> 
            //  */
            // constexpr matrix<DIM, 2> state() const noexcept {

            //     return matrix<DIM, 2>(position_, lin_velocity_);

            // }


            // /**
            //  * @brief Set the matrix of the state (position, lin_velocity)
            //  * 
            //  * @param new_state matrix<DIM, 2> 
            //  * 
            //  * @return void
            //  */
            // constexpr void set_state(const matrix<DIM, 2>& new_state) noexcept {

            //     position_ = new_state[0]; 
            //     lin_velocity_ = new_state[1]; 

            // }


            /**
             * @brief Get the momentum vector
             * 
             * @return constexpr vector<DIM> 
             */
            constexpr momentum<DIM> as_momentum() const { 
                
                return mass_ * lin_velocity_;
                
            }


            /**
             * @brief Get the angular momentum vector
             * 
             * @return constexpr vector<DIM> 
             */
            constexpr angular_momentum<DIM> as_angular_momentum() const { 
                
                return mass_ * cross(position_, lin_velocity_); 
                
            }


            /**
             * @brief Get the kinetic energy
             * 
             * @return constexpr energy_m 
             */
            constexpr energy_m kinetic_energy() const { 
                
                return 0.5 * mass_ * lin_velocity_.norm2(); 
                
            }


            constexpr void gravitate(const mass<DIM>& other) noexcept {

                if (other.position_ != this->position_)
                    lin_acceleration_ = - constants::G * other.mass_ * (position_ - other.position_).normalize() / (position_ - other.position_).norm2();

                else 
                    lin_acceleration_ = lin_acceleration<DIM>();

            }


            /// @brief Print the mass object to the standard output
            constexpr void print() const noexcept {

                std::cout << "\nmass = " << mass_ << '\n'; 
                position_.print(); 
                lin_velocity_.print(); 
                lin_acceleration_.print();

            }               


        protected: 

            mass_m mass_; ///< mass measurement

            position<DIM> position_; ///< position of the mass object

            lin_velocity<DIM> lin_velocity_; ///< linear velocity of the mass object

            lin_acceleration<DIM> lin_acceleration_; ///< linear acceleration of the mass object


            friend class system; 
            

    }; // class mass


} // namespace scipp::physics {