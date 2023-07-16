# add_executable(HelloWorld HelloWorld.cpp)
# target_link_libraries(HelloWorld ${PROJECT_NAME} python3.10)

# add_executable(measurements measurements.cpp)
# target_link_libraries(measurements ${PROJECT_NAME} python3.10)

# add_executable(integral integral.cpp)
# target_link_libraries(integral ${PROJECT_NAME} python3.10)

# add_executable(autodiff autodiff.cpp)
# target_link_libraries(autodiff ${PROJECT_NAME} python3.10)

add_executable(derivative derivative.cpp)
target_link_libraries(derivative ${PROJECT_NAME} python3.10)