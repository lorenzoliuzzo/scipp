
#include "physics.hpp"

using namespace physics;


template <size_t DIM>
class star : public mass<DIM> {


    public:

        explicit constexpr star(const std::string& name,
                                const mass_measurement& mass,
                                const position<DIM>& pos) noexcept : 

            mass<DIM>(mass, pos),
            name_{name} {}


        constexpr ~star() noexcept = default;


        constexpr std::string name() const noexcept {

            return name_; 

        }


    private: 
        
        std::string name_;


}; // class star


template <size_t DIM>
class planet : public mass<DIM> {


    private:

        std::string name_;

        time_measurement orbit_period_;

        position<DIM> perihelion_position_;

        position<DIM> aphelion_position_;

        linear_velocity<DIM> perihelion_velocity_;

        linear_velocity<DIM> aphelion_velocity_;
        

    public:

        explicit constexpr planet(const std::string& name,
                                  const mass_measurement& mass,
                                  const position<DIM>& aphelion_pos, 
                                  const linear_velocity<DIM>& aphelion_vel,
                                  const position<DIM>& perihelion_pos, 
                                  const linear_velocity<DIM>& perihelion_vel,  
                                  const time_measurement& orbit_period = time_measurement()) noexcept : 

            mass<DIM>(mass, position<DIM>()),
            name_{name},
            orbit_period_{orbit_period}, 
            perihelion_position_{perihelion_pos}, 
            aphelion_position_{aphelion_pos},
            perihelion_velocity_{perihelion_vel}, 
            aphelion_velocity_{aphelion_vel} {}


        constexpr planet(const planet& other) noexcept : 

            mass<DIM>(other.as_mass_object()), 
            name_{other.name_},
            orbit_period_{other.orbit_period_}, 
            perihelion_position_{other.perihelion_position_}, 
            aphelion_position_{other.aphelion_position_}, 
            perihelion_velocity_{other.perihelion_velocity_}, 
            aphelion_velocity_{other.aphelion_velocity_} {}


        constexpr planet(planet&& other) noexcept :

            mass<DIM>(std::move(other.as_mass_object())), 
            name_{std::move(other.name_)},
            orbit_period_{std::move(other.orbit_period_)}, 
            perihelion_position_{std::move(other.perihelion_position_)}, 
            aphelion_position_{std::move(other.aphelion_position_)}, 
            perihelion_velocity_{std::move(other.perihelion_velocity_)}, 
            aphelion_velocity_{std::move(other.aphelion_velocity_)} {}


        constexpr planet& operator=(const planet& other) noexcept {

            if (this != &other) {

                mass<DIM>::operator=(other); 
                name_ = other.name_;
                orbit_period_ = other.orbit_period_; 
                perihelion_position_ = other.perihelion_position_; 
                aphelion_position_ = other.aphelion_position_; 
                perihelion_velocity_ = other.perihelion_velocity_; 
                aphelion_velocity_ = other.aphelion_velocity_; 

            }

            return *this; 

        }


        constexpr planet& operator=(planet&& other) noexcept {

            if (this != &other) {

                mass<DIM>::operator=(std::move(other)); 
                name_ = std::move(other.name_);
                orbit_period_ = std::move(other.orbit_period_); 
                perihelion_position_ = std::move(other.perihelion_position_); 
                aphelion_position_ = std::move(other.aphelion_position_); 
                perihelion_velocity_ = std::move(other.perihelion_velocity_); 
                aphelion_velocity_ = std::move(other.aphelion_velocity_); 

            }

            return *this; 

        }


        constexpr ~planet() noexcept = default;


        constexpr void set_at_perihelion() noexcept {

            this->position_ = perihelion_position_; 
            this->linear_velocity_ = perihelion_velocity_; 

        }


        constexpr void set_at_aphelion() noexcept {

            this->position_ = aphelion_position_; 
            this->linear_velocity_ = aphelion_velocity_; 

        }


        constexpr time_measurement orbit_period() const noexcept {

            return orbit_period_; 

        }


        constexpr position<DIM> perihelion_position() const noexcept {

            return perihelion_position_; 

        }


        constexpr position<DIM> aphelion_position() const noexcept {

            return aphelion_position_; 

        }


        constexpr linear_velocity<DIM> perihelion_velocity() const noexcept {

            return perihelion_velocity_; 

        }   


        constexpr linear_velocity<DIM> aphelion_velocity() const noexcept {

            return aphelion_velocity_; 

        }


        constexpr std::string name() const noexcept {

            return name_; 

        }


}; // class planet


star<2> Sun("Sun", 1.989e30 * kg, position<2>(0.0 * m, 0.0 * m));


planet<2> Mercury("Mercury", 0.33010E24 * kg, 
                position<2>(69.818E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, 38.86 * km_s), 
                position<2>(-46E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, -58.98 * km_s),
                87.969 * 24 * 3600. * s);


planet<2> Venus("Venus", 4.8673E24 * kg, 
                position<2>(108.941E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, 34.79 * km_s), 
                position<2>(-107.480E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, -35.26 * km_s),
                224.701 * 24 * 3600. * s);

    
planet<2> Earth("Earth", 5.9722E24 * kg, 
                position<2>(152.100E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, 29.2911 * km_s), 
                position<2>(-147.095E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, -30.2865 * km_s),
                365.256 * 24 * 3600. * s);


planet<2> Mars("Mars", 0.64169E24 * kg, 
                position<2>(249.261E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, 21.97 * km_s), 
                position<2>(-206.650E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, -26.50 * km_s),
                686.980 * 24 * 3600. * s);


planet<2> Jupiter("Jupiter", 1898.13E24 * kg, 
                position<2>(816.363E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, 12.44 * km_s), 
                position<2>(-740.595E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, -13.72 * km_s),
                4332.589 * 24 * 3600. * s);


planet<2> Saturn("Saturn", 568.32E24 * kg, 
                position<2>(1506.527E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, 9.09 * km_s), 
                position<2>(-1357.554E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, -10.18 * km_s),
                10759.22 * 24 * 3600. * s);


planet<2> Uranus("Uranus", 86.811E24 * kg, 
                position<2>(3001.390E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, 6.49 * km_s), 
                position<2>(-2732.696E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, -7.11 * km_s),
                30685.4 * 24 * 3600. * s);


planet<2> Neptune("Neptune", 102.409E24 * kg, 
                position<2>(4558.857E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, 5.37  * km_s), 
                position<2>(-4471.050E6 * km, 0.0 * km), linear_velocity<2>(0.0 * km_s, -5.50 * km_s),
                60189 * 24 * 3600. * s);

