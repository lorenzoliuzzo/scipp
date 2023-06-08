            constexpr complex& operator+=(const complex& other) noexcept {

                this->real += other.real;
                this->imag += other.imag;

                return *this;

            }

            constexpr complex& operator+=(complex&& other) noexcept {

                this->real += std::move(other.real);
                this->imag += std::move(other.imag);

                return *this;

            }


            constexpr complex& operator-=(const complex& other) noexcept {

                this->real -= other.real;
                this->imag -= other.imag;

                return *this;

            }

            constexpr complex& operator-=(complex&& other) noexcept {

                this->real -= std::move(other.real);
                this->imag -= std::move(other.imag);

                return *this;

            }


            template <typename SCALAR_MEAS_TYPE>
                requires (is_scalar_measurement_v<SCALAR_MEAS_TYPE> || is_scalar_umeasurement_v<SCALAR_MEAS_TYPE>)
            constexpr complex& operator*=(const complex<SCALAR_MEAS_TYPE>& other) noexcept {

                this->real *= other.real; 
                this->real -= this->imag * other.imag; 
                this->imag *= other.real; 
                this->imag += this->real * other.imag;

                return *this;

            }

            template <typename SCALAR_MEAS_TYPE>
                requires (is_scalar_measurement_v<SCALAR_MEAS_TYPE> || is_scalar_umeasurement_v<SCALAR_MEAS_TYPE>)
            constexpr complex& operator*=(complex<SCALAR_MEAS_TYPE>&& other) noexcept {

                this->real *= std::move(other.real); 
                this->real -= this->imag * std::move(other.imag); 
                this->imag *= std::move(other.real); 
                this->imag += this->real * std::move(other.imag);

                return *this;

            }

            template <typename NUMBER_TYPE>
                requires (math::is_number_v<NUMBER_TYPE>)
            constexpr complex& operator*=(const NUMBER_TYPE& other) noexcept {

                this->real *= other; 
                this->imag *= other; 
                
                return *this;

            }

            template <typename NUMBER_TYPE>
                requires (math::is_number_v<NUMBER_TYPE>)
            constexpr complex& operator*=(NUMBER_TYPE&& other) noexcept {

                this->real *= std::move(other); 
                this->imag *= std::move(other); 

                return *this;

            }


            template <typename SCALAR_MEAS_TYPE>
                requires (is_scalar_measurement_v<SCALAR_MEAS_TYPE> || is_scalar_umeasurement_v<SCALAR_MEAS_TYPE>)
            constexpr complex& operator/=(const complex<SCALAR_MEAS_TYPE>& other) {

                if (other == SCALAR_MEAS_TYPE::zero) 
                    throw std::runtime_error("Cannot divide a complex measurment by zero.");

                this->real *= other.real; 
                this->real += this->imag * other.imag; 
                this->imag *= other.real;
                this->imag -= this->real * other.imag; 

                *this /= math::op::sqrt(math::op::sq(other.real) + math::op::sq(other.imag));

                return *this;

            }

            template <typename SCALAR_MEAS_TYPE>
                requires (is_scalar_measurement_v<SCALAR_MEAS_TYPE> || is_scalar_umeasurement_v<SCALAR_MEAS_TYPE>)
            constexpr complex& operator/=(complex<SCALAR_MEAS_TYPE>&& other) {

                if (other == SCALAR_MEAS_TYPE::zero) 
                    throw std::runtime_error("Cannot divide a complex measurment by zero.");

                this->real *= std::move(other.real); 
                this->real += this->imag * std::move(other.imag); 
                this->imag *= std::move(other.real);
                this->imag -= this->real * std::move(other.imag); 

                *this /= math::op::sqrt(math::op::sq(std::move(other.real)) + math::op::sq(std::move(other.imag)));

                return *this;

            }


            template <typename NUMBER_TYPE>
                requires (math::is_number_v<NUMBER_TYPE>)
            constexpr complex& operator/=(const NUMBER_TYPE& other) {

                if (other == NUMBER_TYPE{}) 
                    throw std::runtime_error("Cannot divide a complex measurment by zero.");

                this->real /= other; 
                this->imag /= other; 
                
                return *this;

            }


            template <typename NUMBER_TYPE>
                requires (math::is_number_v<NUMBER_TYPE>)
            constexpr complex& operator/=(NUMBER_TYPE&& other) {

                if (other == NUMBER_TYPE{}) 
                    throw std::runtime_error("Cannot divide a complex measurment by zero.");

                this->real /= std::move(other); 
                this->imag /= std::move(other); 

                return *this;

            }


            constexpr complex operator-() const noexcept {

                complex result; 
                result.real = -this->real;
                result.imag = -this->imag;

                return result;

            }


            constexpr complex operator+(const complex& other) const noexcept {

                complex result; 
                result.real = this->real + other.real;
                result.imag = this->imag + other.imag;

                return result;

            }

            constexpr complex operator-(const complex& other) const noexcept {

                complex result; 
                result.real = this->real - other.real;
                result.imag = this->imag - other.imag;

                return result;

            }


            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> || is_umeasurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const complex<OTHER_MEAS_TYPE>& other) const noexcept {

                return math::op::mult(*this, other);

            }


            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> || is_umeasurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const OTHER_MEAS_TYPE& other) const noexcept 
                -> complex<math::functions::multiply_t<measurement_t, OTHER_MEAS_TYPE>> {
                
                complex<math::functions::multiply_t<measurement_t, OTHER_MEAS_TYPE>> result; 
                result.real = this->real * other;
                result.imag = this->real * other;

                return result;

            }

            template <typename OTHER_CMEAS_TYPE>
                requires (math::is_complex_v<OTHER_CMEAS_TYPE>)
            constexpr auto operator/(const OTHER_CMEAS_TYPE& other) const 
                -> math::functions::divide_t<complex, OTHER_CMEAS_TYPE> {
                
                auto denom = math::op::norm(other);
                if (denom == OTHER_CMEAS_TYPE::measurement_t::zero) 
                    throw std::runtime_error("Division by zero!");

                return ((*this) * other.conj()) / denom;

            }

            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> || is_umeasurement_v<OTHER_MEAS_TYPE> || math::is_number_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(const OTHER_MEAS_TYPE& other) const 
                -> math::functions::divide_t<complex, OTHER_MEAS_TYPE> {
                
                if (other == OTHER_MEAS_TYPE{})
                    throw std::runtime_error("Division by zero!");

                math::functions::divide_t<complex, OTHER_MEAS_TYPE> result; 
                result.real = this->real / other;
                result.imag = this->real / other;

                return result;

            }


            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> || is_umeasurement_v<OTHER_MEAS_TYPE> || math::is_number_v<OTHER_MEAS_TYPE>)
            friend constexpr complex<math::functions::multiply_t<OTHER_MEAS_TYPE, MEAS_TYPE>> operator*(const OTHER_MEAS_TYPE& other, const complex<MEAS_TYPE>& other_c) noexcept {
                
                complex<math::functions::multiply_t<measurement_t, OTHER_MEAS_TYPE>> result; 
                result.real = other * other_c.real;
                result.imag = other * other_c.imag;

                return result;

            }

            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> || is_umeasurement_v<OTHER_MEAS_TYPE>)
            friend constexpr auto operator/(const OTHER_MEAS_TYPE& other, const complex<MEAS_TYPE>& other_c) noexcept 
                -> complex<math::functions::divide_t<OTHER_MEAS_TYPE, MEAS_TYPE>> {

                return complex<OTHER_MEAS_TYPE>(other) / other_c;

            }


            friend constexpr std::ostream& operator<<(std::ostream& os, const complex& other) noexcept {


                os << '(' << other.real << " " << other.imag << ')'; 

                return os;

            }


