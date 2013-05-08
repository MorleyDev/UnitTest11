include_directories (${CMAKE_SOURCE_DIR}/PROJNAME/Code/include) 

link_directories (${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

FILE(GLOB_RECURSE PROJNAMETests_SRC *.cpp)
add_executable(PROJNAME_Tests ${PROJNAMETests_SRC})
target_link_libraries(PROJNAME_Tests PROJNAME UnitTest11)
