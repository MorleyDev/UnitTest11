include_directories("Code/include")

FILE(GLOB_RECURSE UnitTest11_SRC *.cpp)
add_library(UnitTest11 ${UnitTest11_SRC})
