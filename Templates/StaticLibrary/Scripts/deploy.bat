pushd ..\
	mkdir %2\lib\
	mkdir %2\include\
	REM xcopy Build\bin\* %2\bin\ /y /s
	xcopy Build\lib\* %2\lib\ /y /s
	xcopy %1\Code\include\* %2\include\ /y /s
popd

