cmake_minimum_required(VERSION 3.1)
project(ca)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    include/AnimatedCA.hpp
    include/AnimatedCA1D.h
    include/AnimatedCA2D.h
    include/CA.h
    include/CellularAutomaton.h
    include/FirstOrderCA1D.h
    include/FirstOrderCA2D.h
    src/AnimatedCA1D.cpp
    src/AnimatedCA2D.cpp
    src/FirstOrderCA1D.cpp
    src/FirstOrderCA2D.cpp
    test/BriansBrain.hpp
    test/LangtonsAnt.hpp
    test/Life.hpp
    test/main.cpp
    test/Rule30.hpp)

add_executable(ca ${SOURCE_FILES})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})