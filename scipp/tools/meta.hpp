/**
 * @file    tools/meta.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-28
 * 
 * @copyright Copyright (c) 2023
 */


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::meta {


    template <size_t i>
    struct Index {

        constexpr static size_t index = i;
        constexpr operator size_t() const { return index; }
        constexpr operator size_t() { return index; }
        
    };

    template <size_t i, size_t ibegin, size_t iend, typename Function>
    constexpr auto aux_for(Function&& f) {
        if constexpr (i < iend) {
            f(Index<i>{});
            aux_for<i + 1, ibegin, iend>(std::forward<Function>(f));
        }
    }

    template <size_t ibegin, size_t iend, typename Function>
    constexpr auto for_(Function&& f) {
        aux_for<ibegin, ibegin, iend>(std::forward<Function>(f));
    }

    template <size_t iend, typename Function>
    constexpr auto for_(Function&& f) {
        for_<0, iend>(std::forward<Function>(f));
    }


    template <typename T, size_t... Indices>
    constexpr auto make_tuple_repeated_impl(T value, std::index_sequence<Indices...>) {
        return std::make_tuple((static_cast<void>(Indices), value)...);
    }

    template <typename T, size_t N>
    constexpr auto make_tuple_repeated(T value) {
        return make_tuple_repeated_impl(value, std::make_index_sequence<N>{});
    }


} // scipp::meta