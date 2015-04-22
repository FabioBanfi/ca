cmake_minimum_required(VERSION 3.1)
project(ca)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/AnimatedCA1D.cpp
    src/AnimatedCA2D.cpp
    src/FirstOrderCA1D.cpp
    src/FirstOrderCA2D.cpp
    test/main.cpp)

include_directories(include)

add_executable(ca ${SOURCE_FILES})

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

find_package(Boost REQUIRED COMPONENTS program_options regex)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_REGEX_LIBRARY})