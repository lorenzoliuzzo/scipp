add_executable(functions functions.cpp)
target_link_libraries(functions ${PROJECT_NAME})

# add_executable(statistics statistics.cpp)
# target_link_libraries(statistics ${PROJECT_NAME})

add_executable(integrals integrals.cpp)
target_link_libraries(integrals ${PROJECT_NAME})

add_executable(gauss gauss.cpp)
