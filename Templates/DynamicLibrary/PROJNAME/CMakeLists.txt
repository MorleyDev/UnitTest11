include_directories(Code/include $ENV{GCC_PLS}/include) 

FILE(GLOB_RECURSE PROJNAME_SRC *.cpp)
add_library(PROJNAME SHARED ${PROJNAME_SRC})
