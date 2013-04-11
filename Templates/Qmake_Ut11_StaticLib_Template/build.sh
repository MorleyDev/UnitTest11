#!/bin/bash

pushd Scripts
	./clean.sh
	./build.sh $PROJNAME
popd

