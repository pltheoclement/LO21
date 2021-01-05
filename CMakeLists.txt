cmake_minimum_required(VERSION 3.15)
project(ProjetLO21 CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*.h)

find_package(Qt5Widgets REQUIRED)

add_executable(ProjetLO21 ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(ProjetLO21 PROPERTIES AUTOMOC TRUE)

target_link_libraries(ProjetLO21 Qt5::Widgets)