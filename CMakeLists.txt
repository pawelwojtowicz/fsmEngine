cmake_minimum_required(VERSION 3.10)
project( fsmEngine VERSION 1.0.1 DESCRIPTION "Open Street Maps toolkit")

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )

add_subdirectory(src)
add_subdirectory(test)