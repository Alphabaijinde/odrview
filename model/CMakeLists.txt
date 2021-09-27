SET(ROOT_DIR ${CMAKE_SOURCE_DIR})
include_directories(${ROOT_DIR}/libs)
include_directories(${ROOT_DIR}/algorithm)

file(GLOB MODEL_SOURCES "*")
add_library(model ${MODEL_SOURCES})

find_package(Qt5Widgets REQUIRED)
target_link_libraries(model algorithm util Qt5::Widgets)
