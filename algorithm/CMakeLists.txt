SET(ROOT_DIR ${CMAKE_SOURCE_DIR})
include_directories(${ROOT_DIR}/util)
include_directories(${ROOT_DIR}/libs)

file(GLOB ALGO_SOURCES "*")
add_library(algorithm ${ALGO_SOURCES})

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
target_link_libraries(algorithm Qt5::Widgets Qt5::Gui)
