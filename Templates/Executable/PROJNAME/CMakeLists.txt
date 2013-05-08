include_directories(Code/include) 

FILE(GLOB_RECURSE PROJNAME_SRC *.cpp)
add_library(PROJNAME_Library SHARED ${PROJNAME_SRC})
add_executable(PROJNAME ${PROJNAME_SRC})
