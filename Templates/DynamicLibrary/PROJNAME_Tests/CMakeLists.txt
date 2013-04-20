include_directories (../PROJNAME/Code/include $ENV{GCC_PLS}/include) 

link_directories (${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} $ENV{GCC_PLS}/lib)

FILE(GLOB_RECURSE PROJNAMETests_SRC *.cpp)
add_executable(PROJNAME_Tests ${PROJNAMETests_SRC})
target_link_libraries(PROJNAME_Tests PROJNAME UnitTest11)
