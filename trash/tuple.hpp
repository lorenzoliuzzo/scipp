    // /// @brief Tuple constructed from a fixed size and a list of types 
    // template <size_t N, typename... Ts>
    // struct types_tuple {

    //     using type = std::tuple<Ts...>;
    //     using size = std::integral_constant<size_t, N>;

    // };


    // /// @brief Tuple constructed from a fixed size and single type
    // template <size_t N, typename T>
    // struct types_tuple<N, T> {

    //     template <size_t... Is>
    //     static auto create_tuple(std::index_sequence<Is...>) {

    //         // Create a tuple with N copies of T
    //         return std::make_tuple((static_cast<void>(Is), T{})...);

    //     }

    //     using type = decltype(create_tuple(std::make_index_sequence<N>{}));
    //     using size = std::integral_constant<size_t, N>;

    // };


    // template <size_t N, typename... Ts>
    // using types_tuple_t = typename types_tuple<N, Ts...>::type;

