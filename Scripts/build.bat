mkdir ..\Build
pushd ..\Build
	cmake ..\ -G"MinGW Makefiles" -DCMAKE_MAKE_PROGRAM=make -DCMAKE_BUILD_TYPE=Release
	make
popd

call run_tests.bat %1
