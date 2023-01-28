/**
 * @file    unit_base.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-21
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
                    
                    if (this->metre_ != 0) {
                        if (this->metre_ == 1) 
                            unit_base_string.append("m");
                        else 
                            unit_base_string.append("m^" + std::to_string(metre_)); 
                    }

                    if (this->second_ != 0) {
                        if (this->second_ == 1) 
                            unit_base_string.append("s"); 
                        else 
                            unit_base_string.append("s^" + std::to_string(second_)); 
                    }

                    if (this->kilogram_ != 0) { 
                        if (this->kilogram_ == 1) 
                            unit_base_string.append("kg"); 
                        else 
                            unit_base_string.append("kg^" + std::to_string(kilogram_)); 
                    }

                    if (this->ampere_ != 0) {
                        if (this->ampere_ == 1) 
                            unit_base_string.append("A"); 
                        else 
                            unit_base_string.append("A^" + std::to_string(ampere_)); 
                    }

                    if (this->kelvin_ != 0) {
                        if (this->kelvin_ == 1) 
                            unit_base_string.append("K");
                        else 
                            unit_base_string.append("K^" + std::to_string(kelvin_)); 
                    }

                    if (this->mole_ != 0) {
                        if (this->mole_ == 1) 
                            unit_base_string.append("mol"); 
                        else 
                            unit_base_string.append("mol^" + std::to_string(mole_)); 
                    }

                    if (this->candela_ != 0) {
                        if (this->candela_ == 1) 
                            unit_base_string.append("cd"); 
                        else 
                            unit_base_string.append("cd^" + std::to_string(candela_)); 
                    }

                    if (this->radian_ != 0) {
                        if (this->radian_ == 1) 
                            unit_base_string.append("rad"); 
                        else 
                            unit_base_string.append("rad^" + std::to_string(radian_)); 
                    
                    }

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
        

            constexpr unit_base metre2(2, 0, 0, 0, 0, 0, 0, 0); //< metre2 unit_base
            
            constexpr unit_base second2(0, 2, 0, 0, 0, 0, 0, 0); //< second2 unit_base
            
            constexpr unit_base kilogram2(0, 0, 2, 0, 0, 0, 0, 0); //< kilogram2 unit_base
            
            constexpr unit_base Ampere2(0, 0, 0, 2, 0, 0, 0, 0); //< Ampere2 unit_base
            
            constexpr unit_base Kelvin2(0, 0, 0, 0, 2, 0, 0, 0); //< Kelvin2 unit_base
            

            constexpr unit_base metre3(3, 0, 0, 0, 0, 0, 0, 0); //< metre3 unit_base
            
            constexpr unit_base second3(0, 3, 0, 0, 0, 0, 0, 0); //< second3 unit_base
            
            constexpr unit_base kilogram3(0, 0, 3, 0, 0, 0, 0, 0); //< kilogram3 unit_base
            
            constexpr unit_base Ampere3(0, 0, 0, 3, 0, 0, 0, 0); //< Ampere3 unit_base
            
            constexpr unit_base Kelvin3(0, 0, 0, 0, 3, 0, 0, 0); //< Kelvin3 unit_base


        } // namespace basis


    } // namespace units


} // namespace scipp::measurements


using namespace scipp::measurements;