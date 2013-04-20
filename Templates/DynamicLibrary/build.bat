@echo off

pushd Scripts
	call clean.bat
	call build.bat PROJNAME
popd
