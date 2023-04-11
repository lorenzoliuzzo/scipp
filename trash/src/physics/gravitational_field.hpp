/**
 * @file    gravitational_field.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-22
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::physics {


    namespace potentials {


        /**
         * @brief Class representing a gravitational field
         * @see math::equations::ode 
         * 
         * @tparam DIM: dimension of the space
         */
        template <size_t DIM>
        class gravitational_field : public math::equations::ode<position<DIM>, mass_m, mass_m, position<DIM>> {


            public: 


                /// @brief Construct a new gravitational field object
                constexpr gravitational_field() noexcept : 
                    
                    math::equations::ode<position<DIM>, mass_m, mass_m, position<DIM>>(
                        
                        /// evaluate the gravitational field
                        [this](const position<DIM>& init, 
                               const mass_m& mass, 
                               const mass_m& source_mass, 
                               const position<DIM>& source_position) { 
                            
                            return - constants::G * mass * source_mass * (init - source_position) / math::op::norm2(init - source_position);
                            
                        }, 

                        /// evaluate the gravitational potential
                        [this](const position<DIM>& init, 
                               const mass_m& mass, 
                               const mass_m& source_mass, 
                               const position<DIM>& source_position) {   

                            return constants::G * mass * source_mass * (init - source_position) / math::op::cube(math::op::norm(init - source_position));

                        }

                    ) {}
                    

        }; // class gravitational_field


    } // namespace potentials


} // namespace scipp::physics