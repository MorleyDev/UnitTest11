#!/bin/bash

pushd ../
	mkdir Build
	pushd Build
		mkdir GCC_Tests
		pushd GCC_Tests
			mkdir release
		popd
	popd
popd

mkdir ../Build/GCC_Tests/release
cp ../Build/GCC/*.a ../Build/GCC_Tests/release -f
cp ../Build/GCC/*.so ../Build/GCC_Tests/release -f

pushd ../Build/GCC_Tests
	qmake ../../$1_Tests/$1_Tests.pro -r "CONFIG-=debug"
	make

	rc=$?
	if [[ $rc != 0 ]] ; then
		exit $rc
	fi
popd
