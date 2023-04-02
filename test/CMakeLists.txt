add_executable(measurements measurements.cpp)
target_link_libraries(measurements ${PROJECT_NAME})

add_executable(vector vector.cpp)
target_link_libraries(vector ${PROJECT_NAME})

add_executable(matrix matrix.cpp)
target_link_libraries(matrix ${PROJECT_NAME})

add_executable(integral integral.cpp)
target_link_libraries(integral ${PROJECT_NAME})

add_executable(statistics statistics.cpp)
target_link_libraries(statistics ${PROJECT_NAME})