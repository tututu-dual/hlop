#!/bin/bash

# [ -d build ] && rm -rf build
# [ -d bin ] && rm -rf bin
# [ -d lib ] && rm -rf lib
# [ -d ../install ] && rm -rf ../install
# mkdir -p build bin lib ../install

(cd build; make clean;)

cmake -DCMAKE_C_COMPILER=clang \
	  -DCMAKE_CXX_COMPILER=clang++ \
	  -DCMAKE_BUILD_TYPE=Release \
	  -DCMAKE_INSTALL_PREFIX=$(pwd)/../install \
	  -B build \
	  -S .

(cd build; make -j 8; make install;)