#!/bin/bash

./build_library.sh $1
rc=$?
if [[ $rc != 0 ]] ; then
	exit $rc
fi

./build_tests.sh $1
rc=$?
if [[ $rc != 0 ]] ; then
	exit $rc
fi

./run_tests.sh $1
rc=$?
if [[ $rc != 0 ]] ; then
	exit $rc
fi

