cmake_minimum_required(VERSION 3.0.0)
project(rayHTMLib VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

option(BUILD_TESTS "Build tests" OFF)

# Add raylib
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git 
    GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

# Add the source files
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

# Declare executable
add_library(rayHTMLib ${SOURCES})
target_include_directories(rayHTMLib PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")
target_link_libraries(rayHTMLib PRIVATE raylib)

set_target_properties(rayHTMLib PROPERTIES VERSION ${PROJECT_VERSION})

# Install
install(TARGETS rayHTMLib DESTINATION lib)
install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/include/" DESTINATION include)

if(${BUILD_TESTS})
    MESSAGE(STATUS "Building tests")
    # Add tests
    enable_testing()
    file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_LIST_DIR}/tests/*.cpp")
    add_executable(tests ${TEST_SOURCES} ${SOURCES})

    target_include_directories(tests PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")
    target_link_libraries(tests PRIVATE raylib)

    # Copy test assets
    add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/tests/assets/ ${CMAKE_CURRENT_BINARY_DIR}/Debug/assets/ DEPENDS ${CMAKE_CURRENT_LIST_DIR}/tests/assets/)
    add_dependencies(tests copy_assets)


    add_test(NAME tests COMMAND tests)
endif()
