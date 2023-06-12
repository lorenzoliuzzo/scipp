/**
 * @file    math/numbers/dual.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-12
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    /// @brief dual number struct
    /// @tparam T the type of the measurement
    template <typename T>
        requires (is_generic_number_v<T> || physics::is_measurement_v<T>)
    struct dual<T> {


        // ==============================================
        // aliases
        // ==============================================

            /// @brief alias for the type of the class
            using _t = dual<T>; 

            /// @brief alias for the type of the measurement
            using value_t = T; 


        // ==============================================
        // members
        // ==============================================

            /// @brief value of the dual number
            value_t real; 

            /// @brief epsilon of the dual number
            value_t imag;


        // ==============================================
        // constructors
        // ==============================================

            /// @brief default constructor
            /// @details constructs a dual number with value 0 and epsilon 0
            constexpr dual() noexcept : 
                
                real{}, imag{} {}


            /// @brief constructor from a value
            /// @details constructs a dual number with value val and epsilon 0
            constexpr dual(const value_t& real) noexcept :

                real{real}, imag{1.0} {}

            /// @brief constructor from a value
            /// @details constructs a dual number with value val and epsilon 0
            constexpr dual(value_t&& real) noexcept :

                real{std::move(real)}, imag{1.0} {}


            /// @brief constructor from a value and an epsilon
            /// @details constructs a dual number with value val and epsilon eps
            constexpr dual(const value_t& real, const value_t& imag) noexcept : 
                
                real{real}, imag{imag} {}

            /// @brief constructor from a value and an epsilon
            /// @details constructs a dual number with value val and epsilon eps
            constexpr dual(value_t&& real, value_t&& imag) noexcept :

                real{std::move(real)}, imag{std::move(imag)} {}


            /// @brief copy constructor
            constexpr dual(const dual& other) noexcept :

                real{other.real}, imag{other.imag} {}

            /// @brief move constructor
            constexpr dual(dual&& other) noexcept :

                real{std::move(other.real)}, imag{std::move(other.imag)} {}


            /// @brief destructor
            constexpr ~dual() = default;
    

        // ==============================================
        // operators
        // ==============================================

            /// @brief copy assignment operator
            constexpr dual& operator=(const dual& other) noexcept {
                
                this->real = other.real;
                this->imag = other.imag;

                return *this;

            }   

            /// @brief move assignment operator
            constexpr dual& operator=(dual&& other) noexcept {
                
                this->real = std::move(other.real);
                this->imag = std::move(other.imag);

                return *this;

            }


    }; /// dual struct


} /// namespace scipp::math