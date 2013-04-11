#!/bin/bash

pushd ../Build/GCC_Tests
	./$1_Tests

	rc=$?
	if [[ $rc != 0 ]] ; then
		exit $rc
	fi
popd

