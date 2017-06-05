[![Build Status](https://travis-ci.org/SysprogV2/Sysprog2017.svg?branch=master)](https://travis-ci.org/SysprogV2/Sysprog2017)

# SysProg2017
This is a project for university - a compiler for a rather simple custom programming language. Nothing too special.

## Build
### Oldstyle Make without tests
````
  make -f _makefile all
````
### CMake
````
  mkdir build
  cd build
  cmake ..
  make
````

## Run tests
````
  ./AllTests
  ./MainTest
  ./Automat/AutomatTest
  ./Buffer/BufferTest
  ./Parser/ParserTest
  ./Scanner/ScannerTest
  ./Symboltable/SymboltableTest
  ./Symboltable/StringtableTest
````

## Run executables
````
  ./MainExe <inputfile>
  ./Scanner/ScannerExe <inputfile> <outputfile>
  ./Parser/ParserExe <inputfile>
````
