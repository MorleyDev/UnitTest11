mkdir ..\Build
pushd ..\Build
	cmake ..\ -G"MinGW Makefiles" -DCMAKE_MAKE_PROGRAM=make -DCMAKE_BUILD_TYPE=Release
	IF NOT %ERRORLEVEL% EQU 0 EXIT %ERRORLEVEL%
	make
popd

call run_tests.bat %1
