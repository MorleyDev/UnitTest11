pushd ../
	mkdir %2\lib\
	mkdir %2\include\
	xcopy Build\Mingw32\release\*.dll %2\bin\ /y /s
	xcopy Build\Mingw32\release\*.a %2\lib\ /y /s
	xcopy %1\Code\include\* %2\include\ /y /s
popd

