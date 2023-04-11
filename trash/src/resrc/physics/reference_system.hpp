/**
 * @file reference_system.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2022-12-24
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::physics {


    template <std::size_t DIM>
    class reference_system {


        public: 

        // =============================================
        // constructors and destructor
        // =============================================     

            constexpr reference_system(const position<DIM>& origin = position<DIM>(), 
                                       const geometry::linear_algebra::base<DIM>& B = geometry::linear_algebra::base<DIM>(), 
                                       const std::string& name = std::string()) noexcept : 

                base_(B), 
                origin_(origin),
                name_{name} {}


            constexpr reference_system(const reference_system& RS) noexcept : 

                base_(RS.base_), 
                origin_(RS.origin_), 
                name_{RS.name_} {}


            constexpr reference_system(reference_system&& RS) noexcept : 

                base_(std::move(RS.base_)), 
                origin_(std::move(RS.origin_)),
                name_(std::move(RS.name_)) {}


            constexpr reference_system& operator=(const reference_system& RS) noexcept {

                base_ = RS.base_;
                origin_ = RS.origin_;
                name_ = RS.name_;

                return *this;

            }


            constexpr reference_system& operator=(reference_system&& RS) noexcept {

                base_ = RS.base_;
                origin_ = RS.origin_;
                name_ = RS.name_;

                return *this;

            }


            ~reference_system() = default;


            constexpr position<DIM> relative_position(const position<DIM>& pos) const noexcept {

                if (origin_ == position<DIM>()) 
                    return pos; 
                    
                else 
                    return (pos - origin_); 

            }
            

            constexpr position<DIM> origin() const noexcept {

                return origin_; 
                
            }


        protected: 

        // =============================================
        // class members
        // =============================================     

            geometry::linear_algebra::base<DIM> base_; 

            position<DIM> origin_; 

            std::string name_;


    }; // class reference_system


} // namespace geometry