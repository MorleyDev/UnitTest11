#!/bin/bash

pushd ../Build
	cmake ../ -G"Unix Makefiles" -DCMAKE_MAKE_PROGRAM=make -DCMAKE_BUILD_TYPE=Release
	make
popd

./run_tests.sh $1
