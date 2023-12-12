cmake_minimum_required(VERSION 3.0)

project("CS102-Final-Project")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory("vendor")
add_subdirectory("src")

FILE(COPY ./res DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})