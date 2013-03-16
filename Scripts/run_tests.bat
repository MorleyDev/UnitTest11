pushd ..\Build\Mingw32\release
	%1_Tests.exe
	IF NOT %ERRORLEVEL% EQU 0 EXIT %ERRORLEVEL%
popd

