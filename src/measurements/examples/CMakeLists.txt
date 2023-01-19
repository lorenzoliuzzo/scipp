add_executable(measurement_ex ${CMAKE_CURRENT_SOURCE_DIR}/measurement.cpp)  
target_link_libraries(measurement_ex PRIVATE ${PROJECT_NAME})

add_executable(umeasurement_ex ${CMAKE_CURRENT_SOURCE_DIR}/umeasurement.cpp)  
target_link_libraries(umeasurement_ex PRIVATE ${PROJECT_NAME})

