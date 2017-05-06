# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required(VERSION 3.7)
project(Sysprog2017)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory (CatchLib)
add_subdirectory (Automat)
add_subdirectory (Buffer)
add_subdirectory (Symboltable) # abhängig von Scanner (Information)
add_subdirectory (Scanner) # abhängig von Automat, Buffer, Symboltable
add_subdirectory (Parser) # abhängig von Scanner

add_executable(MainTest main.cpp)
target_link_libraries(MainTest LINK_PUBLIC ParserLib ScannerLib SymboltableLib BufferLib AutomatLib CatchLib)