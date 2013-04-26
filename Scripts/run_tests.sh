#!/bin/bash

pushd ../
pushd Build
pushd bin
	./$1_Tests

	rc=$?
	if [[ $rc != 0 ]] ; then
		exit $rc
	fi
popd
popd
popd
