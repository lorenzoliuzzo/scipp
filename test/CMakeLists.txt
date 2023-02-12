
add_executable(measurement_test ${CMAKE_CURRENT_SOURCE_DIR}/measurement.cpp)  
target_link_libraries(measurement_test PRIVATE ${PROJECT_NAME})

add_executable(vector_test ${CMAKE_CURRENT_SOURCE_DIR}/vector.cpp)  
target_link_libraries(vector_test PRIVATE ${PROJECT_NAME})

add_executable(matrix_test ${CMAKE_CURRENT_SOURCE_DIR}/matrix.cpp)  
target_link_libraries(matrix_test PRIVATE ${PROJECT_NAME})


add_executable(integral_test ${CMAKE_CURRENT_SOURCE_DIR}/integral.cpp)  
target_link_libraries(integral_test PRIVATE ${PROJECT_NAME})
