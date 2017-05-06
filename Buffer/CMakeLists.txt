## CMakeLists files in this project can
## refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
## to the root binary directory of the project as ${HELLO_BINARY_DIR}.
#cmake_minimum_required(VERSION 3.7)
#project(Sysprog2017_Buffer)
#set(CMAKE_CXX_STANDARD 11)

add_library(BufferLib src/Buffer.cpp)
target_include_directories(BufferLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(BufferTest src/TestBuffer.cpp)
target_link_libraries(BufferTest LINK_PUBLIC BufferLib CatchLib)