# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
#cmake_minimum_required(VERSION 3.7)#too high for travis!?
cmake_minimum_required(VERSION 3.2.3)
project(Sysprog2017)

set(CMAKE_CXX_STANDARD 11)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory (CatchLib)
add_subdirectory (Automat)
add_subdirectory (Buffer)
add_subdirectory (Symboltable) # abhängig von Scanner (Information)
add_subdirectory (Scanner) # abhängig von Automat, Buffer, Symboltable

add_executable(MainTest main.cpp)
target_link_libraries(MainTest LINK_PUBLIC ScannerLib SymboltableLib BufferLib AutomatLib CatchLib)