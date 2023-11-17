#!/bin/bash

ROOT_DIR="$(pwd)"

cd example/

# Cleanup previous artifacts
rm -rf build/

# Build example
mkdir build
cd build
cmake ..
make -j

# Execute example
echo "== Executing example =="
./example
