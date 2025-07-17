#!/bin/bash

module purge
module load compiler/gcc/11.2.0
module load compiler/cmake/3.24.1
module load mathlib/gsl/2.7/gnu

[ -d build ] && rm -rf build
[ -d bin ] && rm -rf bin
[ -d lib ] && rm -rf lib
mkdir -p build bin lib

cmake -DCMAKE_C_COMPILER=gcc \
	  -DCMAKE_CXX_COMPILER=g++ \
	  -DCMAKE_BUILD_TYPE=Release \
	  -DCMAKE_INSTALL_PREFIX=/work1/dtune/hzq \
	  -B build \
	  -S .

(cd build; make -j 8; make install;)