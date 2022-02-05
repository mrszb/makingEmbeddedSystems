cmake_minimum_required(VERSION 3.19)

include_directories(${CPPUTEST_SRC_DIR})
include_directories(${CPPUTESTEXT_SRC_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)

set(SOURCE_FILES
    main.cpp
    test.cpp
    ${PROJECT_SOURCE_DIR}/src/code.cpp
    )

add_executable(countones_ut ${SOURCE_FILES})
target_link_libraries(countones_ut CppUTest CppUTestExt)

add_test(countones_test countones_ut)