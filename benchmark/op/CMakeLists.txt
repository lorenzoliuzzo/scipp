add_executable(built_in built_in.cpp)
target_link_libraries(built_in benchmark::benchmark ${PROJECT_NAME})

add_executable(double double.cpp)
target_link_libraries(double benchmark::benchmark ${PROJECT_NAME})

add_executable(measurement measurement.cpp)
target_link_libraries(measurement benchmark::benchmark ${PROJECT_NAME})