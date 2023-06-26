# add_executable(measurements measurements.cpp)
# target_link_libraries(measurements ${PROJECT_NAME})

# add_executable(hamiltonian hamiltonian.cpp)
# target_link_libraries(hamiltonian ${PROJECT_NAME} python3.10)

add_executable(spring spring.cpp)
target_link_libraries(spring ${PROJECT_NAME} python3.10)
