#!/bin/bash

ROOT_DIR="$(pwd)"

# Cleanup previous artifacts
rm -rf yaml-cpp*

# Fetch new yaml-cpp release
curl -L -o yaml-cpp.tar.gz https://github.com/jbeder/yaml-cpp/archive/refs/tags/0.8.0.tar.gz

# Extract yaml-cpp
tar xfzv yaml-cpp.tar.gz
cd yaml-cpp-0.8.0/

# Build yaml-cpp
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=${ROOT_DIR}/yaml-cpp-install ..
make -j
make install
