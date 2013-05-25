@echo off

pushd Scripts
	call clean.bat
	call build.bat UnitTest11
popd
