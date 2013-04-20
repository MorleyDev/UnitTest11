include_directories (../UnitTest11/Code/include) 

link_directories (${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

FILE(GLOB_RECURSE UnitTest11Tests_SRC *.cpp)
add_executable(UnitTest11_Tests ${UnitTest11Tests_SRC})
target_link_libraries(UnitTest11_Tests UnitTest11)
