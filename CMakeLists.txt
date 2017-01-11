cmake_minimum_required(VERSION 3.2.2)
project(SysProg2015)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(DEPENDENCIES Automat Buffer Scanner Symboltable Parser)

add_executable(run${PROJECT_NAME} main.cpp)

foreach(DEPENDENCY ${DEPENDENCIES})
    find_library(${DEPENDENCY}_LOCATION ${DEPENDENCY} PATHS ${DEPENDENCY})
    target_link_libraries(run${PROJECT_NAME} LINK_PUBLIC ${${DEPENDENCY}_LOCATION})
endforeach()