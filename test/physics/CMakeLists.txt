# add_executable(measurements measurements.cpp)
# target_link_libraries(measurements ${PROJECT_NAME})

# add_executable(hamiltonian hamiltonian.cpp)
# target_link_libraries(hamiltonian ${PROJECT_NAME} python3.10)

# add_executable(spring spring.cpp)
# target_link_libraries(spring ${PROJECT_NAME} python3.10)

# add_executable(potentials potentials.cpp)
# target_link_libraries(potentials ${PROJECT_NAME} python3.10)

# add_executable(curves curves.cpp)
# target_link_libraries(curves ${PROJECT_NAME} python3.10)

# add_executable(multidim multidim.cpp)
# target_link_libraries(multidim ${PROJECT_NAME} python3.10)


# add_executable(termo termo.cpp)
# target_link_libraries(termo ${PROJECT_NAME} python3.10)


add_executable(point point.cpp)
target_link_libraries(point ${PROJECT_NAME})
