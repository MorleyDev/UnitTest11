include_directories(../include)

FILE(GLOB_RECURSE UNITTEST11_SRC *.cpp)
add_library(unittest11 ${UNITTEST11_SRC})
