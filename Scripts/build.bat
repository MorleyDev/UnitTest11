call clean.bat

call build_library.bat %1%
IF NOT %ERRORLEVEL% EQU 0 EXIT %ERRORLEVEL%

call build_tests.bat %1%
IF NOT %ERRORLEVEL% EQU 0 EXIT %ERRORLEVEL%

call run_tests.bat %1%
IF NOT %ERRORLEVEL% EQU 0 EXIT %ERRORLEVEL%
