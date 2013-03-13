@echo off
pushd ..\
mkdir Build\Mingw32
pushd Build\Mingw32

qmake ..\..\%1\%1.pro -r -spec win32-g++ "CONFIG-=debug"
make
IF NOT %ERRORLEVEL% EQU 0 EXIT %ERRORLEVEL%

qmake ..\..\%1_Tests\%1_Tests.pro -r -spec win32-g++ "CONFIG-=debug"
make
IF NOT %ERRORLEVEL% EQU 0 EXIT %ERRORLEVEL%

pushd release
UnitTest11_Tests.exe
IF NOT %ERRORLEVEL% EQU 0 EXIT %ERRORLEVEL%
popd

popd
popd