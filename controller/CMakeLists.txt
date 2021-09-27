SET(ROOT_DIR ${CMAKE_SOURCE_DIR})
include_directories(${ROOT_DIR}/model)
include_directories(${ROOT_DIR}/libs)

file(GLOB CONTROLLER_SOURCES "*")
add_library(controller ${CONTROLLER_SOURCES})

target_link_libraries(controller model)