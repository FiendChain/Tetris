cmake_minimum_required(VERSION 3.11)

set(CMAKE_C_COMPILER C:/MinGW/bin/gcc.exe)
set(CMAKE_CXX_COMPILER C:/MinGW/bin/g++.exe)

project(Tetris)

set(SRC_FILES_DIR ${CMAKE_SOURCE_DIR}/src)
set(SFML_DIR ${CMAKE_SOURCE_DIR}/SFML-2.5.0)

set(SRC_FILES 
    ${SRC_FILES_DIR}/main.cpp
    ${SRC_FILES_DIR}/App.cpp
    ${SRC_FILES_DIR}/BlockGrid.cpp
    ${SRC_FILES_DIR}/Tetrimino/Tetrimino.cpp
    ${SRC_FILES_DIR}/Tetrimino/StandardBlocks.cpp)

include_directories(${SRC_FILES_DIR})
include_directories(${SFML_DIR}/include)

# sfml-graphics
macro(add_sfml_library name)
    add_library(${name} STATIC IMPORTED)
    set_target_properties(${name} PROPERTIES
        IMPORTED_LOCATION "${SFML_DIR}/lib/lib${name}.a"
        INTERFACE_INCLUDE_DIRECTORIES "${SFML_DIR}/include/SFML"
        INTERFACE_COMPILE_DEFINITIONS SFML_STATIC
    )
endmacro()

add_sfml_library(sfml-graphics-s)
add_sfml_library(sfml-window-s)
add_sfml_library(sfml-system-s)
add_sfml_library(freetype)
add_sfml_library(jpeg)
set(EXTRA_LIBS ${EXTRA_LIBS}
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
    winmm
    gdi32
    opengl32
    freetype
    jpeg)

add_executable(tetris ${SRC_FILES})
target_compile_definitions(tetris PUBLIC SFML_STATIC)
target_compile_options(tetris PUBLIC -Werror=return-type)
target_link_libraries(tetris ${EXTRA_LIBS})

install(TARGETS tetris DESTINATION bin)
