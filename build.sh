#!/bin/bash

install_dir="${install_dir:-$(pwd)}"

# [ -d ${install_dir} ] && rm -rf ${install_dir}
[ -d build ] && rm -rf build
[ -d bin ] && rm -rf bin
[ -d lib ] && rm -rf lib
mkdir -p ${install_dir} build bin lib

cmake -DCMAKE_C_COMPILER=clang \
	  -DCMAKE_CXX_COMPILER=clang++ \
	  -DCMAKE_BUILD_TYPE=Release \
	  -DCMAKE_INSTALL_PREFIX=${install_dir} \
	  -B build \
	  -S .

(cd build; make -j 8; make install;)