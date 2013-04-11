#!/bin/bash

pushd ../
	mkdir $2
	pushd $2
		mkdir lib
		mkdir include
	popd
	
	cp Build/GCC/*.a $2/lib/ -f -r
	cp Build/GCC/*.so $2/bin/ -f -r
	cp $1/Code/include/* $2/include/ -f -r
popd

