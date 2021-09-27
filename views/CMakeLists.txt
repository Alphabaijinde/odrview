set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH $ENV{Qt})

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)


SET(ROOT_DIR ${CMAKE_SOURCE_DIR})

include_directories(${ROOT_DIR}/libs)
include_directories(${ROOT_DIR}/algorithm)
include_directories(${ROOT_DIR}/model)
include_directories(${ROOT_DIR}/controller)
include_directories(${RooT_DIR}/util)

file(GLOB VIEWS_SOURCES "*")
add_library(view ${VIEWS_SOURCES})

link_directories(${ROOT_DIR}/libs)
target_link_libraries(view controller libxodr.so Qt5::Core Qt5::Gui Qt5::Widgets)


add_executable(${PROJECT_NAME} common.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/views)
target_link_libraries(${PROJECT_NAME} algorithm controller view model util)
