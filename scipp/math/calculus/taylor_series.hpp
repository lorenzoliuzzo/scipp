/**
 * @file    math/calculus/taylor_series.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-06-29
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    

    namespace calculus {


        /// Represents a Taylor series along a direction for either a scalar or vector function.
        template <size_t N, typename T>
        struct taylor_series { 


            /// ==================================================
            /// @brief aliases
            /// ==================================================

                /// The numeric floating point type of the derivatives, which can be a vector of values or just one.
                using value_t = T;

                using data_t = std::array<value_t, N + 1>;

                using _t = taylor_series<N, value_t>;


            /// ==================================================
            /// @brief members
            /// ==================================================

                inline static constexpr size_t order = N + 1; 

                /// The directional derivatives of the function up to Nth order.
                data_t derivatives;


            /// ==================================================
            /// @brief constructors
            /// ==================================================

                /// Construct a default taylor_series object.
                constexpr taylor_series() = default;


                template <typename... Ts>
                    requires (std::is_same_v<value_t, Ts>, ...)
                constexpr taylor_series(Ts... other) noexcept 
                    requires (sizeof...(other) == order) : 
                    
                    derivatives{std::forward<value_t>(other)...} {}


                /// Construct a taylor_series object with given directional derivatives.
                constexpr taylor_series(const data_t& other) noexcept : 
                    
                    derivatives(other) {}


            /// ==================================================
            /// @brief operators
            /// ==================================================

                /// Evaluate the Taylor series object with given directional derivatives.
                constexpr auto operator()(const T& t) {
                    auto res = derivatives[0];
                    auto factor = t;

                    const auto range = std::views::iota(1u, order);
                    std::ranges::for_each(range, [&](auto&& i) constexpr {
                        res += factor * derivatives[i];
                        factor *= t / (i + 1);
                    });

                    return res;
                }


        }; /// struct taylor_series


    } /// namespace calculus


} /// namespace scipp::math