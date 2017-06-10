## CMakeLists files in this project can
## refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
## to the root binary directory of the project as ${HELLO_BINARY_DIR}.
#cmake_minimum_required(VERSION 3.7)
#project(Sysprog2017_Parser)
#set(CMAKE_CXX_STANDARD 11)

add_library(ParserLib src/Parser.cpp src/ParseTree.cpp src/TokenSequence.cpp src/Errors.cpp)
target_include_directories(ParserLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


include_directories(../gtest/include gtest)

add_executable(ParserExe src/ParserExe.cpp)
target_link_libraries(ParserExe LINK_PUBLIC
        CompabLib
        ParserLib
        ScannerLib
        SymboltableLib
        BufferLib
        AutomatLib
        )


add_executable(ParserTest src/TestParser.cpp)
target_link_libraries(ParserTest LINK_PUBLIC
        CompabLib
        ParserLib
        ScannerLib
        SymboltableLib
        BufferLib
        AutomatLib
        gtest gtest_main)
target_compile_definitions(ParserTest PRIVATE PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")