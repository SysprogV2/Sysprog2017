cmake_minimum_required(VERSION 3.2.2)
project(Symboltable)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(LIBRARIES Compatibility)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS includes/*.h)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})
add_executable(run${PROJECT_NAME}Test src/Test${PROJECT_NAME}.cpp)

foreach(LIBNAME ${LIBRARIES})
    find_library(${LIBNAME}_LOCATION ${LIBNAME} ../)
    target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${${LIBNAME}_LOCATION})
endforeach()

target_link_libraries(run${PROJECT_NAME}Test ${PROJECT_NAME})