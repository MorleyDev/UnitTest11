cmake_minimum_required (VERSION 2.6) 
project (UnitTest11) 

if (MSVC)
		SET(CMAKE_CXX_FLAGS "/MP ${CMAKE_CXX_FLAGS}")
elseif(CMAKE_COMPILER_IS_GNUCXX)
	execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GXX_VERSION)
	if (GXX_VERSION VERSION_GREATER 4.6)
		SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
	else()
		SET(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
	endif()
elseif ("${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ARG1}" MATCHES ".*clang")
	SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

FILE(GLOB_RECURSE UNITTEST11_SRC src/*.cpp)
add_library(unittest11 ${UNITTEST11_SRC})

link_directories (${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

FILE(GLOB_RECURSE UNITTEST11_TESTS_SRC tests/*.cpp)

add_executable(unittest11_tests ${UNITTEST11_TESTS_SRC})
target_link_libraries(unittest11_tests unittest11)
