add_executable(dot_prod dot_prod.cpp)
target_link_libraries(dot_prod ${PROJECT_NAME} python3.10)

add_executable(meas_prod meas_prod.cpp)
target_link_libraries(meas_prod ${PROJECT_NAME} python3.10)

