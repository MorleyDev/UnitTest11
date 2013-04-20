#!/bin/bash

pushd ../Build/bin
	./$1_Tests

	rc=$?
	if [[ $rc != 0 ]] ; then
		exit $rc
	fi
	
	pushd Scripts
		./run_tests.sh UnitTest11
	popd
popd

