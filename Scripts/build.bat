mkdir ..\Build
pushd ..\Build
	call cmake ..\ -G"MinGW Makefiles" -DCMAKE_MAKE_PROGRAM=make -DCMAKE_BUILD_TYPE=Release
	IF NOT %ERRORLEVEL% EQU 0 EXIT %ERRORLEVEL%
	
	make
	IF NOT %ERRORLEVEL% EQU 0 EXIT %ERRORLEVEL%
popd

call run_tests.bat UnitTest11
