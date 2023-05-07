/**
 * @file    math/numbers/dual.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    inline static constexpr size_t factorial(size_t n) noexcept {

        if (n == 0) 
            return 1;

        else 
            return n * factorial(n - 1);

    }


    inline static constexpr size_t binomial_coeff(size_t i, size_t j) noexcept {

        if (j > i) 
            return 0;

        else 
            return factorial(i) / (factorial(j) * factorial(i - j));

    }


    /// @brief dual number struct
    /// @tparam MEAS_TYPE the type of the measurement
    template <typename MEAS_TYPE>
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    struct dual {


        // ==============================================
        // aliases
        // ==============================================

            /// @brief alias for the type of the class
            using _t = dual<MEAS_TYPE>; 

            /// @brief alias for the type of the measurement
            using measurement_t = MEAS_TYPE; 


        // ==============================================
        // members
        // ==============================================

            /// @brief value of the dual number
            measurement_t val; 

            /// @brief epsilon of the dual number
            measurement_t eps;


        // ==============================================
        // constructors
        // ==============================================

            /// @brief default constructor
            /// @details constructs a dual number with value 0 and epsilon 0
            constexpr dual() noexcept : 
                
                val{}, eps{} {}


            /// @brief constructor from a value
            /// @details constructs a dual number with value val and epsilon 0
            constexpr dual(const measurement_t& val) noexcept :

                val{val}, eps{1.0} {}

            /// @brief constructor from a value
            /// @details constructs a dual number with value val and epsilon 0
            constexpr dual(measurement_t&& val) noexcept :

                val{std::move(val)}, eps{1.0} {}


            /// @brief constructor from a value and an epsilon
            /// @details constructs a dual number with value val and epsilon eps
            constexpr dual(const measurement_t& val, const measurement_t& eps) noexcept : 
                
                val{val}, eps{eps} {}

            /// @brief constructor from a value and an epsilon
            /// @details constructs a dual number with value val and epsilon eps
            constexpr dual(measurement_t&& val, measurement_t&& eps) noexcept :

                val{std::move(val)}, eps{std::move(eps)} {}


            /// @brief copy constructor
            constexpr dual(const dual& other) noexcept :

                val{other.val}, eps{other.eps} {}

            /// @brief move constructor
            constexpr dual(dual&& other) noexcept :

                val{std::move(other.val)}, eps{std::move(other.eps)} {}


            /// @brief destructor
            constexpr ~dual() = default;


        // ==============================================
        // operators with duals
        // ==============================================

            /// @brief copy assignment operator
            constexpr dual& operator=(const dual& other) noexcept {
                
                this->val = other.val;
                this->eps = other.eps;

                return *this;

            }   

            /// @brief move assignment operator
            constexpr dual& operator=(dual&& other) noexcept {
                
                this->val = std::move(other.val);
                this->eps = std::move(other.eps);

                return *this;

            }


            /// @brief copy assignment operator with addition
            constexpr dual& operator+=(const dual& other) noexcept {
                
                this->val += other.val;
                this->eps += other.eps;

                return *this;

            }

            /// @brief move assignment operator with addition
            constexpr dual& operator+=(dual&& other) noexcept {
                
                this->val += std::move(other.val);
                this->eps += std::move(other.eps);

                return *this;

            }


            /// @brief copy assignment operator with subtraction
            constexpr dual& operator-=(const dual& other) noexcept {
                
                this->val -= other.val;
                this->eps -= other.eps;

                return *this;
                
            }   
            
            /// @brief move assignment operator with subtraction
            constexpr dual& operator-=(dual&& other) noexcept {
                
                this->val -= std::move(other.val);
                this->eps -= std::move(other.eps);

                return *this;
                
            }


            /// @brief copy assignment operator with multiplication
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE> && physics::is_scalar_v<OTHER_MEAS_TYPE>)
            constexpr dual& operator*=(const dual<OTHER_MEAS_TYPE>& other) noexcept {
                
                this->val *= other.val;
                this->eps += this->val * other.eps;
                this->eps *= other.val;

                return *this;

            }

            /// @brief move assignment operator with multiplication
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE> && physics::is_scalar_v<OTHER_MEAS_TYPE>)
            constexpr dual& operator*=(dual<OTHER_MEAS_TYPE>&& other) noexcept {
                    
                this->val *= std::move(other.val);
                this->eps += this->val * std::move(other.eps);
                this->eps *= std::move(other.val);

                return *this;

            }


            /// @brief copy assignment operator with division
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE> && physics::is_scalar_v<OTHER_MEAS_TYPE>)
            constexpr dual& operator/=(const dual<OTHER_MEAS_TYPE>& other) {

                if (other.val == OTHER_MEAS_TYPE::zero) 
                    throw std::runtime_error("Cannot divide a dual number by a dual zero");

                this->val /= other.val;
                this->eps *= other.val; 
                this->eps -= this->val * other.eps;
                this->eps /= op::square(other.val); 

                return *this;

            }

            /// @brief copy assignment operator with division
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE> && physics::is_scalar_v<OTHER_MEAS_TYPE>)
            constexpr dual& operator/=(dual<OTHER_MEAS_TYPE>&& other) {

                if (other.val == OTHER_MEAS_TYPE::zero) 
                    throw std::runtime_error("Cannot divide a dual number by a dual zero");

                this->val /= std::move(other.val);
                this->eps *= std::move(other.val); 
                this->eps -= this->val * std::move(other.eps);
                this->eps /= op::square(std::move(other.val)); 

                return *this;

            }


            /// @brief unary minus operator
            constexpr dual operator-() const noexcept {
                
                return {-val, -eps};

            }


            /// @brief addition operator 
            constexpr dual operator+(const dual& other) const noexcept {
                
                return {this->val + other.val, this->eps + other.eps};

            }

            /// @brief addition operator
            constexpr dual operator+(dual&& other) const noexcept {
                
                return {this->val + std::move(other.val), this->eps + std::move(other.eps)};

            }


            /// @brief subtraction operator
            constexpr dual operator-(const dual& other) const noexcept {
                
                return {this->val - other.val, this->eps - other.eps};

            }

            /// @brief subtraction operator
            constexpr dual operator-(dual&& other) const noexcept {
                
                return {this->val - std::move(other.val), this->eps - std::move(other.eps)};

            }


            /// @brief multiplication operator
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const dual<OTHER_MEAS_TYPE>& other) const noexcept 
                -> dual<multiply_t<measurement_t, OTHER_MEAS_TYPE>> {

                return {this->val * other.val, this->val * other.eps + this->eps * other.val};

            } 

            /// @brief multiplication operator
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(dual<OTHER_MEAS_TYPE>&& other) const noexcept 
                -> dual<multiply_t<measurement_t, OTHER_MEAS_TYPE>> {

                return {this->val * std::move(other.val), this->val * std::move(other.eps) + this->eps * std::move(other.val)};

            } 


            /// @brief division operator
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(const dual<OTHER_MEAS_TYPE>& other) const
                -> dual<meta::divide<measurement_t, OTHER_MEAS_TYPE>> {

                if (other.val == OTHER_MEAS_TYPE::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {this->val / other.val, (this->eps * other.val - this->val * other.eps) / op::square(other.val)};

            }

            /// @brief division operator
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(dual<OTHER_MEAS_TYPE>&& other) const
                -> dual<meta::divide<measurement_t, OTHER_MEAS_TYPE>> {

                if (other.val == OTHER_MEAS_TYPE::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {this->val / std::move(other.val), (this->eps * std::move(other.val) - this->val * std::move(other.eps)) / op::square(std::move(other.val))};

            }
            

        // ==============================================
        // operators with measurement_t
        // ==============================================

            /// @brief copy assignment operator from a measurement_t
            constexpr dual& operator=(const measurement_t& val) noexcept {
                
                this->val = val;
                this->eps = measurement_t{};

                return *this;

            }

            /// @brief copy assignment operator from a measurement_t
            constexpr dual& operator=(measurement_t&& val) noexcept {
                
                this->val = std::move(val);
                this->eps = measurement_t{};

                return *this;

            }

            
            /// @brief copy assignment operator from a measurement_t with addition
            constexpr dual& operator+=(const measurement_t& val) noexcept {
                
                this->val += val;
                
                return *this;

            }

            /// @brief copy assignment operator from a measurement_t with addition
            constexpr dual& operator+=(measurement_t&& val) noexcept {
                
                this->val += std::move(val);
                
                return *this;

            }


            /// @brief copy assignment operator from a measurement_t with subtraction
            constexpr dual& operator-=(const measurement_t& val) noexcept {
                
                this->val -= val;

                return *this;

            }

            /// @brief copy assignment operator from a measurement_t with subtraction
            constexpr dual& operator-=(measurement_t&& val) noexcept {
                
                this->val -= std::move(val);

                return *this;

            }


            /// @brief copy assignment operator from a scalar measurement with multiplication
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_measurement_v<OTHER_MEAS_TYPE> && physics::is_scalar_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*=(const OTHER_MEAS_TYPE& other) noexcept 
                -> dual<multiply_t<measurement_t, OTHER_MEAS_TYPE>>& {
                
                this->val *= other;
                this->eps *= other;

                return *this;
        
            }

            /// @brief copy assignment operator from a scalar measurement with multiplication
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_measurement_v<OTHER_MEAS_TYPE> && physics::is_scalar_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*=(OTHER_MEAS_TYPE&& other) noexcept 
                -> dual<multiply_t<measurement_t, OTHER_MEAS_TYPE>>& {
                
                this->val *= std::move(other);
                this->eps *= std::move(other);

                return *this;
        
            }
            

            /// @brief copy assignment operator from a scalar measurement with division
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_measurement_v<OTHER_MEAS_TYPE> && physics::is_scalar_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/=(const OTHER_MEAS_TYPE& other) 
                -> dual<meta::divide<measurement_t, OTHER_MEAS_TYPE>>& {

                if (other == OTHER_MEAS_TYPE::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");
                
                this->val /= other;
                this->eps /= other;

                return *this;
        
            }

            /// @brief copy assignment operator from a scalar measurement with division
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_measurement_v<OTHER_MEAS_TYPE> && physics::is_scalar_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/=(OTHER_MEAS_TYPE&& other) 
                -> dual<meta::divide<measurement_t, OTHER_MEAS_TYPE>>& {

                if (other == OTHER_MEAS_TYPE::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");
                
                this->val /= std::move(other);
                this->eps /= std::move(other);

                return *this;
        
            }

            

            constexpr dual operator+(const measurement_t& val) const noexcept {
                
                dual<measurement_t> result; 
                result.val = this->val + val;

                return result;

            }

            constexpr dual operator+(measurement_t&& val) const noexcept {
                
                dual<measurement_t> result; 
                result.val = this->val + std::move(val);

                return result;

            }


            constexpr dual operator-(const measurement_t& val) const noexcept {
                
                dual<measurement_t> result; 
                result.val = this->val - val;

                return result;

            }

            constexpr dual operator-(measurement_t&& val) const noexcept {
                
                dual<measurement_t> result; 
                result.val = this->val - std::move(val);

                return result;

            }


            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const OTHER_MEAS_TYPE& other) const noexcept 
                -> dual<multiply_t<measurement_t, OTHER_MEAS_TYPE>> {
                    
                return {this->val * other, this->eps * other};
        
            }

            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(OTHER_MEAS_TYPE&& other) const noexcept 
                -> dual<multiply_t<measurement_t, OTHER_MEAS_TYPE>> {
                    
                return {this->val * std::move(other), this->eps * std::move(other)};
        
            }


            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(const OTHER_MEAS_TYPE& other) const 
                -> dual<meta::divide<measurement_t, OTHER_MEAS_TYPE>> {

                if (other == OTHER_MEAS_TYPE::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {this->val / other, this->eps / other};

            }

            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(OTHER_MEAS_TYPE&& other) const 
                -> dual<meta::divide<measurement_t, OTHER_MEAS_TYPE>> {

                if (other == OTHER_MEAS_TYPE::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {this->val / std::move(other), this->eps / std::move(other)};

            }


            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            friend constexpr auto operator*(const OTHER_MEAS_TYPE& other, const dual<measurement_t>& other_dual) noexcept 
                -> dual<multiply_t<OTHER_MEAS_TYPE, measurement_t>> {
                    
                return {other_dual.val * other, other_dual.eps * other};
        
            }

            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            friend constexpr auto operator/(const OTHER_MEAS_TYPE& other, const dual<measurement_t>& other_dual) 
                -> dual<meta::divide<OTHER_MEAS_TYPE, measurement_t>> {

                if (other_dual.val == measurement_t::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {other / other_dual.val, -other * other_dual.eps / op::square(other_dual.val)};

            }


    }; /// struct dual


    /// @brief Type trait to check if a type is a dual measurement
    template <typename T>
    struct is_dual_measurement : std::false_type {};

    template <typename MEAS_TYPE>
    struct is_dual_measurement<dual<MEAS_TYPE>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_dual_measurement_v = is_dual_measurement<T>::value;


    /// @brief Type trait to check if a set of types are all dual measurements
    template <typename... MEAS_TYPES>
    struct are_dual_measurements : std::conjunction<is_dual_measurement<MEAS_TYPES>...>{};

    template <typename... MEAS_TYPES>
    inline constexpr bool are_dual_measurements_v = are_dual_measurements<MEAS_TYPES...>::value;


    /// @brief dual numbers with order N
    template <typename MEAS_TYPE, size_t N>    
        requires (physics::is_measurement_v<MEAS_TYPE>)
    struct dual_n {
        
        // ==============================================
        // aliases
        // ==============================================

            /// @brief alias for the type of the class
            using _t = dual<MEAS_TYPE>; 

            /// @brief alias for the type of the measurement
            using measurement_t = MEAS_TYPE; 

            /// @brief alias for the type of the data
            using derivative_t = std::array<measurement_t, N>;


            /// @brief order of the dual number
            inline static constexpr size_t order = N;


        // ==============================================
        // members
        // ==============================================

            /// @brief value of the dual number
            measurement_t val;

            /// @brief derivative up to N order of the dual number
            std::array<measurement_t, N> der; 


        // ==============================================
        // constructors
        // ==============================================

            /// @brief default constructor
            constexpr dual_n() = default;

            /// @brief constructor from a measurement and a derivative vector
            constexpr dual_n(const measurement_t& val, const derivative_t& der = derivative_t{}) noexcept : 
                
                val{val}, der{der} {}

            /// @brief constructor from a measurement
            constexpr dual_n(measurement_t&& val, derivative_t&& der) noexcept :
                
                val{std::move(val)}, der{std::move(der)} {}      


            /// @brief copy constructor
            constexpr dual_n(const dual_n& other) = default;

            /// @brief move constructor
            constexpr dual_n(dual_n&& other) = default;


            /// @brief destructor
            constexpr ~dual_n() = default;  


        // ==============================================
        // operators
        // ==============================================

            /// @brief assignment operator
            constexpr dual_n& operator=(const dual_n& other) = default;

            /// @brief assignment operator
            constexpr dual_n& operator=(dual_n&& other) = default;


            /// @brief unary plus operator
            constexpr dual_n operator-() const noexcept {

                return {-*this.val, -*this->der};

            }


            /// @brief addition operator
            constexpr dual_n operator+(const dual_n& other) const noexcept {

                return {this->val + other.val, this->der + other.der};

            }


            /// @brief addition operator
            constexpr dual_n operator+(dual_n&& other) const noexcept {

                return {this->val + std::move(other.val), this->der + std::move(other.der)};

            }


            /// @brief subtraction operator
            constexpr dual_n operator-(const dual_n& other) const noexcept {

                return {this->val - other.val, this->der - other.der};

            }


            /// @brief subtraction operator
            constexpr dual_n operator-(dual_n&& other) const noexcept {

                return {this->val - std::move(other.val), this->der - std::move(other.der)};

            }


            /// @brief multiplication operator
            constexpr dual_n operator*(const dual_n& other) const noexcept {

                derivative_t tmp; 
                for (size_t i{}; i < order; ++i)
                    for (size_t j{}; j < order; ++j)
                        if (i + j < order)
                            tmp[i + j] += this->der[i] * other.der[j] * binomial_coeff(i + j, i);
                            
                return {this->val * other.val, tmp};

            }


            /// @brief multiplication operator
            constexpr dual_n operator*(dual_n&& other) const noexcept {

                derivative_t tmp; 
                for (size_t i{}; i < order; ++i)
                    for (size_t j{}; j < order; ++j)
                        if (i + j < order)
                            tmp[i + j] += this->der[i] * std::move(other.der[j]) * binomial_coeff(i + j, i);
                            
                return {this->val * std::move(other.val), tmp};

            }


            /// @brief division operator
            constexpr dual_n operator/(const dual_n& other) const noexcept {

                if (other.val == measurement_t::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                derivative_t tmp; 
                for (size_t i{}; i < order; ++i)
                    for (size_t j{}; j < order; ++j)
                        if (i + j < order)
                            tmp[i + j] += this->der[i] * other.der[j] * binomial_coeff(i + j, i);
                            
                return {this->val / other.val, tmp};

            }


            /// @brief division operator
            constexpr dual_n operator/(dual_n&& other) const noexcept {

                if (other.val == measurement_t::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                derivative_t tmp; 
                for (size_t i{}; i < order; ++i)
                    for (size_t j{}; j < order; ++j)
                        if (i + j < order)
                            tmp[i + j] += this->der[i] * std::move(other.der[j]) * binomial_coeff(i + j, i);
                            
                return {this->val / std::move(other.val), tmp};

            }




            


// DnumN operator/(DnumN f1, float f2) {
// DnumN res; foreach(j) res(j) = f1(j) / f2;
// return res;
// }
// DnumN operator*(DnumN f1, DnumN f2) {
// DnumN res;
// foreach(j) foreach(k)
// if (j + k <= N) res(j+k) += f1(j) * f2(k) * choose(j+k, j);
// return res;
// }
// DnumN operator/(DnumN f1, DnumN f2) {
// if (f2.isReal()) return f1 / f2(0);
// else return (f1 * f2.conjugate()) / (f2 * f2.conjugate());
// }

            
            
    }; /// struct dual_n
    

} /// namespace scipp::math