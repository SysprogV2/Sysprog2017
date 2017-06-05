## CMakeLists files in this project can
## refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
## to the root binary directory of the project as ${HELLO_BINARY_DIR}.
#cmake_minimum_required(VERSION 3.7)
#project(Sysprog2017_Automat)
#set(CMAKE_CXX_STANDARD 11)

add_library(AutomatLib src/Automat.cpp src/Stack.cpp src/Syntax.cpp)
target_include_directories(AutomatLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(../gtest/include gtest)

add_executable(AutomatTest src/TestAutomat.cpp)
target_link_libraries(AutomatTest LINK_PUBLIC AutomatLib gtest gtest_main)

target_compile_definitions(AutomatTest PRIVATE PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")