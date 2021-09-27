SET(ROOT_DIR ${CMAKE_SOURCE_DIR})
include_directories(${ROOT_DIR}/libs)

file(GLOB UTIL_SOURCES "*")
add_library(util ${UTIL_SOURCES})

target_link_libraries(util model)



