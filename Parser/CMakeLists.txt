## CMakeLists files in this project can
## refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
## to the root binary directory of the project as ${HELLO_BINARY_DIR}.
#cmake_minimum_required(VERSION 3.7)
#project(Sysprog2017_Parser)
#set(CMAKE_CXX_STANDARD 11)

add_library(ParserLib src/Parser.cpp src/ParseTree.cpp src/TokenSequence.cpp src/Errors.cpp)
target_include_directories(ParserLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ParserTest src/TestParser.cpp)
target_link_libraries(ParserTest LINK_PUBLIC
        ParserLib
        ScannerLib
        SymboltableLib
        BufferLib
        AutomatLib
        CatchLib)
