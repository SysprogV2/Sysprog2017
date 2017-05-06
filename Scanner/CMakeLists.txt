## CMakeLists files in this project can
## refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
## to the root binary directory of the project as ${HELLO_BINARY_DIR}.
#cmake_minimum_required(VERSION 3.7)
#project(Sysprog2017_Scanner)
#set(CMAKE_CXX_STANDARD 11)

add_library(ScannerLib src/Scanner.cpp src/Information.cpp src/Token.cpp)
target_include_directories(ScannerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ScannerTest src/TestScanner.cpp)
target_link_libraries(ScannerTest LINK_PUBLIC ScannerLib AutomatLib BufferLib SymboltableLib CatchLib)