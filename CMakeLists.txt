cmake_minimum_required(VERSION 3.0.0)
project(rayHTMLib VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

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