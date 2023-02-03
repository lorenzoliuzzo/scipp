add_executable(measurement_test ${CMAKE_CURRENT_SOURCE_DIR}/measurement.cpp)  
target_link_libraries(measurement_test PRIVATE ${PROJECT_NAME})


add_executable(integral_test ${CMAKE_CURRENT_SOURCE_DIR}/integral.cpp)  
target_link_libraries(integral_test PRIVATE ${PROJECT_NAME})