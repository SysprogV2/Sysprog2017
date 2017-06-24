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

add_subdirectory (Compab)
add_subdirectory (Automat)
add_subdirectory (Buffer)
add_subdirectory (Symboltable) # abhängig von Scanner (Information)
add_subdirectory (Scanner) # abhängig von Automat, Buffer, Symboltable
add_subdirectory (Parser) # abhängig von Scanner
add_subdirectory (gtest)
include_directories(gtest/include gtest)

add_executable(MainExe main.cpp)
target_link_libraries(MainExe LINK_PUBLIC 
	CompabLib
	ParserLib 
	ScannerLib 
	SymboltableLib 
	BufferLib 
	AutomatLib)

add_executable(MainTest mainTest.cpp)
target_link_libraries(MainTest LINK_PUBLIC 
	CompabLib
	ParserLib 
	ScannerLib 
	SymboltableLib 
	BufferLib 
	AutomatLib 
	gtest 
	gtest_main)
target_compile_definitions(MainTest PRIVATE PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

add_executable(AllTests AllTests.cpp
        Automat/src/TestAutomat.cpp
        Buffer/src/TestBuffer.cpp
        Parser/src/TestParser.cpp
        Scanner/src/TestScanner.cpp
        Symboltable/src/TestSymboltable.cpp
        Symboltable/src/TestStringTab.cpp)
target_link_libraries(AllTests LINK_PUBLIC 
	CompabLib
	ParserLib 
	ScannerLib 
	SymboltableLib 
	BufferLib 
	AutomatLib 
	gtest 
	gtest_main)
target_compile_definitions(AllTests PRIVATE PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")