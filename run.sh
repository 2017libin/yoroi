#!/bin/bash
if [ -d "build" ]; then
  rm -rf build
fi
mkdir build/
cd build/
cmake ../Hash_DRBG/src/
make 
cd ..
gcc yoroi.c T_tables.c -lhash_drbg -L ./build -static -o main
./main
