#!/bin/bash

pushd ../
	mkdir Build
	pushd Build
		mkdir GCC
		pushd GCC
			qmake ../../$1/$1.pro -r "CONFIG-=debug"
			make
		
			rc=$?
			if [[ $rc != 0 ]] ; then
				exit $rc
			fi

		popd
	popd
popd
