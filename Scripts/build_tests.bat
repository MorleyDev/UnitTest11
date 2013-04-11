mkdir ..\Build\Mingw32_Tests\release
xcopy ..\Build\Mingw32\release\*.a ..\Build\Mingw32_Tests\release /y /s
xcopy ..\Build\Mingw32\release\*.dll ..\Build\Mingw32_Tests\release /y /s

pushd ..\Build\Mingw32_Tests
	qmake ..\..\%1_Tests\%1_Tests.pro -r -spec win32-g++ "CONFIG-=debug"
	make
	IF NOT %ERRORLEVEL% EQU 0 EXIT %ERRORLEVEL%
popd
