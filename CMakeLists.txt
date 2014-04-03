cmake_minimum_required (VERSION 2.6) 
project(UNITTEST11 CXX) 

option(ENABLE_GCOV "Adds the --coverage flag to compilation" OFF)

if (ENABLE_GCOV)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
	set(CMAKE_EXE_LINKER_FLAGS="${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

if (MSVC)
	set(CMAKE_CXX_FLAGS "/MP ${CMAKE_CXX_FLAGS}")

elseif(CMAKE_COMPILER_IS_GNUCXX)
	execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GXX_VERSION)
	if (GXX_VERSION VERSION_LESS 4.8)
		if (GXX_VERSION VERSION_LESS 4.7)
			set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
		else()
			set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
		endif()
	else()
		set (CMAKE_CXX_FLAGS "-std=c++1y ${CMAKE_CXX_FLAGS}")
	endif()

elseif ("${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ARG1}" MATCHES ".*clang")
	set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()



add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
