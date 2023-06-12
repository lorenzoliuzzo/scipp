add_executable(functions functions.cpp)
target_link_libraries(functions ${PROJECT_NAME})

add_executable(dual dual.cpp)
target_link_libraries(dual ${PROJECT_NAME} python3.10)


# add_executable(statistics statistics.cpp)
# target_link_libraries(statistics ${PROJECT_NAME})

add_executable(integrals integrals.cpp)
target_link_libraries(integrals ${PROJECT_NAME})

add_executable(poly poly.cpp)
target_link_libraries(poly ${PROJECT_NAME})

add_executable(gauss gauss.cpp)
target_link_libraries(gauss ${PROJECT_NAME})

