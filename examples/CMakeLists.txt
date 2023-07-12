add_executable(HelloWorld HelloWorld.cpp)
target_link_libraries(HelloWorld ${PROJECT_NAME} python3.10)

add_executable(measurements measurements.cpp)
target_link_libraries(measurements ${PROJECT_NAME} python3.10)
