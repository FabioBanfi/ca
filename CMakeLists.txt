cmake_minimum_required(VERSION 3.1)
project(ca)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/IAnimatedCA1D.cpp
    src/IAnimatedCA2D.cpp
    src/IFirstOrderCA1D.cpp
    src/IFirstOrderCA2D.cpp
    src/ICentralInitCA1D.cpp
    src/ICentralInitCA2D.cpp
    src/ISecondOrderCA1D.cpp
    test/main.cpp)

include_directories(include)

add_executable(ca ${SOURCE_FILES})

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_PROGRAM_OPTIONS_LIBRARY})