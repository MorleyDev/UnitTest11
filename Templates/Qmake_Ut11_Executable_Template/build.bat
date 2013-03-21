@echo off
pushd Scripts
	call clean.bat
	call build.bat $PROJNAME

	call clean.bat
	call build_exe.bat $PROJNAME
popd
