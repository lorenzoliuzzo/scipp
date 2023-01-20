add_executable(hello_world ${CMAKE_CURRENT_SOURCE_DIR}/hello_world.cpp)  
target_link_libraries(hello_world PRIVATE ${PROJECT_NAME})

add_executable(measurement_test ${CMAKE_CURRENT_SOURCE_DIR}/measurement.cpp)  
target_link_libraries(measurement_test PRIVATE ${PROJECT_NAME})

add_executable(umeasurement_test ${CMAKE_CURRENT_SOURCE_DIR}/umeasurement.cpp)  
target_link_libraries(umeasurement_test PRIVATE ${PROJECT_NAME})

add_executable(sizes ${CMAKE_CURRENT_SOURCE_DIR}/sizes.cpp)  
target_link_libraries(sizes PRIVATE ${PROJECT_NAME})

add_executable(bench_measurements ${CMAKE_CURRENT_SOURCE_DIR}/bench/bench.cpp)  
target_link_libraries(bench_measurements PRIVATE ${PROJECT_NAME})
