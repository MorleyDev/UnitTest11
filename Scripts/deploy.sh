#!/bin/bash

pushd ../
	mkdir $2
	pushd $2
		mkdir lib
		mkdir include
	popd

	#cp Build/bin/* $2/bin/ -f -r
	cp Build/lib/* $2/lib/ -f -r
	cp $1/Code/include/* $2/include/ -f -r
popd
