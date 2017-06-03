## CMakeLists files in this project can
## refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
## to the root binary directory of the project as ${HELLO_BINARY_DIR}.
#cmake_minimum_required(VERSION 3.7)
#project(Sysprog2017_Symboltable)
#set(CMAKE_CXX_STANDARD 11)

add_library(SymboltableLib src/Symboltable.cpp src/StringTab.cpp src/SymtabEntry.cpp)
target_include_directories(SymboltableLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(SymboltableTest src/TestSymboltable.cpp)
add_executable(StringtableTest src/TestStringTab.cpp)

target_link_libraries(SymboltableTest LINK_PUBLIC SymboltableLib ScannerLib CatchLib)
target_link_libraries(StringtableTest LINK_PUBLIC SymboltableLib CatchLib)
target_compile_definitions(SymboltableTest PRIVATE CMAKE_SOURCE_DIR=${PROJECT_SOURCE_DIR})
target_compile_definitions(StringtableTest PRIVATE CMAKE_SOURCE_DIR=${PROJECT_SOURCE_DIR})