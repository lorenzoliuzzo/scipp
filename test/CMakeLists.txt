add_executable(measurement_test ${CMAKE_CURRENT_SOURCE_DIR}/meas.cpp)
target_link_libraries(measurement_test PRIVATE ${PROJECT_NAME})

add_executable(geometry_test ${CMAKE_CURRENT_SOURCE_DIR}/vec.cpp)
target_link_libraries(geometry_test PRIVATE ${PROJECT_NAME})

add_executable(physics_test ${CMAKE_CURRENT_SOURCE_DIR}/position.cpp)
target_link_libraries(physics_test PRIVATE ${PROJECT_NAME})

add_executable(bench_test ${CMAKE_CURRENT_SOURCE_DIR}/bench/bench.cpp)
target_link_libraries(bench_test PRIVATE ${PROJECT_NAME})

add_executable(bench_test_2 ${CMAKE_CURRENT_SOURCE_DIR}/bench/bench2.cpp)
target_link_libraries(bench_test_2 PRIVATE ${PROJECT_NAME})

add_executable(timer_over ${CMAKE_CURRENT_SOURCE_DIR}/bench/timer_overhead.cpp)
target_link_libraries(timer_over PRIVATE ${PROJECT_NAME})
