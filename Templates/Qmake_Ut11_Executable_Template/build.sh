@echo off
pushd Scripts
	./clean.sh
	./build.sh $PROJNAME

	./clean.sh
	./build_exe.sh $PROJNAME
popd
