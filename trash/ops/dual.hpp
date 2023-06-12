/**
 * @file    math/ops/dual.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    
    
    namespace op {

        // ==============================================
        // operators with duals
        // ==============================================


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
            template <typename OTHER_T>
                requires (physics::is_generic_measurement_v<OTHER_T> && physics::is_scalar_v<OTHER_T>)
            constexpr dual& operator*=(const dual<OTHER_T>& other) noexcept {
                
                this->val *= other.val;
                this->eps += this->val * other.eps;
                this->eps *= other.val;

                return *this;

            }

            /// @brief move assignment operator with multiplication
            template <typename OTHER_T>
                requires (physics::is_generic_measurement_v<OTHER_T> && physics::is_scalar_v<OTHER_T>)
            constexpr dual& operator*=(dual<OTHER_T>&& other) noexcept {
                    
                this->val *= std::move(other.val);
                this->eps += this->val * std::move(other.eps);
                this->eps *= std::move(other.val);

                return *this;

            }


            /// @brief copy assignment operator with division
            template <typename OTHER_T>
                requires (physics::is_generic_measurement_v<OTHER_T> && physics::is_scalar_v<OTHER_T>)
            constexpr dual& operator/=(const dual<OTHER_T>& other) {

                if (other.val == OTHER_T::zero) 
                    throw std::runtime_error("Cannot divide a dual number by a dual zero");

                this->val /= other.val;
                this->eps *= other.val; 
                this->eps -= this->val * other.eps;
                this->eps /= op::square(other.val); 

                return *this;

            }

            /// @brief copy assignment operator with division
            template <typename OTHER_T>
                requires (physics::is_generic_measurement_v<OTHER_T> && physics::is_scalar_v<OTHER_T>)
            constexpr dual& operator/=(dual<OTHER_T>&& other) {

                if (other.val == OTHER_T::zero) 
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
            template <typename OTHER_T>
                requires (physics::is_generic_measurement_v<OTHER_T>)
            constexpr auto operator*(const dual<OTHER_T>& other) const noexcept 
                -> dual<multiply_t<measurement_t, OTHER_T>> {

                return {this->val * other.val, this->val * other.eps + this->eps * other.val};

            } 

            /// @brief multiplication operator
            template <typename OTHER_T>
                requires (physics::is_generic_measurement_v<OTHER_T>)
            constexpr auto operator*(dual<OTHER_T>&& other) const noexcept 
                -> dual<multiply_t<measurement_t, OTHER_T>> {

                return {this->val * std::move(other.val), this->val * std::move(other.eps) + this->eps * std::move(other.val)};

            } 


            /// @brief division operator
            template <typename OTHER_T>
                requires (physics::is_generic_measurement_v<OTHER_T>)
            constexpr auto operator/(const dual<OTHER_T>& other) const
                -> dual<meta::divide<measurement_t, OTHER_T>> {

                if (other.val == OTHER_T::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {this->val / other.val, (this->eps * other.val - this->val * other.eps) / op::square(other.val)};

            }

            /// @brief division operator
            template <typename OTHER_T>
                requires (physics::is_generic_measurement_v<OTHER_T>)
            constexpr auto operator/(dual<OTHER_T>&& other) const
                -> dual<meta::divide<measurement_t, OTHER_T>> {

                if (other.val == OTHER_T::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {this->val / std::move(other.val), (this->eps * std::move(other.val) - this->val * std::move(other.eps)) / op::square(std::move(other.val))};

            }
            

        // ==============================================
        // operators with value_t
        // ==============================================

            /// @brief copy assignment operator from a value_t
            constexpr dual& operator=(const value_t& val) noexcept {
                
                this->val = val;
                this->eps = value_t{};

                return *this;

            }

            /// @brief copy assignment operator from a value_t
            constexpr dual& operator=(measurement_t&& val) noexcept {
                
                this->val = std::move(val);
                this->eps = value_t{};

                return *this;

            }

            
            /// @brief copy assignment operator from a value_t with addition
            constexpr dual& operator+=(const value_t& val) noexcept {
                
                this->val += val;
                
                return *this;

            }

            /// @brief copy assignment operator from a value_t with addition
            constexpr dual& operator+=(measurement_t&& val) noexcept {
                
                this->val += std::move(val);
                
                return *this;

            }


            /// @brief copy assignment operator from a value_t with subtraction
            constexpr dual& operator-=(const value_t& val) noexcept {
                
                this->val -= val;

                return *this;

            }

            /// @brief copy assignment operator from a value_t with subtraction
            constexpr dual& operator-=(measurement_t&& val) noexcept {
                
                this->val -= std::move(val);

                return *this;

            }


            /// @brief copy assignment operator from a scalar measurement with multiplication
            template <typename OTHER_T>
                requires (physics::is_measurement_v<OTHER_T> && physics::is_scalar_v<OTHER_T>)
            constexpr auto operator*=(const OTHER_T& other) noexcept 
                -> dual<multiply_t<measurement_t, OTHER_T>>& {
                
                this->val *= other;
                this->eps *= other;

                return *this;
        
            }

            /// @brief copy assignment operator from a scalar measurement with multiplication
            template <typename OTHER_T>
                requires (physics::is_measurement_v<OTHER_T> && physics::is_scalar_v<OTHER_T>)
            constexpr auto operator*=(OTHER_T&& other) noexcept 
                -> dual<multiply_t<measurement_t, OTHER_T>>& {
                
                this->val *= std::move(other);
                this->eps *= std::move(other);

                return *this;
        
            }
            

            /// @brief copy assignment operator from a scalar measurement with division
            template <typename OTHER_T>
                requires (physics::is_measurement_v<OTHER_T> && physics::is_scalar_v<OTHER_T>)
            constexpr auto operator/=(const OTHER_T& other) 
                -> dual<meta::divide<measurement_t, OTHER_T>>& {

                if (other == OTHER_T::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");
                
                this->val /= other;
                this->eps /= other;

                return *this;
        
            }

            /// @brief copy assignment operator from a scalar measurement with division
            template <typename OTHER_T>
                requires (physics::is_measurement_v<OTHER_T> && physics::is_scalar_v<OTHER_T>)
            constexpr auto operator/=(OTHER_T&& other) 
                -> dual<meta::divide<measurement_t, OTHER_T>>& {

                if (other == OTHER_T::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");
                
                this->val /= std::move(other);
                this->eps /= std::move(other);

                return *this;
        
            }

            

            constexpr dual operator+(const value_t& val) const noexcept {
                
                dual<measurement_t> result; 
                result.val = this->val + val;

                return result;

            }

            constexpr dual operator+(measurement_t&& val) const noexcept {
                
                dual<measurement_t> result; 
                result.val = this->val + std::move(val);

                return result;

            }


            constexpr dual operator-(const value_t& val) const noexcept {
                
                dual<measurement_t> result; 
                result.val = this->val - val;

                return result;

            }

            constexpr dual operator-(measurement_t&& val) const noexcept {
                
                dual<measurement_t> result; 
                result.val = this->val - std::move(val);

                return result;

            }


            template <typename OTHER_T>
                requires (physics::is_generic_measurement_v<OTHER_T>)
            constexpr auto operator*(const OTHER_T& other) const noexcept 
                -> dual<multiply_t<measurement_t, OTHER_T>> {
                    
                return {this->val * other, this->eps * other};
        
            }

            template <typename OTHER_T>
                requires (physics::is_generic_measurement_v<OTHER_T>)
            constexpr auto operator*(OTHER_T&& other) const noexcept 
                -> dual<multiply_t<measurement_t, OTHER_T>> {
                    
                return {this->val * std::move(other), this->eps * std::move(other)};
        
            }


            template <typename OTHER_T>
                requires (physics::is_generic_measurement_v<OTHER_T>)
            constexpr auto operator/(const OTHER_T& other) const 
                -> dual<meta::divide<measurement_t, OTHER_T>> {

                if (other == OTHER_T::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {this->val / other, this->eps / other};

            }

            template <typename OTHER_T>
                requires (physics::is_generic_measurement_v<OTHER_T>)
            constexpr auto operator/(OTHER_T&& other) const 
                -> dual<meta::divide<measurement_t, OTHER_T>> {

                if (other == OTHER_T::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {this->val / std::move(other), this->eps / std::move(other)};

            }


            template <typename OTHER_T>
                requires (physics::is_generic_measurement_v<OTHER_T>)
            friend constexpr auto operator*(const OTHER_T& other, const dual<measurement_t>& other_dual) noexcept 
                -> dual<multiply_t<OTHER_T, value_t>> {
                    
                return {other_dual.val * other, other_dual.eps * other};
        
            }

            template <typename OTHER_T>
                requires (physics::is_generic_measurement_v<OTHER_T>)
            friend constexpr auto operator/(const OTHER_T& other, const dual<measurement_t>& other_dual) 
                -> dual<meta::divide<OTHER_T, value_t>> {

                if (other_dual.val == value_t::zero)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {other / other_dual.val, -other * other_dual.eps / op::square(other_dual.val)};

            }


    }; /// struct dual


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr MEAS_TYPE ceil(const MEAS_TYPE& other) noexcept {

            return {op::ceil(other.val), op::ceil(other.eps)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr MEAS_TYPE floor(const MEAS_TYPE& other) noexcept {

            return {op::floor(other.val), op::floor(other.eps)}; 

        }





        template <typename MEAS_TYPE, size_t POWER>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr auto pow(const MEAS_TYPE& other) noexcept 
            -> dual<meta::pow_t<typename MEAS_TYPE::measurement_t, POWER>> {

            const auto pow = op::pow<POWER - 1>(other.val);
            return {other.val * pow, other.eps * static_cast<double>(POWER) * pow}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr auto square(const MEAS_TYPE& other) noexcept 
            -> dual<meta::square_t<typename MEAS_TYPE::measurement_t>> {

            const auto pow = op::square(other.val);
            return {other.val * pow, 2.0 * other.eps * pow}; 

        }


        /// @todo pow(MEAS_TYPE, MEAS_TYPE)
        // template<class T1, class T2>
        // inline auto
        // pow(const dual<T1> b, const dual<T2>& e)
        // {
        //     using std::pow;
        //     using std::log;

        //     using T = common_numeric_t<T1,T2>;

        //     const auto ba_ea_1 = T(pow(b.val(), e.val()-1));

        //     return dual<T>{
        //         T(b.val()) * ba_ea_1 * (T(1) + (T(e.eps()) * T(log(b.val()))) ),
        //         T(b.eps()) * T(e.val()) * ba_ea_1 };
        // }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr auto sqrt(const MEAS_TYPE& other) noexcept 
            -> dual<meta::sqrt_t<typename MEAS_TYPE::measurement_t>> {

            const auto sqrt = op::sqrt(other.val);
            return {sqrt, other.eps / (2.0 * sqrt)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr auto cbrt(const MEAS_TYPE& other) noexcept 
            -> dual<meta::cbrt_t<typename MEAS_TYPE::measurement_t>> {

            const auto cbrt = op::cbrt(other.val);
            return {cbrt, other.eps / (3.0 * op::square(cbrt))}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE sin(const MEAS_TYPE& other) noexcept {

            return {op::sin(other.val), other.eps * op::cos(other.val)}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE cos(const MEAS_TYPE& other) noexcept {

            return {op::cos(other.val), - other.eps * op::sin(other.val)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE tan(const MEAS_TYPE& other) noexcept {

            return {op::tan(other.val), other.eps * op::square(op::cos(other.val))}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE asin(const MEAS_TYPE& other) noexcept {

            return {op::asin(other.val), other.eps / op::sqrt(1.0 - op::square(other.val))}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE acos(const MEAS_TYPE& other) noexcept {

            return {op::acos(other.val), -other.eps / op::sqrt(1.0 - op::square(other.val))}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE atan(const MEAS_TYPE& other) noexcept {

            return {op::atan(other.val), other.eps / (1.0 + op::square(other.val))}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE sinh(const MEAS_TYPE& other) noexcept {

            return {op::sinh(other.val), other.eps * op::cosh(other.val)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE cosh(const MEAS_TYPE& other) noexcept {

            return {op::cosh(other.val), other.eps * op::sinh(other.val)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE tanh(const MEAS_TYPE& other) noexcept {

            return {op::tanh(other.val), other.eps / op::square(op::cosh(other.val))}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE asinh(const MEAS_TYPE& other) noexcept {

            return {op::asinh(other.val), other.eps / op::sqrt(op::square(other.val) + 1.0)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE acosh(const MEAS_TYPE& other) noexcept {

            return {op::acosh(other.val), other.eps / op::sqrt(op::square(other.val) - 1.0)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE atanh(const MEAS_TYPE& other) noexcept {

            return {op::atanh(other.val), other.eps / (1.0 - op::square(other.val))}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE exp(const MEAS_TYPE& other) noexcept {

            const auto exp = op::exp(other.val); 
            return {exp, other.eps * exp}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE exp10(const MEAS_TYPE& other) noexcept {

            const auto exp10 = op::exp10(other.val); 
            return {exp10, other.eps * std::exp(10.0) * exp10}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE log(const MEAS_TYPE& other) noexcept {

            return {op::log(other.val), other.eps / other.val}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE log10(const MEAS_TYPE& other) noexcept {

            return {op::log10(other.val), other.eps / (other.val * std::log(10.0))}; 

        }


    } /// namespace op


} /// namespace scipp::math