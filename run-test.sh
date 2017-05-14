#!/bin/bash
# rsync script
cd Automat
make
cd ..

cd Buffer
make
cd ..

cd Symboltable
make
cd ..

./"Automat/debug/AutomatTest"
./"Symboltable/debug/SymboltableTest"
./"Buffer/debug/BufferTest" test/scanner0.txt
