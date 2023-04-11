/**
 * @file mass.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2022-12-21
 * 
 * @copyright Copyright (c) 2023
 */



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
             * @param m: mass_measurement of mass
             * @param pos: position<DIM> vector
             * @param vel: linear_velocity vector
             * @param acc: linear_acceleration vector
             * 
             */
            explicit constexpr mass(const mass_measurement& m, 
                                    const position<DIM>& pos = position<DIM>(), 
                                    const linear_velocity<DIM>& vel = linear_velocity<DIM>(), 
                                    const linear_acceleration<DIM>& acc = linear_acceleration<DIM>()) noexcept : 

                mass_(m),
                position_(pos),
                linear_velocity_(vel), 
                linear_acceleration_(acc) {}


            /**
             * @brief Copy construct a new mass object
             * 
             * @param other: mass object to copy from as l-result const reference
             */
            constexpr mass(const mass& other) noexcept : 
            
                mass_(other.mass_),
                position_(other.position_), 
                linear_velocity_(other.linear_velocity_), 
                linear_acceleration_(other.linear_acceleration_) {} 


            /**
             * @brief Move construct a new mass object
             * 
             * @param other: mass object to move from as r-value reference
             */
            constexpr mass(mass&& other) noexcept : 
            
                mass_(std::move(other.mass_)),
                position_(std::move(other.position_)), 
                linear_velocity_(std::move(other.linear_velocity_)), 
                linear_acceleration_(std::move(other.linear_acceleration_)) {} 


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
                    linear_velocity_ = other.linear_velocity_;
                    linear_acceleration_ = other.linear_acceleration_;

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
                    linear_velocity_ = std::move(other.linear_velocity_);
                    linear_acceleration_ = std::move(other.linear_acceleration_);

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
                        linear_velocity_ == other.linear_velocity_ && 
                        linear_acceleration_ == other.linear_acceleration_);

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
            constexpr mass_measurement as_mass_measurement() const noexcept { 
                
                return mass_; 
                
            }


            /**
             * @brief Get the mass measurement
             * 
             * @return constexpr measurement& 
             */
            constexpr measurement& as_mass_measurement() noexcept {

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
             * @return constexpr linear_velocity<DIM> 
             */
            constexpr linear_velocity<DIM> as_linear_velocity() const noexcept { 
                
                return linear_velocity_; 
            
            }


            /**
             * @brief Get the linear velocity vector
             * 
             * @return constexpr linear_velocity<DIM>& 
             */
            constexpr linear_velocity<DIM>& as_linear_velocity() noexcept { 
                
                return linear_velocity_; 
            
            }


            /**
             * @brief Get the linear acceleration vector 
             * 
             * @return constexpr linear_acceleration<DIM> 
             */
            constexpr linear_acceleration<DIM> as_linear_acceleration() const noexcept { 
                
                return linear_acceleration_; 
            
            }


            /**
             * @brief Get the linear acceleration vector
             * 
             * @return constexpr linear_acceleration<DIM>& 
             */
            constexpr linear_acceleration<DIM>& as_linear_acceleration() noexcept { 
                
                return linear_acceleration_; 
            
            }

      
            /**
             * @brief Get the dimesion of the space
             * 
             * @return constexpr size_t 
             */
            static constexpr size_t dim() {

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


            /**
             * @brief Get the matrix of the state (position, linear_velocity)
             * 
             * @return constexpr matrix<DIM, 2> 
             */
            constexpr matrix<DIM, 2> state() const noexcept {

                return matrix<DIM, 2>(position_, linear_velocity_);

            }


            /**
             * @brief Set the matrix of the state (position, linear_velocity)
             * 
             * @param new_state matrix<DIM, 2> 
             * 
             * @return void
             */
            constexpr void set_state(const matrix<DIM, 2>& new_state) noexcept {

                position_ = new_state[0]; 
                linear_velocity_ = new_state[1]; 

            }


            /**
             * @brief Get the momentum vector
             * 
             * @return constexpr vector<DIM> 
             */
            constexpr vector<DIM> momentum() const { 
                
                return mass_ * linear_velocity_;
                
            }


            /**
             * @brief Get the angular momentum vector
             * 
             * @return constexpr vector<DIM> 
             */
            constexpr vector<DIM> angular_momentum() const { 
                
                return mass_ * cross(position_, linear_velocity_); 
                
            }


            /**
             * @brief Get the kinetic energy
             * 
             * @return constexpr measurement 
             */
            constexpr measurement kinetic_energy() const { 
                
                return 0.5 * mass_ * linear_velocity_.norm2(); 
                
            }


            constexpr void gravitate(const mass<DIM>& other) noexcept {

                if (other.position_ != this->position_)
                    linear_acceleration_ = - constants::G * other.mass_ * (position_ - other.position_).normalize() / (position_ - other.position_).norm2();

                else 
                    linear_acceleration_ = linear_acceleration<DIM>();

            }


            /// @brief Print the mass object to the standard output
            constexpr void print() const noexcept {

                std::cout << "\nmass = " << mass_ << '\n'; 
                position_.print(); 
                linear_velocity_.print(); 
                linear_acceleration_.print();

            }               


        protected: 

            mass_measurement mass_; ///< mass measurement

            position<DIM> position_; ///< position of the mass object

            linear_velocity<DIM> linear_velocity_; ///< linear velocity of the mass object

            linear_acceleration<DIM> linear_acceleration_; ///< linear acceleration of the mass object


            friend class system; 
            

    }; // class mass


} // namespace scipp::physics {