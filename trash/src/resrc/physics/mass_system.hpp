/**
 * @file mass_system.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2022-12-25
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::physics {


    /**
     * @brief Class for a system of mass
     * 
     * @tparam T: mass type
     */
    template <std::size_t DIM>
    class mass_system : public reference_system<DIM> {


        public:

            constexpr mass_system(const position<DIM>& origin = position<DIM>(), 
                                  const geometry::linear_algebra::base<DIM>& B = geometry::linear_algebra::base<DIM>(), 
                                  const std::string& name = "Mass system") noexcept : 

                reference_system<DIM>(origin, B, name), 
                center_of_mass_(0.0 * kg) {}

        
        // =============================================
        // operators
        // =============================================     

            /**
             * @brief Get a specific mass in the mass_system
             * 
             * @param index: size_t mass index
             * 
             * @return constexpr mass<DIM> 
             */
            constexpr mass<DIM> operator[](const size_t& index) const { 
                
                return bodies_[index]; 
                
            }


            /**
             * @brief Get a specific mass in the mass_system
             * 
             * @param index: size_t mass index
             * 
             * @return constexpr mass<DIM>&
             */
            constexpr mass<DIM>& operator[](const size_t& index) { 
                
                return bodies_[index]; 
                
            }


        // ========================================
        // =========== ITERATORS ==================
        // ========================================

            constexpr mass<DIM>* begin() noexcept {

                return bodies_.data();

            }


            constexpr const mass<DIM>* begin() const noexcept {

                return bodies_.data();

            }


            constexpr mass<DIM>* end() noexcept {

                return bodies_.data() + bodies_.size();

            }


            constexpr const mass<DIM>* end() const noexcept {

                return bodies_.data() + bodies_.size();

            }


        // =============================================
        // get methods
        // =============================================     
 
            /**
             * @brief Add a pack of mass to the mass_system
             * 
             * @param others: parameter pack of masses
             */
            template <typename... masses>
            constexpr void add_mass(masses&&... objs) noexcept {

                for (mass<DIM> m : {objs...}) {

                    
                    m.as_position() = this->relative_position(m.as_position());
                    bodies_.emplace_back(m);

                    mass_measurement old_cm_mass = center_of_mass_.as_mass_measurement();
                    center_of_mass_.as_mass_measurement() += m.as_mass_measurement(); 
                    center_of_mass_.as_position() = (old_cm_mass * center_of_mass_.as_position() + m.as_mass_measurement() * m.as_position()) / center_of_mass_.as_mass_measurement(); 

                }

            }


            /**
             * @brief Get the number of mass in the mass_system
             * 
             * @return constexpr size_t 
             */
            constexpr size_t count() const noexcept { 
                
                return bodies_.size(); 
                
            }


            /**
             * @brief Get all the mass in the mass_system
             * 
             * @return constexpr std::vector<mass<DIM>> 
             */
            constexpr std::vector<mass<DIM>> bodies() const noexcept { 
                
                return bodies_; 
                
            }


            /**
             * @brief Get the total mass of the system
             * 
             * @return constexpr mass_measurement 
             */
            constexpr mass_measurement total_mass() const noexcept {

                return center_of_mass_.as_mass_measurement();

            }


            /**
             * @brief Get the position of the center of mass 
             * 
             * @return position<DIM> 
             */
            constexpr position<DIM> baricenter() const noexcept {

                return center_of_mass_.as_position();

            }

            
            /**
             * @brief Evolve the mass_system for a given time
             * 
             * @param dt: measurement time step as l-value const reference
             */
            void evolve(const time_measurement& dt) {

                vector<DIM> mx(basis::kilogram * basis::metre);
                mass_measurement m_tot(0.0 * kg);

                for (mass<DIM>& obj : bodies_) {

                    mass<DIM> relative_cm = center_of_mass_; 
                    relative_cm.as_mass_measurement() -= obj.as_mass_measurement(); 
                    relative_cm.as_position() = (center_of_mass_.as_mass_measurement() * center_of_mass_.as_position() - obj.as_mass_measurement() * obj.as_position()) / relative_cm.as_mass_measurement(); 
                    
                    obj.gravitate(relative_cm); 
                    obj.as_linear_velocity() += obj.as_linear_acceleration() * dt;
                    obj.as_position() += obj.as_linear_velocity() * dt;

                    mx += obj.as_mass_measurement() * obj.as_position(); 
                    m_tot += obj.as_mass_measurement();

                }

                center_of_mass_.as_mass_measurement() = m_tot;
                center_of_mass_.as_position() = mx / m_tot;

            }


            // /// @brief Print the mass_system to the standard output
            // void print() const noexcept {

            //     std::cout << "\n------------------------ Mass system -----------------------\n"; 

            //     for (const mass<DIM>& m : bodies_)
            //         m.print(); 

            //     std::cout << "\n\ncenter of mass:";
            //     center_of_mass_.print();  

            //     std::cout << "\n------------------------------------------------------------\n";

            // }


            // /// @brief Plot the mass_system using matplotlib-cpp
            // void plot(const unit& length_unit = m) const requires (DIM == 2) {

            //     std::vector<double> x, y;
            //     x.reserve(bodies_.size()), 
            //     y.reserve(bodies_.size());

            //     std::vector<double> x_cm, y_cm; 
            //     x_cm.emplace_back(center_of_mass_.as_position().x().value_as(length_unit));  
            //     y_cm.emplace_back(center_of_mass_.as_position().y().value_as(length_unit));  

            //     for (const mass<DIM>& obj : bodies_) {
            //         x.emplace_back(obj.as_position().x().value_as(length_unit));
            //         y.emplace_back(obj.as_position().y().value_as(length_unit));
            //     }

            //     plt::plot(x, y, std::map<std::string, std::string>({{"label", "mass_system"}, {"marker", "o"}, {"linestyle", ""}, {"color", "b"}})); 
            //     plt::plot(x_cm, y_cm, std::map<std::string, std::string>({{"label", "CM"}, {"marker", "o"}, {"linestyle", ""}, {"color", "r"}})); 

            //     plt::title(this->reference_system<DIM>::name_); 
            //     plt::xlabel("x [" + length_unit.to_string() + "]");
            //     plt::ylabel("y [" + length_unit.to_string() + "]");
            //     plt::grid(true);
            //     plt::tight_layout(); 
            //     plt::legend(); 
            //     plt::show(); 
                        
            // }


            // /// @brief Plot the mass_system using matplotlib-cpp
            // void plot(const unit& length_unit = m) const requires (DIM == 3) {

            //     std::vector<double> x, y, z;
            //     x.reserve(bodies_.size()), 
            //     y.reserve(bodies_.size());
            //     z.reserve(bodies_.size());

            //     std::vector<double> x_cm, y_cm, z_cm; 

            //     x_cm.emplace_back(center_of_mass_.as_position().x().value_as(length_unit));  
            //     y_cm.emplace_back(center_of_mass_.as_position().y().value_as(length_unit));  
            //     z_cm.emplace_back(center_of_mass_.as_position().z().value_as(length_unit));  

            //     for (const mass<DIM>& obj : bodies_) {
            //         x.emplace_back(obj.as_position().x().value_as(length_unit));
            //         y.emplace_back(obj.as_position().y().value_as(length_unit));
            //         z.emplace_back(obj.as_position().z().value_as(length_unit));
            //     }

            //     plt::plot3(x, y, z, std::map<std::string, std::string>({{"label", "mass_system"}, {"marker", "o"}, {"linestyle", ""}, {"color", "b"}})); 
            //     plt::plot3(x_cm, y_cm, z_cm, std::map<std::string, std::string>({{"label", "CM"}, {"marker", "o"}, {"linestyle", ""}, {"color", "r"}})); 

            //     plt::title(this->reference_system<DIM>::name_); 
            //     plt::xlabel("x [" + length_unit.to_string() + "]");
            //     plt::ylabel("y [" + length_unit.to_string() + "]");
            //     plt::set_zlabel("z [" + length_unit.to_string() + "]");
            //     plt::grid(true);
            //     plt::tight_layout(); 
            //     plt::legend(); 
            //     plt::show(); 
                        
            // }


            // void animate(const time_measurement& t_max, time_measurement t_step = 0. * s, const unit& length_unit = m) requires (DIM == 2) {

            //     if (t_step == 0. * s)
            //         t_step = t_max / 1000.; 

            //     std::vector<double> x, y;
            //     x.reserve(bodies_.size()), 
            //     y.reserve(bodies_.size());

            //     std::vector<double> x_cm, y_cm; 

            //     plt::ion(); 

            //     for (time_measurement t = 0.0 * s; t < t_max; t += t_step) {

            //         x_cm.emplace_back(center_of_mass_.as_position().x().value_as(length_unit));  
            //         y_cm.emplace_back(center_of_mass_.as_position().y().value_as(length_unit));  

            //         for (const mass<DIM>& obj : bodies_) {

            //             x.emplace_back(obj.as_position().x().value_as(length_unit));
            //             y.emplace_back(obj.as_position().y().value_as(length_unit));

            //         }

            //         plt::clf();
            //         plt::plot(x, y, std::map<std::string, std::string>({{"label", "mass_system"}, {"marker", "o"}, {"linestyle", ""}, {"color", "b"}}));
            //         plt::plot(x_cm, y_cm, std::map<std::string, std::string>({{"label", "CM"}, {"marker", "o"}, {"linestyle", ""}, {"color", "r"}}));

            //         plt::title(this->reference_system<DIM>::name_); 
            //         plt::xlabel("x [" + length_unit.to_string() + "]");
            //         plt::ylabel("y [" + length_unit.to_string() + "]");
            //         plt::grid(true);
            //         plt::legend(); 

            //         plt::draw();
            //         plt::pause(0.01);

            //         x.clear();
            //         y.clear();
            //         x_cm.clear();
            //         y_cm.clear();

            //         this->evolve(t_step);

            //     }

            // }


        protected:
        
        // =============================================
        // class members
        // =============================================     

            std::vector<mass<DIM>> bodies_; ///< bodies of the mass_system

            mass<DIM> center_of_mass_; ///< baricenter of the mass_system
            

    }; // class mass_system
 

} // namespace scipp::physics {