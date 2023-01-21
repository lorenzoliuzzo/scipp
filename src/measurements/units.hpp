/**
 * @file    units.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the definition and implementation of the units namespace 
 *          with the unit_base class, the unit class
 * @date    2023-01-18
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief measurements namespace contains all the classes and functions of the measurements library
namespace scipp::measurements {

    
    /// @brief units namespace contains all the units of the measurements library
    namespace units {

        
        /// @brief bitwidth namespace contains the bitwidth of the powers of the unit_base struct
        namespace bitwidth {


            constexpr uint32_t base_size{sizeof(uint32_t) == 8 ? 8 : 4}; ///< exponent bitwidth
                
            constexpr uint32_t metre{(base_size == 8) ? 8 : 4}; ///< metre exponent bitwidth
                
            constexpr uint32_t second{(base_size == 8) ? 8 : 4}; ///< second exponent bitwidth
                
            constexpr uint32_t kilogram{(base_size == 8) ? 6 : 3}; ///< kilogram exponent bitwidth
                
            constexpr uint32_t ampere{(base_size == 8) ? 6 : 3}; ///< ampere exponent bitwidth
                
            constexpr uint32_t candela{(base_size == 8) ? 4 : 2}; ///< candela exponent bitwidth
                
            constexpr uint32_t kelvin{(base_size == 8) ? 6 : 3}; ///< kelvin exponent bitwidth
                
            constexpr uint32_t mole{(base_size == 8) ? 4 : 2}; ///< mole exponent bitwidth

            constexpr uint32_t radian{(base_size == 8) ? 6 : 3}; ///< radian exponent bitwidth


        } // namespace bitwidth


        /// @brief unit_base use an array of powers of the some unit_base to represent a base for a physical unit
        struct unit_base {


            // =============================================
            // constructors and destructor
            // =============================================  

                /**
                 * @brief Construct a new unit_base object with powers of the seven SI unit_bases
                 * 
                 * @note: The powers are all set to zero
                 */
                explicit consteval unit_base() noexcept :

                    metre_{0}, second_{0}, kilogram_{0}, ampere_{0}, 
                    kelvin_{0}, mole_{0}, candela_{0}, radian_{0} {}


                /**
                 * @brief Construct a new unit_base object with powers of the seven SI unit_bases
                 * 
                 * @param metres: int power of metre
                 * @param seconds: int power of second
                 * @param kilograms: int power of kilogram
                 * @param amperes: int power of ampere
                 * @param kelvins: int power of kelvin
                 * @param moles: int power of mole
                 * @param candelas: int power of candela
                 * @param radian: int power of radian
                 *
                 * @note: The powers of the seven SI unit_bases are stored as it is explained in the bitwidth namespace
                 */
                explicit constexpr unit_base(int metres, 
                                             int seconds, 
                                             int kilograms, 
                                             int amperes, 
                                             int kelvins,  
                                             int moles, 
                                             int candelas,
                                             int radian) noexcept : 
                        
                    metre_(metres), second_(seconds), kilogram_(kilograms), ampere_(amperes), 
                    kelvin_(kelvins), mole_(moles), candela_(candelas), radian_{radian} {}


                /**
                 * @brief Construct a new unit_base object from a string representation of the unit_base
                 * 
                 * @param unit_string: string as l-value const reference
                 */
                explicit constexpr unit_base(const std::string& unit_string) noexcept : 
                    
                    metre_{0}, second_{0}, kilogram_{0}, ampere_{0}, 
                    kelvin_{0}, mole_{0}, candela_{0}, radian_{0} {
                    
                    if (!unit_string.empty()) {

                        std::size_t finder = unit_string.find('m');
                        if (finder != std::string::npos) {

                            if (finder == unit_string.size() - 1 || unit_string.at(finder + 1) != '^') 
                                this->metre_ = 1; 
                            else {
                                if (unit_string.at(finder + 2) == '-') 
                                    this->metre_ -= std::stoi(unit_string.substr(finder + 3));
                                else 
                                    this->metre_ = std::stoi(unit_string.substr(finder + 2));
                            }
                            
                        }

                        finder = unit_string.find('s');
                        if (finder != std::string::npos) {

                            if (finder == unit_string.size() - 1 || unit_string.at(finder + 1) != '^') 
                                this->second_ = 1; 
                            else {
                                if (unit_string.at(finder + 2) == '-') 
                                    this->second_ -= std::stoi(unit_string.substr(finder + 3));
                                else 
                                    this->second_ = std::stoi(unit_string.substr(finder + 2));
                            }
                            
                        }

                        finder = unit_string.find("kg");
                        if (finder != std::string::npos) {

                            if (finder == unit_string.size() - 1 || unit_string.at(finder + 1) != '^') 
                                this->kilogram_ = 1; 
                            else {
                                if (unit_string.at(finder + 2) == '-') 
                                    this->kilogram_ -= std::stoi(unit_string.substr(finder + 3));
                                else 
                                    this->kilogram_ = std::stoi(unit_string.substr(finder + 2));
                            }

                        }

                        finder = unit_string.find('A');
                        if (finder != std::string::npos) {

                            if (finder == unit_string.size() - 1 || unit_string.at(finder + 1) != '^') 
                                this->ampere_ = 1; 
                            else {
                                if (unit_string.at(finder + 2) == '-') 
                                    this->ampere_ -= std::stoi(unit_string.substr(finder + 3));
                                else 
                                    this->ampere_ = std::stoi(unit_string.substr(finder + 2));
                            }                            
                        }

                        finder = unit_string.find('K');
                        if (finder != std::string::npos) {

                            if (finder == unit_string.size() - 1 || unit_string.at(finder + 1) != '^') 
                                this->kelvin_ = 1; 
                            else {
                                if (unit_string.at(finder + 2) == '-') 
                                    this->kelvin_ -= std::stoi(unit_string.substr(finder + 3));
                                else 
                                    this->kelvin_ = std::stoi(unit_string.substr(finder + 2));
                            }

                        }

                        finder = unit_string.find("mol");
                        if (finder != std::string::npos) {

                            if (finder == unit_string.size() - 1 || unit_string.at(finder + 1) != '^') 
                                this->mole_ = 1; 
                            else {
                                if (unit_string.at(finder + 2) == '-') 
                                    this->mole_ -= std::stoi(unit_string.substr(finder + 3));
                                else 
                                    this->mole_ = std::stoi(unit_string.substr(finder + 2));
                            }

                        }

                        finder = unit_string.find("cd");
                        if (finder != std::string::npos) {

                            if (finder == unit_string.size() - 1 || unit_string.at(finder + 1) != '^') 
                                this->candela_ = 1; 
                            else {
                                if (unit_string.at(finder + 2) == '-') 
                                    this->candela_ -= std::stoi(unit_string.substr(finder + 3));
                                else 
                                    this->candela_ = std::stoi(unit_string.substr(finder + 2));
                            }
                            
                        }

                        finder = unit_string.find("rad");
                        if (finder != std::string::npos) {

                            if (finder == unit_string.size() - 1 || unit_string.at(finder + 1) != '^') 
                                this->radian_ = 1; 
                            else {
                                if (unit_string.at(finder + 2) == '-') 
                                    this->radian_ -= std::stoi(unit_string.substr(finder + 3));
                                else 
                                    this->radian_ = std::stoi(unit_string.substr(finder + 2));
                            }
                            
                        }

                    } 

                }
                

                /**
                 * @brief Copy construct a new unit_base from an other unit_base object
                 * 
                 * @param other: unit_base as l-value const reference
                 */
                consteval unit_base(const unit_base& other) noexcept : 

                    metre_(other.metre_), second_(other.second_), kilogram_(other.kilogram_), ampere_(other.ampere_), 
                    kelvin_(other.kelvin_), mole_(other.mole_), candela_(other.candela_), radian_(other.radian_) {}


                /// @brief Default destructor
                ~unit_base() = default; 


            // =============================================
            // operators
            // ============================================= 

                /**
                 * @brief Copy assignment operator
                 * 
                 * @param other: unit_base as l-value const reference
                 * 
                 * @return consteval unit_base&
                 */
                consteval unit_base& operator=(const unit_base& other) noexcept {

                    if (*this != other) {

                        this->metre_ = other.metre_; 
                        this->second_ = other.second_; 
                        this->kilogram_ = other.kilogram_; 
                        this->ampere_ = other.ampere_; 
                        this->kelvin_ = other.kelvin_; 
                        this->mole_ = other.mole_; 
                        this->candela_ = other.candela_; 
                        this->radian_ = other.radian_; 

                    }

                    return *this; 

                }


                /**
                 * @brief Perform a multiplication by adding the powers together
                 * 
                 * @param other: unit_base object to multiply with as l-value const reference
                 * 
                 * @return constexpr unit_base 
                 */
                constexpr unit_base operator*(const unit_base& other) const noexcept {

                    return unit_base(this->metre_ + other.metre_, 
                                     this->second_ + other.second_, 
                                     this->kilogram_ + other.kilogram_, 
                                     this->ampere_ + other.ampere_, 
                                     this->kelvin_ + other.kelvin_, 
                                     this->mole_ + other.mole_, 
                                     this->candela_ + other.candela_, 
                                     this->radian_ + other.radian_); 

                }


                /**
                 * @brief Perform a division by subtracting the powers
                 * 
                 * @param other: unit_base object to divide with as l-value const reference
                 * 
                 * @return constexpr unit_base 
                 */
                constexpr unit_base operator/(const unit_base& other) const noexcept {
                
                    return unit_base(this->metre_ - other.metre_, 
                                     this->second_ - other.second_, 
                                     this->kilogram_ - other.kilogram_, 
                                     this->ampere_ - other.ampere_, 
                                     this->kelvin_ - other.kelvin_, 
                                     this->mole_ - other.mole_, 
                                     this->candela_ - other.candela_,
                                     this->radian_ - other.radian_); 

                }


                /**
                 * @brief Equality operator
                 * 
                 * @param other: unit_base object to compare with as l-value const reference
                 * 
                 * @return bool
                 */
                consteval bool operator==(const unit_base& other) const noexcept {
                
                    return this->metre_ == other.metre_ &&
                           this->second_ == other.second_ &&
                           this->kilogram_ == other.kilogram_ &&
                           this->ampere_ == other.ampere_ &&
                           this->candela_ == other.candela_ &&
                           this->kelvin_ == other.kelvin_ &&
                           this->mole_ == other.mole_ &&
                           this->radian_ == other.radian_; 

                }


                /**
                 * @brief Inequality operator
                 * 
                 * @param other: unit_base object to !compare with as l-value const reference
                 * 
                 * @return bool
                 */                    
                consteval bool operator!=(const unit_base& other) const noexcept { 
                    
                    return this->metre_ != other.metre_ ||
                           this->second_ != other.second_ ||
                           this->kilogram_ != other.kilogram_ ||
                           this->ampere_ != other.ampere_ ||
                           this->candela_ != other.candela_ ||
                           this->kelvin_ != other.kelvin_ ||
                           this->mole_ != other.mole_ ||
                           this->radian_ != other.radian_; 
                    
                }


                /**
                 * @brief Printing on video the unit_base litterals
                 * 
                 * @param os: std::ostream& 
                 * @param base: unit_base as l-value const reference
                 * 
                 * @return std::ostream&
                 */
                friend std::ostream& operator<<(std::ostream& os, const unit_base& base) noexcept {

                    os << base.to_string(); 

                    return os; 

                }


                /**
                 * @brief Printing on file the unit_base litterals
                 * 
                 * @param file: std::ofstream& 
                 * @param base: unit_base as l-value const reference
                 * 
                 * @return std::ofstream&
                 */
                friend std::ofstream& operator<<(std::ofstream& file, const unit_base& base) noexcept {

                    file << base.to_string(); 

                    return file; 

                }


            // =============================================
            // operations
            // ============================================= 

                /**
                 * @brief Invert the unit_base
                 * 
                 * @return constexpr unit_base
                 */
                consteval unit_base inv() const noexcept {
                
                    return unit_base(-this->metre_, 
                                     -this->second_, 
                                     -this->kilogram_, 
                                     -this->ampere_, 
                                     -this->kelvin_, 
                                     -this->mole_, 
                                     -this->candela_,
                                     -this->radian_);

                }


                /**
                 * @brief Take the power of the unit_base
                 * 
                 * @param power 
                 * 
                 * @return consteval unit_base 
                 */
                consteval unit_base pow(const int& power) const noexcept { 

                    return unit_base(this->metre_ * power, 
                                     this->second_ * power, 
                                     this->kilogram_ * power, 
                                     this->ampere_ * power, 
                                     this->kelvin_ * power, 
                                     this->mole_ * power, 
                                     this->candela_ * power,
                                     this->radian_ * power);

                }


                /**
                 * @brief Take the square unit_base
                 * 
                 * @return consteval unit_base 
                 */
                consteval unit_base square() const noexcept { 
                    
                    return unit_base(this->metre_ * 2, 
                                     this->second_ * 2, 
                                     this->kilogram_ * 2, 
                                     this->ampere_ * 2, 
                                     this->kelvin_ * 2, 
                                     this->mole_ * 2, 
                                     this->candela_ * 2,
                                     this->radian_ * 2);

                }


                /**
                 * @brief  Take the cube unit_base
                 * 
                 * @return consteval unit_base 
                 */
                consteval unit_base cube() const noexcept { 
                    
                    return unit_base(this->metre_ * 3, 
                                     this->second_ * 3, 
                                     this->kilogram_ * 3, 
                                     this->ampere_ * 3, 
                                     this->kelvin_ * 3, 
                                     this->mole_ * 3, 
                                     this->candela_ * 3,
                                     this->radian_ * 3);

                }


                /**
                 * @brief Take the root of the unit_base
                 * 
                 * @param power 
                 * 
                 * @return unit_base 
                 */
                consteval unit_base root(const int& power) const noexcept {

                    if (this->has_valid_root(power)) 
                        return unit_base(this->metre_ / power,
                                         this->second_ / power,
                                         this->kilogram_ / power,
                                         this->ampere_ / power,
                                         this->kelvin_ / power,
                                         this->mole_ / power,
                                         this->candela_ / power, 
                                         this->radian_ / power);

                }


                /**
                 * @brief Take the square root of the unit_base
                 * 
                 * @return unit_base 
                 */
                consteval unit_base sqrt() const noexcept { 
                    
                    if (this->has_valid_root(2)) 
                        return unit_base(this->metre_ / 2,
                                         this->second_ / 2,
                                         this->kilogram_ / 2,
                                         this->ampere_ / 2,
                                         this->kelvin_ / 2,
                                         this->mole_ / 2,
                                         this->candela_ / 2, 
                                         this->radian_ / 2);

                }


                /**
                 * @brief Take the cubic root of the unit_base
                 * 
                 * @return unit_base 
                 */
                consteval unit_base cbrt() const noexcept { 
                    
                    if (this->has_valid_root(3)) 
                        return unit_base(this->metre_ / 3,
                                         this->second_ / 3,
                                         this->kilogram_ / 3,
                                         this->ampere_ / 3,
                                         this->kelvin_ / 3,
                                         this->mole_ / 3,
                                         this->candela_ / 3, 
                                         this->radian_ / 3);

                }


            // =============================================
            // get methods
            // =============================================

                /**
                 * @brief Check if the unit_base has a valid root
                 * 
                 * @param power: int as l-value const reference
                 * 
                 * @return bool 
                 */
                constexpr bool has_valid_root(const int& power) const noexcept {
                
                    return (this->metre_ % power == 0) &&
                           (this->second_ % power == 0) &&
                           (this->kilogram_ % power == 0) &&
                           (this->ampere_ % power == 0) &&
                           (this->candela_ % power == 0) &&
                           (this->kelvin_ % power == 0) &&
                           (this->mole_ % power == 0) &&
                           (this->radian_ % power == 0); 

                }      


                /**
                 * @brief Get the unit_base litterals to string
                 * 
                 * @return std::string 
                 */
                std::string to_string() const noexcept {
                    
                    std::string unit_base_string;   
                    
                    if (this->metre_ == 1) 
                        unit_base_string.append("m");
                    else if (this->metre_ != 0) 
                        unit_base_string.append("m^" + std::to_string(metre_)); 

                    if (this->second_ == 1) 
                        unit_base_string.append("s"); 
                    else if (this->second_ != 0) 
                        unit_base_string.append("s^" + std::to_string(second_)); 

                    if (this->kilogram_ == 1) 
                        unit_base_string.append("kg"); 
                    else if (this->kilogram_ != 0)    
                        unit_base_string.append("kg^" + std::to_string(kilogram_)); 

                    if (this->ampere_ == 1) 
                        unit_base_string.append("A"); 
                    else if (this->ampere_ != 0)  
                        unit_base_string.append("A^" + std::to_string(ampere_)); 

                    if (this->kelvin_ == 1) 
                        unit_base_string.append("K");
                    else if (this->kelvin_ != 0) 
                        unit_base_string.append("K^" + std::to_string(kelvin_)); 

                    if (this->mole_ == 1) 
                        unit_base_string.append("mol"); 
                    else if (this->mole_ != 0) 
                        unit_base_string.append("mol^" + std::to_string(mole_)); 

                    if (this->candela_ == 1) 
                        unit_base_string.append("cd"); 
                    else if (this->candela_ != 0) 
                        unit_base_string.append("cd^" + std::to_string(candela_)); 

                    if (this->radian_ == 1) 
                        unit_base_string.append("rad"); 
                    else if (this->radian_ != 0) 
                        unit_base_string.append("rad^" + std::to_string(radian_)); 
                    
                    return unit_base_string; 
                
                }


            // =============================================
            // struct members & friends
            // =============================================

                signed int metre_    : bitwidth::metre;    ///< Metre exponent
                
                signed int second_   : bitwidth::second;   ///< Second exponent
                
                signed int kilogram_ : bitwidth::kilogram; ///< Kilogram exponent
                
                signed int ampere_   : bitwidth::ampere;   ///< Ampere exponent
                
                signed int kelvin_   : bitwidth::kelvin;   ///< Kelvin exponent
                
                signed int mole_     : bitwidth::mole;     ///< Mole exponent
                
                signed int candela_  : bitwidth::candela;  ///< Candela exponent

                signed int radian_  : bitwidth::radian;  ///< Radian exponent

            
        }; // struct unit_base


        /// @brief Namespace with the SI unit bases
        namespace basis {


            constexpr unit_base scalar(0, 0, 0, 0, 0, 0, 0, 0); //< scalar unit_base

            constexpr unit_base metre(1, 0, 0, 0, 0, 0, 0, 0); //< metre unit_base
            
            constexpr unit_base second(0, 1, 0, 0, 0, 0, 0, 0); //< second unit_base
            
            constexpr unit_base kilogram(0, 0, 1, 0, 0, 0, 0, 0); //< kilogram unit_base
            
            constexpr unit_base Ampere(0, 0, 0, 1, 0, 0, 0, 0); //< Ampere unit_base
            
            constexpr unit_base Kelvin(0, 0, 0, 0, 1, 0, 0, 0); //< Kelvin unit_base
            
            constexpr unit_base mole(0, 0, 0, 0, 0, 1, 0, 0); //< mole unit_base
            
            constexpr unit_base candela(0, 0, 0, 0, 0, 0, 1, 0); //< candela unit_base

            constexpr unit_base radian(0, 0, 0, 0, 0, 0, 0, 1); //< radian unit_base
        

        } // namespace basis


        /// @brief Namespace containg the SI prefixes
        namespace prefixes {


            constexpr scalar yocto{1.e-24}; //< yocto prefix

            constexpr scalar zepto{1.e-21}; //< zepto prefix

            constexpr scalar atto{1.e-18}; //< atto prefix

            constexpr scalar femto{1.e-15}; //< femto prefix

            constexpr scalar pico{1.e-12}; //< pico prefix

            constexpr scalar nano{1.e-9}; //< nano prefix

            constexpr scalar micro{1.e-6}; //< micro prefix

            constexpr scalar milli{1.e-3}; //< milli prefix

            constexpr scalar centi{1.e-2}; //< centi prefix

            constexpr scalar deci{1.e-1}; //< deci prefix

            constexpr scalar hecto{1.e2}; //< hecto prefix

            constexpr scalar kilo{1.e3}; //< kilo prefix

            constexpr scalar mega{1.e6}; //< mega prefix

            constexpr scalar giga{1.e9}; //< giga prefix
    
            constexpr scalar tera{1.e12}; //< tera prefix

            constexpr scalar peta{1.e15}; //< peta prefix

            constexpr scalar exa{1.e18}; //< exa prefix

            constexpr scalar zetta{1.e21}; //< zetta prefix

            constexpr scalar yotta{1.e24}; //< yotta prefix


            std::map<scalar, char> map = {

                {yocto, 'y'},
                {zepto, 'z'},
                {atto, 'a'},
                {femto, 'f'},
                {pico, 'p'},
                {nano, 'n'},
                {micro, 'u'},
                {milli, 'm'},
                {centi, 'c'},
                {deci, 'd'},
                {hecto, 'h'},
                {kilo, 'k'},
                {mega, 'M'},
                {giga, 'G'},
                {tera, 'T'},
                {peta, 'P'},
                {exa, 'E'},
                {zetta, 'Z'},
                {yotta, 'Y'}

            }; //< Map with the SI prefixes and their corresponding symbols


        } // namespace prefix


        /** 
         * @brief Struct represents an unit of measurement as an union of an unit_base and a scalar prefix
         * @tparam UB: unit_base of the unit
         */
        template <unit_base UB> 
        class unit {


            public: 

                /// @brief Construct a new default unit object
                consteval unit() noexcept : 

                    prefix_{1.} {}


                /**
                 * @brief Construct a new unit object from a scalar prefix 
                 * 
                 * @param prefix: scalar as l-value const reference
                 */
                consteval unit(const scalar& prefix) noexcept : 

                    prefix_{prefix} {}


                /**
                 * @brief Construct a new unit object from a scalar prefix 
                 * 
                 * @param prefix: scalar as r-value reference
                 */
                consteval unit(scalar&& prefix) noexcept : 

                    prefix_{std::move(prefix)} {}


                /**
                 * @brief Copy construct a new unit from another unit object
                 * 
                 * @param other: unit object as l-value const reference
                 */
                consteval unit(const unit& other) noexcept : 

                    prefix_(other.prefix_) {}


                /**
                 * @brief Move construct a new unit from another unit object
                 * 
                 * @param other: unit object as r-value reference
                 */
                consteval unit(unit&& other) noexcept : 

                    prefix_(std::move(other.prefix_)) {}


                /// @brief Default destructor
                ~unit() noexcept = default; 


            // =============================================
            // operators
            // ============================================= 

                /**
                 * @brief Copy assignment operator
                 * 
                 * @param other: unit as l-value const reference
                 * 
                 * @return consteval unit&
                 */
                consteval unit& operator=(const unit& other) noexcept {

                    this->prefix_ = other.prefix_;
 
                    return *this;

                }


                /**
                 * @brief Move assignment operator
                 * 
                 * @param other: unit as r-value reference
                 * 
                 * @return consteval unit& 
                 */
                consteval unit& operator=(unit&& other) noexcept {

                    this->prefix_ = std::move(other.prefix_);

                    return *this;

                }


                /**
                 * @brief Perform a multiplication by multiply the bases and the prefixes
                 * 
                 * @param other: unit as l-value const reference
                 *                      
                 * @return consteval unit
                 */
                template <unit_base UB2>
                consteval unit<UB * UB2> operator*(const unit<UB2>& other) const noexcept { 
                    
                    return { this->prefix_ * other.prefix() }; 
                    
                }


                /**
                 * @brief Perform a multiplication by multiply the bases and the prefixes
                 * 
                 * @param other: unit as r-value reference
                 *                      
                 * @return consteval unit
                 */
                template <unit_base UB2>
                consteval unit<UB * UB2> operator*(unit<UB2>&& other) const noexcept { 
                    
                    return { this->prefix_ * other.prefix() }; 
                    
                }


                /**
                 * @brief Perform a division by divide the bases and the prefixes
                 * 
                 * @param other: unit as l-value const reference
                 *                      
                 * @return consteval unit
                 */
                template <unit_base UB2>
                consteval unit<UB / UB2> operator/(const unit<UB2>& other) const noexcept { 
                    
                    return { this->prefix_ / other.prefix() }; 
                    
                }                


                /**
                 * @brief Perform a division by divide the bases and the prefixes
                 * 
                 * @param other: unit as r-value reference
                 *                      
                 * @return consteval unit
                 */
                template <unit_base UB2>
                consteval unit<UB / UB2> operator/(unit<UB2>&& other) const noexcept { 
                    
                    return { this->prefix_ / other.prefix() }; 
                    
                }          


                /**
                 * @brief Equality operator
                 * 
                 * @param other: unit as l-value const reference
                 * 
                 * @return consteval bool 
                 */
                consteval bool operator==(const unit& other) const noexcept {

                    return this->prefix_ == other.prefix_;

                }


                /**
                 * @brief Inequality operator
                 * 
                 * @param other: unit as l-value const reference
                 * 
                 * @return consteval bool 
                 */
                consteval bool operator!=(const unit& other) const noexcept { 

                    return this->prefix_ != other.prefix_;

                }


            // =============================================
            // operations
            // ============================================= 

                /**
                 * @brief Invert the unit
                 * 
                 * @return consteval unit   
                 */
                consteval unit<UB.inv()> inv() const noexcept { 
                    
                    return { 1. / this->prefix_ }; 
                    
                }


                /**
                 * @brief Take the power of the unit
                 * 
                 * @param power
                 * 
                 * @return consteval unit 
                 */
                consteval auto pow(const int& power) const noexcept { 
                    
                    return { UB.pow(power), std::pow(this->prefix_, power) }; 
                    
                }


                /**
                 * @brief Take the square of the unit
                 * 
                 * @return consteval unit 
                 */
                consteval unit<UB.square()> square() const noexcept { 
                    
                    return { std::pow(this->prefix_, 2) }; 
                    
                }


                /**
                 * @brief Take the cube of the unit
                 * 
                 * @return consteval unit 
                 */
                consteval unit<UB.cube()> cube() const noexcept { 
                    
                    return { std::pow(this->prefix_, 3) }; 
                    
                }


                /**
                 * @brief Take the root of the unit
                 * 
                 * @param power
                 * 
                 * @return consteval unit 
                 */
                consteval auto root(const int& power) const { 
                    
                    return { UB.pow(1. / power), std::pow(this->prefix_, 1. / power) }; 

                }


                /**
                 * @brief Take the square root of the unit
                 * 
                 * @return consteval unit 
                 */
                consteval auto sqrt() const { 
                    
                    return { UB.sqrt(), std::sqrt(this->prefix_) }; 
                    
                }


                /**
                 * @brief Take the cube root of the unit
                 * 
                 * @return consteval unit 
                 */
                consteval auto cbrt() const { 
                    
                    return { UB.cbrt(), std::cbrt(this->prefix_) }; 

                }
                    

            // =============================================
            // setters & getters
            // ============================================= 

                /**
                 * @brief Check if the unit is a base unit or it's prefixed
                 * 
                 * @return constexpr bool 
                 */
                constexpr bool is_prefixed() const noexcept { 
                    
                    return this->prefix_ != 1.;

                }


                /**
                 * @brief Convert a value from the base unit to this unit
                 * 
                 * @param value: scalar as l-value const reference
                 * 
                 * @return constexpr scalar&
                 */
                constexpr scalar convert(const scalar& value) const noexcept { 
                    
                    return value / this->prefix_;
                
                }


                /**
                 * @brief Convert a value from the base unit to this unit
                 * 
                 * @param value: scalar as r-value reference
                 * 
                 * @return consteval scalar 
                 */
                constexpr scalar convert(scalar&& value) noexcept { 
                    
                    return value / this->prefix_;
                
                }


                /**
                 * @brief Convert a value in the current unit to the target unit 
                 * 
                 * @param value: value to convert 
                 * @param units: desired unit unit
                 * 
                 * @return constexpr scalar 
                 * @note the units will only convert if they have the same base unit
                 */
                constexpr scalar convert(const scalar& value, const unit& units) const noexcept { 
                    
                    return value * this->prefix_ / units.prefix();
                
                }


                /**
                 * @brief Convert a value in the current unit to the target unit 
                 * 
                 * @param value: value to convert 
                 * @param units: desired unit unit
                 * 
                 * @return constexpr scalar 
                 * @note the units will only convert if they have the same base unit
                 */
                constexpr scalar convert(scalar&& value, const unit& units) const noexcept { 
                    
                    return value * this->prefix_ / units.prefix();
                
                }


                /**
                * @brief Generate a conversion factor between this unit and another unit 
                * 
                * @param result: desired unit
                * 
                * @return constexpr scalar 
                * @note the units will only convert if they have the same base unit
                */
                consteval scalar convertion_factor(const unit& other) const noexcept { 
                    
                    return this->prefix_ / other.prefix_;
                }


                /**
                 * @brief Get the unit prefix object
                 * 
                 * @return constexpr unit_prefix 
                 */
                constexpr scalar prefix() const noexcept {

                    return prefix_; 

                }


                /**
                 * @brief Get the unit base object
                 * 
                 * @return consteval unit_base& 
                 */
                consteval unit_base base() const noexcept {

                    return UB; 

                }


                /**
                 * @brief Get the unit object
                 * 
                 * @return constexpr unit
                 */
                constexpr const unit& units() const noexcept { 
                    
                    return *this; 
                    
                }


                /**
                 * @brief Get the unit object
                 * 
                 * @return constexpr unit& 
                 */
                constexpr unit& units() noexcept { 
                    
                    return *this; 
                    
                }


                // /**
                //  * @brief Get the unit string
                //  * 
                //  * @return std::string 
                //  */
                // constexpr std::string to_string() const noexcept { 

                //     // std::string unit_string{this->prefix_.to_string()}; 
                //     // unit_string += ; 

                //     return UB.to_string(); 

                // }


                /// @brief Print the unit to the standard output
                constexpr void print() const noexcept {

                    std::cout << UB;

                }

            
            protected:

                scalar prefix_; ///< unit prefix


        }; // class unit
         

        /// @brief Namespace units type aliases
        namespace types {


            using scalar_unit = unit<basis::scalar>;
            using length_unit = unit<basis::metre>; 
            using time_unit = unit<basis::second>; 
            using mass_unit = unit<basis::kilogram>; 
            using temperature_unit = unit<basis::Kelvin>; 
            using mole_unit = unit<basis::mole>; 
            using angle_unit = unit<basis::radian>; 
            using current_unit = unit<basis::Ampere>;
            using luminous_intensity_unit = unit<basis::candela>;
            using mole_unit = unit<basis::mole>;


            // unitless 
            constexpr unit<basis::scalar> unitless;
            constexpr unit<basis::radian> rad;

            // SI units
            constexpr unit<basis::metre> m;
            constexpr unit<basis::second> s;
            constexpr unit<basis::kilogram> kg;
            constexpr unit<basis::Kelvin> K;
            constexpr unit<basis::Ampere> A;
            constexpr unit<basis::mole> mol;
            constexpr unit<basis::candela> cd;

            // // length units
            constexpr length_unit ym(prefixes::yocto);
            constexpr length_unit zm(prefixes::zepto);
            constexpr length_unit am(prefixes::atto);
            constexpr length_unit fm(prefixes::femto);
            constexpr length_unit pm(prefixes::pico);
            constexpr length_unit nm(prefixes::nano);
            constexpr length_unit um(prefixes::micro);
            constexpr length_unit mm(prefixes::milli);
            constexpr length_unit cm(prefixes::centi);
            constexpr length_unit dm(prefixes::deci);
            constexpr length_unit hm(prefixes::hecto);
            constexpr length_unit km(prefixes::kilo);
            constexpr length_unit Mm(prefixes::mega);
            constexpr length_unit Gm(prefixes::giga);
            constexpr length_unit Tm(prefixes::tera);
            constexpr length_unit Pm(prefixes::peta);
            constexpr length_unit Em(prefixes::exa);

            // // time units
            constexpr time_unit ys(prefixes::yocto);
            constexpr time_unit zs(prefixes::zepto);
            constexpr time_unit as(prefixes::atto);
            constexpr time_unit fs(prefixes::femto);
            constexpr time_unit ps(prefixes::pico);
            constexpr time_unit ns(prefixes::nano);
            constexpr time_unit us(prefixes::micro);
            constexpr time_unit ms(prefixes::milli);
            constexpr time_unit cs(prefixes::centi);
            constexpr time_unit ds(prefixes::deci);
            constexpr time_unit hs(prefixes::hecto);
            constexpr time_unit ks(prefixes::kilo);
            constexpr time_unit Ms(prefixes::mega);
            constexpr time_unit Gs(prefixes::giga);
            constexpr time_unit Ts(prefixes::tera);
            constexpr time_unit Ps(prefixes::peta);
            constexpr time_unit Es(prefixes::exa);

            // constexpr unit<basis::metre / basis::second> m_s;
            // constexpr unit<basis::metre / basis::second> km_s(prefixes::kilo);
            // constexpr unit<basis::metre / basis::second.square()> m_ss;


            // // composed units
            constexpr unit<basis::second.inv()> hertz;
            constexpr unit Hz = hertz;

            constexpr unit<basis::second.inv()> MHz(prefixes::mega); 
            constexpr unit<basis::second.inv()> GHz(prefixes::giga); 
                            
            constexpr unit<unit_base(2, -3, 1, -1, 0, 0, 0, 0)> volt;
            constexpr unit V = volt;

            constexpr unit<unit_base(1, -2, 1, 0, 0, 0, 0, 0)> newton;
            constexpr unit N = newton;

            constexpr unit<unit_base(-1, -2, 1, 0, 0, 0, 0, 0)> Pa;
            constexpr unit pascal = Pa;

            constexpr unit<unit_base(2, -2, 1, 0, 0, 0, 0, 0)> joule;
            constexpr unit J = joule;

            constexpr unit<unit_base(2, -3, 1, 0, 0, 0, 0, 0)> watt;
            constexpr unit W = watt;

            constexpr unit<unit_base(0, 1, 0, 1, 0, 0, 0, 0)> coulomb;
            constexpr unit C = coulomb;

            constexpr unit<unit_base(-2, 4, -1, 2, 0, 0, 0, 0)> farad;
            constexpr unit F = farad;

            constexpr unit<unit_base(2, -2, 1, -1, 0, 0, 0, 0)> weber;
            constexpr unit Wb = weber;

            constexpr unit<unit_base(0, -2, 1, -1, 0, 0, 0, 0)> tesla;
            constexpr unit T = tesla;

            constexpr unit<unit_base(2, -2, 1, -2, 0, 0, 0, 0)> henry;                    
            constexpr unit H = henry;


        }; // namespace types

        
        using namespace types; 


    } // namespace units


    using namespace units; 

    
} // namespace scipp::measurements