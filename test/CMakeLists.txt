# add_executable(measurements measurements.cpp)
# target_link_libraries(measurements ${PROJECT_NAME})

# add_executable(integral integral.cpp)
# target_link_libraries(integral ${PROJECT_NAME} python3.10)

add_executable(complex complex.cpp)
target_link_libraries(complex ${PROJECT_NAME})

# add_executable(geometry geometry.cpp)
# target_link_libraries(geometry ${PROJECT_NAME} python3.10)

# add_executable(derivatives derivatives.cpp)
# target_link_libraries(derivatives ${PROJECT_NAME} python3.10)

add_executable(linear_algebra linear_algebra.cpp)
target_link_libraries(linear_algebra ${PROJECT_NAME})