add_executable(hermite hermite.cpp)
target_link_libraries(hermite ${PROJECT_NAME} python3.10)

add_executable(bessel bessel.cpp)
target_link_libraries(bessel ${PROJECT_NAME} python3.10)

add_executable(quiver quiver.cpp)
target_link_libraries(quiver ${PROJECT_NAME} python3.10)