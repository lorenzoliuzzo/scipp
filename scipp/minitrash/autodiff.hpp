/// @file math/autodiff.hpp
/// @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
/// @data 2023-04-12
/// @brief Autodifferentiation for measurements uncertainty evaluation
	

namespace scipp::math {


	template <typename MEAS_TYPE, std::size_t DIM>	
		requires (physics::is_measurement_v<MEAS_TYPE>)
	struct var {
	
		// aliases
		using _t = var<MEAS_TYPE, DIM>; 
		
		using measurement_t = MEAS_TYPE; 
		
		
		// members
		inline static constexpr std::size_t order = DIM; 
		
		measurement_t val; // value
		
		geometry::vector<measurement_t, DIM> unc; // uncertainty components
		
		
		// constructors
		constexpr var() noexcept : 
			
			val{}, unc{} {}
			
			
		constexpr var(const measurement_t& val) noexcept : 
			
			val{val}, unc{} {}
		
		
		constexpr var operator*(const var& other) const noexcept {

			var tmp;
			tmp.val = this->val * other.val;
			tmp.unc = this->val * other.unc + other.val * this->unc;

			return tmp;

		}


		constexpr var operator/(const var& other) const noexcept {

			var tmp;
			tmp.val = this->val / other.val;
			tmp.unc = (this->unc * other.val - this->val * other.unc) / op::square(other.val);

			return tmp;

		}


		friend constexpr var<measurement_t, DIM> cosine(const var<measurement_t, DIM>& other) noexcept {

			var<measurement_t, DIM> tmp;
			tmp.val = op::cos(other.val);
			tmp.unc = -op::sin(other.val) * other.unc;
			return tmp;

		}


	}; // struct var
	
	
	
	template <typename MEAS_TYPE, std::size_t DIM>
		requires (physics::is_measurement_v<MEAS_TYPE>)
	struct correlation_model {
	
		// aliases
		using _t = correlation_model<MEAS_TYPE, DIM>; 
		
		using measurement_t = MEAS_TYPE; 
		
		
		// members
		inline static constexpr std::size_t n_input = DIM; 
		
		geometry::matrix<geometry::vector<measurement_t, DIM>, DIM> r; // correlation coefficients
		
		
		// constructors
		constexpr correlation_model() noexcept : 
			
			r{measurement_t::one} {}
			
			
		// other methods
		constexpr auto variable(std::size_t i, const measurement_t& value, const measurement_t& uncert = measurement_t::one) const
			-> var<measurement_t, DIM> {
			
			if (uncert < measurement_t::zero)	
				throw std::invalid_argument("Cannot initializate a umeasurement with negative uncertainty"); 
				
			var<measurement_t, DIM> tmp;
			tmp.val = value;
			tmp.unc[i] = uncert;
			return tmp;
			
		}
				
		constexpr auto constant(std::size_t i, const measurement_t& value) const noexcept 
			-> var<measurement_t, DIM> {
			
			var<measurement_t, DIM> tmp;
			tmp.x = value;
			return tmp;
			
		}
		
		constexpr void setCorrelation(std::size_t i, std::size_t j, const measurement_t& rho) noexcept {
		
			r.element(i, j) = r.element(i, j) = rho;
			
		}
		
		
		constexpr auto combinedUncertainty(const var<measurement_t, DIM>& y) const noexcept 
			-> measurement_t {
				
			// tools::print("r", r);
			// tools::print("y.unc", y.unc);
			// tools::print("r * y.unc", r * y.unc);
			// tools::print("op::dot(y.unc, r * y.unc)", op::dot(y.unc, r * y.unc));
			return op::sqrt(op::abs(op::dot(y.unc, r * y.unc)));
			
		}
		
		
	}; // struct model


} // namespace scipp::math

