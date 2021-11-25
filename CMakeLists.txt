cmake_minimum_required(VERSION 3.11)

project(SolutionName)

find_package(OpenCV REQUIRED)

set(TARGETNAME "ProjectName")

add_executable(${TARGETNAME} ./src/main.cpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${OpenCV_INCLUDE_DIRS} ${OpenCV2_INCLUDE_DIR})
target_link_libraries(${TARGETNAME} ${OpenCV_LIBS})