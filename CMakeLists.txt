cmake_minimum_required(VERSION 3.10)
project(odrViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(algorithm/)
add_subdirectory(controller/)
add_subdirectory(model/)
add_subdirectory(util/)
add_subdirectory(views/)
#add_subdirectory(opendrive)
