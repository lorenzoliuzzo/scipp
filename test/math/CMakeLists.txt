add_executable(meta meta.cpp)
target_link_libraries(meta ${PROJECT_NAME} python3.10)

# add_executable(function function.cpp)
# target_link_libraries(function ${PROJECT_NAME} python3.10)

add_executable(complex complex.cpp)
target_link_libraries(complex ${PROJECT_NAME} python3.10)

# add_executable(dual dual.cpp)
# target_link_libraries(dual ${PROJECT_NAME} python3.10)

# add_executable(integral integral.cpp)
# target_link_libraries(integral ${PROJECT_NAME} python3.10)

# add_executable(derivatives derivatives.cpp)
# target_link_libraries(derivatives ${PROJECT_NAME} python3.10)

# add_executable(statistics statistics.cpp)
# target_link_libraries(statistics ${PROJECT_NAME})

# add_executable(hermite hermite.cpp)
# target_link_libraries(hermite ${PROJECT_NAME} python3.10)

# add_executable(bessel bessel.cpp)
# target_link_libraries(bessel ${PROJECT_NAME})
