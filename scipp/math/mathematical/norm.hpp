            template <typename T>
            struct norm_impl;


            template <typename CMEAS_TYPE>  
                requires (math::is_complex_v<CMEAS_TYPE>)
            struct norm_impl<CMEAS_TYPE> : unary_function<typename CMEAS_TYPE::value_t, CMEAS_TYPE> {

                constexpr typename CMEAS_TYPE::value_t f(const CMEAS_TYPE& other) const noexcept override {

                    return op::sqrt(op::sq(other.real) + op::sq(other.imag));

                }

            };
            

            /// @brief Get the norm of the vector
            template <typename VEC_TYPE>
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct norm_impl<VEC_TYPE> : unary_function<typename VEC_TYPE::measurement_t, VEC_TYPE> { 

                constexpr typename VEC_TYPE::measurement_t f(const VEC_TYPE& other) const noexcept override {

                    if constexpr (VEC_TYPE::dim == 1) 
                        return other.data[0];

                    square_t<typename VEC_TYPE::measurement_t> result;

                    for (size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result += op::sq(other.data[i]);

                    return op::sqrt(result);

                }

            };

