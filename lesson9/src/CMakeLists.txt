cmake_minimum_required(VERSION 3.19)

project(emb9_code)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.cpp code.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(emb9_code ${SOURCE_FILES})

# link against math library.
#target_link_libraries(cpputest_example_pythagorean m)
install(TARGETS emb9_code DESTINATION bin)