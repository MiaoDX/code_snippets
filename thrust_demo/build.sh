#!/bin/bash

bd=./build

rm -r $bd
#cmake --log-level=VERBOSE -B$bd -S${PWD} -DThrust_DIR=/home/dongxu/libs/thrust/thrust/cmake/
cmake --log-level=VERBOSE -B$bd -S${PWD} -DThrust_DIR=${PWD}/thrust/thrust/cmake/
cd $bd
make -j4

