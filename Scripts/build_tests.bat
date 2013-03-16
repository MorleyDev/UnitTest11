pushd ..\Build\Mingw32
	qmake ..\..\%1_Tests\%1_Tests.pro -r -spec win32-g++ "CONFIG-=debug"
	make
	IF NOT %ERRORLEVEL% EQU 0 EXIT %ERRORLEVEL%
popd
