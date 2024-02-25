cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 11)
project(Terminal)

include_directories(
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/src
)

aux_source_directory(src SOURCES)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})