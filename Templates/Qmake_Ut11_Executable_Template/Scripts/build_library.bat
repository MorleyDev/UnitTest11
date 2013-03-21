mkdir ..\Build\Mingw32

pushd ..\Build\Mingw32
	qmake ..\..\%1\%1.pro -r -spec win32-g++ "CONFIG-=debug"
	make
	IF NOT %ERRORLEVEL% EQU 0 EXIT %ERRORLEVEL%
popd
